
#include <vector>
#include <iostream>
typedef std::vector<double> Vector;

template <typename T>
class Ray
{
public:
	std::vector<T> origin {0,0,0};
	std::vector<T> direction {0,0,0};

	//Constructor
	Ray(const std::vector<T>& origin = {0,0,0},	const std::vector<T>& direction = {0,0,0})
	: origin(origin), direction(direction)
	{}

	void operator=(Ray ray)
	{
		origin = ray.origin; 
		direction = ray.direction; 
	}
};

typedef std::vector<Ray<double>> Rays;



template<class F>
void repeat(F functor, int i, const Rays& rays, Ray<double> n_uplet)
{
	if(i != rays.size())
	{
		for()
		{
			std::cout << "i = " << i << "\n";
			n_uplet = rays[i];
			repeat(functor, i+1, rays, n_uplet);
		}
	}
	else
		functor(rays[0]);
}

template<class F>
void for_each_combinaison(F functor, const Rays& rays)
{
	repeat(functor, 0, rays, Ray<double>());
}

struct Disp {
	void operator()(const Ray<double>& r) const {
		std::cout << "origin = (" << r.origin.at(0) << ", " << r.origin.at(1) << ", " << r.origin.at(2) << ")\n";
		std::cout << "direction = (" << r.direction.at(0) << ", " << r.direction.at(1) << ", " << r.direction.at(2) << ")\n";
	}};

int main()
{
	Ray<double> ray0({1,1,1},{2,2,2});
	Ray<double> ray1;
	Rays rays;
	rays.push_back(ray0);
	rays.push_back(ray1);

	for_each_combinaison(Disp(), rays);
}
