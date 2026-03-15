/*
* 两数之和 II - 输入有序数组
* 使用双指针的方式在空间复杂度为 O(1) 的情况下求解
* 保证一定有唯一的一组解
*
* 正确解 i 和 j 是固定的，初始时左指针 <= i，右指针 >= j
* 只要左指针没到 i,右指针就不会越过 j，只要右指针没到 j，左指针就不会越过 i
*/

#include <iostream>
#include <vector>

class Solution
{
  public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        int left = 0, right = numbers.size() - 1, sum;

        while (left < right)
        {
            sum = numbers[left] + numbers[right];
            if (sum < target)
                left++;
            else if (sum > target)
                right--;
            else
                return {left + 1, right + 1};
        }
        return {-1, -1};
    }
};

int main()
{
    std::vector<int> input = {2, 7, 11, 15};
    Solution s;
    std::vector<int> res = s.twoSum(input, 9);
    for (auto iter : res)
    {
        std::cout << iter << " ";
    }
    return 0;
}
