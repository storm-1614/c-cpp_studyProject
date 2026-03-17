/*
 * =====================================================================================
 *
 *       Filename:  4.cpp
 *
 *    Description: 编写一个程序，任意从键盘输入两个字符，能将它们按由大到小的顺序输出。
 *【要求】：程序中有一个交换两个字符的函数，其形参是变量的引用。
 *
 *        Version:  1.0
 *        Created:  03/16/2026 07:27:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>

void swap(char &x, char &y)
{
    char tmp = x;
    x = y;
    y = tmp;
}

int main(int argc, char *argv[])
{
    char a, b;
    std::cin >> a >> b;
    if (a < b)
        swap(a, b);
    std::cout << a << " " << b;

    return 0;
}
