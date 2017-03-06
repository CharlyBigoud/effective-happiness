struct{auto operator+(auto...x){return[](auto f,auto...x){return f(x...);};}}x;

int main()
{
    x + x;
    return 0;
}
