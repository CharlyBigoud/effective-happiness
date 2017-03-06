#include <iostream>

template <typename A>
A temp_fun()
{
	return 5.12;
}

template <typename B>
B temp_fun2()
{
	temp_fun<B>();
}

template <typename E>
E temp_fun3(E e)
{
	return e;
}

struct Structure
{
	int struc_fun()
	{
		return 7.12;
	}

	template <typename A>
	A templ_fun()
	{
		return 7.12;
	}
	
	template <typename A>
	void another_fun(int a, int b){
		std::cout << a+b << std::endl;
	};
};

int main()
{
	// std::cout << temp_fun<int>() << std::endl;
	// std::cout << temp_fun<float>() << std::endl;

	// std::cout << temp_fun2<int>() << std::endl;
	// std::cout << temp_fun2<float>() << std::endl;

	// Structure jean;
	// std::cout << jean.struc_fun() << std::endl;
	// std::cout << jean.templ_fun<float>() << std::endl;

	float n=1.02;
	std::cout << temp_fun3(n) << std::endl;

	Structure s;
	s.another_fun<double>(1,4);

	return 0;
}