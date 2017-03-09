#include <random>

#include "points.hpp"

struct PinholeCameraModel
{
    double focal;
    double u0;
    double v0;
    double k = 1.0, l = 1.0;

    // PinholeCameraModel(const double f, const double u, const double v, const double k_i, const double l_i)
    // :focal(f), u0(u), v0(v), k(k_i), l(l_i)
    // {};

    P2D project(const P3D& p3d) const
    {
        return {
              (focal / k) * p3d.x / p3d.z + u0
            , (focal / l) * p3d.y / p3d.z + v0
        };
    };

    PinholeCameraModel generate(const double value = 0.0){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> distrib(0, value);

        PinholeCameraModel pcm;
        pcm.focal = focal + distrib(gen);
        pcm.u0 = u0 + distrib(gen);
        pcm.v0 = v0 + distrib(gen);

        return pcm;
    };
};

std::ostream& operator<<(std::ostream& o, const PinholeCameraModel& ucm)
{
    o << "\t- focal: " << ucm.focal << "\n";
    o << "\t- center: {" << ucm.u0 << ", " << ucm.v0 << "}\n";
    o << "\t- k: " << ucm.k << "\n";
    o << "\t- l: " << ucm.l << "\n";
    return o;
}
