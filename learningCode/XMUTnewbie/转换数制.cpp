/*
* storm-1614
* 转换数制
* 2025-11-25 18:39
*/

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int n, num, a;
    int b;
    stack<int> tranfrom;
    cin >> num >> n;
    while (num != 0)
    {
        a = num % n;
        num /= n;
        tranfrom.push(a);
    }
    while (!tranfrom.empty())
    {
        b = tranfrom.top();
        tranfrom.pop();
        switch (b)
        {
        case 0 ... 9:
            cout << b;
            break;
        case 10:
            cout << 'A';
            break;
        case 11:
            cout << 'B';
            break;
        case 12:
            cout << 'C';
            break;
        case 13:
            cout << 'D';
            break;
        case 14:
            cout << 'E';
            break;
        case 15:
            cout << 'F';
            break;
        }
    }

    return 0;
}
