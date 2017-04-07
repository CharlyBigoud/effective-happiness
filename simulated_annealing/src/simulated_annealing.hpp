#pragma once

#include <random>

#include "display.hpp"

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
    double min_energy;
    // double acceptation_tolerance;

    double current_temperature;
    int current_it;
    double current_energy;
    // double max_iterations_max_for_each;

    double random_value()
    {
        return double(std::rand()) / double(RAND_MAX);
    }

    SimulatedAnnealing(double start_tmp = 1e3, double stop_tmp = 0.0, int it_max = 1000, double min_e = 0.0
        //, double tol = 0.1
        )
    : start_temperature(start_tmp), stop_temperature(stop_tmp), max_iterations(it_max), min_energy(min_e)
    // , acceptation_tolerance(tol)
    // , max_iterations_max_for_each(it_max) //pour l'instant on s'en fou
    {};

    bool metropolisCritieria(const double delta_e, const double temperature)
    {
        if (delta_e <= 0)
            return true;
        else if (random_value() <= std::exp( -delta_e / temperature) )
            return true;
        else
            return false;
    }

    // double temperature(const int it) const
    // {
    //     return double(it) / double(max_iterations) * current_temperature;
    // };

    double temperature(const double t) const
    {
        return 0.99 * t;
    };

    template<typename Energy, typename State, typename Generator>
    void operator()(const Energy& energy, State& state, const Generator& generate)
    {
        //initiate system
        current_it = 0;
        current_temperature = start_temperature;
        double previous_energy = energy(state);
        current_energy = previous_energy;

        bar();

        while (
            (current_it < max_iterations)
        and (current_temperature >= stop_temperature)
        and (current_energy >= min_energy)
        )
        {
            const State current_state = generate(state);
            current_energy = energy(current_state);

            if (metropolisCritieria(current_energy - previous_energy, current_temperature))
            {
                state = current_state;
                previous_energy = current_energy;

                // print<double, green>(*this);
                print(*this, Accepted{});

                current_temperature = temperature(current_temperature);
            }
            else
            {
                // print<double, red>(*this);
                print(*this, Rejected{});
            }
            

            ++current_it;
        }

        final_print(*this);
    }
};
