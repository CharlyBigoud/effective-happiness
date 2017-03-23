#include <random>

// https://fr.wikipedia.org/wiki/Recuit_simul%C3%A9

// Par exemple, on pourrait avoir trois paramètres : la température
// initiale, la longueur d’un palier (nombre d’itérations avant de
// changer la température) et le coefficient de décroissance (si
// décroissance géométrique).
// • On peut aussi utiliser d’autres schémas de refroidissement :
// – On peut faire décroître la température à chaque itération.
// – On utilise parfois une température constante (algorithme de Metropolis).
// – On peut utiliser des schémas plus complexes, dans lesquels la
// température peut parfois remonter.
struct CoolingSchedule{};

//returns a value between 0 or 1
double random_value()
{
    return ((double) std::rand() / (RAND_MAX));
}

template<typename STATE, typename ENERGY>
struct SimulatedAnnealing
{
    STATE& state;
    ENERGY& energy;
    const CoolingSchedule& cool;
    double acceptation_tolerance;
    double temperature_min;
    int iterations_max;

    double temperature_max;
    double iterations_max_for_each_temperature;

    //depend du schéma de refroissement
    double temperature(const int) const;
    bool metropolisCritieria(const double, const double);
    void run();

    double t;
};

template<typename STATE, typename ENERGY>
bool SimulatedAnnealing<STATE, ENERGY>::metropolisCritieria(const double delta_e, const double temperature)
{
    if (delta_e <= 0)
    {
        return true;
    }
    else if (random_value() <= std::exp( -delta_e / temperature) )
    {
        return true;
    }
    else return false;
}


template<typename STATE, typename ENERGY>
double SimulatedAnnealing<STATE, ENERGY>::temperature(const int it) const
{
    return double(it / iterations_max) * t;
}

template<typename STATE, typename ENERGY>
void SimulatedAnnealing<STATE, ENERGY>::run()
{
    t = temperature_max;

    //previous_energy is initiated with initial state;
    double previous_energy = energy(state);

    int it = 0;
    while (
        (it < iterations_max)
    and (t >= temperature_min)
    )
    {
        const STATE current_state = state.generate();
        const double current_energy = energy(current_state);

        if (metropolisCritieria(current_energy - previous_energy, t))
        {
            state = current_state;
            previous_energy = current_energy;

            t = temperature(it);
        }

        ++it;
    }
};