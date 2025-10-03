/*
 * storm-1614
 * 2025-10-03 17:20
 * 爱美的串儿
 */

#include <cctype>
#include <iostream>
#include <string>

using namespace std;
int main(int argc, char *argv[])
{
    string input;
    string res;
    int n = 0, jump = 0;

    cin >> input;

    for (auto i = input.begin(); i != input.end(); i++)
    {
        n = 0;
        if (isdigit(*i))
        {
            jump = 0;
            for (auto j = i; isdigit(*j); j++)
            {
                n *= 10;
                n += *j - '0';
                jump++;
            }
            for (int j = 0; j < n; j++)
                res += *(i + jump);
            i += jump;
        }
        else
            res += *i;
    }

    cout << res;
    return 0;
}
