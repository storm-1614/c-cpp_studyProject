/*
 * storm-1614
 * 2025-10-04 15:50
 * 欢乐的秋游
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, status, now, count = 0;
    scanf("%d", &n);
    int heightList[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &heightList[i]);

    now = heightList[0];
    for (int i = 1; i < n; i++)
    {
        now = heightList[i];
        if (now > heightList[i - 1])
        {
            if (status == -1)
                count++;
            status = 1;
        }
        else if (now < heightList[i - 1])
            status = -1;
    }

    printf("%d", count);
    return 0;
}
