/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description:  设圆半径r=1.5 圆柱高h=3求圆周长、圆面积、圆球表面积、圆球体积、圆柱体积，输出结果要有文字说明，如The
 * area is 7.06.（公式：圆周长2πr、圆面积πr2、圆球表面积4πr2、圆球体积4/3πr3、圆柱体积πr2h。）
 * 设圆半径r=1.5 圆柱高h=3求圆周长、圆面积、圆球表面积、圆球体积、圆柱体积，输出结果要有文字说明，如The area
 * is 7.06.（公式：圆周长2πr、圆面积πr2、圆球表面积4πr2、圆球体积4/3πr3、圆柱体积πr2h。）
 *
 * 【要求】：
 *（1）使用#define定义Pi;采用C++输入输出流对象完成数据的输入输出。
 *（2）使用const 定义Pi;采用C++输入输出流对象完成数据的输入输出。
 *
 *        Version:  1.0
 *        Created:  03/16/2026 05:13:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iomanip>
#include <ios>
#include <iostream>

const double Pi = 3.141592;

#define circle(r) (Pi * 2.0 * r)
#define area(r) (Pi * r * r)
#define surface(r) (4.0 * Pi * r * r)
#define globe(r) (4.0 / 3.0 * Pi * r * r * r)
#define column(r, h) (Pi * r * r * h)

int main(int argc, char *argv[])
{
    double r, h;
    std::cin >> r >> h;
    std::fixed(std::cout);
    std::cout << std::setprecision(2) << "The circle is " << circle(r) << std::endl;
    std::cout << std::setprecision(2) << "The area is " << area(r) << "." << std::endl;
    std::cout << std::setprecision(2) << "The surface is " << surface(r) << std::endl;
    std::cout << std::setprecision(2) << "The globe is " << globe(r) << std::endl;
    std::cout << std::setprecision(2) << "The column is " << column(r, h) << std::endl;

    return 0;
}
