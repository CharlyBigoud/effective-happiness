#include <iostream>
// #include <concepts>

struct List{  int i; };

// template<int A, int ... T>
// std::ostream& operator<<(std::ostream o, List<A, T...>)
// {
//     // o << 42;
//     return o;
// }

// template<typename T>
// T sum(const T array[], T n)
// {
//   T result = 0;
//   for (int i = 0; i<n; ++i)
//     result = result + array[i];
//   return result;
// }

template<std::CopyConstructible T>
T sum(T array[], int n)
{
  T result = 0;
  for (int i = 0; i < n; ++i)
    result = result + array[i];
  return result;
}

int main()
{
  int values[3] = {1, 2, 3};
  for(int i=0; i<3; ++i)
    std::cout << values[i] << ", ";
  std::cout << std::endl;

  auto s = sum(values, 3);
    std::cout << s << std::endl;

  List list[3] = { {1}, {2}, {3} };
  std::cout << list;
  // for(int i=0; i<3; ++i)
  //   std::cout << list[i] << ", ";
  std::cout << std::endl;

  return 0;
}