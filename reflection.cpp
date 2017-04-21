#include <iostream>
#include <type_traits>

template <class T, class U> concept bool Derived = std::is_base_of<U, T>::value;

class Mother
{
public:
    Mother(){};
    virtual ~Mother(){};

    virtual void f(int i) = 0;
};

class Son
{
public:
    Son(){};
    virtual ~Son(){};

    void f(int i){};
};

class Daugther : public Mother
{
public:
    Daugther(){};
    virtual ~Daugther(){};

    void f(int i){};
};

void methode(const Derived<Mother>& desc){}

int main()
{
    Daugther d;
    Son s;

    //a l'execution
    std::cout << "Value: " << std::is_base_of<Mother, decltype(d)>::value << std::endl;
    std::cout << "Value: " << std::is_base_of<Mother, decltype(s)>::value << std::endl;

    methode(d);
    methode(s);

    return 0;
}
