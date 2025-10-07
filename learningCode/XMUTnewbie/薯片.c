/*
* storm-1614
* 2025-10-05 21:05
* 薯片
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    double m, money = 100;
    int count = 0;
    scanf("%lf", &m);

    if (m > 100)
    {
        printf("0");
        return 0;
    }
    while (money > 0)
    {
        // 防止钱变成负数
        if (money < 5 || m > money)
            break;
        money -= m;
        m *= 0.9;
        if (m < 5)
            m = 5;
        count++;
    }
    printf("%d", count);
    return 0;
}
