/*
* storm-1614
* 2025-10-05 20:53
* 坚强的蜗牛
*/


#include <stdio.h>

int main(int argc, char *argv[])
{
    double n, x, height;
    int days = 1;
    scanf("%lf%lf", &n, &x);
    height = n;

    while (height > 0)
    {
        height -= x;
        if (height > n)
        {
            printf("-1");
            return 0;
        }
        else if (height <= 0)
            break;
        height += 2;
        x *= 0.95;
        days++;
    }
    printf("%d", days);

    return 0;
}
