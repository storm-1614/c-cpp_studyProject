/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description: 九九乘法表
 *
 *        Version:  1.0
 *        Created:  06/19/2026 09:45:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
int main()
{
    int i, j;
    std::cout << "*\t";
    for (i = 1; i <= 9; i++)
        std::cout << i << "\t";
    std::cout << std::endl;
    for (i = 1; i <= 9; i++)
    {
        std::cout << i << "\t";
        for (j = 1; j <= i; j++)
            std::cout << i * j << "\t";
        std::cout << std::endl;
    }
    return 0;
}
