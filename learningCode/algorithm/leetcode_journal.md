## 2026-07-31：189. 轮转数组
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


## 2026-08-01: 121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。  
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。  
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。  

只需要维护一个最小价格，和当前价格进行比较来计算全局最高价格就可以。  

``` cpp
class Solution
{
  public:
    int maxProfit(std::vector<int> &prices)
    {
        int max_profit = 0, profit;
        int min_salary = prices[0];
        int i, n = prices.size();
        for (i = 1; i < n; i++)
        {
            if (prices[i] < min_salary)
            {
                min_salary = prices[i];
            }
            profit = prices[i] - min_salary;
            if (profit > max_profit)
                max_profit = profit;
        }
        return max_profit;
    }
};
```

## 2026-08-01 74. 搜索二维矩阵
给你一个满足下述两条属性的 m x n 整数矩阵：  
- 每行中的整数从左到右按非严格递增顺序排列。
- 每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。  
你必须编写一个时间复杂度为 O(log(m * n)) 的解决方案。  

---

严格递增比较简单，主要就是二分搜索解决。  

第一种是整体二分搜索，也就是把二维数组变成一维的。  
``` cpp
/* 整体二分查找
 * 注意二分查找边界条件
 */
class Solution1
{
  public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int rows = matrix.size(), cols = matrix[0].size();
        int n = rows * cols;
        int left = -1, right = n, mid, row, col;
        while (left + 1 != right)
        {
            mid = left + (right - left) / 2;
            row = mid / cols;
            col = mid % cols;
            // printf("(%d, %d)=%d %d\n", col, row, m, matrix[row][col]);
            // printf("left = %d, right = %d\n", left, right);
            if (matrix[row][col] > target)
                right = mid;
            else if (matrix[row][col] < target)
                left = mid;
            else
                return true;
        }
        return false;
    }
};
```

除此之外可以先定位到目标范围行再查找，这样也是可以到 $O(\log(m \times n))$  

``` cpp
class Solution2
{
  public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int rows = matrix.size(), cols = matrix[0].size();
        int top = -1, bottom = rows, mid, row;
        int left = -1, right = cols;
        // 搜索目标行
        while (top + 1 != bottom)
        {
            mid = top + (bottom - top) / 2;
            if (matrix[mid][0] > target)
                bottom = mid;
            else if (matrix[mid][cols - 1] < target)
                top = mid;
            else
                break;
        }
        row = mid;

        while (left + 1 != right)
        {
            mid = left + (right - left) / 2;
            if (matrix[row][mid] > target)
                right = mid;
            else if (matrix[row][mid] < target)
                left = mid;
            else
                return true;
            // printf("(%d, %d)\n", ro

            w, mid);
        }
        return false;
    }
};
```


还可以利用二叉查找的思想来求。  


``` cpp
// 二叉搜索
class Solution3
{
  public:
    bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
    {
        int rows = matrix.size(), cols = matrix[0].size();
        int x = cols - 1, y = 0;
        while (x >= 0 && y < cols)
        {
            //printf("(%d, %d)\n", x, y);
            if (matrix[y][x] < target)
                y++;
            else if (matrix[y][x] > target)
                x--;
            else
                return true;
        }
        return false;
    }
};
```

## 167. 两数之和 II - 输入有序数组
给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，请你从数组中找出满足相加之和等于目标数 target 的两个数。如果设这两个数分别是 numbers[index1] 和 numbers[index2] ，则 1 <= index1 < index2 <= numbers.length 。  
以长度为 2 的整数数组 [index1, index2] 的形式返回这两个整数的下标 index1 和 index2。  
你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。  
你所设计的解决方案必须只使用常量级的额外空间。  

---

用双指针做两端向内移动，一定能得到两数之和。  
左右内缩，答案始终在 [left, right] 之间，不会被跳过。  

``` cpp
class Solution
{
  public:
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        std::vector<int> result;
        size_t n = numbers.size();
        int left = 0, right = n - 1;
        while (left < right)
        {
            int res = numbers[left] + numbers[right];
            if (res == target)
            {
                result = {left + 1, right + 1};
                return result;
            }
            else if (res < target)
                left++;
            else
                right--;
        }
        return result;
    }
};
```


