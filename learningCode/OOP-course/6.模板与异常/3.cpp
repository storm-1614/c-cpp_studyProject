/*
 * =====================================================================================
 *
 *       Filename:  3.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  06/13/2026 02:48:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>

std::array<int, 10> a;

template <typename Type, size_t size> class Array
{
  private:
    Type data[size] = {0};

  public:
    Array(std::initializer_list<Type> init)
    {
        std::copy(init.begin(), init.end(), data);
    }

    Type *begin()
    {
        return data;
    }

    Type *end()
    {
        return data + size;
    }

    void sort()
    {
        std::sort(data, data + size);
    }
    void reverse()
    {
        std::reverse(data, data + size);
    }

    long find(Type target)
    {
        for (size_t index = 0; index < size; index++)
        {
            if (data[index] == target)
            {
                return index;
            }
        }
        return -1;
    }

    long long sum()
    {
        long long res = 0;
        for (size_t index = 0; index < size; index++)
        {
            res += data[index];
        }
        return res;
    }
};

int main(int argc, char *argv[])
{
    Array<int, 5> int_array = {1, 5, 2, 2, 9};
    Array<double, 5> double_array = {4.3, 11.2, 31.1, 5, 12.2};

    std::cout << "整形数组：";
    for (auto iter : int_array)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    std::cout << "求和：" << int_array.sum() << std::endl;
    std::cout << "查找：" << int_array.find(9) << std::endl;

    std::cout << "排序:";
    int_array.sort();

    for (auto iter : int_array)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    std::cout << "倒置：";
    int_array.reverse();
    for (auto iter : int_array)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    std::cout << "双精度类型数组：";
    for (auto iter : double_array)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    std::cout << "求和：" << double_array.sum() << std::endl;
    std::cout << "查找：" << double_array.find(11.2) << std::endl;

    std::cout << "排序：";
    double_array.sort();
    for (auto iter : double_array)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    std::cout << "倒置：" << std::endl;
    double_array.reverse();
    for (auto iter : double_array)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    return 0;
}
