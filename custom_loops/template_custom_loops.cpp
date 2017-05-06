#include <iostream>
#include <cmath>
#include <array>
#include <ratio>

template<typename ...> struct List{ size_t size;};

template<typename T> T iterate(List<>){}; 

template<typename S, typename A, typename ... T> S iterate(List<A,T...>)
{
    // A{}.reset();

    iterate<S>(List<T...>{});
}

template<int START, int PITCH, int END>
struct LoopSet{
    int get(const int i)
    {
        if (
            i == 0
        or (i > max_it and it > max_it)
        )
            reset();

        return std::fma(PITCH, it++, START);
    };

    void reset(){ it = 0; };

    const int max_it = (END - START) / PITCH;
    // const int max_it = std::ratio<END - START, PITCH>;
    int it = 0;
};

template<int N, typename Set1, typename Set2>
struct Box{
    // List<A,B> list;
    Set1 set1;
    Set2 set2;

    std::array<int,N> get(const int i)
    { 
        return {set1.get(i),
                set2.get(i)
                };
    }

    int end_value() const { return 20; }
};

template<int N, typename Set1, typename Set2>
struct Generator{
    Box<N, Set1, Set2> b;
    int current;

    bool operator!=(const Generator<N, Set1, Set2>& g) const { return g.current != current; }  
    void operator++(){ ++current; }
    std::array<int,N> operator*() { return b.get(current); }
};

template<int N, typename Set1, typename Set2>
Generator<N, Set1, Set2> begin(const Box<N, Set1, Set2>& b){ return Generator<N, Set1, Set2>{b, 0}; };
template<int N, typename Set1, typename Set2>
Generator<N, Set1, Set2> end(const Box<N, Set1, Set2>& b){ return Generator<N, Set1, Set2>{b, b.end_value()}; };

int main()
{
    std::cout << "Using a set:" << std::endl;
    LoopSet<0,1,10> set{};
    LoopSet<0,2,20> set2{};
    for(int i=0 ; i<20; ++i)
    {
        std::cout << set.get(i) << "\t" << set2.get(i) << std::endl;
    }
    std::cout << std::endl;

    List<
        LoopSet<0,1,10>,
        LoopSet<0,2,20>
        > {3};

    std::cout << "Using a box:" << std::endl;
    Box<2,
        LoopSet<0,1,10>,
        LoopSet<0,2,20>
        > box{};

    for(int i=0 ; i<20; ++i)
    {
        auto vals = box.get(i);
        std::cout << vals[0] << "\t" << vals[1] << std::endl;
    }
    std::cout << std::endl;

    //NE FONCTIONNE PAS
    // for(int i=0 ; i<20; ++i)
    //     std::cout << box.get(i)[0] << "\t" << box.get(i)[1] << std::endl;

    std::cout << "Using a Generator:" << std::endl;
    for (auto c : Box<2, LoopSet<0,1,10>, LoopSet<0,2,20>>{})
    {
        std::cout << c[0] << "\t" << c[1] << std::endl;
    }

    return 0;
}