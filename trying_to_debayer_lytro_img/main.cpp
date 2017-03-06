#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main( int argc, char** argv )
{
	char* imageName = argv[1];

	Mat image;
	image = imread( argv[1], CV_LOAD_IMAGE_UNCHANGED);


	if( argc != 2 || !image.data )
	{
		printf( " No image data \n " );
		return -1;
	}

	// Mat gray_image;
	// cvtColor( image, gray_image, CV_BGR2GRAY );

	// // imwrite( "../../images/Gray_Image.jpg", gray_image );
	// imwrite("2016-03-03_13:26:22.RAW", gray_image)

	// namedWindow( imageName, CV_WINDOW_NORMAL );
	// namedWindow( "Gray image", CV_WINDOW_NORMAL );

	// imshow( imageName, image );
	// imshow( "Gray image", gray_image );

	// waitKey(0);

	return 0;
}