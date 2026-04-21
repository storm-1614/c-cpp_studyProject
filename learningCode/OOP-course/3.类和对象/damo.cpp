#include <iostream>

class MyClass
{
  public:
    MyClass()
    {
        count++;
    }
    ~MyClass()
    {
        count--;
    }
    static int count;
};

int MyClass::count = 0;

int main(int argc, char *argv[])
{
    MyClass *a = new MyClass[100];
    MyClass b;

    std::cout << a->count << std::endl;
    delete[] a;
    std::cout << a->count << std::endl;
    MyClass::count = 10;
}
