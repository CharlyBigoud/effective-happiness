#include <iostream>
#include <cmath>
#include <vector>
#include <array>

#include "simulated_annealing.hpp"
#include "camera.hpp"

struct Observations
{
    const P3DS& p3ds;
    P2DS pixels;
};

double distance(const P2D& p1, const P2D& p2)
{
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

double energy(const Observations& obs, const PinholeCameraModel& pcm)
{
    double e = 0.0;
    for (size_t i=0 ; i<obs.pixels.size() ; ++i)
    {
        double d = distance(obs.pixels[i], pcm.project(obs.p3ds[i]));
        e += std::hypot(d, d);
    }

    return std::sqrt(e / (double)obs.pixels.size());
}

/*
 * il faut que STATE ai une fonction generate()
*/
int main()
{
    PinholeCameraModel reference_camera;
    reference_camera.focal = 50.0;
    reference_camera.u0 = 200.0;
    reference_camera.v0 = 200.0;
    reference_camera.xi = 0.0;

    PinholeCameraModel camera_to_optimize;
    camera_to_optimize.focal = 50.0;
    camera_to_optimize.u0 = 200.0;
    camera_to_optimize.v0 = 200.0;
    camera_to_optimize.xi = 0.0;

    Observations observations{
          {{1,2,50}, {3,4,50}, {5,6,50}, {7,8,50}, {9,10,50}, {11,12,50}, {13,14,50}, {15,16,50}, {17,18,50}}
        // , {{0,0}, {3,4}, {5,6}, {7,8}, {9,10}, {11,12}, {13,14}, {15,16}, {17,18}}
        // , P2DS{} (10)
    };

    observations.pixels.resize(observations.p3ds.size());
    for (size_t i=0 ; i<observations.pixels.size() ; ++i)
    {
        observations.pixels[i] = reference_camera.project(observations.p3ds[i]);
        // std::cout << observations.p3ds[i] << " -> " << observations.pixels[i] << "\n";
    }

    SimulatedAnnealing<Observations, PinholeCameraModel> sa{
          observations
        , camera_to_optimize
        , 0.0
        , (int)1e1
    };

    std::cout << reference_camera << std::endl;
    std::cout << camera_to_optimize << std::endl;

    sa.run();

    std::cout << camera_to_optimize << std::endl;

    return 0;
}