
#include <vector>
#include <iostream>
typedef std::vector<int> Vector;
typedef std::vector<std::vector<int>> Vectors;

template<class F>
void repeat(F functor, int i, const Vectors& vectors, Vector n_uplet)
{
	if (i!=vectors.size())
		for(size_t j = 0 ; j < vectors[i].size() ; ++j)
		{
			n_uplet[i] = vectors[i][j];
			repeat(functor,i+1,vectors,n_uplet);
		}
	else
		functor(n_uplet);
}

template<class F>
void for_each_combinaison(F functor, const Vectors& vectors)
{
	repeat(functor,0,vectors,Vector(vectors.size(),0));
}

struct Disp {
	void operator()(const Vector& v) const {
	for(size_t i = 0 ; i < v.size() ; ++i)
		std::cout << v[i] << ",";
	std::cout << std::endl;
	}};

int main()
{
	Vectors w {{1,2},{3,4,5},{6,7,8,9}};
	for_each_combinaison(Disp(),w);
}
