#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int sum(int count, ...)
{
    int total = 0;
    va_list args;

    va_start(args, count);

    for (int i = 0; i < count; i++)
        total += va_arg(args, int);
    va_end(args);

    return total;
}

int main(int argc, char *argv[])
{
    printf("Sum of 1, 2, 3: %d\n", sum(3, 1, 2, 3));
    printf("Sum of 4, 5, 6, 7: %d\n", sum(4, 4, 5, 6, 7));

    return EXIT_SUCCESS;
}
