#include <assert.h>

/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m)
{
    return x | m;
}
int bic(int x, int m)
{
    return x & ~m;
}

/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y)
{
    int result = bis(x, y);
    return result;
}

/* Compute x^y using only calls to functions bis and bic */

int bool_xor(int x, int y)
{
    int result = bis(bic(x, y), bic(y, x)); // x ^ y = (~x & y) | (x & ~y)
    return result;
}
int main()
{
    assert((0x12 | 0x43) == bool_or(0x12, 0x43));
    assert((0x32 ^ 0xf2) == bool_xor(0x32, 0xf2));
    return 0;
}
