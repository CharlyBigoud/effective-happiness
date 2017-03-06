template<typename ...> struct List{};

void iterate_(List<>)
{
    // pour traiter le cas de la liste de vide une fois que tout est dépiler
}

template<typename A, typename ... T> void iterate_(List<A,T...>)
{
    iterate_(List<T...>{});
    // le premier élément A est dépilé, on peut en faire quelque chose
}

template<void (*A)(int &), typename ... T>
void iterate(List<T...> list)
{
    iterate_(list);
}

// template<typename ... T>
// void doSth(T t){};
void doSth(int t){};

int main()
{
    iterate<doSth>(List<int,double>{});

    return 0;
}