#include <iostream>
#include <vector>
#include <any>

struct Type{};

std::iostream& operator<<(std::iostream& o, const Type& t){ o << "excellent!";}

int main()
{
    std::vector<std::any> v (0);

    v.push_back( int() );
    v.push_back( double() );
    v.push_back( std::string() );
    v.push_back( Type{} );

    // for (auto& a : v)
    //     std::cout << a << std::endl;

    std::any a;
    // a = double(0.42);
    a = int(42);

    // float i = std::any_cast<float>(a); //securisé
    // std::cout << i << std::endl;
    
    float i = std::any_cast<int>(a); //securisé
    std::cout << i << std::endl;

    // int i = std::any_cast<int>(a); //securisé
    // std::cout << i << std::endl;

    // int i2 = std::any_cast<double>(a); //securisé
    // std::cout << i2 << std::endl;

    return 0;
}