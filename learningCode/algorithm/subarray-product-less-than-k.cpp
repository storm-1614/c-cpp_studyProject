/*
 * 力扣 713. 乘积小于 K 的子数组
 * 滑动窗口
 */

#include <iostream>
#include <vector>

class Solution
{
  public:
    int numSubarrayProductLessThanK(std::vector<int> &nums, int k)
    {
        int result = 0;
        int mul = 1;
        for (int left = 0, right = 0; right < nums.size(); right++)
        {
            mul = mul * nums[right];
            while (mul >= k && left <= right) // 注意要 left <= right 保证窗口有元素
            {
                mul /= nums[left];
                left++;
            }
            /*
             * 如果 （left, right) 乘积 < k,则 (left + 1... right, right) 乘积都 < k
             */
            result += (right - left + 1);
        }

        return result;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    std::vector<int> input = {1, 2, 3};
    std::cout << s.numSubarrayProductLessThanK(input, 0);

    return 0;
}
