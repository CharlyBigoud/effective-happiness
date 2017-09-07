#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
 
// g++ difference.cpp -o app `pkg-config --cflags --libs opencv` && ./app

int main (int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }

    cv::Mat image0 = cv::imread(argv[1], cv::IMREAD_UNCHANGED);
    cv::Mat image1 = cv::imread(argv[2], cv::IMREAD_UNCHANGED);

    assert(image0.size() == image1.size());

    image0.convertTo(image0, CV_8U);
    image1.convertTo(image1, CV_8U);

    cv::Mat difference;
    cv::absdiff(image0, image1, difference);

    // display
    cv::namedWindow("image0", cv::WINDOW_AUTOSIZE);
    cv::imshow("image0", image0);

    cv::namedWindow("image1", cv::WINDOW_AUTOSIZE);
    cv::imshow("image1", image1);

    cv::namedWindow("difference", cv::WINDOW_AUTOSIZE);
    cv::imshow("difference", difference);

    cv::waitKey(0);

    return 0;
}
