/*
 * storm1614
 * 2025-09-27 11:17
 * DNA 配对
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char olist[5001], rlist[5001];
    char c;
    int len, i;

    scanf("%s", olist);
    len = strlen(olist);

    for (i = 0; i < len; i++)
    {
        switch (olist[i])
        {
        case 'A':
            rlist[i] = 'T';
            break;
        case 'T':
            rlist[i] = 'A';
            break;
        case 'G':
            rlist[i] = 'C';
            break;
        case 'C':
            rlist[i] = 'G';
            break;
        }
    }
    rlist[len] = '\0';

    printf("%s\n", olist);
    for (i = 0; i < len; i++)
        printf("|");
    printf("\n");
    printf("%s\n", rlist);

    return 0;
}
