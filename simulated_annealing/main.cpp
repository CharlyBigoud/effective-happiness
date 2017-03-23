#include <iostream>
#include <cmath>
#include <vector>
#include <array>



struct RecuitSimule
{
    double start_temperature;
    double stop_temperature;
    int max_iterations;
    double acceptation_tolerance;

    double t;
    // double max_iterations_max_for_each;

    double random_value()
    {
        return ((double) std::rand() / (RAND_MAX));
    }

    RecuitSimule( double start_tmp = 1000, double stop_tmp = 0, double it_max = 1000, double tol = 0.1) :
      start_temperature(start_tmp)
    , stop_temperature(stop_tmp)
    , max_iterations(it_max)
    , acceptation_tolerance(tol)
    // , max_iterations_max_for_each(it_max) //pour lin'stnat on s'en fou
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

    double temperature(const int it) const { return double(it / max_iterations) * t; };

    template<typename Params, typename Error, typename Gen> void operator()(Error& energy, Params& state, Gen gen)
    {
        t = start_temperature;

        //previous_energy is initiated with initial state;
        double previous_energy = energy(state);

        int it = 0;
        while (
            (it < max_iterations)
        and (t >= stop_temperature)
        )
        {
            const Params current_state = gen(state);
            const double current_energy = energy(current_state);

            if (metropolisCritieria(current_energy - previous_energy, t))
            {
                state = current_state;
                previous_energy = current_energy;

                t = temperature(it);
            }

            ++it;
        }
    }

};



struct MesParametres
{

};

double ma_fonction_de_cout(MesParametres& )
{
    return 0;
}



struct Error
{
    double operator()(MesParametres p) const
    {
        return ma_fonction_de_cout(p);
    }
};

struct Gen
{
    MesParametres operator()(MesParametres const& m) const { return m; }
};

int main()
{
  {
    MesParametres x;
    Error f;
    RecuitSimule recuite;
    recuite(f,x,Gen());
  }

  {
    double x;
    auto f = [](double x){ return x*x; };
    auto gen = [](double x){ return x+0.1; };
    RecuitSimule recuite;
    recuite(f,x,gen);
  }

    RecuitSimule recuite(1000.0, 0.0, 10000.0, 10.0);
    double x = -100.0;
    auto f = [](double x){ return 5.0 * std::cos(0.25  * x) + x * (x / 750.); };
    auto gen = [](double x){ return x + 5.0*(((double) std::rand() / (RAND_MAX)) - 0.5); };
    std::cout << x << std::endl;
    recuite(f, x, gen);
    std::cout << x << " " << f(x) << std::endl;

    //RecuitSimule
    // std::cout << "faire schéma de refroidissment" << std::endl;
    // std::cout << "bug si les params sont égaux a zero" << std::endl;
    // std::cout << "bug si on optimize k et l" << std::endl;
    // std::cout << std::endl;

    // State simple_function{100.0, 1.0};
    // SimpleEnergy energy{simple_function};

    // SimulatedAnnealing<decltype(simple_function), SimpleEnergy> sa{
    //       simple_function
    //     , energy
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , int(1e4)
    //     , 1e3
    // };

    // std::cout << "simple_function: " << simple_function.x << std::endl;
    // sa.run();
    // std::cout << "simple_function: " << simple_function.x << " cost " << simple_function() << std::endl;
    // std::cout << std::endl;

    // SimpleFunction2 simple_function_2{
    //       5.0, 0.25, 750.0
    //     , -10.0
    //     , 1.0
    // };
    // SimpleEnergy2 energy2{simple_function_2};

    // SimulatedAnnealing<decltype(simple_function_2), SimpleEnergy2> sa3{
    //     simple_function_2
    //     , energy2
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , int(1e4)
    //     , int(1e3)
    // };

    // std::cout << "simple_function_2: " << simple_function_2.x << std::endl;
    // sa3.run();
    // std::cout << "simple_function_2: " << simple_function_2.x << std::endl;
    // std::cout << std::endl;

//////////////////////ROSENBROCK//////////////////////
    // State<Rosenbrock> rosenbrock{1.0, 100.0, 0.0, 0.0, 0.1};
    // SimulatedAnnealing<decltype(rosenbrock)> sa2{
    //     rosenbrock
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , 1e4
    //     , 1e3
    // };

    // std::cout << "Rosenbrock: (" << rosenbrock.f.x << ", " << rosenbrock.f.y << ")" << std::endl;
    // sa2.run();
    // std::cout << "Rosenbrock: (" << rosenbrock.f.x << ", " << rosenbrock.f.y << ")" << std::endl;
    // std::cout << std::endl;

//////////////////////Camera//////////////////////

    // // building reference
    // PinholeCameraModel reference_camera(50.0, 200.0, 200.0, 1.0, 1.0);
    // std::cout << "reference_camera:\n" << reference_camera << std::endl;

    // // computing model
    // Observations observations{
    //       {{1,2,50}, {3,4,50}, {5,6,50}, {7,8,50}, {9,10,50}, {11,12,50}, {13,14,50}, {15,16,50}, {17,18,50}}
    // };

    // observations.pixels.resize(observations.p3ds.size());
    // for (size_t i=0 ; i<observations.pixels.size() ; ++i)
    //     observations.pixels[i] = reference_camera.project(observations.p3ds[i]);

    // PinholeCameraModel to_optimize{1.0, 1.0, 1.0, 1.0, 1.0};
    // CameraState<PinholeCameraModel> camera_state{reference_camera, 1.1};

    // SimulatedAnnealing<decltype(camera_state), Energy> sa{
    //     camera_state
    //     , Energy{camera_state, observations}
    //     , CoolingSchedule{}
    //     , 10.0
    //     , 0.0
    //     , int(1e4)
    //     , 1e3
    // };

    // std::cout << "camera_to_optimize:\n" << camera_state.f << std::endl;
    // sa.run();
    // std::cout << "camera_to_optimize:\n" << camera_state.f << std::endl;


    return 0;
}
