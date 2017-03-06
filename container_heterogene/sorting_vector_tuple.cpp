#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

template<int M, template<typename> class F = std::less>
struct TupleCompare
{
    template<typename T>
    bool operator()(T const &t1, T const &t2)
    {
        return F<typename std::tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2));
    }
};

int main()
{
    std::vector< std::tuple<int, std::string> > v;
    v.push_back( std::make_tuple(1, "Hello") );
    v.push_back( std::make_tuple(2, "Aha") );
    v.push_back( std::make_tuple(14, "HJzen") );
    v.push_back( std::make_tuple(5, "dfo") );

    std::sort( begin(v), end(v), TupleCompare<0>() );
    std::cout << "Old school: " << std::endl;
    for(auto& p : v)    std::cout << std::get<0>(p) << std::endl;

        std::cout << "Using lamdba: " << std::endl;
    std::sort(begin(v), end(v), [](auto const &t1, auto const &t2) {return std::get<0>(t1) > std::get<0>(t2);});
    for(auto& p : v)    std::cout << std::get<0>(p) << std::endl;

    return 0;
}