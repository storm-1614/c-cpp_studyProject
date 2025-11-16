/*
* storm-1614
* 2025-10-31 20:27
* 人人都喜欢的哥德巴赫猜想
*/

#include <stdio.h>

int isPrime(long long n)
{
    long i;
    for (i = 2;i * i <= n;i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    long long n, i;
    scanf("%lld", &n);
    for (i = 3; i <=n/2;i++)
    {
        if (isPrime(i) && isPrime(n - i))
        {
            printf("%lld=%lld+%lld", n, i, n-i);
            return 0;
        }
    }

    return 0;
}
