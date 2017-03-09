#include <random>

// https://fr.wikipedia.org/wiki/Recuit_simul%C3%A9

template<typename MODEL, typename STATE>
struct SimulatedAnnealing
{
    const MODEL& model;
    STATE& state;
    double acceptation_tolerance;
    double temperature_min;
    double iterations_max;

    double temperature(const int) const;
    double metropolis(const double, const double);
    void run();

    double t;
};

template<typename MODEL, typename STATE> double energy(const MODEL&, const STATE&);

//returns a value betwwen 0 or 1
double random_value()
{
    return ((double) std::rand() / (RAND_MAX));
}

template<typename MODEL, typename STATE>
double SimulatedAnnealing<MODEL, STATE>::metropolis(const double delta_e, const double temperature)
{
    return std::exp( -delta_e / temperature);
}

template<typename MODEL, typename STATE>
double SimulatedAnnealing<MODEL, STATE>::temperature(const int it) const
{
    return double(it / iterations_max) * t;
}

template<typename MODEL, typename STATE>
void SimulatedAnnealing<MODEL, STATE>::run()
{
    t = 1000.0;

    //energy_precedente is initiated with initial state;
    double energy_precedente = energy(this->model, state);

    int it = 0;
    while (
        (it < iterations_max)
    and (t >= temperature_min)
    )
    {
        const STATE current_state = state.generate(1.0);
        double current_energy = energy(model, current_state);

        if (
           (current_energy < energy_precedente)
        and (random_value() < metropolis(current_energy - energy_precedente, t))
        ){
            state = current_state;
            energy_precedente = current_energy;

            t = temperature(it);
        }
        else
        {
            //rien du tout
        }

        ++it;
    }

    // std::cout << << std::endl;

};