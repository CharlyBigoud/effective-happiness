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
struct CoolingSchedule{

};

template<typename F>
struct State
{
    F f;
    double exploration_value;

    State<F> generate();
};

template<typename MODEL, typename STATE>
struct SimulatedAnnealing
{
    const MODEL& model;
    STATE& state;
    const CoolingSchedule& cool;
    double acceptation_tolerance;
    double temperature_min;
    double iterations_max;

    double temperature_max;
    double iterations_max_for_each_temperature;

    //depend du schéma de refroissement
    double temperature(const int) const;
    bool metropolisCritieria(const double, const double);
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
bool SimulatedAnnealing<MODEL, STATE>::metropolisCritieria(const double delta_e, const double temperature)
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


template<typename MODEL, typename STATE>
double SimulatedAnnealing<MODEL, STATE>::temperature(const int it) const
{
    return double(it / iterations_max) * t;
}

// cooling schedule

template<typename MODEL, typename STATE>
void SimulatedAnnealing<MODEL, STATE>::run()
{
    t = temperature_max;

    //energy_precedente is initiated with initial state;
    double energy_precedente = energy(this->model, state);

    int it = 0;
    while (
        (it < iterations_max)
    and (t >= temperature_min)
    )
    {
        const STATE current_state = state.generate();
        const double current_energy = energy(model, current_state);

        if (metropolisCritieria(current_energy - energy_precedente, t))
        {
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
};



////////////////////////////
// POUR LA FUNCTON
///////////////////////////////
template<typename STATE>
struct SimulatedAnnealing2
{
    STATE& state;
    const CoolingSchedule& cool;
    double acceptation_tolerance;
    double temperature_min;
    double iterations_max;

    //depend du schéma de refroissement
    double temperature(const int) const;
    bool metropolisCritieria(const double, const double);
    void run();

    double t;
};

template<typename STATE> double energy(const STATE&);

template<typename STATE>
bool SimulatedAnnealing2<STATE>::metropolisCritieria(const double delta_e, const double temperature)
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


template<typename STATE>
double SimulatedAnnealing2<STATE>::temperature(const int it) const
{
    return double(it / iterations_max) * t;
}

template<typename STATE>
void SimulatedAnnealing2<STATE>::run()
{
    t = 500.0;

    //energy_precedente is initiated with initial state;
    double energy_precedente = energy(state);

    int it = 0;
    while (
        (it < iterations_max)
    and (t >= temperature_min)
    )
    {
        const STATE current_state = state.generate();
        const double current_energy = energy(current_state);

        if (metropolisCritieria(current_energy - energy_precedente, t))
        {
            state = current_state;
            energy_precedente = current_energy;

            t = temperature(it);
        }

        ++it;
    }
};