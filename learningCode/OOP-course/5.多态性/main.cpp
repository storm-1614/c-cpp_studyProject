#include <iostream>

class X
{
  public:
    X();
    X(X &&) = default;
    X(const X &) = default;
    X &operator=(X &&) = default;
    X &operator=(const X &) = default;

    X operator++()
    {
        std::cout << "前自增" << std::endl;
        return *this;
    }
    ~X();
    int i1, i2, i3;
    friend X operator++(X &op, int);

  private:
};

X::X()
{
}

X::~X()
{
}

X operator++(X &op, int)
{
    X tmp(op);
    op.i1++;
    op.i2++;
    op.i3++;
    return tmp;
}
int main(int argc, char *argv[])
{
    X a;
    ++(++a++)++;
    return 0;
}
