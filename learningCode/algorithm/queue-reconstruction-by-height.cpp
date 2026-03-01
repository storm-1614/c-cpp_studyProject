/*
 * 根据身高重建队列:贪心
 */

#include <algorithm>
#include <iostream>
#include <vector>
class Solution
{
  public:
    /*
     * 比较函数
     * 按 h 降序，k 升序
     */
    static bool cmp(const std::vector<int> &x, const std::vector<int> &y)
    {
        if (x[0] != y[0])
            return x[0] > y[0];
        return x[1] < y[1];
    }

    /*
     * 算法实现主函数
     *
     */
    static std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>> &people)
    {
        int i;
        std::vector<std::vector<int>> queue;
        /*
         * 对数组排序，排序规则是身高降序，k 值升序
         * x 代表列表中的每个元素
         * x[1] 表示在身高相同的情况下，对 k 值升序排序
         * x[0] 表示对身高降序排序
         */
        std::sort(people.begin(), people.end(), cmp);

        // 遍历排好序的每一个人，把它插入到队列中索引为 k 的位置
        for (i = 0; i < people.size(); i++)
            queue.insert(queue.begin() + people[i][1], people[i]);
        return queue;
    }
};
int main(int argc, char *argv[])
{
    std::vector<std::vector<int>> people = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
    std::vector<std::vector<int>> res = Solution::reconstructQueue(people);
    std::cout << "{";
    for (auto iter = res.begin(); iter < res.end(); iter++)
        std::cout << "{" << iter->at(0) << ", " << iter->at(1) << "}" << (iter != (res.end() - 1) ? ", " : "");
    std::cout << "}";
    return 0;
}
