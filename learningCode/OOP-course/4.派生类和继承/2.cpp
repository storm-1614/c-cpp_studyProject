/*
 * =====================================================================================
 *
 *       Filename:  2.cpp
 *
 *
 *    Description:
 *        Version:  1.0
 *        Created:  05/19/2026 02:56:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

class MyArray
{
  public:
    MyArray(int leng);
    virtual ~MyArray();
    void Input();
    void Display(string);

  protected:
    int *alist;
    int length;
};

MyArray::~MyArray()
{
    delete[] alist;
    cout << "MyArray 类对象被撤销。" << endl;
}

void MyArray::Display(string str)
{
    int i;
    int *p = alist;
    cout << str << length << "个整数：";
    for (i = 0; i < length; i++, p++)
        cout << *p << " ";
    cout << endl;
}

MyArray::MyArray(int leng)
{
    if (leng <= 0)
    {
        cout << "error length";
        exit(1);
    }

    alist = new int[leng];
    length = leng;

    if (alist == NULL)
    {
        cout << "assign failure";
        exit(1);
        cout << "MyArray 类对象已创建。" << endl;
    }
}

void MyArray::Input()
{
    cout << "请从键盘输入" << length << "个整数：";
    int i;
    int *p = alist;
    for (i = 0; i < length; i++, p++)
    {
        cin >> *p;
    }
}

class SortArray : virtual public MyArray
{
  public:
    using MyArray::MyArray; // 懒得写构造函数了，逝世 C++ 17 的 using 语法
    ~SortArray();

    void sort_array();
};

SortArray::~SortArray()
{
}

void SortArray::sort_array()
{
    sort(alist, alist + length);
}

class ReArray : virtual public MyArray
{
  public:
    using MyArray::MyArray;
    ~ReArray();

    void covert();
};

ReArray::~ReArray()
{
}

void ReArray::covert()
{
    sort(alist, alist + length, greater<int>()); // 依旧 STL 懒人函数
}

class Average : virtual public MyArray
{
  public:
    using MyArray::MyArray;
    ~Average();
    double avg();
};

Average::~Average()
{
}

double Average::avg()
{
    double sum = 0, avg;
    for (int i = 0; i < length; i++)
    {
        sum += *(alist + i);
    }
    avg = sum / length;
    std::cout << "平均值：" << avg << std::endl;
    return avg;
}

class NewArray : virtual public MyArray, public SortArray, public ReArray, public Average
{
  public:
    NewArray(int len) : MyArray(len), SortArray(len), ReArray(len), Average(len)
    {
    }
};

int main(int argc, char *argv[])
{
    NewArray a(5);
    a.Input();
    a.sort_array();
    a.Display("显示已排序的");
    a.covert();
    a.Display("显示已倒置的");
    a.avg();
    a.Display("显示已输入的");
    return 0;
}
