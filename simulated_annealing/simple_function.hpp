struct Function
{
    double x;

    double operator()() const { return x*x - M_PI; }
};

template<>
double energy(const State<Function>& s)
{
    return std::abs(s.f());
}

template<>
State<Function> State<Function>::generate()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distrib(0, exploration_value);

    Function new_f{f.x + distrib(gen)};

    return State<Function>{new_f, exploration_value};
}
