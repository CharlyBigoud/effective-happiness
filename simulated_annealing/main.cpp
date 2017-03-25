#include <iostream>
#include <cmath>
#include <vector>
#include <array>

#include <random>

#include "simulated_annealing.hpp"

struct MesParametres
{

};

double ma_fonction_de_cout(MesParametres& )
{
    return 0;
}

struct Error
{
    double operator()(MesParametres p) const
    {
        return ma_fonction_de_cout(p);
    }
};

struct Gen
{
    MesParametres operator()(MesParametres const& m) const { return m; }
};





struct RosenbrockParams
{
    double x, y;
};

int main()
{
    {
        MesParametres params;
        Error err;
        SimulatedAnnealing recuite;
        recuite(err, params, Gen());
    }

    SimulatedAnnealing recuite(1e3, 0.0, int(1e5), 10.0);
    double x = -100.0;
    // double x = 0.0;
    auto f = [](double x){ return 5.0 * std::cos(0.25 * x) + x * (x / 750.0); };
    // auto gen = [](double x){ return x + 1000.0 * (((double) std::rand() / (RAND_MAX)) - 0.5); };

    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<> distrib(0, 1.0);

    auto gen = [&](double x){ return x + distrib(generator); };

    std::cout << "initial value: " << x << " (err: " << f(x) << ")" << std::endl;
    recuite(f, x, gen);
    std::cout << "final value: " << x << " (err: " << f(x) << ")" << std::endl;



    ///rosenbrock
    SimulatedAnnealing ros_recuite(1e3, 0.0, int(1e6), 10.0);

    auto ros_err = [](const RosenbrockParams& r){ return (1 - r.x) * (1 - r.x) + 100 * (r.y - r.x * r.x) * (r.y - r.x * r.x); };
    RosenbrockParams ros_parameters{100.0, 100.0};  
    auto ros_gen = [&](const RosenbrockParams& r){
        return RosenbrockParams{r.x + distrib(generator), r.y + distrib(generator)};
    };

    std::cout << "initial value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;
    ros_recuite(ros_err, ros_parameters, ros_gen);
    std::cout << "final value: (" << ros_parameters.x << ", " << ros_parameters.y << ") (err: " << ros_err(ros_parameters) << ")" << std::endl;





    //SimulatedAnnealing
    // std::cout << "faire schéma de refroidissment" << std::endl;
    // std::cout << "bug si les params sont égaux a zero" << std::endl;
    // std::cout << "bug si on optimize k et l" << std::endl;
    // std::cout << std::endl;

    // State simple_function{100.0, 1.0};
    // SimpleEnergy energy{simple_function};

    // SimulatedAnnealing<decltype(simple_function), SimpleEnergy> sa{
    //       simple_function
    //     , energy
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , int(1e4)
    //     , 1e3
    // };

    // std::cout << "simple_function: " << simple_function.x << std::endl;
    // sa.run();
    // std::cout << "simple_function: " << simple_function.x << " cost " << simple_function() << std::endl;
    // std::cout << std::endl;

    // SimpleFunction2 simple_function_2{
    //       5.0, 0.25, 750.0
    //     , -10.0
    //     , 1.0
    // };
    // SimpleEnergy2 energy2{simple_function_2};

    // SimulatedAnnealing<decltype(simple_function_2), SimpleEnergy2> sa3{
    //     simple_function_2
    //     , energy2
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , int(1e4)
    //     , int(1e3)
    // };

    // std::cout << "simple_function_2: " << simple_function_2.x << std::endl;
    // sa3.run();
    // std::cout << "simple_function_2: " << simple_function_2.x << std::endl;
    // std::cout << std::endl;

//////////////////////Camera//////////////////////

    // // building reference
    // PinholeCameraModel reference_camera(50.0, 200.0, 200.0, 1.0, 1.0);
    // std::cout << "reference_camera:\n" << reference_camera << std::endl;

    // // computing model
    // Observations observations{
    //       {{1,2,50}, {3,4,50}, {5,6,50}, {7,8,50}, {9,10,50}, {11,12,50}, {13,14,50}, {15,16,50}, {17,18,50}}
    // };

    // observations.pixels.resize(observations.p3ds.size());
    // for (size_t i=0 ; i<observations.pixels.size() ; ++i)
    //     observations.pixels[i] = reference_camera.project(observations.p3ds[i]);

    // PinholeCameraModel to_optimize{1.0, 1.0, 1.0, 1.0, 1.0};
    // CameraState<PinholeCameraModel> camera_state{reference_camera, 1.1};

    // SimulatedAnnealing<decltype(camera_state), Energy> sa{
    //     camera_state
    //     , Energy{camera_state, observations}
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , int(1e4)
    //     , 1e3
    // };

    // std::cout << "camera_to_optimize:\n" << camera_state.f << std::endl;
    // sa.run();
    // std::cout << "camera_to_optimize:\n" << camera_state.f << std::endl;


    return 0;
}
