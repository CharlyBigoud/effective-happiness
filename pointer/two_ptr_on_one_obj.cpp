#include <iostream>
#include <memory>

struct Truc
{
    int a;
};

int main()
{
    Truc t{42};
    std::cout << t.a << std::endl;

    std::unique_ptr<Truc> t_ptr (t);
    std::cout << t_ptr->a << std::endl;

    // std::unique_ptr<Truc> t_ptr (new decltype(t));
    // std::cout << t_ptr->a << std::endl;

    // std::unique_ptr<Truc> t_ptr2 (new Truc{});
    // std::cout << t_ptr2->a << std::endl;

    // std::unique_ptr<Truc> t_ptr3 ();
    // std::cout << t_ptr3->a << std::endl;

    return 0;
}