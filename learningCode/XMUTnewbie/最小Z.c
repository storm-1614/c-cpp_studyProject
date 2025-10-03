/*
* storm-1614
* 2025-10-03 17:17
* 最小Z
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char a[100];
    int len;
    int t, flag;
    scanf("%s", a);
    len = strlen(a);
    t = len;

    for (int i = 1; i <= len; i++)
    {
        flag = 1;
        if (len % i == 0)
        {
            for (int j = i; j < len; j++)
            {
                if (a[j % i] != a[j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                printf("%d", i);
                return 0;
            }
        }
    }

    return 0;
}
