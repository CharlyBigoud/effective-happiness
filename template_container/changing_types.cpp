#include <iostream>

template<int I>
struct Type {
    static const int value = I;

    template<typename T>
    T& operator=(const T& t)
    {
        std::cout << t.value << std::endl;
        // return *this;
    };
};

template<typename T, int I = T{}.value>
std::ostream& operator<<(std::ostream& o, const T& t)
{
    return I==0? o<<"Baby" : I==1? o<<"Child" : I==2? o<<"Adult" : o<<"Dead";   //ok
}

using Baby = Type<0>;
using Child = Type<1>;
using Adult = Type<2>;

template<typename A>
struct Box
{
    // template <typename B>
    // operator Box<B>()
    // {
    //     Box<B> result;
    //     // do some converion things
    //     return result;
    // }

    // template <typename B>
    // Box& operator=( const Box<B> &b )
    // {
    //     // A{}.value = B{}.value;
    //     return *this;
    // }
};

template<typename T>
std::ostream& operator<<(std::ostream& o, const Box<T>& b)
{
    return o << "I am a box of " << T() << ".";
}





int main()
{
    Box<Baby> babies;
    std::cout << babies << std::endl;

    Box<Child> children;
    std::cout << children << std::endl;

    Box<Adult> adults;
    std::cout << adults << std::endl;



    Baby b;
    Child c;
    b = c;
    c = b;
    // std::cout << babies << std::endl;



    // auto b2 = Box<T2>{};
    // std::cout << b2 << std::endl;

    // b2 = b1;
    // std::cout << b2 << std::endl;

    // b2 = static_cast<Box<T2>{}>;
}