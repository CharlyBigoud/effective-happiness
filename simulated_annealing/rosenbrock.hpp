/*
 * The function is defined here: https://en.wikipedia.org/wiki/Rosenbrock_function
 */
struct Rosenbrock
{
    double a, b;
    double x, y;

    double operator()() const
    {
        return (a - x) * (a - x) + b * (y - x * x) * (y - x * x);
    }
};

template<>
double energy(const State<Rosenbrock>& s)
{
    return std::abs(s.f());
}

template<>
State<Rosenbrock> State<Rosenbrock>::generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distrib(0, exploration_value);

    Rosenbrock new_f{
        f.a, f.b
        , f.x + distrib(gen)
        , f.y + distrib(gen)
    };

    return State<Rosenbrock>{new_f, exploration_value};
}
