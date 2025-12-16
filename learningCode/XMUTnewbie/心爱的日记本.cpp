/*
 * 心爱的日记本
 * storm-1614
 * 2025-12-15 12:43
 */

#include <bits/stdc++.h>

using namespace std;

string pageToCode(int n)
{
    n--;
    if (n < 26)
        return string(1, 'A' + n);
    n -= 26;
    if (n < 26 * 27)
    {
        string code;
        int first = n / 27;
        int second = n % 27;
        code += 'A' + first;
        if (second == 0)
            code += '0';
        else
            code += 'A' + second - 1;

        return code;
    }

    n -= 26 * 27;

    string code;

    int first = n / (27 * 27);
    int remain = n % (27 * 27);
    int second = remain / 27;
    int third = remain % 27;
    code += 'A' + first;
    if (second == 0)
    {
        code += '0';
    }
    else
    {
        code += 'A' + second - 1;
    }
    if (third == 0)
    {
        code += '0';
    }
    else
    {
        code += 'A' + third - 1;
    }
    return code;
}

int countChar(int n, char target)
{
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        string code = pageToCode(i);
        for (char ch : code)
        {
            if (target == ch)
                count++;
        }
    }
    return count;
}

int main()
{
    int n;
    char ch;
    cin >> n >> ch;
    cout << pageToCode(n) << endl;
    cout << countChar(n, ch) << endl;
    return 0;
}
