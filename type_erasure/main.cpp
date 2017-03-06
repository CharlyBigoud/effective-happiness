
// type erasure
// boost::any/variant

#include <tuple>
#include <vector>
#include <iostream>
#include <string>

struct Base
{
  virtual void disp() = 0;
};


template<typename T> struct Box : Base
{
  Box(T t_):t(t_){}
  T t;
  void disp() {  }
};

template<typename T> Box<T>* create_box(T t)
{
  Box<T> * box = new Box<T>(t);
  return box;
}

struct ContainerMagique
{

  Base * ptr;

  template<typename A>
  void set(A a)
  {
    ptr = create_box<A>(a);
  }

  template<typename A>
  A get()
  {
    return static_cast< Box<A>* >(ptr)->t;
  }

};

int main()
{
  ContainerMagique cm;

  cm.set(3);
  std::cout << " int : " << cm.get<int>() << std::endl;

  cm.set(std::string("Charly"));
  std::cout << " str : " << cm.get<std::string>() << std::endl;

  cm.set(std::vector<int>{1,2,3});
  cm.get<std::vector<int>>();

  cm.set(1.2);
  std::cout << " double : " << cm.get<double>() << std::endl;
}

