/*
* storm-1614
* 2025-10-13 13:34
* 贪玩蓝日
*/


#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, m, temp;
    int count;
    scanf("%d%d", &n, &m);
    int pair[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp);
        pair[i] = temp;
    }

    for (int i = 0; i < n; i++)
    {
        count = 0;
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                continue;
            if (pair[i] == pair[j])
                count++;
        }
        if (count == 0)
            printf("ZGS\n");
        else
            printf("%d\n", count);
    }

    return 0;
}
