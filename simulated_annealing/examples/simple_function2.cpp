#include <iostream>
#include <random>

#include "../simulated_annealing.hpp"

//parameters to optimize
struct Parameters
{
    double x;
};

double cost_function(const Parameters& p)
{
    return p.x * ( p.x - 1);
}

struct Energy
{
    double operator()(const Parameters& p) const
    {
        return cost_function(p);
    }
};

struct Generator
{
    Parameters operator()(Parameters const& p) const
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::normal_distribution<> distrib(0, 10.0);

        return Parameters{p.x + distrib(generator)};
    }
};

int main()
{
    SimulatedAnnealing sim(1e3, 0.0, int(1e5), 10.0);

    Energy energy;
    Parameters params;
    Generator gen;

    std::cout << "initial value: " << params.x << " (err: " << energy(params) << ")" << std::endl;

    sim(energy, params, gen);

    std::cout << "final value: " << params.x << " (err: " << energy(params) << ")" << std::endl;
}
