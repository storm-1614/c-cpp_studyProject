/*
* 买卖股票的最佳时机
* storm-1614
*
* 只要在历史最低点买入即可
*/

#include <climits>
#include <iostream>
#include <vector>

class Solution
{
  public:
    int maxProfit(std::vector<int> &prices)
    {
        int buy = INT_MAX;
        int profit = 0;
        for (auto sell : prices)
        {
            if (sell < buy)
                buy = sell;
            else if (sell - buy > profit)
            {
                profit = sell - buy;
            }
        }
        return profit;
    }
};

int main(int argc, char *argv[])
{

    Solution s;
    std::vector<int> arr = {7,1,5,3,6,4};
    std::cout << s.maxProfit(arr);
    return 0;
}
