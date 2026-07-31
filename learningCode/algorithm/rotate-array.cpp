/*
 * 力扣：189. 轮转数组
 * 2026-07-31
*/

#include <algorithm>
#include <iostream>
#include <vector>

class Solution
{
  public:
    void rotate(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin()+k);
        std::reverse(nums.begin()+k, nums.end());
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    std::vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> arr2 = {-1, -100, 3, 99};

    s.rotate(arr2, 2);
    for (auto iter : arr2)
    {
        std::cout << iter << " ";
    }
    return 0;
}

