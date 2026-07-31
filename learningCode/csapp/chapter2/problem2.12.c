#include <stdio.h>

int main(int argv, char *argc[])
{
    int x = 0x87654321;
    int a = x & 0xff;
    int b = ~x ^ 0xff; // 或者 x ^ 0x000000ff 也可以
    int c = x | 0xff;
    printf("0x%.8x\n", a);
    printf("0x%.8x\n", b);
    printf("0x%.8x\n", c);

    return 0;
}
