/*
* storm-1614
* 2025-10-05 21:45
* 防御罩的工期
*/


#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    int year, month;
    int yearMinus, monthMinus;
    int count;
    pair<int, int> maxdate, mindate;
    vector<pair<int, int>> date;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        scanf("%d.%d", &year, &month);
        date.emplace_back(year, month);
    }

    maxdate = date.at(0);
    mindate = date.at(0);

    for (auto it : date)
    {
        if (it.first > maxdate.first || it.first == maxdate.first && it.second > maxdate.second)
            maxdate = it;

        if (it.first < mindate.first || it.first == mindate.first && it.second < mindate.second)
            mindate = it;
    }

    yearMinus = maxdate.first - mindate.first - 1;
    if (yearMinus < 0)
        yearMinus = 0;

    if (maxdate.first != mindate.first)
        count = yearMinus * 12 + maxdate.second + 12 - mindate.second;
    else
        count = maxdate.second - mindate.second;

    cout << count;

    return 0;
}
