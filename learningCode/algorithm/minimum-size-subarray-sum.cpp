/*
* 力扣：209. 长度最小的子数组
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int minSubArrayLen(int target, std::vector<int> &nums)
    {
        int ans = INT_MAX;
        int sum = 0;
        for (int left = 0, right = 0; right < nums.size(); right++)
        {
            sum += nums[right];
            while (sum >= target && left <= right)
            {
                ans = std::min(ans, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

int main(int argc, char *argv[])
{
    std::vector<int> nums = {1,1,1,1,1,1,1,1};
    Solution s;
    std::cout << s.minSubArrayLen(11, nums);

    return 0;
}
