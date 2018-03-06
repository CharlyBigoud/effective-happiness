#include <iostream>
#include <cstdlib>
#include <cassert>

int main()
{
    assert(std::getenv("v") && "Error: please set v --c======3");
    char* v = std::getenv("v");

    std::cout << v << std::endl;

    return 0;
}
