#include <iostream>

struct A{};

int main()
{
    A a;

    std::cout << sizeof(A) << std::endl;

    char *c = (char *)&a;
    std::cout << int(*c) << std::endl;

    *c = 42;
    std::cout << int(*c) << std::endl;

    return 0;
}