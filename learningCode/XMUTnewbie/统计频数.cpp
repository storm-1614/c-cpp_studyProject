/*
* storm-1614
* 2025-10-14 19:12
* 统计频数
*/


#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int find(std::vector<std::pair<char, int>> m, char value)
{
    for (int i = 0; i < m.size(); i++)
    {
        if (m.at(i).first == value)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int index;
    std::string str;
    std::string res;
    char temp[10];
    std::vector<std::pair<char, int>> m;
    std::getline(std::cin, str);

    for (auto it : str)
    {
        if (isalpha(it))
        {
            if ((index = find(m, it)) == -1)
            {
                m.emplace_back(it, 1);
                res += it;
                res += "1";
            }
            else
            {
                m.at(index).second++;
                sprintf(temp, "%d", m.at(index).second);
                res += it;
                res += temp;
            }
        }
        else
            res += it;
    }

    std::reverse(res.begin(), res.end());
    std::cout << res;

    return 0;
}
