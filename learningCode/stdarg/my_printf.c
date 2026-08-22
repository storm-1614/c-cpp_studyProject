#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// 递归法
void my_putnbr_recur(int val)
{
    unsigned int unum;
    if (val < 0)
    {
        putchar('-');
        /*
         * 直接取反会导致溢出
         */
        unum = (unsigned int)(-(val + 1)) + 1;
    }
    else
        unum = (unsigned int)(val);

    if (unum >= 10)
        my_putnbr_recur(unum / 10);
    putchar('0' + unum % 10);
}

// 逆序数组法整型转字符串
int my_putnbr_itoa(int val)
{
    unsigned int u;
    int count = 0;
    if (val < 0)
    {
        putchar('-');
        u = (unsigned int)(-(val + 1)) + 1;
    }
    else
        u = (unsigned int)(val);

    char tmp[12] = {'\0'};
    int i = 0;
    do
    {
        tmp[i++] = '0' + (u % 10);
        u /= 10;
    } while (u != 0);

    while (i > 0)
    {
        putchar(tmp[--i]);
        count++;
    }
    return count;
}

void my_putstr(const char *str)
{
    for (; *str != '\0'; str++)
        putchar(*str);
}

void my_printf(const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);

    for (const char *p = fmt; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        p++;
        if (*p == 'd')
            my_putnbr_itoa(va_arg(arg, int));
        else if (*p == 's')
        {
            my_putstr(va_arg(arg, char *));
        }
        else if (*p == '%')
            putchar('%');
    }
    va_end(arg);
}

int main(int argc, char *argv[])
{
    my_putnbr_itoa(-123123);
    my_printf("int : %d, string: %s %s", 2131, "adas", "可以");
    return EXIT_SUCCESS;
}
