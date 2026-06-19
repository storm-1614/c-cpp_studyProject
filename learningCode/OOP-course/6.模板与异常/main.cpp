#include <iostream>
using namespace std;


// 求最大元素的函数模板
template <typename T>
T findMax(T arr[], int size)
{
    T maxVal = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

// 求最小元素的函数模板
template <typename T>
T findMin(T arr[], int size)
{
    T minVal = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < minVal)
            minVal = arr[i];
    return minVal;
}

int main()
{
    int intArr[] = {3, 1, 7, 2, 9, 5};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);

    cout << "int 数组:    最大=" << findMax(intArr, intSize)
         << ", 最小=" << findMin(intArr, intSize) << endl;

    double dblArr[] = {3.14, 1.58, 7.23, 2.71, 9.80};
    int dblSize = sizeof(dblArr) / sizeof(dblArr[0]);

    cout << "double 数组: 最大=" << findMax(dblArr, dblSize)
         << ", 最小=" << findMin(dblArr, dblSize) << endl;

    char charArr[] = {'a', 'z', 'm', 'b', 'w'};
    int charSize = sizeof(charArr) / sizeof(charArr[0]);

    cout << "char 数组:   最大=" << findMax(charArr, charSize)
         << ", 最小=" << findMin(charArr, charSize) << endl;

    return 0;
}