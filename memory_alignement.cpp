#include <iostream>
#include <cassert>
#include <array>

template<typename T, std::size_t S>
struct AlignedArray{
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data[S];
    std::size_t m_size = 0;

    // AlignedArray(const T& ... t)
    // {

    // }

    // Delete objects from aligned storage
    ~AlignedArray()
    {
        for (std::size_t i = 0; i < m_size; ++i)
            reinterpret_cast<T*>(data + i)->~T();
    }

          T& operator[](const std::size_t i)       {  assert(S>i);  return *reinterpret_cast<      T*>(data + i);   }
    const T& operator[](const std::size_t i) const {  assert(S>i);  return *reinterpret_cast<const T*>(data + i);   }
};

// template<int DIMENSION> NodeGenerator<DIMENSION> begin(const GridMesh<DIMENSION>& gm){return NodeGenerator<DIMENSION>{gm, 0}; };
// template<int DIMENSION> NodeGenerator<DIMENSION> end(const GridMesh<DIMENSION>& gm){return NodeGenerator<DIMENSION>{gm, gm.nodeNbr()}; };

template<typename T, std::size_t S>
std::ostream& operator<<(std::ostream& o, const AlignedArray<T,S>& array)
{
    // for (auto& a : array)
    //     o << a;

    for (size_t i = 0; i<S; ++i)
        o << array[i] << ", ";

    return o;
}


int main()
{
    AlignedArray<int, 4> a;
    std::cout << a << std::endl;

    a[0] = 45;
    a[1] = 10;
    a[2] = 20;
    a[3] = 30;
    std::cout << a << std::endl;

    // AlignedArray<int, 4> b{1,2,3,4};
    // std::cout << b << std::endl;

    // AlignedArray<int, 4> c(1,2,3,4);
    // std::cout << c << std::endl;

    return 0;
}