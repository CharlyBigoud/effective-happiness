#include <cassert>

template<int I> struct Int { enum { value = I }; };

template<int I, int J> Int<I+J> operator+(Int<I>, Int<J>) { return {};}

int main()
{
    Int<1> i;
    Int<2> j;
    static_assert( decltype(i+j+i+j)::value == 6, "prout" );

    return 0;
}
