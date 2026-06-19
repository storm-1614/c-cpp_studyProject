/*
 * =====================================================================================
 *
 *       Filename:  4.cpp
 *
 *    Description: 编写程序，求输入数的平方根。设置异常处理，对输入负数的情况给出提示
 *
 *        Version:  1.0
 *        Created:  06/13/2026 03:34:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  strom-1614
 *   Organization:
 *
 * =====================================================================================
 */

#include <cmath>
#include <iostream>
#include <stdexcept>

double my_sqrt(double num)
{
    if (num < 0)
    {
        throw std::invalid_argument("负数错误");
    }
    return sqrt(num);
}

int main(int argc, char *argv[])
{

    try
    {
        std::cout << my_sqrt(-1) << std::endl;
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
