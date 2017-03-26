#include <iostream>
#include <random>

#include "../simulated_annealing.hpp"

int main()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<> distrib(0, 10.0);

    SimulatedAnnealing sim(1e3, 0.0, int(1e5), 10.0);

    double x = -100.0;
    auto f = [](double x){ return 5.0 * std::cos(0.25 * x) + x * (x / 750.0); };
    auto gen = [&](double x){ return x + distrib(generator);};

    std::cout << "initial value: " << x << " (err: " << f(x) << ")" << std::endl;

    sim(f, x, gen);

    std::cout << "final value: " << x << " (err: " << f(x) << ")" << std::endl;
}
