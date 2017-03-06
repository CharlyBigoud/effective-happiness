#include <iostream>

struct Box
{
	int val;
	Box(int i):val(i){};
	virtual ~Box(){};
};

void getVal(const Box& b){
	std::cout << "val: " << b.val << std::endl;

};

int main()
{
	std::cout << "youpi !" << std::endl;

	Box	b(15);
	getVal(b);

	getVal( Box(12) );

	return 0;
}
