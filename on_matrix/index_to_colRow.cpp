#include <iostream>
#include <array>
#include <cmath>

std::array<int,2> index_to_colRow(const int matrix_width, const int index)
{
	std::array<int,2> coords;



	double tmp = (double)index / (double)matrix_width;
	if(tmp < 1.0)
	{
		coords[0] = index;
		coords[1] = 0;
	}
	else
	{
		coords[0] = index - (matrix_width*std::floor(tmp));
		coords[1] = std::floor(tmp);
	}
// 
	// int tmp = index / matrix_width;
	// if(tmp < 1)
	// {
		// coords[0] = index;
		// coords[1] = 0;
	// }
	// else
	// {
		// coords[0] = index - (matrix_width*tmp);
		// coords[1] = tmp;
	// }


	return coords;
}

int main()
{

	// std::array<int,2> myCoords = index_to_colRow(5, 78471);
	// std::cout << "(" << myCoords[0] << "," << myCoords[1] << ")" << std::endl;

	// int a = 15;
	// int b = 12;

	double a = 15;
	double b = 12;

	int c = a / b; 
	std::cout << "c = " << c << std::endl;

	return 0;
}
