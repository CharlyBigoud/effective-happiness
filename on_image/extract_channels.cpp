#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>

template<int I> struct Int { static const int value = I; };
template<typename ...> struct List{};

using Red = List<Int<0>, Int<1>>;
using Green = List<Int<0>, Int<2>>;
using Blue = List<Int<1>, Int<2>>;
// using Blue = Int<2>;


struct True{};
struct False{};

template<typename T> True identical(T,T);
template<typename T, typename U> False identical(T,U);

template<void (*F)(cv::Mat&)> auto iterate_(List<>){};
template<void (*F)(cv::Mat&), typename A, typename ... B> auto iterate_(List<A,B...>)
{

};

// //
// template <typename ... T> T reinterpreteLaDemande()
// {
//     // return List{};
//     return Red{};
// }


template<void (*F)(cv::Mat&)> void iterate(std::vector<cv::Mat>& m, List<>)
{
    // pour traiter le cas de la liste de vide une fois que tout est dépiler
}

template<void (*F)(cv::Mat&), typename A, typename ... T> void iterate(std::vector<cv::Mat>& m, List<A,T...>)
{
    iterate<F>(m, List<T...>{});

    //là on peut faire un truc en utlisant les int<val>
    F(m[A::value]);
}

//set an image to zero
void set2zero(cv::Mat& m){ m = cv::Mat::zeros(m.rows, m.cols, CV_MAKETYPE(m.depth(), 1)); }

template<typename ... L> void modifyChannels(std::vector<cv::Mat>& m)
{   
    //verifier les doublons dans les listes et ne retourner qu'une seul liste
    // reinterpreteLaDemande<List<L...>>();

    Red r;
    // Blue r;
    // Green r;

    //pour chaque liste
    iterate<set2zero>(m, r);
}





/*
    take an image, extract desired channel(s) and return another image
*/
// template<typename ... L> cv::Mat getColors(const cv::Mat& input, List<L...>)
template<typename ... L> cv::Mat getColors(const cv::Mat& input)
{
    std::vector<cv::Mat> bgr (input.channels());
    cv::split(input, bgr);

    modifyChannels<List<L...>>(bgr);

    cv::Mat output;
    cv::merge(bgr, output);

    return output;
}





// for i in {1..21..1}; do ./extract_channels fejizj/IMG$i.png; cp ./red_output.png ./outputs/redified$i.png;  done


int main(int argc, char** argv)
{
    if (argc != 2){std::cerr << "Error: No image in input." << std::endl;}

    cv::Mat input = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    
    cv::namedWindow( "input", CV_WINDOW_NORMAL);
    cv::imshow( "input", input );

    cv::Mat output = getColors<Red>(input);
    
    // cv::namedWindow( "output", CV_WINDOW_NORMAL );
    // cv::imshow( "output", output );

    cv::imwrite("./red_output.png", output, {CV_IMWRITE_PNG_COMPRESSION, 0});

    // std::cout << "Press a key to continue." << std::endl;
    // cv::waitKey(0);
    return 0;
}