#include <vector>


template<typename T, int S> struct PT
{
    T data[S];

    template<typename ... X> PT(X ... t) : data{ T(t)... } {}

    PT() {}


    template<int I> T& at() { static_assert(S>I,"NiQ La Peau LisSe."); return data[I];}
    template<int I> T const& at() const { static_assert(S>I,"NiQ La Peau LisSe."); return data[I];}

    T & x() { return at<0>(); }
    T & y() { return at<1>(); }
    T & z() { return at<2>(); }

    T const & x() const { return at<0>(); }
    T const & y() const { return at<1>(); }
    T const & z() const { return at<2>(); }

    T norm() const
    {
        return spec_norm(*this);
    }
};

using P2D = PT<double, 2>;
using P3D = PT<double, 3>;

using P2DS = std::vector<P2D>;
using P3DS = std::vector<P3D>;