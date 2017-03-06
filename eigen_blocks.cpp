#include <iostream>
#include <Eigen/Dense>

int main()
{
	Eigen::Vector3d p3d;
	p3d<<1,2,3;

	std::cout << "p3d = "<<p3d << std::endl;

	std::cout << "p3d -> p2d = "<<p3d.block<2,1>(0,0) << std::endl;

	double rd = p3d.norm();
	std::cout << "rd = "<<rd << std::endl;

	double rdblock = p3d.block<2,1>(0,0).norm();
	std::cout << "rdblock = "<<rdblock << std::endl;

	return 0;
}