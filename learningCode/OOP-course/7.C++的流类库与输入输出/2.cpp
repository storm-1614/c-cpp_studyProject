/*
 * =====================================================================================
 *
 *       Filename:  2.cpp
 *
 *    Description: 统计 xyz.txt 字符个数
 *
 *        Version:  1.0
 *        Created:  06/19/2026 09:51:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    char ch;
    int i = 0;
    ifstream file;
    file.open("xyz.txt", ios::in);
    if (!file)
    {
        cout << "xyz.txt cannot open" << endl;
        abort();
    }
    while (!file.eof())
    {
        file.get(ch);
        i++;
    }
    cout << "文件字符个数：" << i << endl;
    file.close();
    return 0;
}
