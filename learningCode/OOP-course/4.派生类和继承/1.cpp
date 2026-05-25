/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/19/2026 02:41:40 PM
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
class Base
{
  public:
    void setx(int i)
    {
        x = i;
    }
    int getx()
    {
        return x;
    }

  public:
    int x;
};
class Derived : public Base
{
  public:
    void sety(int i)
    {
        y = i;
    }
    int gety()
    {
        return y;
    }
    void show()
    {
        cout << "Base::x=" << x << endl;
    } // 语句1
  public:
    int y;
};
int main()
{
    Derived bb;                                 // 语句2
    bb.setx(16);                                // 语句3
    bb.sety(25);                                // 语句4
    bb.show();                                  // 语句5
    cout << "Base::x=" << bb.x << endl;         // 语句6
    cout << "Derived::y=" << bb.y << endl;      // 语句7
    cout << "Base::x=" << bb.getx() << endl;    // 语句8
    cout << "Derived::y=" << bb.gety() << endl; // 语句9
    return 0;
}
