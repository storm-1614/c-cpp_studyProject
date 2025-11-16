/*
 * storm-1614
 * 2025-11-16 16:54
 * 分词
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::string input;
    std::vector<int> wordLen;
    std::vector<char> cut = {'\n', '\t', ' ', '.', ',', ':', ';'};
    int count = 0;

    char in;
    while ((in = getchar()) != EOF)
        input += in;

    for (auto it : input)
    {
        for (auto c : cut)
        {
            if (it == c)
            {
                wordLen.emplace_back(count);
                count = -1;
            }
        }
        count++;
    }
    for (auto it : wordLen)
    {
        if (it != 0)
            std::cout << it << " ";
    }

    return 0;
}
