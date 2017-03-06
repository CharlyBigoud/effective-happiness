#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;

/// Function header
void cornerHarris_demo( int, void* );

/** @function main */
int main( int argc, char** argv )
{
    /// Load source image and convert it to gray
    src = imread( argv[1], 1 );
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    /// Create a window and a trackbar
    namedWindow( "Source image", WINDOW_NORMAL );
    createTrackbar( "Threshold: ", "Source image", &thresh, max_thresh, cornerHarris_demo );
    imshow( "Source image", src );

    cornerHarris_demo( 0, 0 );

    waitKey(0);
    return(0);
}

/** @function cornerHarris_demo */
void cornerHarris_demo( int, void* )
{
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros( src.size(), CV_32FC1 );

    /// Detector parameters
    int blockSize = 3;
    int apertureSize = 3;
    double k = 0.04;

    /// Detecting corners
    cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

    /// Normalizing
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );

    /// Drawing a circle around corners
    for( int j = 0; j < dst_norm.rows ; j++ )
        for( int i = 0; i < dst_norm.cols; i++ )
            if( (int) dst_norm.at<float>(j,i) > thresh )
                circle( dst_norm_scaled, Point( i, j ), 2,  Scalar(255,0,0), 1, 8, 0 );

    /// Showing the result
    namedWindow( "Corners detected", WINDOW_NORMAL );
    imshow( "Corners detected", dst_norm_scaled );
}