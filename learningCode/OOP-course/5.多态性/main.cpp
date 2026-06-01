#include <iostream>

class Base
{
  public:
    virtual void show()
    {
        std::cout << "基类" << std::endl;
    }

  private:
};

class Derived : public Base
{
  public:
    void Show() override
    {
        std::cout << "派生类" << std::endl;
    }

  private:
};
int main(int argc, char *argv[])
{
    Base a, *ptr;
    Derived b;
    ptr = &a;
    ptr->show();
    ptr = &b;
    ptr->show();
    return 0;
}
