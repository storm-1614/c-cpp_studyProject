/*
 * =====================================================================================
 *
 *       Filename:  2.cpp
 *
 *    Description:
 * 编写一个程序，调用函数名为mul的函数分别求2个整数、3个整数、2个双精度数和3个双精度数的乘积。采用C++输入输出流对象完成数据的输出。
 *
 * 【要求】：
 *  1）使用重载函数实现。
 *  2）使用重载函数和带默认参数的函数实现。
 *
 *        Version:  1.0
 *        Created:  03/16/2026 05:34:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>

int mul(int x, int y)
{
    return x * y;
}

int mul(int x, int y, int z)
{
    return x * y * z;
}

double mul(double x, double y)
{
    return x * y;
}

double mul(double x, double y, double z)
{
    return x * y * z;
}

int main(int argc, char *argv[])
{
    double x, y, z;
    std::cout << "输入三个数：";
    std::cin >> x >> y >> z;
    std::cout << "int mul(int x, int y)=" << mul(int(x), int(y)) << std::endl;
    std::cout << "int mul(int x, int y, int z)=" << mul(int(x), int(y), int(z)) << std::endl;
    std::cout << "double mul(double x, double y)=" << mul(x, y) << std::endl;
    std::cout << "double mul(double x, double y, double z)="  << mul(x, y, z) << std::endl;
    return 0;
}
