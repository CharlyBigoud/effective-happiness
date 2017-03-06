#include <iostream>
#include <array>

template<typename T> using P2 = std::array<T,2>; 

template<typename T>
struct Struct1{
    P2<T> p {T(0), T(0)};

    //Constructor
    Struct1(const P2<T>& p = {0,0})
    : p(p)
    {};

    ~Struct1(){};
};

template<typename T>
struct Struct2{
    P2<T> point(const T i){ return P2<T>{i*T(1), i*T(1)}; };
};

template<typename T>
void affiche(const Struct1<T>& s){ std::cout << "point: {" << s.p[0] << ", " << s.p[1] << "}." << std::endl; }

int main()
{
    Struct1<double> s1;
    affiche(s1);

    // P2<double> p2;
    // affiche(p2);

    Struct2<double> s2;
    affiche(s2.point(2));

    return 0;
}