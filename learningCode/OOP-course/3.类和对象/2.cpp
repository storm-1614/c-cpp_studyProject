/*
 * =====================================================================================
 *
 *       Filename:  2.cpp
 *
 *    Description:
 * 设计一个用来表示直角坐标系的Location类，在主程序中创建类Location的两个对象A和B，要求A的坐标点在第3象限，B的坐标点在第2象限，分别采用成员函数和友元函数计算给定两个坐标点之间的距离。
 *
 *        Version:  1.0
 *        Created:  04/23/2026 08:37:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  strom-1614
 *   Organization:
 *
 * =====================================================================================
 */

#include <cmath>
#include <cstdio>

class Location
{
  private:
    double x, y;

  public:
    Location(double a, double b) : x(a), y(b)
    {
    }
    double get_x()
    {
        return x;
    }
    double get_y()
    {
        return y;
    }
    double distance_cal(const Location &object2)
    {
        return sqrt(pow(object2.x - this->x, 2.0) + pow(object2.y - this->y, 2));
    }

    friend double distance_cal(const Location &loc1, Location &loc2);
};

double distance_cal(const Location &loc1, Location &loc2)  // Location 类的 distance_cal 友元函数实现
{
    return sqrt(pow(loc2.x - loc1.x, 2.0) + pow(loc2.y - loc1.y, 2));
}

int main(int argc, char *argv[])
{
    double x1 = -3.3, y1 = -3.4;
    double x2 = -1.2, y2 = 6.3;
    double d1, d2;

    Location A(x1, y1), B(x2, y2);
    d1 = A.distance_cal(B);
    d2 = distance_cal(A, B);

    printf("A(%.2lf, %.2lf), B(%.2lf, %.2lf)\n", x1, y1, x2, y2);
    printf("Distance1 = %.2lf\n", d1);
    printf("Distance2 = %.2lf\n", d2);


    return 0;
}
