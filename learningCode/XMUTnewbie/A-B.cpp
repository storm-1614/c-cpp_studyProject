/*
 * storm-1614
 * 2025-10-20 18:39
 * A - B
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::string str1;
    std::string str2;
    int max, temp = 0;
    std::cin >> str1 >> str2;

    // 获取最大长度
    max = str1.length() > str2.length() ? str1.length() : str2.length();

    std::vector<int> num1(max, 0), num2(max, 0);
    std::vector<int> res(max, 0);

    for (int i = 0; i < str1.length(); i++)
        num1[max - i - 1] = str1[str1.length() - i - 1] - '0';

    for (int i = 0; i < str2.length(); i++)
        num2[max - i - 1] = str2[str2.length() - i - 1] - '0';

    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());

    for (int i = 0; i < max; i++)
    {
        if (num1[i] < num2[i])
        {
            res[i] = num1[i] + 10 - num2[i];
            num1[i + 1]--;
        }
        else
            res[i] = num1[i] - num2[i];
    }
    // std:reverse(res.begin(), res.end());

    // 又是依托不知道什么东西的判断💩
    for (int i = res.size() - 1; i >= 0; i--)
    {
        /*
         * 缝缝补补
         * 关键在于 res.size() > 2
         * 如果是 4 - 2 会输出 02
         * 如果是 11 - 3 会输出 07
         * 所以输出 0 要在长度大于 2 的时候开始
         * 这就很玄学
         */
        if (i == 0 && res.size() > 2 && temp == 0)
            std::cout << 0;

        temp += res[i];
        if (temp == 0)
            continue;
        else
            std::cout << res[i];
    }
    return 0;
}
