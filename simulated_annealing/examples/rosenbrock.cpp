#include <iostream>
#include <random>

#include "../simulated_annealing.hpp"

struct RosenbrockParams
{
    double x, y;
};

int main()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<> distrib(0, 1.0);

    SimulatedAnnealing cuite(1e3, 0.0, int(1e6), 10.0);

    auto ros_err = [](const RosenbrockParams& r){ return (1 - r.x) * (1 - r.x) + 100 * (r.y - r.x * r.x) * (r.y - r.x * r.x); };

    RosenbrockParams ros_parameters{100.0, 100.0};  

    auto ros_gen = [&](const RosenbrockParams& r){
        return RosenbrockParams{r.x + distrib(generator), r.y + distrib(generator)};
    };

    std::cout << "initial value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;
    cuite(ros_err, ros_parameters, ros_gen);
    std::cout << "final value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;
}
