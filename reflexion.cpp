class Mother
{
    Mother();
    ~Mother();

    // virtual void f() = 0;
    virtual void f(int i);
};

// class Daugther : public Mother
class Daugther
{
    Daugther(){};
    ~Daugther(){};

    void f(){};
};

int main()
{
    Daugther d();

    d.f();

    return 0;    
}
