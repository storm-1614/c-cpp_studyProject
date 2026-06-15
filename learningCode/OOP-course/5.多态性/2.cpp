/*
 * =====================================================================================
 *
 *       Filename:  2.cpp
 *
 *    Description:
 * 编写一个程序，其中设计一个时间类Time，用来保存时、分、秒等私有数据成员，通过重载操作符“+”实现两个时间的相加。
 *
 *        Version:  1.0
 *        Created:  06/09/2026 02:44:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm1614
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdexcept>
#include <string>

class Time
{
  public:
    Time(int h = 0, int m = 0, int s = 0);
    Time operator+(const Time &);
    void DispTime(std::string = "");

  private:
    int hours;
    int minuters;
    int seconds;
};

Time::Time(int h, int m, int s)
{
    if (m > 60 || s > 60)
    {
        throw std::range_error("超出范围");
    }
    hours = h;
    minuters = m;
    seconds = s;
}

Time Time::operator+(const Time &other)
{
    int h = 0, m = 0, s = 0;
    s = seconds + other.seconds;
    if (s >= 60)
    {
        m = 1;
        s %= 60;
    }
    m += minuters + other.minuters;
    if (m >= 60)
    {
        h = 1;
        m %= 60;
    }
    h += hours + other.hours;
    return Time(h, m, s);
}


void Time::DispTime(std::string prefix)
{
    std::cout << prefix << ": " << hours << ":" << minuters << ":" << seconds << std::endl;
}

int main (int argc, char *argv[]) {
    Time t1(12, 21, 43), t2(2, 12, 49), t3;
    t1.DispTime("t1 = ");
    t2.DispTime("t2 = ");
    t3 = t1 + t2;
    std::cout << "t3 = t1 + t2" << std::endl;
    t3.DispTime("t3 = ");

    return 0;
}
