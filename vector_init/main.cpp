#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

std::string generate_name()
{
	return std::string("Jean-Charles");
}

struct double_generator{
	double operator()()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::normal_distribution<> distribution(0,1);
		// return double(distribution);
		return double(distribution(gen));
	};
};

double generate_double()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distribution(0,1);

	return distribution(gen);
}

int main()
{
	//TEST1
	// std::string elt = "Datta";
	// std::vector<std::string> super_names (10, elt);
	// std::vector<std::string> super_names (10, generate_name());

	//TEST2
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distribution(0,1);

	auto generator_lamdba = [&](){
		return double(distribution(gen));
	};

	// std::vector<double> super_numbers (10, generator_lamdba()); //Ne fonctionne pas car le constructeur ne prend qu'une valeur
	
	//TEST3
	// std::vector<double> super_numbers2 (10);
	// std::generate(super_numbers2.begin(), super_numbers2.end(), double_generator());

	//TEST4
	std::vector<double> super_numbers3 (10);
	for(double& dbl : super_numbers3)
		dbl = generate_double();
	
	//DISPLAY
	for(auto& s : super_numbers3)
		std::cout << s << std::endl;

	return 0;
}