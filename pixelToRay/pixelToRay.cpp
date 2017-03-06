#include <iomanip>
#include <math.h>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <GL/gl.h>
#include <boost/function.hpp>
#include <boost/format.hpp>

#include <libv/geometry/camera_model.hpp>
#include <libv/geometry/plane_equation.hpp>
#include <libv/geometry/pose.hpp>
#include <libv/geometry/rotation.hpp>
#include <libv/graphic/viewer_context.hpp>

#include <libv/charlib/graphic/banners.hpp>
#include <libv/charlib/graphic/draw.hpp>
#include <libv/charlib/lytroGeometry/lytroProjection.hpp>
#include <libv/charlib/lytroGeometry/lytroPose.hpp>
#include <libv/charlib/tools/tools.hpp>

/* 
	Brief: This is the plenoptic_camera simulation version 2
	Using pixel Ray method 
*/

int main()
{
	niHao();

/////////////////////////////////////////////////////////////Loading file/////////////////////////////////////////////////////
	std::cout << "- Loading file -" << std::endl;

	//Loading configuration files
	// const std::string configPath = argv[1];
	const std::string configPath = "../../../config";
	const std::string fileName = "/config.ini";
	Camera_config camera_config;
	v::load(configPath + fileName, camera_config);

	laPub();

/////////////////////////////////////////////////////////////Hypotheses & tools/////////////////////////////////////////////////////
	std::cout << "- Hypotheses & tools -" << std::endl;

	float lensPitch = camera_config.lenslet_grid().lensPitch();
	// float microLensDiameter = camera_config.microLens().lensDiameter();
	// float mainLensDiameter = camera_config.mainLens().lensDiameter();
	float microLensDiameter = 10.0; //in millimeter
	float mainLensDiameter = 30.0; //in millimeter

	auto degToRad = [](auto angle){return(angle*M_PI/180.0); };
	double sin60 = std::sin(degToRad(60));

	//Define projection matrix of each microlenses
	double fx,fy,u0,v0,xi;
	fx = fy = 100.0; //in millimeter
	u0 = v0 = 5; //in millimeter //correspond to the microlensPose(0,0)/2
	xi = 0.0;
	v::UnifiedCameraModel microProjMat(fx,fy,u0,v0,xi);

	//thinLens projection Matrix
	double focalLength = 25;
	Eigen::MatrixXd thinLensProjMat (4,4);
	thinLensProjMat<<	focalLength,0,0,0,
						0,focalLength,0,0,
						0,0,focalLength,0,
						0,0,1,0;

	//Determine the t coef for a parametric line equation (depending on the slope and originPoint) the intersec the plane
	auto computeT = [](const Eigen::Vector4d& plane, const Eigen::Vector3d& slope, const Eigen::Vector3d& originPoint){
		double t;
		t = -(plane(0)*originPoint(0) + plane(1)*originPoint(1) + plane(2)*originPoint(2) + plane(3));
		t /= (plane(0)*slope(0) + plane(1)*slope(1) + plane(2)*slope(2));
		return t;
	};

	//Determine a 3D point based on the parametric equation of a line and the argument t
	auto pointOfLine = [](const double t, const Eigen::Vector3d& slope, const Eigen::Vector3d& originPoint){
		Eigen::Vector3d p3d;
		p3d.x() = slope.x() * t + originPoint.x();
		p3d.y() = slope.y() * t + originPoint.y();
		p3d.z() = slope.z() * t + originPoint.z();
		return p3d;
	};

	laPub();

/////////////////////////////////////////////////////////////Defining elements/////////////////////////////////////////////////////
	std::cout << "- Defining elements -" << std::endl;

	//Camera - WORLD 
	LytroCamera lytro(1,1);
	lytro.pose.translation() = {0,0,-200}; //-100 on z axis
	v::apply_rotation(lytro.pose.rotation(),{0,0,0});
	// std::cout << boost::format("Camera position - WORLD : %1%")%lytro.pose.translation().transpose() << std::endl;

	//ThinLens position - CAMERA
	lytro.thinLens.pose.translation() = {0,0,0};
	v::apply_rotation(lytro.thinLens.pose.rotation(),{0,0,0});
	// std::cout << boost::format("ThinLens position - CAMERA : %1%")%lytro.thinLens.pose.translation().transpose() << std::endl;

	//Microlenses position - CAMERA
	double xLens, yLens, zLens;
	for(unsigned int row=0 ; row<lytro.height ; ++row)
		for(unsigned int col=0 ; col<lytro.width ; ++col)
		{	
			// //TODO: take rotations into account
			// if(row%2 == 0)
			// {
			// 	//Coord are centered in front of the thinLens
			// 	// xLens = (col + 0.5)*lensPitch + 1 - microLensDiameter*lytro.width/2;
			// 	// yLens = row*lensPitch*sin60		  - microLensDiameter*(lytro.height-1)/2;
				
			// 	//Coord are not centered in front of the thinLens
			// 	xLens = (col + 0.5)*lensPitch + 1 - xValtest;
			// 	yLens = row*lensPitch*sin60 - yValtest;
			// }
			// else
			// {	
			// 	//Coord are centered in front of the thinLens
			// 	// xLens = col*lensPitch + 1	 - microLensDiameter*lytro.width/2;
			// 	// yLens = row*lensPitch*sin60	 - microLensDiameter*(lytro.height-1)/2;

			// 	//Coord are not centered in front of the thinLens
			// 	xLens = col*lensPitch + 1 - xValtest;
			// 	yLens = row*lensPitch*sin60 - yValtest;
			// }


			xLens = 0;
			yLens = 0;
			zLens = lytro.thinLens.pose.translation().z() - 70;


			lytro.microLens[row*lytro.width+col].pose.translation() = {xLens,yLens,zLens};
			v::apply_rotation(lytro.microLens[row*lytro.width+col].pose.rotation(),{0,0,0});
			// std::cout << boost::format("Microlens position (%1%,%2%) - CAMERA : %3%")%row%col%microLensPoseInCam(lytro,row,col).translation().transpose() << std::endl;
		}

	laPub();

/////////////////////////////////////////////////////////////Ray tracing (using libv)////////////////////////////////////////////////////////////////////////////////
	std::cout << "- Ray tracing -" << std::endl;

	/////////////////////////////////////////////////////////////Step 1.0: Passing through the microlenses (using libv)////////////////////////////////////////////////////////////////////////////////
	std::cout << ". Step 1.0: Passing through the microlenses (using libv) -" << std::endl;

	//Define a pixelRay: block(0-2) contains a pixel, block(3-5) contains the corresponding ray
	//Here is just an example: 100 stands for the number of point around the microlens
	AlignedVector<Eigen::VectorXd> pixelRay (10000, Eigen::VectorXd (5) );	
	double pixNumber = 4; //6000 is out

	//Configure a square pixel grid (here 100x100)
	double gridSize = std::sqrt(pixelRay.size());
	for(unsigned int row=0 ; row<gridSize ; ++row)
		for(unsigned int col=0 ; col<gridSize ; ++col)
		{	
			pixelRay[row*gridSize+col].x() = col;
			pixelRay[row*gridSize+col].y() = row;
		}

	for(unsigned int pt=0 ; pt<pixelRay.size() ; ++pt)
	{
		Eigen::Vector2d aPixel;
		Eigen::Vector3d aRay;

		//The exact border of the lens
		// Eigen::Vector3d microlensCenter = microLensPoseInWorld(lytro,0,0).translation();	//test for only one microlens
		// float theta = 2 * M_PI * pt / pixelRay.size();
		// aPixel.x() = microlensCenter.x() + (microLensDiameter/2) * cos(theta);
		// aPixel.y() = microlensCenter.y() + (microLensDiameter/2) * sin(theta);

		aPixel = pixelRay[pt].head(2);

		microProjMat.raytrace(aPixel,aRay);
		
		//change aRay from MICROLENS to WORLD coordinate system 
		aRay = v::from_coordinate_system_of(microLensPoseInWorld(lytro,0,0),aRay);
	
		pixelRay[pt].tail(3) =  aRay;
	}

	// std::cout << boost::format("microLensPoseInWorld(lytro,0,0).translation() = %1%")%microLensPoseInWorld(lytro,0,0).translation().transpose() << std::endl;
	// std::cout << boost::format("aPixel[6] = %1%")%pixelRay[pixNumber].head(2).transpose() << std::endl;
	// std::cout << boost::format("aRay[6] = %1%")%pixelRay[pixNumber].tail(3).transpose() << std::endl;

	/////////////////////////////////////////////////////////////Step 1.2: Passing through the thinLens////////////////////////////////////////////////////////////////////////////////
	std::cout << ". Step 1.1: Extend the ray to the thinLens" << std::endl;

	//The plane of the thinLens (orthogonal to z axis)
	Eigen::Vector3d thinLensPoint1, thinLensPoint2;
	thinLensPoint1<< thinLensPoseInWorld(lytro).translation().x()+1, thinLensPoseInWorld(lytro).translation().y()+1, thinLensPoseInWorld(lytro).translation().z(); 
	thinLensPoint2<< thinLensPoseInWorld(lytro).translation().x()+1, thinLensPoseInWorld(lytro).translation().y()-1, thinLensPoseInWorld(lytro).translation().z(); 
	Eigen::Vector4d thinLensPlane = v::plane_from_3_points(thinLensPoseInWorld(lytro).translation(), thinLensPoint1, thinLensPoint2);

	//slopeRay1 of the ray
	Eigen::Vector3d slopeRay1 = pixelRay[pixNumber].tail(3) - microLensPoseInWorld(lytro,0,0).translation();
	
	//t is the intersection between the ray and thinLens plane
	double t = computeT(thinLensPlane, slopeRay1, microLensPoseInWorld(lytro,0,0).translation());
	
	//Extend the the rays to the thinLens plane (z coord) and then passing through it
	Eigen::Vector3d endingPointRay1 = pointOfLine(t,slopeRay1,microLensPoseInWorld(lytro,0,0).translation());

	std::cout << boost::format("t = %1%")%t << std::endl;
	std::cout << boost::format("slopeRay1 = %1%")%slopeRay1.transpose() << std::endl;
	std::cout << boost::format("endingPointRay1 = %1%")%endingPointRay1.transpose() << std::endl;

	/////////////////////////////////////////////////////////////Step 1.2: test if the ray touch the thinLens////////////////////////////////////////////////////////////////////////////////
	std::cout << ". Step 1.2: Test if the ray touch the thinLens" << std::endl;

	//The test is to verify the distance between the intersection point on the thin lens plane and the thinlens diameter 
	Eigen::Vector2d vectorTest = thinLensPoseInWorld(lytro).translation().head(2) - endingPointRay1.head(2);
	std::cout << boost::format("vectorTest = %1%")%vectorTest.transpose() << std::endl;

	if( vectorTest.norm() >= mainLensDiameter/2)
	{
		std::cerr << "The ray doesn't touch the thinLens !" << std::endl;
		return 0;
	}		

	/////////////////////////////////////////////////////////////Step 1.3: Passing through the thinLens////////////////////////////////////////////////////////////////////////////////
	std::cout << ". Step 1.3: Passing through the thinLens" << std::endl;

	//Change microlensPoseInWorld from WORLD to THINLENS coordinate system				
	Eigen::Vector3d p3dInThinLens = thinLensPoseInWorld(lytro).rotation() * microLensPoseInWorld(lytro,0,0).translation() - thinLensPoseInWorld(lytro).translation();
		
	//projectedPoint is the microLens center projected through the thinLens
	Eigen::Vector4d projectedPoint = thinLensProjMat * p3dInThinLens.homogeneous();
	projectedPoint /= projectedPoint(3); //divide by lamdba

	//Change THINLENS to WORLD coordinate system
	projectedPoint.head(3) = thinLensPoseInWorld(lytro).rotation().transpose() * (projectedPoint.head(3) + thinLensPoseInWorld(lytro).translation());
	std::cout << boost::format("test proj point = %1%")%projectedPoint.head(3).transpose() << std::endl;

	/////////////////////////////////////////////////////////////Step 1.3: Passing through the thinLens////////////////////////////////////////////////////////////////////////////////
	std::cout << ". Step 1.4: Create the ray based on the projected point" << std::endl;
	
	Eigen::Vector3d slopeRay2 = projectedPoint.head(3) - endingPointRay1;
	std::cout << boost::format("slopeRay2 = %1%")%slopeRay2.transpose() << std::endl;

	/////////////////////////////////////////////////////////////Step 1.2: Passing through the thinLens////////////////////////////////////////////////////////////////////////////////
	std::cout << ". Step 1.5: Extend the final ray to the infinite and beyond !" << std::endl;
	
	Eigen::Vector3d endingPointRay2;
	double var = (1 - endingPointRay1.z() ) / slopeRay2.z();
	endingPointRay2 = pointOfLine(var,slopeRay2,endingPointRay1);
	std::cout << boost::format("endingPointRay2 = %1%")%endingPointRay2.transpose() << std::endl;

	laPub();

/////////////////////////////////////////////////////////////Create a cube////////////////////////////////////////////////////////////////////////////////
	std::cout << "- Create a cube -" << std::endl;

	double edgesLength = 25;
	AlignedVector<Eigen::Vector3d> cubeNodes;
	cubeNodes.emplace_back(-edgesLength,-edgesLength,-edgesLength); //A
	cubeNodes.emplace_back(edgesLength,-edgesLength,-edgesLength); //B
	cubeNodes.emplace_back(edgesLength,edgesLength,-edgesLength); //C
	cubeNodes.emplace_back(-edgesLength,edgesLength,-edgesLength); //D
	cubeNodes.emplace_back(-edgesLength,-edgesLength,edgesLength); //E
	cubeNodes.emplace_back(edgesLength,-edgesLength, edgesLength); //F
	cubeNodes.emplace_back(edgesLength,edgesLength,edgesLength); //G
	cubeNodes.emplace_back(-edgesLength,edgesLength,edgesLength); //H

	laPub();

/////////////////////////////////////////////////////////////Get cube planes equations////////////////////////////////////////////////////////////////////////////////
	std::cout << "- Get cube planes equations -" << std::endl;

	//libv plane from 3 points
	AlignedVector<Eigen::Vector4d> cubePlanes (6);
	cubePlanes[0] = v::plane_from_3_points(cubeNodes[0],cubeNodes[1],cubeNodes[2]); //A,B,C
	cubePlanes[1] = v::plane_from_3_points(cubeNodes[0],cubeNodes[1],cubeNodes[4]); //A,B,E

	laPub();

/////////////////////////////////////////////////////////////Intersection between plane and ray?////////////////////////////////////////////////////////////////////////////////
	std::cout << "- Intersection between plane and ray? -" << std::endl;

	Eigen::Vector3d intersectionPointNear,intersectionPointFar;

	//Test1: Ray box intersection (Kay & Kayjia method based on slabs)
	//Determine the variable tNear, tFar of the paramteric equation of the ray intersecting the plane 
	double tNear, tFar;

	tNear = computeT(cubePlanes[0], slopeRay2,endingPointRay1);
	// tFar = computeT(cubePlanes[1], slopeRay2,endingPointRay1);
	// std::cout << boost::format("tNear = %1% and tFar = %2%")%tNear%tFar << std::endl;

	// //Determine the position of the intersection between the plane and the ray 
	intersectionPointNear = pointOfLine(tNear, slopeRay2,endingPointRay1);
	// intersectionPointFar = pointOfLine(tFar, slopeRay2,endingPointRay1);
	std::cout << boost::format("intersectionPointNear = %1%")%intersectionPointNear.transpose() << std::endl;

	if(tNear > tFar)
		std::cerr << "The intersection point is outside the cube !" << std::endl;

	//Test2: Proj cube face in image to verify if the pixel in inside
	AlignedVector<Eigen::Vector2d> cubeNodesInImage (cubeNodes.size());

	for(unsigned int n=0 ; n < cubeNodesInImage.size() ; ++n)
	{	
		//WORLD to THINLENS
		Eigen::Vector3d p3d = thinLensPoseInWorld(lytro).rotation() * cubeNodes[n] - thinLensPoseInWorld(lytro).translation();

		Eigen::Vector4d p4dTmp = thinLensProjMat * p3d.homogeneous();
		p4dTmp /= p4dTmp(3); //divide by lamdba

		//THINLENS to WORLD
		p3d = thinLensPoseInWorld(lytro).rotation().transpose() * ( p4dTmp.head(3) + thinLensPoseInWorld(lytro).translation());

		//WORLD to MICROLENS
		p3d = microLensPoseInWorld(lytro,0,0).rotation() * p3d - microLensPoseInWorld(lytro,0,0).translation();

		microProjMat.project(p3d,cubeNodesInImage[n]);
	}

	for(auto p : cubeNodesInImage)
		std::cout << boost::format("cubeNodesInImage = %1%")%p.transpose() << std::endl;

	//Compute nodes vectors
	Eigen::Vector2d ab = cubeNodesInImage[1] - cubeNodesInImage[0];
	Eigen::Vector2d bc = cubeNodesInImage[2] - cubeNodesInImage[1];
	Eigen::Vector2d cd = cubeNodesInImage[3] - cubeNodesInImage[2];
	Eigen::Vector2d da = cubeNodesInImage[0] - cubeNodesInImage[3];

	Eigen::Vector2d aPixelVec = pixelRay[pixNumber].head(2) - cubeNodesInImage[0];
	Eigen::Vector2d bPixelVec = pixelRay[pixNumber].head(2) - cubeNodesInImage[1];
	Eigen::Vector2d cPixelVec = pixelRay[pixNumber].head(2) - cubeNodesInImage[2];
	Eigen::Vector2d dPixelVec = pixelRay[pixNumber].head(2) - cubeNodesInImage[3];

	auto cosinusAngleVector = [](const Eigen::Vector2d& v1, const Eigen::Vector2d& v2){
		return ( v1.x()*v2.x() + v1.y()*v2.y() ) / ( v1.norm() * v2.norm() );
	};

	double cosTheta1 = cosinusAngleVector(ab, aPixelVec);
	double cosTheta2 = cosinusAngleVector(bc, bPixelVec);
	double cosTheta3 = cosinusAngleVector(cd, cPixelVec);
	double cosTheta4 = cosinusAngleVector(da, dPixelVec);
	std::cout << boost::format("cosTheta1 = %1%")%cosTheta1 << std::endl;
	std::cout << boost::format("cosTheta2 = %1%")%cosTheta2 << std::endl;
	std::cout << boost::format("cosTheta3 = %1%")%cosTheta3 << std::endl;
	std::cout << boost::format("cosTheta4 = %1%")%cosTheta4 << std::endl;

	if(cosTheta1 < 0 || cosTheta2 < 0 || cosTheta3 < 0 || cosTheta4 < 0)
		std::cout << "Miss the cube !" << std::endl;
	else
		std::cout << "Hit the cube !" << std::endl;

	laPub();

/////////////////////////////////////////////////////////////Viewers////////////////////////////////////////////////////////////////////////////////
	std::cout << "- Viewers -" << std::endl;
	
	/////////////////////////////////////////////////////////////viewer3D////////////////////////////////////////////////////////////////////////////////
	v::ViewerContext viewer3D = v::viewer(0).title("3D view").size(800,600).background(v::gray).interaction_mode(v::INTERACTION_CAD);
	v::Pose poseMonde; //trans (0,0,0) && rot(id3)
	viewer3D.layer(0).name("World coordSystem").add_opengl([&](){
		glLineWidth(2);
		glBegin(GL_LINES);
			drawAxis(poseMonde,1);
		glEnd();
	}).update();

	viewer3D.layer(1).name("Camera pose").add_opengl([&](){
		glLineWidth(2);
		glBegin(GL_LINES);
			drawAxis(lytro.pose,1);
		glEnd();
		}).update();

	viewer3D.layer(2).name("ThinLens pose").add_opengl([&](){
		glLineWidth(2);
		glBegin(GL_LINES);
			drawAxis(thinLensPoseInWorld(lytro),1);
		glEnd();
		}).update();

	viewer3D.layer(3).name("MicroLens pose").add_opengl([&](){
		glBegin(GL_LINES);
			for(unsigned int row=0 ; row<lytro.height ; ++row)
				for(unsigned int col=0 ; col<lytro.width ; ++col)
					drawAxis(microLensPoseInWorld(lytro,row,col),1);
		glEnd();
	}).update();

	viewer3D.layer(5).name("Rays1 : microlens to thinLens").add_opengl([&](){
		glLineWidth(2);
		glBegin(GL_LINES);
			drawLine(microLensPoseInWorld(lytro,0,0).translation(), endingPointRay1);
		glEnd();
	}).update();

	viewer3D.layer(6).name("Rays2: thinLens to world").add_opengl([&](){
		glLineWidth(2);
		glBegin(GL_LINES);
			drawLine(endingPointRay1, endingPointRay2);
		glEnd();
	}).update();

	viewer3D.layer(54).name("test points").add_opengl([&](){
		glPointSize(4);
		glBegin(GL_POINTS);
			// meta_drawPoint(endingPointRay1, projectedPoint.head(3), endingPointRay2,intersectionPointFar,intersectionPointNear);
			meta_drawPoint(endingPointRay1, projectedPoint.head(3), endingPointRay2,intersectionPointNear);
		glEnd();
	}).update();

	viewer3D.layer(4848).name("Cube").add_opengl([&](){
		glPointSize(4);
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
			for(auto n : cubeNodes)
				drawPoint(n);
		glEnd();
		glBegin(GL_LINES);
			drawLine(cubeNodes[0], cubeNodes[1]);
			drawLine(cubeNodes[1], cubeNodes[2]);
			drawLine(cubeNodes[2], cubeNodes[3]);
			drawLine(cubeNodes[3], cubeNodes[0]);

			drawLine(cubeNodes[4], cubeNodes[5]);
			drawLine(cubeNodes[5], cubeNodes[6]);
			drawLine(cubeNodes[6], cubeNodes[7]);
			drawLine(cubeNodes[7], cubeNodes[4]);

			drawLine(cubeNodes[0], cubeNodes[4]);
			drawLine(cubeNodes[1], cubeNodes[5]);
			drawLine(cubeNodes[2], cubeNodes[6]);
			drawLine(cubeNodes[3], cubeNodes[7]);
		glEnd();
	}).update();

	/////////////////////////////////////////////////////////////viewer2D////////////////////////////////////////////////////////////////////////////////
	v::ViewerContext viewer2D = v::viewer(1).title("2D view").size(800,600).background(v::gray).pen_width(4);

	viewer2D.layer(0).name("Pixel of interest").pen_color(v::black);
	for(auto p : pixelRay)
		viewer2D.add_point(p.head(2).x(),p.head(2).y());
	viewer2D.layer(0).pen_width(5).pen_color(v::red);
		viewer2D.add_point(pixelRay[pixNumber].head(2).x(),pixelRay[pixNumber].head(2).y());
	viewer2D.layer(0).update();

	viewer2D.layer(1).name("Cube").pen_color(v::green).pen_width(5);
	for(unsigned int n=0 ; n<cubeNodesInImage.size()-4 ; ++n)
		viewer2D.add_point(cubeNodesInImage[n].x(),cubeNodesInImage[n].y());
	viewer2D.pen_width(1);
	for(unsigned int n=0 ; n<cubeNodesInImage.size()-5 ; ++n)
		viewer2D.add_line(cubeNodesInImage[n].x(),cubeNodesInImage[n].y(), cubeNodesInImage[n+1].x(),cubeNodesInImage[n+1].y());
	viewer2D.add_line(cubeNodesInImage[0].x(),cubeNodesInImage[0].y(), cubeNodesInImage[3].x(),cubeNodesInImage[3].y());

	viewer2D.layer(1).update();

	v::wait_viewers();
	zaiJian();
	return 0;
}