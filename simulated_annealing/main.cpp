#include <iostream>
#include <cmath>
#include <vector>
#include <array>

#include "simulated_annealing.hpp"
#include "simple_function.hpp"
#include "camera.hpp"

struct Observations
{
    const P3DS& p3ds;
    P2DS pixels;
};

struct State
{
    PinholeCameraModel& camera;
    double exploration_value;

    State generate(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> distrib(0, exploration_value);

        PinholeCameraModel pcm(
          camera.focal + distrib(gen)
        , camera.u0 + distrib(gen)
        , camera.v0 + distrib(gen)
        // , camera.k + distrib(gen)
        // , camera.l + distrib(gen)
        );

        return State{pcm, exploration_value};
    };

    void operator=(const State& s)
    {
        camera = s.camera;
        exploration_value = s.exploration_value;
    }
};

double distance(const P2D& p1, const P2D& p2)
{
    return std::hypot(p1.x() - p2.x(), p1.y() - p2.y());
}

double energy(const Observations& obs, const State& s)
{
    double e = 0.0;
    for (size_t i=0 ; i<obs.pixels.size() ; ++i)
    {
        double d = distance(obs.pixels[i], s.camera.project(obs.p3ds[i]));
        e += std::hypot(d, d);
    }

    return std::sqrt(e / (double)obs.pixels.size());
}

/*
 * il faut que STATE ai une fonction generate()
*/
int main()
{
    std::cout << "faire schéma de refroidissment" << std::endl;
    std::cout << "bug si les params sont égaux a zero" << std::endl;
    std::cout << "bug si on optimize k et l" << std::endl;

    //building reference
    PinholeCameraModel reference_camera(50.0, 200.0, 200.0, 1.0, 1.0);
    std::cout << "reference_camera:\n" << reference_camera << std::endl;

    //computing model
    Observations observations{
          {{1,2,50}, {3,4,50}, {5,6,50}, {7,8,50}, {9,10,50}, {11,12,50}, {13,14,50}, {15,16,50}, {17,18,50}}
    };

    observations.pixels.resize(observations.p3ds.size());
    for (size_t i=0 ; i<observations.pixels.size() ; ++i)
    {
        observations.pixels[i] = reference_camera.project(observations.p3ds[i]);
    }

    //Creating state
    PinholeCameraModel to_optimize{1.0, 1.0, 1.0, 1.0, 1.0};
    State state{
        to_optimize
        , 0.1
    State<Function> simple_function{10.0, 0.1};
    SimulatedAnnealing2<decltype(simple_function)> sa{
        simple_function
        , CoolingSchedule{}
        , 10.0
        , 0.0
        , 1e4
        , 1e3
    };

    SimulatedAnnealing<Observations, State> sa{
          observations
        , state
    std::cout << "prout: " << simple_function.f.x << std::endl;
    sa.run();
    std::cout << "prout: " << simple_function.f.x << std::endl;

        , CoolingSchedule{}
        , 10.0
        , 0.0
        , 1e4
    };

    std::cout << "camera_to_optimize:\n" << state.camera << std::endl;

    sa.run();

    std::cout << "camera_to_optimize:\n" << state.camera << std::endl;

    return 0;
}