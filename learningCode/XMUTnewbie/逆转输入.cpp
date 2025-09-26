/*
* storm-1614
* 2025-09-25 07:11
* 逆转输入
*/

#include <iostream>
#include <stack>

using namespace std;
int main(int argc, char *argv[])
{

    stack<int> list;
    int s;

    while (cin >> s)
    {
        list.push(s);
    }

    while (!list.empty())
    {
        cout << list.top() << " ";
        list.pop();
    }
    return 0;
}
