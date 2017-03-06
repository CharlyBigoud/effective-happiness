#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

using Farthest = std::greater<void>;
using Nearest = std::less<void>;

template<typename T> struct P2{
    T x, y;

    auto operator-(P2<T> p) const { return P2<T>{this->x - p.x, this->y - p.y}; };

    T norm() const { return std::hypot(x,y); };
};

template<typename T>
std::ostream& operator<<(std::ostream& o, P2<T> p){    o << "{" << p.x << ", " << p.y << "}";    };

template<typename T> using P2S = std::vector<P2<T>>;

template<int I> struct Int { static const int value = I; };

template<typename F, typename T>
auto findNeighbors(
    P2S<T> group //par copie car on veux pas vraiment toucher au classement
    , const P2<T>& point
    , auto neihbors_nbr
    , F f = F()
    )
{
    if (decltype(neihbors_nbr)::value > group.size())
        throw std::out_of_range("findNeighbors: you have asked too much neihbors.");

    //On trouve les trois plus proches voisin de point
    std::array<P2<T>, decltype(neihbors_nbr)::value> voisins;

    auto comparison_law = [&](const auto& t1, const auto& t2){
        double d1 = (t1 - point).norm();
        double d2 = (t2 - point).norm();
        return f(d1, d2);// ou f((t1 - point).norm(),(t2 - point).norm());
    };

    //on fait un nth_element: le tableau est séparé à la grosse
    std::nth_element(begin(group), begin(group) + voisins.size(), end(group), comparison_law);

    //on sort le vecteur en fonction de la distance de chaque elt de group / point
    std::sort(begin(group), begin(group) + voisins.size(), comparison_law);

    //a présent on récupère les voisins on piochant directement dans le vecteur
    std::copy(begin(group), begin(group)+voisins.size(), begin(voisins));

    return voisins;
};

int main()
{
    P2<double> p {10,10};
    P2S<double> ps {{0,10},{1,11},{2,12},{3,13},{4,14},{5,15},{6,16},{7,17},{8,18},{9,19},{10,20}};

    auto result = findNeighbors<Nearest>(ps, p, Int<5>{});
    std::cout << "Nearest neihbors:" << std::endl;
    for (auto& p : result)
        std::cout << p << std::endl;

    auto result2 = findNeighbors<Farthest>(ps, p, Int<10>{});
    std::cout << "Farthest neihbors:" << std::endl;
    for (auto& p : result2)
        std::cout << p << std::endl;

    return 0;
}