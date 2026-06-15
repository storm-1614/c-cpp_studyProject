/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description: 将实验2
 * 类与对象的第2题“设计一个用来表示直角坐标系的Location类…”中的mydistance函数改为运算符重载函数operator-，分别用友元函数和成员函数实现。
 *
 *        Version:  1.0
 *        Created:  06/09/2026 02:32:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <cstdio>

class Location
{
  private:
    double x, y;

  public:
    Location()
    {
        x = 0.0, y = 0.0;
    }
    Location(double a, double b) : x(a), y(b)
    {
    }
    double get_x() const
    {
        return x;
    }
    double get_y() const
    {
        return y;
    }

    void output() const
    {
        printf("x = %lf, y = %lf\n", x, y);
    }

    Location operator-(const Location &other)
    {
        return Location(this->get_x() - other.get_x(), this->get_y() - other.get_y());
    }

    friend Location operator-(const Location &loc1, const Location &loc2);
};

Location operator-(const Location &loc1, const Location &loc2)
{
    return Location(loc1.get_x() - loc2.get_y(), loc1.get_y() - loc2.get_y());
}

int main(int argc, char *argv[])
{
    Location l1(1, 2), l2(3, 2), l3;
    l1.output();
    l2.output();
    printf("l3 = l1 - l2\n");
    l3 = l1 - l2;
    l3.output();
    return 0;
}
