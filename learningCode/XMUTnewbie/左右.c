/*
* storm-1614
* 2025-10-27 15:14
* 左右
*/


#include <math.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int s, m, res;
    scanf("%d%d", &s, &m);
    res = ceil((double)s / m);

    res % 2 == 0 ? printf("YES") : printf("NO");

    return 0;
}
