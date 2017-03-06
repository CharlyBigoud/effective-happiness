#include <iostream>
#include <vector>

void dipslay(const std::string& s){std::cout << s << "!" << std::endl;};

struct Display 
{
	const int& monNombre;
	void operator()(const std::string& s, const int truc){
		std::cout << s  << " a " << monNombre <<" ans !!";
		std::cout   << " ou " << truc <<" ans !!" << std::endl;
	};
};

template <typename T>
struct monFunctor
{
	void operator()(const std::vector<T>& v)
	{
		for(auto& i : v)
			std::cout << i << std::endl;
	};
};

int main()
{
	// std::string name = "Tawsif";

	// std::cout << name << std::endl;
	// dipslay(name);
	// Display{32}(name, 4);

	std::vector<int> monVector {0,1,2,3,4};
	std::vector<double> monVector2 {01.15,11.15,21.15,321.15,41.4};
	
	// for(auto& v : monVector)
		// std::cout << v << std::endl;

	monFunctor<int>{}(monVector);
	monFunctor<double>{}(monVector2);

	// monFunctor f;
	// f(monVector);
	// f(monVector2);

	return 0;
}