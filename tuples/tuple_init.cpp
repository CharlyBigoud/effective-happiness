#include <tuple>
#include <vector>
#include <iostream>
#include <string>

#include <Eigen/Dense>

template<class T> using AlignedVector = std::vector<T,Eigen::aligned_allocator<T>>;

int main()
{
    std::tuple<int, char> t { 1, '1' };
    std::cout << "t:\n" << std::get<0>(t) << ", " << std::get<1>(t) << std::endl;

    std::vector<std::tuple<int, char>> vt {{ 0, '0' }, { 1, '1' }, { 2, '2' }};
    std::cout << "\nvt:" << std::endl;
    for(auto p : vt) 
        std::cout << std::get<0>(p) << ", " << std::get<1>(p) << std::endl;

    //Testing with Eigen::Vector2d
    AlignedVector<std::tuple<int, Eigen::Vector2d>> avt {{ 0, {0,0} }, { 1, {1,1} }, { 2, {2,2} }};
    std::cout << "\navt:" << std::endl;
    for(auto p : avt) 
        std::cout << std::get<0>(p) << ", [" << std::get<1>(p).transpose() << "]"<< std::endl;

    return 0;
}