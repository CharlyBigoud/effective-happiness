#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>

int main()
{
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<> d(-300, 300);
    std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
    for(int n = 0; n < 5; ++n) {
        int v = d(g);
        std::cout << std::setw(4) << v
                  << std::setw(20) << std::clamp(v, INT8_MIN, INT8_MAX)
                  << std::setw(21) << std::clamp(v, 0, UINT8_MAX) << '\n';
    }
}
