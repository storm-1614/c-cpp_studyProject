/*
 * =====================================================================================
 *
 *       Filename:  1.2.cpp
 *
 *    Description: 调试模板程序
 *
 *        Version:  1.0
 *        Created:  06/13/2026 02:37:05 PM
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
    cout << " myMax ('3','7') is " << myMax('3', '7') << endl;
    return 0;
}
