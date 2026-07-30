#include <stdio.h>

void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int a[], int cnt)
{
    int first, last;
    for (first = 0, last = cnt - 1; first <= last; first++, last--)
    {
        inplace_swap(&a[first], &a[last]);
    }
}
void reverse_array_fix(int a[], int cnt)
{
    int first, last;
    for (first = 0, last = cnt - 1; first <= last; first++, last--)
    {
        if (first != last)
            inplace_swap(&a[first], &a[last]);
    }
}

void print_array(int a[], int cnt)
{
    int i;
    for (i = 0; i < cnt; i++)
    {
        printf("%d ", a[i]);
    }
    puts("");
}

int main(int argc, char *argv[])
{
    int a = 4, b = 5;
    printf("a = %d, b = %d\n", a, b);
    inplace_swap(&a, &b);
    printf("inplace_swap(&a, &b);\n");
    printf("a = %d, b = %d\n", a, b);

    printf("========\n");
    printf("Even-length array:");
    int even_array[4] = {1, 2, 3, 4};
    print_array(even_array, 4);
    reverse_array(even_array, 4);
    printf("reverse_array\n");
    print_array(even_array, 4);

    printf("========\n");
    printf("Odd-length array:");
    int odd_array[5] = {1, 2, 3, 4, 5};
    print_array(odd_array, 5);
    printf("reverse_array\n");
    reverse_array(odd_array, 5);
    print_array(odd_array, 5);

    printf("========\n");
    printf("Odd-length array:");
    int odd_array_2[5] = {1, 2, 3, 4, 5};
    print_array(odd_array_2, 5);
    printf("Fixed reverse_array\n");
    reverse_array_fix(odd_array_2, 5);
    print_array(odd_array_2, 5);

    return 0;
}
