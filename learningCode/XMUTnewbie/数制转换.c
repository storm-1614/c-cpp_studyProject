/*
* storm-1614
* 2025-10-04 08:50
* 数制转换
*/

#include <math.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int system, len, res = 0;
    char number[1000], reverse[1000];

    scanf("%d%s", &system, number);
    len = strlen(number);

    for (int i = len - 1; i >= 0; i--)
    {
        reverse[len - 1 - i] = number[i];
    }

    for (int i = len - 1; i >= 0; i--)
    {
        switch (reverse[i])
        {
        case '0':
            res += 0;
            break;
        case '1':
            res += pow(system, i) * 1;
            break;
        case '2':
            res += pow(system, i) * 2;
            break;
        case '3':
            res += pow(system, i) * 3;
            break;
        case '4':
            res += pow(system, i) * 4;
            break;
        case '5':
            res += pow(system, i) * 5;
            break;
        case '6':
            res += pow(system, i) * 6;
            break;
        case '7':
            res += pow(system, i) * 7;
            break;
        case '8':
            res += pow(system, i) * 8;
            break;
        case '9':
            res += pow(system, i) * 9;
            break;
        case 'A':
            res += pow(system, i) * 10;
            break;
        case 'B':
            res += pow(system, i) * 11;
            break;
        case 'C':
            res += pow(system, i) * 12;
            break;
        case 'D':
            res += pow(system, i) * 13;
            break;
        case 'E':
            res += pow(system, i) * 14;
            break;
        case 'F':
            res += pow(system, i) * 15;
            break;
        }
    }

    printf("%d", res);
    return 0;
}
