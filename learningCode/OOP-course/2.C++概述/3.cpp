/*
 * =====================================================================================
 *
 *       Filename:  3.cpp
 *
 *    Description:
 * 编写一个程序，对一个整型数组的元素求和，结果使用全局变量sum存储，另外对数组元素中的奇数求和，结果使用局部变量sum存储，在主程序将两个结果输出。
 *
 *        Version:  1.0
 *        Created:  03/16/2026 05:42:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>

int sum_all(std::vector<int> arr)
{
    int sum = 0;
    for (auto iter : arr)
        sum += iter;
    return sum;
}

int sum_odd(std::vector<int> arr)
{
    int sum = 0;
    for (auto iter : arr)
        sum += (iter % 2 == 1) ? iter : 0;
    return sum;
}

int main(int argc, char *argv[])
{
    std::vector<int> list = {1, 2, 3, 4,5, 6, 7, 8, 9};

    for (auto iter:list)
        std::cout << iter << " ";
    std::cout << std::endl;
    std::cout << "元素求和：" << sum_all(list) << std::endl;
    std::cout << "奇数求和：" << sum_odd(list) << std::endl;

    return 0;
}
