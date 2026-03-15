/*
 * 424. 替换后的最长重复字符
 * 滑动窗口、哈希表
 *
 * 给你一个字符串 `s` 和一个整数 `k` 。你可以选择字符串中的任一字符，并将其更改为任何其他大写英文字符。该操作最多可执行
 * `k` 次。在执行上述操作后，返回 包含相同字母的最长子字符串的长度。
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

class Solution
{
  public:
    /*
     * 要求 maxCount 只增不减（即窗口右移时只考虑新加入的字符是否让最大计数变大）
     */
    int characterReplacement(std::string s, int k)
    {
        std::unordered_map<char, int> count;
        int left = 0;
        int maxCount = 0;
        int maxLength = 0;
        int right, winLength;

        for (right = 0; right < s.length(); right++)
        {
            count[s[right]]++;
            // maxCount = std::max(std::max_element(count.begin(), count.end())->second, maxCount);
            // maxCount = std::max_element(count.begin(), count.end())->second;
            maxCount = std::max(maxCount, count[s[right]]);

            winLength = right - left + 1;

            if (winLength - maxCount > k)
            {
                count[s[left]]--;
                left++;
            }
            maxLength = std::max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    std::cout << s.characterReplacement("AABABBA", 1);

    return 0;
}
