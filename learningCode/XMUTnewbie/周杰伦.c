/*
* storm-1614
* 2025-11-09 17:43
* 周杰伦
*/


#include <stdio.h>

int main(int argc, char *argv[])
{
    int m, n;
    int k = 0;
    int cosume = 0;
    scanf("%d%d", &m, &n);
    int list[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &list[i]);
    }
    for (int i = n - 1; i >= 0; i -= m)
    {
        for (int j = 0; j < m && i - j >= 0; j++)
        {
            cosume += (k + 1) * list[i - j];
        }
        k++;
    }
    printf("%d", cosume);
    return 0;
}
