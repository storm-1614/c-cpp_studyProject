/*
 * =====================================================================================
 *
 *       Filename:  5.cpp
 *
 *    Description: 一个声明为返回引用的函数，还可以用在赋值号的左边，即这种函数调用本身也是一个左值。
 *
 *        Version:  1.0
 *        Created:  03/16/2026 07:32:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

int myArray[] = {2, 4, 6, 8, 10};
int& index(int i);
int main()
{
    index(3) = 16;
    for (int i = 0; i < 5; i++)
        cout << index(i) << " ";
    return 0;
}

int& index(int i)
{
    return myArray[i];
}

