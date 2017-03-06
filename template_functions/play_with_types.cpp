#include <iostream>
#include <tuple>

template<typename ...> struct List{};
template<typename T> struct Type{};

//add an element in front at the end of a list
template<typename ... T, typename A>
List<T...,A> push_back(List<T...>, Type<A>) { return {};}

//add an element in front of a list
template<typename ... T, typename A>
List<A, T...> push_front(List<T...>, Type<A>) { return {};}

//verify is types are identical
template<class T> void test_type(T,T)
{
    std::cout << " Types are identical " << std::endl;
}

template<class T, class U> void test_type(T,U)
{
    std::cout << " Types are different " << std::endl;
}

//generate a tuple from a list
template<typename ... T> std::tuple<T...> as_tuple(List<T...>) { return {};}

//generate a list from a tuple
template<typename ... T> List<T...> as_list(std::tuple<T...>) { return {};}

int main()
{
    using une_liste_de_2_types = List<int,double>;
    auto liste2 = push_back(une_liste_de_2_types{},Type<float>{});
    using type_of_liste2 = decltype(liste2);

    auto liste3 = push_front(une_liste_de_2_types{}, Type<int>{});
    using type_of_liste3 = decltype(liste3);

    test_type(liste2,List<int,double,float>{});
    test_type(liste3,List<int,double,char>{});
    test_type(liste3,liste2);
    test_type(liste3,liste3);

    as_tuple(List<int,double,char>{});
    as_list(std::tuple<int,double,char>{});

    return 0;
}