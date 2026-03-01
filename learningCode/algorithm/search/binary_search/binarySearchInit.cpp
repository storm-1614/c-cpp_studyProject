/*
 * 二分查找，不考虑重复元素
 * binary search
 *
 * 问题：
 * 给定一个长度为 n 的数组 nums ，元素按从小到大的顺序排列且不重复。请查找并返回元素 target
 * 在该数组中的索引。若数组不包含该元素，则返回 -1。
 */

#include <iostream>
#include <vector>

int binarySearch(std::vector<int> &list, int target)
{
    int len = list.size();
    int l = -1, r = len, m;
    while (l + 1 != r)
    {
        // m = (l + r) / 2;  l + r 容易大数越界，所以改用下面的算法
        m = l + (r - l) / 2;
        if (list[m] < target)
            l = m;
        else if (list[m] > target)
            r = m;
        else
            return m;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    std::vector<int> arr = {1, 5, 42, 132, 435};
    for (auto iter : arr)
        std::cout << binarySearch(arr, iter) << std::endl;
    return 0;
}
