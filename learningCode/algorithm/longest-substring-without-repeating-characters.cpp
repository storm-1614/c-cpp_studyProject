/*
 * 力扣 3. 无重复字符的最长子串
 * 滑动窗口、剪枝
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

class Solution
{
  public:
    int lengthOfLongestSubstring(std::string s)
    {
        int answer = 0, len = 0;
        std::unordered_map<char, int> charList;
        for (int left = 0, right = 0; right < s.size(); right++)
        {
            charList[s[right]]++;
            while (charList[s[right]] > 1)
            {
                charList[s[left]]--;
                left++;
            }
            answer = std::max(answer, right - left + 1);
        }
        return answer;
    }
};

int main(int argc, char *argv[])
{
    std::string str = "bbbbbb";
    Solution s;
    std::cout << s.lengthOfLongestSubstring(str);

    return 0;
}
