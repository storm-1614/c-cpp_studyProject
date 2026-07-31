# 2026-07-31：189. 轮转数组
[leetcode 189 轮转数组](https://leetcode.cn/problems/rotate-array/description/)  
给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。  

朴素解法：  
``` cpp
class Solution
{
  public:
    void rotate(std::vector<int> &nums, int k)
    {
        int n = nums.size();
        std::vector<int> res(n, 0);
        for (int i = 0; i < n; i++)
        {
            res[(i + k) % n] = nums[i];
        }
        nums = res;
    }
};
```

三次反转法：  

第一次反转将后面的倒置整体换位置，然后局部反转将倒置抵消，只剩下换位。  
``` cpp
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
```

