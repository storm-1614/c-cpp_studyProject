/*
* 力扣：238. 除了自身以外数组的乘积
* 2026-04-19
*/

#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> productExceptSelf(std::vector<int> &nums)
    {
        size_t n = nums.size();
        std::vector<int> left (n, 1);
        std::vector<int> right(n, 1);
        std::vector<int> answer(n, 1);
        for (int i = 1; i < n; i++)
            left[i] = left[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; i--)
            right[i] = right[i + 1] * nums[i + 1];
        for (int i = 0; i < n; i++)
            answer[i] = right[i] * left[i];
        return answer;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    std::vector<int> nums = {1, 2, 3, 4};
    std::vector<int> ans = s.productExceptSelf(nums);
    for (auto iter:ans)
    {
         std::cout << iter << " ";
    }
    return 0;
}
