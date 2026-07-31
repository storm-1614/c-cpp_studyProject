#include <assert.h>

int equal(int x, int y)
{
    return !(x ^ y);
}
int main()
{
    assert(!equal(0x32, 0x31));
    assert(equal(0xd3, 0xd3));
    return 0;
}
