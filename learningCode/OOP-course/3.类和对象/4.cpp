/*
 * =====================================================================================
 *
 *       Filename:  4.cpp
 *
 *    Description:
 * 定义一个圆类（Circle），属性为半径（radius）和圆周长、面积，操作为输入半径并计算周长、面积，输出半径、周长和面积。要求定义构造函数（以半径为参数，缺省值为0，周长和面积在构造函数中生成）和复制构造函数。
 *
 *        Version:  1.0
 *        Created:  04/23/2026 11:15:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>

const double PI = 3.1415926;

class Circle
{
  private:
    double radius;
    double perimeter;
    double area;

  public:
    Circle()
    {
        radius = perimeter = area = 0;
    }
    Circle(double r) : radius(r)
    {
        perimeter = 2 * PI * radius;
        area = PI * radius * radius;
    }

    Circle(const Circle &c)
    {
        radius = c.radius;
        perimeter = c.perimeter;
        area = c.area;
    }
    double get_perimeter()
    {
        return perimeter;
    }

    double get_area()
    {
        return area;
    }

    void show()
    {
        std::cout << "r = " << radius << std::endl;
        std::cout << "perimeter = " << perimeter << std::endl;
        std::cout << "area = " << area << std::endl;
    }
};

int main(int argc, char *argv[])
{
    double r = 0;
    std::cin >> r;
    Circle circle0(r);
    Circle circle1(0);
    Circle circle2 = circle0;

    std::cout << "带参函数：" << std::endl;
    std::cout << "circle0: " << std::endl;
    circle0.show();
    std::cout << "==================" << std::endl;
    std::cout <<"默认构造函数：" << std::endl;
    std::cout << "circle1: " << std::endl;
    circle1.show();
    std::cout << "==================" << std::endl;
    std::cout << "复制构造函数：" << std::endl;
    std::cout << "circle2: " << std::endl;
    circle2.show();

    return 0;
}
