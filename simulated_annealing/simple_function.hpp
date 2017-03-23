// struct State
// {
//     double x;
//     double exploration_value;


//     State generate();
// };

// State State::generate()
// {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::normal_distribution<> distrib(0, exploration_value);

//     return State{
//         x + distrib(gen)
//         , exploration_value
//         };
// }

// struct SimpleEnergy
// {
//     double operator()(State s) const { return s(); }

//     // double operator()() const { return x * x; }
//     // double operator()() const { return x * x - M_PI; }
//     // double operator()() const { return x * (x - 1); }
// };


