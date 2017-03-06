#include <libv/lma/lma.hpp>
// #include <plein d'autres trucs>

struct StructFunctor{
	bool operator()(double x, double y, double& r) const
	{
		r = x*x + 100.*(y - x*x)*(y - x*x);
		return true;
	}
};

int main()
{
	auto lamdba_functor = [&](double x, double y, double& r){ r = x*x + 100.*(y - x*x)*(y - x*x); return true; };

	// Initial solution
	double x[2] ={-1,-1};
	std::cout << " Initial parameters   : (" << x[0] << "," << x[1] << ") " <<  std::endl;

	lma::Solver<decltype(lamdba_functor)>()
	.add(lamdba_functor,&x[0],&x[1])
	.solve(lma::DENSE, lma::enable_verbose_output());

	// lma::Solver<StructFunctor>()
	// .add(StructFunctor(),&x[0],&x[1])
	// .solve(lma::DENSE, lma::enable_verbose_output());

	std::cout << " Optimized parameters : (" << x[0] << "," << x[1] << ") " <<  std::endl;
	return EXIT_SUCCESS;
}
