#define COMP <
#define TEST <

typedef int data_t;

int comp(data_t a, data_t b)
{
    return a COMP b;
}

int test(data_t a)
{
    return a TEST 0;
}

int ccomp(long x, long y)
{
    long z;
    if (x > y)
    {
        z = 1;
    }
    else
    {
        z = 2;
    }
    return z;
}
