#include <iostream>
#include <vector>

template<typename T>
struct Type1
{
    int width, height;
    std::vector<std::vector<T>> data;

    Type1(const int w, const int h)
    : width(w), height(h)
    {
        data.resize(height);

        for(auto& d : data)
        {
            d.resize(width);
            d.assign(width, 0.);
        }
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& o, const Type1<T>& t)
{
    for(auto& dh : t.data)
    {
        for(auto& dw : dh)
            o << dw << "\t";
        o << "\n";
    }

    return o;
}


// struct True{ constexpr static bool value = true; };
// struct False{ constexpr static bool value = false; };
// template<typename A> True is_same(A,A){}
// template<typename A, typename B> False is_same(A,B){}

enum Type{
    NONE = -1,
    T2_8U = 0,
    T2_64F = 1
};

template<typename T>
struct Type2 {
    int height, width;
    Type type;

    std::vector<std::vector<T>> data;

    Type2(const int h = 0, const int w = 0, Type t = NONE, const T& v = 0)
    : height(h), width(w), type(t)
    {
        data.resize(height);

        for(auto& d : data)
        {
            d.resize(width);
            d.assign(width, v);
        }
    }

    // template<typename T> const T& at(const int row, const int col) const { return T(data.at(row).at(col)); }
    // template<typename T>       T& at(const int row, const int col)       { return T(data.at(row).at(col)); }
    // template<typename T> const T& at(const int row, const int col) const { static_assert( same_type<decltype(data), T>::value, ""); return data.at(row).at(col); }
    template<typename A> A  at(const int row, const int col) const { return A(data.at(row).at(col)); }
                         T& at(const int row, const int col)       { return data.at(row).at(col); }
};

// template<typename T>
// std::ostream& operator<<(std::ostream& o, const Type2<T>& t)
// // std::ostream& operator<<(std::ostream& o, const Type2<double>& t)
// {
//     for (int row = 0; row < t.height; ++row)
//     {
//         for (int col = 0; col < t.width; ++col)
//         {
//             // o << t.at<double>(row,col) << "\t";
//             // o << t.at<T>(row,col) << "\t";
//         }
//         o << "\n";
//     }

//     return o;
// }

template<typename T>
std::ostream& operator<<(std::ostream& o, const Type2<double>& t)
{
    T machin;
    for (int row = 0; row < t.height; ++row)
    {
        for (int col = 0; col < t.width; ++col)
        {
            o << t.at<double>(row,col) << "\t";
        }
        o << "\n";
    }

    return o;
}

void ma_fonction(){}

int main()
{
    Type1<double> t1(10, 10);
    std::cout << "t1:\n" << t1 << std::endl;

    Type2<double> t2(10, 10, T2_64F, 12.34);
    // std::cout << "t2:\n" << t2 << std::endl;
    std::cout << t2 << std::endl;

    t2.at(5,5) = 0.0;

    // for (int row = 0; row < t2.height; ++row)
    // {
    //     for (int col = 0; col < t2.width; ++col)
    //     {
    //         std::cout << t2.at<double>(row,col) << "\t";
    //     }
    //     std::cout << "\n";
    // }

    // std::cout << t1(col,row) << std::endl;
    // t2.at<double>(5,6) = 0.0;
    // std::cout << t2.at<double>(row,col) << std::endl;

    return 0;   
}