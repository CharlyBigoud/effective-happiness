#include <iostream>
#include <vector>
#include <cassert>

namespace std
{
    template<class T, class Compare>
    constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp )
    {
        return assert( !comp(hi, lo) ),
            comp(v, lo) ? lo : comp(hi, v) ? hi : v;
    }

    template<class T>
    constexpr const T& clamp( const T& v, const T& lo, const T& hi )
    {
        // return clamp( v, lo, hi, std::greater<>() );
        return clamp( v, lo, hi, std::less<>() );
    }
}

int main()
{
    // std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};

    std::cout << "value: " << std::clamp(5, 1, 10) << std::endl;
    return 0;
}
