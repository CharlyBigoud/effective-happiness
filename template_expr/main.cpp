
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;



/*
Vector operator*(Vector a, double b)
{
  Vector v(a.size());
  for(size_t i = 0 ; i < a.size() ; i++)
    v[i] = a[i] * b;
  return v;
}

Vector operator*(Vector a, Vector b)
{
  Vector v(a.size());
  for(size_t i = 0 ; i < a.size() ; i++)
    v[i] = a[i] * b[i];
  return v;
}

Vector operator+(Vector a, Vector b)
{
  Vector v(a.size());
  for(size_t i = 0 ; i < a.size() ; i++)
    v[i] = a[i] + b[i];
  return v;
}*/

struct _{};
void show_type(_) {}

struct Vector : std::vector<double>
{
    using moi = std::vector<double>;

    Vector(){}

    Vector(auto expr)
    {
        moi::resize(expr.size());

        for(size_t i = 0 ; i < expr.size() ; ++i)
           at(i) = expr.at(i);
    }
};

template<class A, class B> struct Add
{
    A a;
    B b;
    size_t size() const { return a.size(); }
    auto at(size_t i) const { return a.at(i) + b.at(i); }
};

template<class A, class B>
Add<A,B> operator+(A a, B b)
{
    return Add<A,B>{a,b};
}

template<class A, class B> struct Mul
{
    A a;
    B b;
    size_t size() const { return a.size(); }
    auto at(size_t i) const { return a.at(i) * b.at(i); }
};

template<class A, class B>
Mul<A,B> operator*(A a, B b)
{
    return Mul<A,B>{a,b};
}



int main()
{
    Vector a;a.resize(10);
    std::iota(a.begin(),a.end(),0);

    Vector b;b.resize(10);
    std::iota(b.begin(),b.end(),0);

    Vector c = a + a * (b + a * a) + b;
    //
    /*
    Vector c = a + a * (b + a * a) + b * 2.0;

    Vector d;
    for(size_t i = 0 ; i < a.size() ; i++)
    d[i] = a[i] + a[i] * (b[i] + a[i] * a[i]) + b[i] * 2.0;
    */

    for(auto x : c)
    std::cout << x << ", ";
    std::cout << std::endl;
    return 0;
}
