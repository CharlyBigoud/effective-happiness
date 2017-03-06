#include <iostream>

double recursiveFunction(const int& number)
{
	if(number < 1)
		return 1;

	double value;
	return value = 1 + recursiveFunction(number-1);
}


int main(int argc, char const *argv[])
{
	auto recursiveLambda = [](const int& number)
	{
		if(number < 1)
			return 1;

		double value;
		return value = 1 + recursiveLambda(number-1);
	};

	double result = recursiveLambda(4);
	// double result = recursiveFunction(4);
	
	std::cout<<"result = "<<result<<std::endl;

	return 0;
}