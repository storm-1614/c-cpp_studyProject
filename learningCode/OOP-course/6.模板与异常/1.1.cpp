/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description: 调试模板
 *
 *        Version:  1.0
 *        Created:  06/13/2026 02:32:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;
template <typename T> T myMax(T x, T y)
{
    return x > y ? x : y;
}
int myMax(int a, int b)
{
    return a > b ? a : b;
}
double myMax(double a, double b)
{
    return a > b ? a : b;
}
int main()
{
    cout << "max('3','7') is " << myMax('3', '7') << endl;
    return 0;
}
