#include <tuple>
#include <vector>
#include <iostream>
#include <string>


struct _{};
void show_types(_){}

// template<typename ... L> => ... designe une liste de types
template<typename ... L> struct SDD
{
  //std::tuple<L...> => contient une liste de types
  using Tuple = std::tuple<std::vector<L>...>;
  Tuple tuple;

  template<typename X>
  SDD& add(X x)
  {
    get<X>().push_back(x);
    return *this;
  }

  template<typename X>
  std::vector<X>& get()
  {
    return std::get<std::vector<X>>(tuple);
  }


  template<typename X>
  X& get(int i)
  {
    return get<X>().at(i);
  }

};

int main()
{

  SDD<int,double,char,std::string> sdd;

  sdd.add(1).add(1.0).add('c').add(std::string("Charly"));
  sdd.add(std::string("&"));
  sdd.add(std::string("Jérémy"));

  std::cout << " int : " << sdd.get<int>(0) << std::endl;
  std::cout << " str : " << sdd.get<std::string>(0) << " " << sdd.get<std::string>(1) << " " << sdd.get<std::string>(2) << std::endl;

  show_types(sdd.tuple);
}

