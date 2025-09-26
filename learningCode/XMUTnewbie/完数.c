/*
 * storm-1614
 * 2025-09-25 06:43
 * 完数
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < 10000; i++)
    {
        int sum = 0;
        for (int j = 1; j < i; j++)
        {
            if (i % j == 0)
                sum += j;
        }
        if (i == sum)
            printf("%d\n", i);
    }
    return 0;
}
