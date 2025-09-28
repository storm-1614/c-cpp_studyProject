/*
 * storm-1614
 * 2025-09-27 09:55
 * 分类质因数
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, i;
    scanf("%d", &n);
    printf("%d=", n);
    for (int i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            printf("%d", i);
            n /= i;
            if (n != 1)
                printf("*");
        }
    }
    return 0;
}
