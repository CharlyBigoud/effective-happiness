#include <iostream>

struct True{};
struct False{};

template<typename ...> struct List{};
template<typename T> struct Type{};

//verify is types are identical
template<class T> True test_type(T,T)
{
    std::cout << " Types are identical " << std::endl;
};
template<class T, class U> False test_type(T,U)
{
    std::cout << " Types are not identical " << std::endl;
};

//compress if identical
// template<typename ... T> List<T...> compress_if_identical(List<T...>, List<T...>){ return{};}
// template<typename ... T, typename ... U> List<T..., U...> compress_if_identical(List<T...>, List<U...>){ return{};}

// pour traiter le cas de la liste de vide une fois que tout est dépilé
template<typename S> S iterate_(List<>){};

template<typename S, typename A, typename ... T> S iterate_(List<A,T...>)
{
    test_type(S{},A{});

    iterate_<S>(List<T...>{});

    // le premier élément A est dépilé, on peut en faire quelque chose
    //verif si A n'est pas déjà présent dans la liste de sortie
    // List<S...> l = isPresentInList(A, List<S...>{});
}

// template<class ... T, class ... A> List<A...> check_doublons(List<T...> list)
// {
//     //depiler la liste
//     iterate_(list);

//     //for each elt de la lists

//         //verif que l'element n'est présent qu'une seul fois dans la lsite de sortie

//         //si l'elements n'est pas présent dnas la liste de sortie alors on la rentre dedans
//     //end_for
// }



//verify is types is present in a List
template<class A, class ... B> True isPresentInList(A, List<B...> list)
{
    iterate_<A>(list);
};

// template<class T, class ... U> False isPresentInList(T, List<U...>){};



int main()
{
    using listeDarguments = List<int,double,int>;

    // test_type( 0.0, 0);
    // test_type(double{},double{});
    // test_type(List<int,double,int>{},List<int,double,char>{});

    // compress_if_identical(List<int,double>{},List<int,double>{});
    // compress_if_identical(List<int>{},List<double>{});

    // check_doublons(List<int,double,int>{});

    isPresentInList(int{}, List<double,int,int,int,int,double,int>{});

    //TODO: create if and else functions
    // if_(True, cond 1,cond 2);

    return 0;
}