#include <string.h>
#include <iostream>

struct test{
    int x;
    char a[4];
    int y;
    char b[4];
    int z;
};

int main(int argc, char *argv[])
{
    test t1{1, "abc", 1, "xyz", 1};
    std::cout << t1.x << " " << t1.y << " " << t1.z << std::endl;
    strcat(t1.a, t1.b);
    std::cout << t1.a << std::endl;
    std::cout << t1.x << " " << t1.y << " " << t1.z << std::endl;

    return 0;
}
