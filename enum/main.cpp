#include "header.hpp"

class A{
public:
	A(){};
	~A(){};

	enum Myenum{
		SUCCESS = 0,
		FAIL = 1
	};
};

int main()
{
	A a;
	A::Myenum em;
	nspc::autreEnum em2;

	em2 = nspc::SUCCESS;

	return 0;
}