#include <iostream>
#include <vector>

int main()
{
    int a = 42;

    if (int b = a)
        std::cout << "a: " << a << std::endl;
    else if (int c = 2 * b)
        std::cout << "c: " << c << std::endl;

    return 0;
}
