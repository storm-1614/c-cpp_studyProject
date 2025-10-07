/*
 * storm-1614
 * 2025-10-04 08:55
 * 算最大
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int n, res = 0, temp = 0;
    scanf("%d", &n);
    int list[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &list[i]);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (list[j] < list[j + 1])
            {
                int temp = list[j + 1];
                list[j + 1] = list[j];
                list[j] = temp;
            }
        }
    }

    for (int i = 0; i + 1 < n; i += 2)
    {
        temp = list[i] + list[i + 1];
        if (temp > 0 && i > 0 || i == 0)
            res += temp;
        else
            break;
    }

    printf("%d", res);
    return 0;
}
