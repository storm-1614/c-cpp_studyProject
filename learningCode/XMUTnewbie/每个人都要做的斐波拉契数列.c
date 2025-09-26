/*
* storm-1614
* 2025-09-24 12:50
* 斐波拉契数列
*/

#include <stdio.h>

int fab(int n)
{
    int res;

    if (n == 1 || n == 2)
        res = 1;
    else
        res = fab(n - 1) + fab(n - 2);
    return res;
}

int main(int argc, char *argv[])
{
    int n;
    int temp;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &temp);
        printf("%d\n", fab(temp));
    }
    return 0;
}
