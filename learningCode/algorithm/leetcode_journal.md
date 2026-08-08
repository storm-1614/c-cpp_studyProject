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

## 3. 无重复字符的最长子串
给定一个字符串 s ，请你找出其中不含有重复字符的最长子串的长度。  

---
用滑动窗口配合哈希表就可以求解。  

``` cpp
class Solution
{
  public:
    int lengthOfLongestSubstring(std::string s)
    {
        int left = 0, right = 0, n = 0, max_n = 0;
        int len = s.size();
        std::unordered_map<char, int> map;
        while (right < len)
        {
            if (map.find(s[right]) == map.end())
            {
                n++;
                map[s[right]] = right;
                max_n = std::max(max_n, n);
                right++;
            }
            else
            {
                map.erase(s[left]);
                left++;
                n--;
            }
        }
        return max_n;
    }
};
```

这个代码效率不够，因为每走一步都有 if 判断是否有重复字符。实际可以优化为嵌套循环：  
``` cpp
class Solution
{
  public:
    int lengthOfLongestSubstring(std::string s)
    {
        int left, right, ans = 0;
        int len = s.size();
        std::unordered_map<char, int> charList;
        for (left = 0, right = 0; right < len; right++)
        {
            charList[s[right]]++;
            while (charList[s[right]] > 1)
            {
                charList[s[left]]--;
                left++;
            }
            ans = std::max(ans, right - left + 1);
        }
        return ans;
    }
};
```

这样将判断语句放在循环内，当有重复字符时循环缩短左指针相较第一版代码观感更好。  

## 2026-08-04 567. 字符串的排列
给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的 。如果是，返回 true ；否则，返回 false 。  
换句话说，s1 的排列之一是 s2 的 子串 。  

---
只要是一种排列，那反正字母数量一样就行。那就用频数数组来存好了。C++ 的 vector 有重载`==` 运算符，直接用：  

``` cpp
class Solution
{
  public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        std::vector<int> window(26, 0);
        std::vector<int> need(26, 0);
        int left, right, n = s1.size();
        for (auto iter : s1)
        {
            need[iter - 'a']++;
        }
        for (left = 0, right = 0; right < s2.size(); right++)
        {
            if (right - left + 1 < n)
            {
                window[s2[right] - 'a']++;
                continue;
            }
            window[s2[right] - 'a']++;
            if (window == need)
                return true;
            window[s2[left] - 'a']--;
            left++;
        }
        return false;
    }
};
```

其实这样不是最简的，还可以去掉些冗余的判断：  

``` cpp
bool checkInclusion(std::string s1, std::string s2)
{
    std::vector<int> window(26, 0); // 当前窗口的字符频次
    std::vector<int> need(26, 0);   // s1 的字符频次
    int left, right, i;

    if (s1.length() > s2.length())
        return false;

    // 遍历 s1 填好需求数组
    for (i = 0; i < s1.length(); i++)
        need[s1[i] - 'a'] += 1;

    left = 0;
    for (right = 0; right < s2.length(); right++)
    {
        window[s2[right] - 'a'] += 1;

        if (right - left + 1 > s1.length())
        {
            window[s2[left] - 'a'] -= 1;
            left++;
        }
        if (window == need)
            return true;
    }
    return false;
}
```

## 2026-08-05 406. 根据身高重建队列
假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [$h_i$, $k_i$] 表示第 i 个人的身高为 hi ，前面 正好 有 $k_i$ 个身高大于或等于 hi 的人。

请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [$h_j$, $k_j$] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。  

---
核心就在于怎么排序与插入。这是一个数学问题。  

最终推导出来的排序规则是：**身高 h 降序，若身高相同，则按 k 升序。**    
我们采用数学归纳法来证明：  

假设排序后的人依次为：$p_1, p_2, ..., p_n$  
有命题 $P(i)$：在完成前 i 个人的插入操作后，`ans` 中这 i 个人构造的序列，对于这 i 个人中的每一个人而言，其前面身高大于等于他的人数的恰好等于他自身的 k 值。  

当 $i=0$ 时，`ans` 为空，命题显然成立。  

假设 $P(i)$ 成立，现在要插入第 i + 1 个人 $p=(h,k)$  
我们执行 `ans.insert(ans.begin() + k, p)` 即把 p 插入到 ans 的第 k 个位置（从 0 开始索引）。  

当前 ans 中已有 i 个人，且他们都满足 身高 $\geq h$ （由排序性质得出）。我们恰好在索引 k 处插入，因此 p 的前面恰好正好有 k 个元素。而这 k 个元素的身高都必然 $\geq h$，且不存在任何身高 $< h$ 的元素，因为矮个子尚未被插入。 因此，p 前面身高大于等于他的人恰好为 k，p 满足条件。  

对于已插入到人 $q=(h_q, k_q)$，(q 在插入 p 之前就已经在 ans 中)分两种情况：  
A. q 原来在插入位置 k 的前面，插入 p 后 q 仍然在 p 前面，其前面的元素集合没有发生任何变化，因此 q 的 k 值不变。  
B. q 原来在插入位置 k 的后面（或正好被 k 位置挤到后面），插入 p 后，q 会向后移动一位，p 会被添加到 q 的前面，此时检查 p 是否会记录 q 的更高或等高计数：  

