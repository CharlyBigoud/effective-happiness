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
    //     const long double pi = 128.546;
    // std::cout << "default precision (6): " << pi << '\n'
    //           << "std::setprecision(3): " << std::setprecision(3) << pi << '\t'
    //           << "std::setprecision(10): " << std::setprecision(10) << pi << '\n'
    //           << "max precision:         "
    //           << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
    //           << pi << '\n';
    // return 0;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<> distrib(0, 1.0);

    SimulatedAnnealing sim(
          1e3      //start temp
        , 1e-3     //stop temp
        , int(1e6) //max it
        , 1e-4     //energy min
        );

    auto ros_err = [](const Parameters& r)
    {
        return (1 - r.x) * (1 - r.x) + 100 * (r.y - r.x * r.x) * (r.y - r.x * r.x);
    };

    Parameters ros_parameters{100.0, 100.0};

    auto ros_gen = [&](const Parameters& r, const SimulatedAnnealing& s)
    {
        return Parameters{
            //   r.x + 1.0 / (s.current_it != 0 ? s.current_it : 1.0) * distrib(generator)
            // , r.y + 1.0 / (s.current_it != 0 ? s.current_it : 1.0) * distrib(generator)
              r.x + distrib(generator)
            , r.y + distrib(generator)
        };
    };

    std::cout << "initial value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;

    sim(ros_err, ros_parameters, ros_gen);

    std::cout << "final value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;
}
