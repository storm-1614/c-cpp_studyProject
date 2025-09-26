/*
* storm-1614
* 2025-09-27 07:15
* 求 n 以内素数的数目
*/

#include <stdio.h>

int isPrime(unsigned long n)
{
    for (unsigned long i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    unsigned long n, count = 0;
    scanf("%ld", &n);

    int PrimeList[n+1];

    for (int i = 0; i < n; i++)
        PrimeList[i] = 1;

    for (int i = 2; i * i < n + 1; i++)
    {
        if (isPrime(i))
        {
            for (int j = i * i; j < n + 1; j += i)
            {
                PrimeList[j] = 0;
            }
        }
    }

    for (int i = 2; i <= n; i++)
    {
        if (PrimeList[i] == 1)
            count++;
    }

    printf("%ld", count);
    return 0;
}
