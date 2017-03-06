template<typename T, typename A> std::ostream& operator<<(std::ostream& o, const std::vector<T,A>&){}

template<typename T> struct Boite { const T& ref; };

template<typename T> Boite<T> disp(const T& ref) { return Boite<T>{ref}; }

template<typename T> std::ostream& operator<<(std::ostream& o, const Boite<T>& boite)
{
return o << boite.ref;
}


int main()
{
 std::cout << disp("c") << std::endl;
}