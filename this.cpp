#include <iostream>

template<typename T>
struct A
{
    T t;

    A()
    {}
};

template<typename T>
struct B
{
    T t;

};

int main()
{
    A<double> a;
    B<double> b;

    A<B<A<A<B<A<A<B<A<A<B<A<A<B<A<A<B<A<A<B<A<A<B<A<A<B<A<A<B<A<double>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ab;

    return 0;
}
