#include <iostream>
#include <thread>
#include <exception>

void hello(){ int i; while (++i < 10) std::cout << "Hello ("<< i << ")" << std::endl; }
void salut(){ int i; while (++i < 100) std::cout << "\tSalut ("<< i << ")" << std::endl; }

struct Caca{
    int a;

    Caca(){ a = 42; std::cout << "je suis un caca" << std::endl; }

    void operator()(){ std::cout << "j'ai " << a << " caca(s)." << std::endl;}
};

int main()
{
    std::thread t_struct(Caca);
    std::thread t1(hello);
    std::thread t2(salut);
    std::thread t_lambda([](){ int i; while (++i < 1000) std::cout << "\t\tPROUT ("<< i << ")" << std::endl;});

    // t1.join();
    // t2.join();
    // t_lambda.join();

    Caca c;
    c();

    std::terminate();

    return 0;
}
