/*
* storm-1614
* 2025-10-04 16:08
* 最大公约数递归版
*/


#include<stdio.h>

long long gcd( long long m, long long n ){
    long long temp = n;
    if (n == 0)
        return m;
    n = m % n;
    m = temp;
    return gcd(m, n);
}

int main(int argc, char *argv[])
{
    printf("%lld", gcd(20, 4));
    return 0;
}
