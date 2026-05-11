#include <iostream>

struct Member {
    Member() { std::cout << "Member()\n"; }
    ~Member() { std::cout << "~Member()\n"; }
};

struct Base {
    Base() { std::cout << "Base()\n"; }
    ~Base() { std::cout << "~Base()\n"; }
};

struct Derived : public Base {
    Member m;
    Derived() { std::cout << "Derived()\n"; }
    ~Derived() { std::cout << "~Derived()\n"; }
};

int main() {
    Derived d;
}
