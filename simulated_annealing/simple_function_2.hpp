#include <cmath>

 /*
 * The function is defined here:
 * 5\cos \left(0.25\cdot x\right)+x\cdot \frac{x}{750}
 * 5 * std::cos(0.25 * x) + x * (x / 750);
 */
struct SimpleFunction2
{
    double a, b, c;
    double x;

    double operator()() const
    {
        return a * std::cos(b * x) + x * (x / c);
    }
};

template<>
double energy(const State<SimpleFunction2>& s)
{
    return s.f();
}

template<>
State<SimpleFunction2> State<SimpleFunction2>::generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distrib(0, exploration_value);

    SimpleFunction2 new_f{
        f.a, f.b, f.c
        , f.x + distrib(gen)
    };

    return State<SimpleFunction2>{new_f, exploration_value};
}
