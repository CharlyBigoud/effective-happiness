#include <iostream>
#include <vector>
#include <array>
#include <opencv2/opencv.hpp>



template <typename T>
T return_argument(T t)
{
	return t;
}

std::ostream& operator<<(std::ostream& os, const char c)
{
	os << c;
	return os;
}

// std::ostream& operator<<(std::ostream& os, const char s [5])
// {
// 	os << s;
// 	return os;
// }

template <typename P>
std::ostream& operator<<(std::ostream& os, P p)
{
	for(auto& a : p)
		os << a;
	return os;
}

int main()
{
	// std::cout << "Hello" << std::endl;
	
	//Creating 	
	std::vector<double> dbls {0,0,0};
	std::vector<int> ints {1,1,1};
	std::array<int,3> arrs {2,2,2};
	cv::Mat img(10,1, CV_8UC3, cv::Scalar(255,0,0));


	std::cout << 2.0 << std::endl;
	std::cout << return_argument(dbls) << std::endl;
	std::cout << return_argument(ints) << std::endl;
	std::cout << return_argument(arrs) << std::endl;

	//printing cv::Mat
	std::cout << return_argument(img) << std::endl;
	std::cout << img << std::endl;

	// std::cout << 'c' << std::endl;
	// std::cout << "truc" << std::endl;


	return 0;
}