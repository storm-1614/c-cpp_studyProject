/*
 * =====================================================================================
 *
 *       Filename:  2.cpp
 *
 *    Description: 求数组中的最大和最小 
 *
 *        Version:  1.0
 *        Created:  06/13/2026 02:40:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
T getMax(const std::vector<T> &array)
{
    return *std::max_element(array.begin(), array.end());
}

template<typename T>
T getMin(const std::vector<T> &array)
{
    return *std::min_element(array.begin(), array.end());
}

int main (int argc, char *argv[]) {
    std::vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    std::vector<double> b = {3.14, 2.71, 1.41, 1.73};
    std::vector<char> c = {'d', 'a', 'z', 'b'};

    std::cout << "int max: " << getMax(a) << ", min: " << getMin(a) << std::endl;
    std::cout << "double max: " << getMax(b) << ", min: " << getMin(b) << std::endl;
    std::cout << "char max: " << getMax(c) << ", min: " << getMin(c) << std::endl;

    return 0;
} 
