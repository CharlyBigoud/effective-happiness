#include <random>

#include "points.hpp"

struct PinholeCameraModel
{
    double focal;
    double u0;
    double v0;
    double k;
    double l;

    PinholeCameraModel(const double f, const double u, const double v, const double k_i = 1.0, const double l_i  = 1.0)
    : focal(f), u0(u), v0(v), k(k_i), l(l_i)
    {};

    P2D project(const P3D& p3d) const
    {
        return {
              (focal / k) * p3d.x() / p3d.z() + u0
            , (focal / l) * p3d.y() / p3d.z() + v0
        };
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

struct Observations
{
    const P3DS& p3ds;
    P2DS pixels;
};

template<typename F>
struct CameraState
{
    F f;
    double exploration_value;

    CameraState<F> generate();
};

template<>
CameraState<PinholeCameraModel> CameraState<PinholeCameraModel>::generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distrib(0, exploration_value);

    PinholeCameraModel pcm(
      f.focal + distrib(gen)
    , f.u0 + distrib(gen)
    , f.v0 + distrib(gen)
    // , f.k + distrib(gen)
    // , f.l + distrib(gen)
    );

    return CameraState<PinholeCameraModel> {pcm, exploration_value};
};

struct Energy
{
    CameraState<PinholeCameraModel>& s;
    const Observations& model;

    double operator()() const
    {
        double e = 0.0;
        for (size_t i = 0 ; i<model.pixels.size() ; ++i)
        {
            double d = distance(model.pixels[i], s.f.project(model.p3ds[i]));
            e += std::hypot(d, d);
        }

        return std::sqrt(e / (double)model.pixels.size());
    };
};