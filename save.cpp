#include <iostream>
#include <tuple>

template<typename ... T> struct BackUp
{
    std::tuple<T...> values;
    std::tuple<T&...> reference;
    void restore() { reference = values; }
};

template<typename ... T> BackUp<T...> back_up(T& ... args)
{
    return BackUp<T...>{std::make_tuple(args...),std::tie(args...)};
}

struct Truc{ int val;};

int main()
{
    int a = 0;
    double b = 2.0;
    float c = 2.0;
    Truc d{42};

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d.val: " << d.val << std::endl;

    auto backup = back_up(a, b, c, d);

    a += 12;
    b += 0.5;
    c += 0.54;
    d.val += 545;

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d.val: " << d.val << std::endl;

    backup.restore();

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d.val: " << d.val << std::endl;

    return 0;

}
