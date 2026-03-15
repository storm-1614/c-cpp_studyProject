/*
 * 力扣：567. 字符串的排列
 * 定长滑动窗口 + 频次数组
 */

#include <iostream>
#include <string>
#include <vector>

bool checkInclusion(std::string s1, std::string s2)
{
    std::vector<int> window(26, 0); // 当前窗口的字符频次
    std::vector<int> need(26, 0);   // s1 的字符频次
    int left, right, i;

    if (s1.length() > s2.length())
        return false;

    // 遍历 s1 填好需求数组
    for (i = 0; i < s1.length(); i++)
        need[s1[i] - 'a'] += 1;

    left = 0;
    for (right = 0; right < s2.length(); right++)
    {
        window[s2[right] - 'a'] += 1;

        if (right - left + 1 > s1.length())
        {
            window[s2[left] - 'a'] -= 1;
            left++;
        }
        if (window == need)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    std::cout << (checkInclusion("ab", "eidbaooo") ? "true" : "false") << std::endl;
    std::cout << (checkInclusion("ab", "eidboaoo") ? "true" : "false") << std::endl;
    return 0;
}
