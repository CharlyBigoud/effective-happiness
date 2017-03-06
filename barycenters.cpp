#include <vector>
#include <iostream>
#include <functional>
#include <numeric>

template<typename A, typename B> struct Tuple{A a; B b; };


template<typename T> struct Point
{
    T x, y;

    void operator=(const Point& p){x=p.x; y=p.y;};
    void operator+=(const Point& p){x+=p.x; y+=p.y;};

    Point operator+(const Point& p) const {return {x+p.x, y+p.y}; };
    Point operator/(const T a) const { return {x/a, y/a}; };
};


template<typename T>
std::ostream& operator<<(std::ostream& o, const Point<T>& p)
{
    o << p.x << ", " << p.y;
    return o;
}

template<typename T> struct Point3D
{
    T x, y, z;

    void operator=(const Point3D& p){x=p.x; y=p.y; z=p.z;};
    void operator+=(const Point3D& p){x+=p.x; y+=p.y; z+=p.z;};

    Point3D operator+(const Point3D& p) const {return {x+p.x, y+p.y, z+p.z}; };
    Point3D operator/(const T a) const { return {x/a, y/a, z/a}; };
};

template<typename T>
std::ostream& operator<<(std::ostream& o, const Point3D<T>& p)
{
    o << p.x << ", " << p.y << ", " << p.z;
    return o;
}

/////////////////////////////////////////////////la base//////////////////////////////////////////////////////////////////
template<typename T>
T get_barycenter(const std::vector<T>& boite)
{
    T t = T();

    for (auto& b : boite)
        t += b;

    return t / boite.size();
}

/////////////////////////////////////////////////avec iterators//////////////////////////////////////////////////////////////////

// typename A sinon ça marchera pas avec des vecteurs alignés qui n'utilies pas l'allocateur par défaut
// template<typename T, typename A> T get(std::vector<T,A>::iterator);
// template<typename T, typename A> T get(std::vector<T,A>::iterator it) { return *it; }

template<typename Iterator> auto get(Iterator it) { return *it;}

//idem
// template<typename T> Point<T> const& get(Point<T> const& p) { return p; }
template<typename T> const Point<T>& get(const Point<T>& p) { return p; }

template<typename I, typename Value>
Value sum(I start, I end, Value init_value)
{
  for (I current = start; current != end; current = next(current))
    init_value += get(current); // ça marche mais je suis pas sûr qu'il y ait un intérêt
    // init_value += *current;

  return init_value;
}

template<typename I, typename Value>
Value get_barycenter_with_iterator(I start, I end, Value init_value)
{
  return sum(start, end, init_value) / std::distance(start,end);
}

/////////////////////////////////////////////////avec accesseur custom//////////////////////////////////////////////////////////////////
template<typename I, typename Value, typename Acc>
Value sum(I start, I end, Value init_value, Acc get)
{
  for (I current = start; current != end; current = next(current))
    init_value += get(current);

  return init_value;
}

template<typename I, typename Value, typename Acc>
Value get_barycenter_with_accessor(I start, I end, Value init_value, Acc get)
{
    // return sum(start, end, init_value, get) / std::distance(start,end);
    return std::accumulate(start, end, init_value, [get](const Value& prev, const auto& t){ return prev + get(t); }) / std::distance(start,end);
}

// template<typename T, typename Acc>
// auto get_barycenter_with_accessor(const T& truc, Acc get)
// {
//     decltype(get());
//     // return get_barycenter_with_accessor(begin(truc), end(truc), decltype(get), get);


//     return get_barycenter_with_accessor(begin(truc), end(truc), get(begin(T{})), get);

//     // const static T t{};
//     // return get_barycenter_with_accessor(begin(truc), end(truc), get(begin(t)), get);
// }

template<typename T, typename Value, typename Acc> Value get_barycenter_with_accessor(const T& truc, Value init, Acc get){ return get_barycenter_with_accessor(begin(truc), end(truc), init, get); }

int main()
{
    std::vector<Point<double>> des_points {{0,0}, {1,1}, {2,2}, {0,0}, {0,0}, {1,1}, {2,2}};

    std::cout << "bary_white: " << get_barycenter(des_points) << std::endl;
    std::cout << "bary_whITe: " << get_barycenter_with_iterator(begin(des_points), end(des_points), Point<double>{}) << std::endl;

    std::vector<Tuple<int, Point<double>>> machin {
        {1, {0,0}},
        {1, {0,0}},
        {1, {0,0}},
        {1, {1,1}},
        {1, {1,1}},
        {1, {2,2}},
        {1, {2,2}}
    };

    // std::cout << "bary_prout: " << get_barycenter_with_accessor(begin(machin), end(machin), Point<double>{}, [](const auto& t){return t->b;}) << std::endl;

    // get_barycenter_with_accessor(machin, [](const auto& t){ return t->b; }, Point<double>{15,15});
    // std::cout << "bary_prout test: " << get_barycenter_with_accessor(machin, [](const auto& t){ return t->b; }) << std::endl;

    std::cout << "bary_prout test: " << get_barycenter_with_accessor(machin, Point<double>{}, [](const auto& t){ return t.b; }) << std::endl;

    std::vector<Point3D<double>> p3ds {{0,0,12}, {1,1,5}, {2,2,12}, {0,0,12}, {0,0,145.4}, {1,1,12}, {2,2,12}};
    std::cout << "bary_prout test: " << get_barycenter_with_accessor(p3ds, Point3D<double>{}, [](const auto& t){ return t; }) << std::endl;


    return 0;
}