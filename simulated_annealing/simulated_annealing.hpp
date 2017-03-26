#pragma once

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

struct SimulatedAnnealing
{
    double start_temperature;
    double stop_temperature;
    int max_iterations;
    double acceptation_tolerance;

    double current_temperature;
    // double max_iterations_max_for_each;

    double random_value()
    {
        return ((double) std::rand() / (RAND_MAX));
    }

    SimulatedAnnealing( double start_tmp = 1000.0, double stop_tmp = 0.0, double it_max = 1000, double tol = 0.1)
    : start_temperature(start_tmp), stop_temperature(stop_tmp), max_iterations(it_max), acceptation_tolerance(tol)
    // , max_iterations_max_for_each(it_max) //pour l'instant on s'en fou
    {};

    bool metropolisCritieria(const double delta_e, const double temperature)
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

    double temperature(const int it) const
    {
        return double(it / max_iterations) * current_temperature;
    };

    template<typename Energy, typename State, typename Generator>
    void operator()(const Energy& energy, State& state, const Generator& generate)
    {
        current_temperature = start_temperature;

        //previous_energy is initiated with initial state;
        double previous_energy = energy(state);

        int it = 0;
        while (
            (it < max_iterations)
        and (current_temperature >= stop_temperature)
        )
        {
            const State current_state = generate(state);
            const double current_energy = energy(current_state);

            if (metropolisCritieria(current_energy - previous_energy, current_temperature))
            {
                state = current_state;
                previous_energy = current_energy;

                current_temperature = temperature(it);
            }

            ++it;
        }
    }
};
