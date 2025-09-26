/*
 * storm-1614
 * 2025-09-25 21:56
 * 数字符
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int count = 0;
    char str[100];
    char c;
    char *ptr = str;
    for (int i = 0; c != '\n'; i++)
    {
        scanf("%c", &c);
        str[i] = c;
    }

    for (int i = 0; i < strlen(str) - 1; i++)
        if (!isdigit(str[i]))
            count++;
    printf("%d", count);
    return 0;
}
