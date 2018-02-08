#include <iostream>
#include <memory>
#include <vector>

// //version normal
// struct Tomate{
//     std::string color;
// };

// struct Caisse{
//     std::vector<Tomate*> tomates;
// };

// std::ostream& operator<<(std::ostream& o, const Caisse& c)
// {
//     o << "Une caisse de tomates ";

//     for (auto& t : c.tomates)
//         o << t->color << ", ";

//     return o;
// }

//version heritage
struct Fruit{
    const std::string n;
    std::string c;

    virtual const std::string& name() = 0;
    virtual       std::string& color() = 0;
};

struct Pomme : virtual public Fruit
{
    const std::string n = "pomme";
    std::string c;

    const std::string& name(){ return n; };
          std::string& color(){ return c; };
};

struct Poire : virtual public Fruit
{
    const std::string n = "poire";
    std::string c;

    const std::string& name(){ return n; };
          std::string& color(){ return c; };
};

struct Sac{
    std::vector<Fruit*> fruits;
};

std::ostream& operator<<(std::ostream& o, const Sac& s)
{
    o << "Mon sac contient ";

    for (auto& f : s.fruits)
        o << "un(e) " << f->name() << f->color() << ", ";

    return o;
}

int main()
{
    // // Caisse
    // Tomate tomate0;
    // std::cout << "Une tomate " << tomate0.color << std::endl;

    // Caisse caisse;
    // caisse.tomates.push_back(&tomate0);
    // std::cout << caisse << std::endl;
    
    // tomate0.color = "rouge";
    // std::cout << "Une tomate " << tomate0.color << std::endl;

    // Tomate tomate1;
    // tomate1.color = "verte";
    // std::cout << "Une tomate " << tomate1.color << std::endl;

    // caisse.tomates.push_back(&tomate1);
    // std::cout << caisse << std::endl;

    // caisse.tomates[0]->color = "jaune";
    // std::cout << "Une tomate " << tomate0.color << std::endl;
    // std::cout << caisse << std::endl;

    // Sac
    Sac sac;
    std::cout << sac << std::endl;

    Pomme pomme;
    sac.fruits.push_back(&pomme);
    std::cout << sac << std::endl;

    Poire poire;
    sac.fruits.push_back(&poire);
    std::cout << sac << std::endl;
  
    return 0;
}
