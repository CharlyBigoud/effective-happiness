#include <iostream>
#include <random>

#include "../src/simulated_annealing.hpp"

//parameters to optimize
struct Parameters
{
    double x, y;
};

int main()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<> distrib(0, 1.0);

    SimulatedAnnealing sim(
        1e3     //start temp
        , 1e-3 //stop temp
        , int(1e1) //max it
        , 1e-4 //energy min
        );

    auto ros_err = [](const Parameters& r)
    {
        return (1 - r.x) * (1 - r.x) + 100 * (r.y - r.x * r.x) * (r.y - r.x * r.x);
    };

    Parameters ros_parameters{100.0, 100.0};  

    auto ros_gen = [&](const Parameters& r)
    {
        return Parameters{r.x + distrib(generator), r.y + distrib(generator)};
    };

    std::cout << "initial value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;

    sim(ros_err, ros_parameters, ros_gen);

    std::cout << "final value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;
}
