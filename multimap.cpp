#include <iostream>
#include <vector>
#include <map>

struct Point{
    int group_id;
    int x;
    int y;
};

struct PointCmp {
    bool operator()(const Point& lhs, const Point& rhs) const { 
        return lhs.group_id < rhs.group_id; // NB. ignores y on purpose
    }
};

int main()
{
    // setting my data
    std::vector<Point> points (10);

    int c = 0;
    int gid = 0;
    bool change_group = true;
    for (auto& p : points)
    {
        p.group_id = gid;
        p.x = c;
        p.y = c;
        ++c;

        if (c > 4 and change_group)
        {
            c += 10;
            ++gid;
            change_group = false;
        }

        std::cout << p.group_id << ": " << p.x << ", " << p.y << std::endl;
    }

    std::multimap<Point, int, PointCmp> map;
    map.insert(points[0]);

    return 0;
}
