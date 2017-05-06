#include <iostream>
#include <cmath>
#include <array>

struct LoopSet{
    const int start_value;
    const int pitch;
    const int end_value;

    //a chaque appel de fonction on avance d'un cran
    //si i et it dépassent la max_it, on reset it 
    //on recommence à faire avancer it
    int get(const int i)
    {
        if (
            i == 0
        or (i > max_it and it > max_it)
        )
            reset();

        return std::fma(pitch, it++, start_value);
    };

    void reset(){ it = 0; };

    const int max_it = (end_value - start_value) / pitch;
    int it = 0;
};

struct Box{
    LoopSet& ls_a;
    LoopSet& ls_b;

    std::array<int,2> get(const int i) const
    { 
        return {ls_a.get(i),
                ls_b.get(i)
                };
    }

    int end_value() const { return 20; }
};

struct Generator{
    const Box& b;
    int current;

    bool operator!=(const Generator& g) const { return g.current != current; }  
    void operator++(){ ++current; }
    std::array<int,2> operator*() const { return b.get(current); }
};

Generator begin(const Box& b){ return Generator{b, 0}; };
Generator end(const Box& b){ return Generator{b, b.end_value()}; };

int main()
{
    std::cout << "Using a set:" << std::endl;
    LoopSet set{0,1,10};
    LoopSet set2{0,2,20};
    std::cout << "set.max_it:" << set.max_it << "\n";
    std::cout << "set2.max_it:" << set2.max_it << "\n";

    for(int i=0 ; i<20; ++i)
    {
        std::cout << set.get(i) << "\t" << set2.get(i) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Using a box:" << std::endl;
    Box box{set, set2};
    for(int i=0 ; i<20; ++i)
    {
        std::array<int,2> vals = box.get(i);
        std::cout << vals[0] << "\t" << vals[1] << std::endl;
    }
    std::cout << std::endl;

    //NE FONCTIONNE PAS
    // for(int i=0 ; i<20; ++i)
    //     std::cout << box.get(i)[0] << "\t" << box.get(i)[1] << std::endl;

    std::cout << "Using a Generator:" << std::endl;
    for (auto c : Box{set,set2})
    {
        std::cout << c[0] << "\t" << c[1] << std::endl;
    }

    return 0;
}