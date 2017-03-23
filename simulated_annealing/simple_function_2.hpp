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
    double exploration_value;

    double operator()() const { return a * std::cos(b * x) + x * (x / c); }

    SimpleFunction2 generate();
};


SimpleFunction2 SimpleFunction2::generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distrib(0, exploration_value);

    SimpleFunction2 new_f{
    };

    return SimpleFunction2{
        a, b, c
        , x + distrib(gen)
        , exploration_value
        };
}

struct SimpleEnergy2
{
    SimpleFunction2 s;

    double operator()() const { return s(); }
};
