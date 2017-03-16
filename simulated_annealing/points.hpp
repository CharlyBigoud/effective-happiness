#include <vector>

template<typename PT> struct Truc
{
    auto operator[](int i) const { return cast().data[i]; }
    auto operator[](int i) { return cast().data[i]; }

    PT const & cast() const { return static_cast<PT const&>(*this); }
    PT & cast() { return static_cast<PT &>(*this); }
};

template<typename T, int S> struct PT : Truc<PT<T, S>>
{
    T data[S];

    template<typename ... X> PT(X ... t) : data{ T(t)... } {}

    PT() {}

    template<bool b> struct Inf {};

    template<int, int> struct OutOfRange;
    template<int I> T const& at(Inf<true>) const { return data[I]; }
    template<int I> T const& at(Inf<false>) const { OutOfRange<I, S> InvalidAccess; return data[I]; }
    template<int I> T & at(Inf<true>) { return data[I]; }
    template<int I> T & at(Inf<false>) { OutOfRange<I, S> InvalidAccess; return data[I]; }

    T & x() { return at<0>(Inf < (S > 0) > {}); }
    T & y() { return at<1>(Inf < (S > 1) > {}); }
    T & z() { return at<2>(Inf < (S > 2) > {}); }

    T const & x() const { return at<0>(Inf < (S > 0) > {}); }
    T const & y() const { return at<1>(Inf < (S > 1) > {}); }
    T const & z() const { return at<2>(Inf < (S > 2) > {}); }

    T norm() const
    {
        return spec_norm(*this);
    }
};

using P2D = PT<double, 2>;
using P3D = PT<double, 3>;

using P2DS = std::vector<P2D>;
using P3DS = std::vector<P3D>;