usage

//using struct
    {
        struct MesParametres{};

        double ma_fonction_de_cout(MesParametres& ){ return 0; }

        struct Error{
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
            MesParametres x;
            Error f;
            RecuitSimule recuite;
            recuite(f,x,Gen());
        }
    }

//using lambda
    {
        double x;
        auto f = [](double x){ return x*x; };
        auto gen = [](double x){ return x+0.1; };
        RecuitSimule recuite;
        recuite(f,x,gen);
    }