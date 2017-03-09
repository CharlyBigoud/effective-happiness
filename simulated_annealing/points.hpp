#include <iostream>

struct P2D{ double x, y; };
struct P3D{ double x, y, z; };

using P2DS = std::vector<P2D>;
using P3DS = std::vector<P3D>;

std::ostream& operator<<(std::ostream& o, const P2D& p)
{
    o << "{" << p.x << ", " << p.y << "}";
    return o;
}

std::ostream& operator<<(std::ostream& o, const P3D& p)
{
    o << "{" << p.x << ", " << p.y << ", " << p.z << "}";
    return o;
}

