#include <iostream>
#include <vector>

struct Ray{};
using Rays = std::vector<Ray>;

// struct Box{
//     Rays rays;
//     size_t size;
// };

struct Container{
    size_t size;
    std::vector<Rays> boxes;

    Container(const size_t s = 0)
    : size(s)
    {}
};

struct LightField
{
    Container container; //a chaque camera une Box de rayons 

    LightField(const Container& c = Container(0))
    : container(c)
    {}

    ~LightField(){}

    template<typename Camera>
    void add(const Camera& c)
    {
    }

    template<typename Camera>
    void remove(const Camera& c)
    {
    }
};

struct Pose{};
struct Camera1{};
struct Camera2{};

int main()
{
    Camera1 cam1{};
    Camera2 cam2{};

    LightField lf;

    lf.add(cam1);
    lf.add(cam2);

    lf.remove(cam1);
    lf.remove(cam2);

    // lf.get_image();

    return 0;
}