如果 $h_q > h$  ，则 q 更矮，不会记录 q 的计数，所以 q 的 k 值保持不变。如果 $h_q = h$ 那么 q 与 p 等高。因为排序是同身高按 k 升序，而 p 是第 i + 1 个被处理的，q 先于 p 被处理，说明 $k_q < k$ 也就是说，q 的原始 k 值小于 p 的原始 k 值。  
基于有效解的隐含条件，$k_q < k$ 意味着 q 在最终队列必然位于 q 的前面。因此， q 不可能远比在索引 k 的后面，它必然在前面的位置，所以这种冲突不可能发生。  
因此所有成员的 k 值在插入 p 后全部保持不变。  

得证。  
``` cpp
class Solution
{
  public:
    std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>> &people)
    {
        int i;
        std::vector<std::vector<int>> ans;
        std::sort(people.begin(), people.end(), [](const std::vector<int> &x, const std::vector<int> &y) {
            if (x[0] != y[0])
                return x[0] > y[0];
            return x[1] < y[1];
        });
        for (i = 0; i < people.size(); i++)
            ans.insert(ans.begin() + people[i][1], people[i]);
        return ans;
    }
};
```

## 2026-08-06 713. 乘积小于 K 的子数组

给你一个整数数组 nums 和一个整数 k ，请你返回子数组内所有元素的乘积严格小于 k 的**连续子数组**的数目。  

---
核心是滑动窗口。  
只需要维护一个窗口 `[left, right]` 保证窗口内的所有元素严格小于 k。可以发现有任意 $left'\in [left, right]$ 开头的子数组的层积也都满足小于 k。所以对于每个 right，满足条件的子数组就是 `right - left + 1`。  

由此可以得到算法：  
``` cpp
class Solution
{
  public:
    int numSubarrayProductLessThanK(std::vector<int> &nums, int k)
    {
        int left, right, mul = 1;
        int n = nums.size();
        int ans = 0;
        for (left = 0, right = 0; right < n; right++)
        {
            mul *= nums[right];
            while (mul >= k && left <= right)
            {
                mul /= nums[left];
                left++;
            }
            ans += right - left + 1;
        }
        return ans;
    }
};
```

只需要在窗口乘积大于 k 时，将 left 向右移动直到窗口回归小于 k 此时就有如上所写的满足条件子数组。  

## 2026-08-07 424. 替换后的最长重复字符
给你一个字符串 s 和一个整数 k 。你可以选择字符串中的任一字符，并将其更改为任何其他大写英文字符。该操作最多可执行 k 次。  
在执行上述操作后，返回 包含相同字母的最长子字符串的长度。  

---
滑动窗口 + 哈希表。因为是子串，可以考虑滑动窗口。通过哈希表记录当前窗口的字符数量。因为窗口从左向右滑动，所以最大的那个字符永远可能出现在 s[right]。只需比较该值即可。  
对于改写字符无法在 k 个内完成的。因为求的是子串，只需要 left 向右缩短窗口，更新哈希表减去 s[left]，直至窗口长度 - s[right] 数量小于等于 k 即可回归满足的窗口。此时计算最长字符串。  

``` cpp
class Solution
{
  public:
    int characterReplacement(std::string s, int k)
    {
        std::unordered_map<char, int> count;
        int maxCount = 0;
        int maxLength = 0;
        int n = s.length();
        int left, right;
        for (left = 0, right = 0; right < n; right++)
        {
            count[s[right]]++;
            maxCount = std::max(maxCount, count[s[right]]);
            while ((right - left + 1) - maxCount > k && left <= right)
            {
                count[s[left]]--;
                left++;
            }
            maxLength = std::max(maxLength, right - left + 1);
        }
        return maxLength;
    }
};
```

## 2026-08-08 209. 长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 target 。  
找出该数组中满足其总和大于等于 target 的长度最小的  [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。  

---

我第一想法是滑动窗口。然后一顿操作又加了 flag 和各种额外的 if 算是通过了。  

``` cpp
class Solution
{
  public:
    int minSubArrayLen(int target, std::vector<int> &nums)
    {
        int n = nums.size();
        int minestLength = INT_MAX;
        int left, right;
        int sum = 0;
        bool flag = false;
        for (left = 0, right = 0; right < n; right++)
        {
            sum += nums[right];
            while (sum >= target && left < right)
            {
                sum -= nums[left];
                left++;
                flag = true;
            }
            if (sum >= target)
                minestLength = std::min(minestLength, right - left + 1);
            if (flag)
                minestLength = std::min(minestLength, right - left + 2);
            flag = false;
        }
        if (minestLength == INT_MAX)
            return 0;
        return minestLength;
    }
};
```

不过显然不太好，效率低下，代码乱。  
然后我发现其实判断在 whlie 循环里面做是最好的。（好傻呀我）  

``` cpp
class Solution
{
  public:
    int minSubArrayLen(int target, std::vector<int> &nums)
    {
        int n = nums.size();
        int minestLength = INT_MAX;
        int left, right;
        int sum = 0;
        for (left = 0, right = 0; right < n; right++)
        {
            sum += nums[right];
            while (sum >= target && left <= right)
            {
                minestLength = std::min(minestLength, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }
        return minestLength == INT_MAX ? 0 : minestLength;
    }
};
```
