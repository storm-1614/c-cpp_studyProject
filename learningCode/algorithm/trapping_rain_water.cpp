/*
* 接雨水问题
*/

#include <algorithm>
#include <iostream>
#include <vector>

int trap(std::vector<int> &height)
{
    size_t len = height.size();
    std::vector<int> left_max(len, 0);
    std::vector<int> right_max(len, 0);
    int water = 0, i;

    left_max[0] = height[0];
    for (i = 1; i < len; i++)
        left_max[i] = std::max(left_max[i - 1], height[i]);

    right_max[len - 1] = height[len - 1];
    for (i = len - 2; i >= 0; i--)
        right_max[i] = std::max(right_max[i + 1], height[i]);

    for (i = 0; i < len; i++)
        water += std::min(left_max[i], right_max[i]) - height[i];

    return water;
}

int main()
{
    std::vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    std::vector<int> arr1 = {4,2,0,3,2,5};
    std::cout << trap(arr1);
}
