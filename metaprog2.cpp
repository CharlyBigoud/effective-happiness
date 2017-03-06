#include <iostream>

/*
 * @Brief display each number between N (see f(Int<N>{});) and 10 then stops
*/

template<int I> struct F
{
	F(){std::cout << " I = " << I << std::endl; F<I+1>();}
};

template<> struct F<10>{ F(){std::cout << " charly " << std::endl;}};

template<int I> struct Int{};

template<int I> void f(Int<I>)
{
	std::cout << " I = " << I << std::endl;
	f(Int<I+1>{});
}

void f(Int<10>)
{
	std::cout << " je m'arrête " << std::endl;
}


constexpr void g(int i)
{
	// std::cout << " i : " << i << std::endl;
	if (i < 10)
		g(i+1);
}

 int main()
 {
 	f(Int<0>{});

 	g(0);
 	return 0;
 }

