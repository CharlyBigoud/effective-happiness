#include <random>

// https://fr.wikipedia.org/wiki/Recuit_simul%C3%A9

template<typename MODEL, typename STATE>
struct SimulatedAnnealing
{
    const MODEL& model;
    STATE& state;
    double acceptation_tolerance;
    double temperature_min;
    int iterations_max;

    void run();
    double metropolis(const double, const double);

    double temperature;
};

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
double energy(const MODEL& model, const STATE& state);

template<typename MODEL, typename STATE>
void SimulatedAnnealing<MODEL, STATE>::run()
{
    temperature = 1000.0;

    //energy_precedente is initiated with initial state;
    double energy_precedente = energy(this->model, state);

    int it = 0;
    while (
        (temperature >= temperature_min)
    or  (it <= iterations_max)
    )
    {
        const STATE current_state = state.generate(1.0);
        double current_energy = energy(model, current_state);

        if (
           (current_energy < energy_precedente)
        or (random_value() < metropolis(current_energy - energy_precedente, temperature))
        ){
            std::cout << "iejvice";
            state = current_state;
            energy_precedente = current_energy;

            --temperature;
        }
        else
        {
            //rien du tout
        }

        ++it;
    }

    // std::cout << 

};