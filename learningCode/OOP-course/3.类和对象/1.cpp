/*
 * =====================================================================================
 *
 *       Filename:  1.cpp
 *
 *    Description: 实验1
 *
 *        Version:  1.0
 *        Created:  04/23/2026 08:37:02 PM
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

class Coordinator
{
  public:
    Coordinator() : x(0), y(0)
    {
        cout << "constructor() is called.\n";
    }
    Coordinator(int a) : x(a), y(0)
    {
        cout << "constructor(int) is called.\n";
    }

    Coordinator(int x1, int y1)
    {
        cout << "constructor is called.\n";
        x = x1;
        y = y1;
    }
    Coordinator(Coordinator &p);
    ~Coordinator()
    {
        cout << "Destructor is called\n";
    }
    int getx()
    {
        return x;
    }
    int gety()
    {
        return y;
    }

  private:
    int x, y;
};
Coordinator::Coordinator(Coordinator &p)
{
    x = p.x;
    y = p.y;
    cout << "Copy-initialization Constructor is called\n";
}
int main()
{
    Coordinator p1(3, 4);
    Coordinator p2(p1);
    Coordinator p3 = p2;
    cout << "p3=(" << p3.getx() << "," << p3.gety() << ")\n";
    Coordinator p4;
    Coordinator p5(2);
    return 0;
}
