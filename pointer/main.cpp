#include <iostream>
#include <memory>

struct Tomate{};

struct Caisse{

	std::unique_ptr<Tomate> mon_pointeur;

	// Caisse():mon_pointeur(new Tomate){};
	Caisse(){ mon_pointeur.reset(new Tomate); };
	
	~Caisse(){};
};

int main()
{
	Caisse c;
	Tomate t;

	// std::unique_ptr<Tomate> mon_pointeur_dans_le_main (new Tomate);

	c.mon_pointeur.reset(new Tomate);

	return 0;
}