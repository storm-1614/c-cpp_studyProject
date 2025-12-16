#include <stdio.h>
#define M 1005

int recall(int list[], int len, int StartIndex, int sum, int target)
{
    int i;
    if (sum == target)
        return 1;
    if (StartIndex >= len || sum > target)
        return 0;
    for (i = StartIndex; i < len; i++)
        if (recall(list, len, i + 1, sum + list[i], target))
            return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    int n, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        int fac = 1, target;
        int list[M];
        scanf("%d", &target);
        for (j = 1; fac <= target; j++)
        {
            fac *= j;
            list[j - 1] = fac;
        }
        if (fac == target)
        {
            printf("Yes\n");
            break;
        }
        if (recall(list, j, 0, 0, target))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
