// https://fr.wikipedia.org/wiki/Recuit_simul%C3%A9

struct State
{
    State generate(){ return State{}; };
};

struct Model
{
};




struct SimulatedAnnealing
{
    Model model;
    State state;
    double temperature_min;
    int iterations_max;

    void run();
    double metropolis(const double, const double);

    double temperature;
};


double valeur_random()
{
    return double{};

}

double SimulatedAnnealing::metropolis(const double delta_E, const double temperature)
{
    return std::exp(- delta_E / temperature);
}


double calcul_energie(const Model model, const State state);

void SimulatedAnnealing::run()
{
    double energie_precedente;

    int it = 0;
    while (
        (temperature >= temperature_min)
    or  (it <= iterations_max)
    ) 
    {
        const State s_voisin = state.generate();

        double energie_courante = calcul_energie(this->model, s_voisin);

        //on accepte
        double delta_E = energie_courante - energie_precedente;
        if (
           (delta_E < 0)
        or (valeur_random() < metropolis(delta_E, temperature))
        ){
            state = s_voisin;
            energie_precedente = energie_courante;
        }
        else
        {
            //rien du tout
        }

        ++it;
    }
};