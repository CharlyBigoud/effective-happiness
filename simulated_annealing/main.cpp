#include <iostream>
#include <cmath>
#include <vector>
#include <array>

#include "simulated_annealing.hpp"
#include "simple_function.hpp"
#include "simple_function_2.hpp"
// #include "rosenbrock.hpp"
// #include "camera.hpp"

int main()
{
    std::cout << "faire schéma de refroidissment" << std::endl;
    std::cout << "bug si les params sont égaux a zero" << std::endl;
    std::cout << "bug si on optimize k et l" << std::endl;
    std::cout << std::endl;

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
    // std::cout << "simple_function: " << simple_function.x << std::endl;
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

//////////////////////ROSENBROCK//////////////////////
    // State<Rosenbrock> rosenbrock{1.0, 100.0, 0.0, 0.0, 0.1};
    // SimulatedAnnealing<decltype(rosenbrock)> sa2{
    //     rosenbrock
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , 1e4
    //     , 1e3
    // };

    // std::cout << "Rosenbrock: (" << rosenbrock.f.x << ", " << rosenbrock.f.y << ")" << std::endl;
    // sa2.run();
    // std::cout << "Rosenbrock: (" << rosenbrock.f.x << ", " << rosenbrock.f.y << ")" << std::endl;
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
