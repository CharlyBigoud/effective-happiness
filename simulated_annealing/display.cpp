#include "display.hpp"

void bar()
{
    std::cout << "it\tenergy" << std::endl;
    std::cout << "-------------------------" << std::endl;
}

void print(const int it, const double energy)
{
    std::cout << it << "\t" << energy;
    std::cout << std::endl;
}

std::string red(const std::string& s)
{
    return "\033[31m" + s + "\033[0m";
}