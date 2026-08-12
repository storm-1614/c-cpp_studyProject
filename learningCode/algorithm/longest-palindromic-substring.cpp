#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Solution1
{
  public:
    bool isPalindrome(const std::string &s, int left, int right)
    {
        while (left < right)
        {
            if (s[left] != s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }
    std::string longestPalindrome(std::string s)
    {
        int n = s.size();
        if (n < 2)
            return s;
        int maxLen = 1, start = 0;
        int i, j;
        for (i = 0; i < n; i++)
        {
            for (j = i; j < n; j++)
            {
                if (isPalindrome(s, i, j) && (j - i + 1) > maxLen)
                {
                    start = i;
                    maxLen = j - i + 1;
                }
            }
        }
        return s.substr(start, maxLen);
    }
};

class Solution2
{
  public:
    std::string longestPalindrome(std::string s)
    {
        int n = s.size();
        if (n < 2)
            return s;
        // dp[i][j] = true 代表 s[i..j] 是回文
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

        int start = 0;   // 最长回文的起始位置
        int max_len = 1; // 记录最长回文的长度

        // 单个字符必然回文
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int len = 2; len <= n; len++)
        {
            for (int i = 0; i + len - 1 < n; i++)
            {
                int j = i + len - 1;
                if (s[i] != s[j])
                {
                    dp[i][j] = false;
                    continue;
                }
                // 首尾相等看中间部分
                if (len == 2)
                    dp[i][j] = true; // 长度为 2,首尾相等即可
                else
                    dp[i][j] = dp[i + 1][j - 1]; // 长度 >= 3，取决于去掉首尾后的部分

                // 更新
                if (dp[i][j] && len > max_len)
                {
                    start = i;
                    max_len = len;
                }
            }
        }
        return s.substr(start, max_len);
    }
};

class Solution
{
  public:
    std::pair<int, int> expandAroundCenter(const std::string &s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }
    std::string longestPalindrome(std::string s)
    {
        if (s.empty())
            return "";
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); i++)
        {
            // 奇数长子串
            auto [l1, r1] = expandAroundCenter(s, i, i);
            if (r1 - l1 > end - start)
            {
                start = l1;
                end = r1;
            }

            // 偶数长度
            auto [l2, r2] = expandAroundCenter(s, i, i + 1);
            if (r2 - l2 > end - start)
            {
                start = l2;
                end = r2;
            }
        }
        return s.substr(start, end - start + 1);
    }
};

int main(int argc, char *argv[])
{
    std::string str = "babad";
    Solution s;

    std::cout << s.longestPalindrome(str);
    return 0;
}
