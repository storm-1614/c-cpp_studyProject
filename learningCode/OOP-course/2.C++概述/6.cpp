/*
 * =====================================================================================
 *
 *       Filename:  6.cpp
 *
 *    Description: 编写一个函数，其原型为：void Index(int a[], int n, int &
 * sub)，其功能是，在大小为n的数组a中，查找某个数sub，若找到，将其下标存放在sub中，若没有找到，将-1存放在sub中，在主调函数中通过判断值来判断数组中是否有该数。
 *   【提示】：在这里，sub 是引用类型的参数，但起返回值的作用。
 *
 *        Version:  1.0
 *        Created:  03/16/2026 07:34:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <print>

void Index(int a[], int n, int &sub)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == sub)
        {
            sub = i;
            return;
        }
    }
    sub = -1;
}

int main(int argc, char *argv[])
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int res = 10;
    Index(a, 10, res);
    std::print("{0}", res);

    return 0;
}
