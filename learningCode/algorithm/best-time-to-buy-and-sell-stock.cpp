/*
 * 买卖股票的最佳时机
 * storm-1614
 *
 * 只要在历史最低点买入即可
 */

#include <iostream>
#include <vector>

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

int main(int argc, char *argv[])
{

    Solution s;
    std::vector<int> arr = {7, 1, 5, 3, 6, 4};
    std::cout << s.maxProfit(arr);
    return 0;
}
