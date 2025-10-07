/*
 * storm-1614
 * 2025-10-04 18:02
 * 数字反转递归版
 */

#include <stdio.h>

int sum = 0, temp;

int rev_num(int num, int len)
{
    if (num)
    {
        temp = num % 10;
        sum = sum * 10 + temp;
        rev_num(num / 10, len);
    }
    else
        return sum;
    return sum;
}

int main(int argc, char *argv[])
{
    printf("%d", rev_num(123, 3));
    return 0;
}
