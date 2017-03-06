#include <iostream>
#include <algorithm>
#include <vector>

typedef std::vector<int> Vector;

// template <typename T>
// void function(T& t)
void function(int& t)
{
	std::cout << "\n" << t;	
}

int main()
{
	Vector v {1,2,3,26,56};

	for_each(v.begin(), v.end(), function);
	// for_each(v.begin(), v.end(), [](const int truc){std::cout << "\n" << truc;});
}