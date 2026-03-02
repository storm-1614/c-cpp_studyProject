/*
 * 搜索二维矩阵
 */

#include <iostream>
#include <vector>

bool searchMatrix_1(std::vector<std::vector<int>> &matrix, int target)
{
    // 二分查找定位目标行
    int m = matrix.size(), n = matrix[0].size();
    int top = -1, bottom = m, mid = 0, row;
    int left = -1, right = n;
    while (top + 1 != bottom)
    {
        mid = top + (bottom - top) / 2;
        if (matrix[mid][0] <= target && target <= matrix[mid][n - 1])
            break;
        else if (matrix[mid][0] > target)
            bottom = mid;
        else
            top = mid;
    }
    // 没有找到合适的行
    if (top > bottom)
        return false;

    row = mid;
    left = -1, right = n;

    // 在目标行内进行二分查找
    while (left + 1 != right)
    {
        mid = left + (right - left) / 2;
        if (matrix[row][mid] == target)
            return true;
        else if (matrix[row][mid] < target)
            left = mid;
        else
            right = mid;
    }
    return false;
}

/*
 * 整体二分查找
 */
bool searchMatrix_2(std::vector<std::vector<int>> &matrix, int target)
{
    int m = matrix.size(), n = matrix[0].size();
    int left = -1, right = m * n, mid;
    int row, col;

    while (left + 1 != right)
    {
        mid = left + (right - left) / 2;
        row = mid / n;
        col = mid % n;

        if (matrix[row][col] < target)
            left = mid;
        else if (matrix[row][col] > target)
            right = mid;
        else
            return true;
    }
    return false;
}

/*
 * 考虑二叉搜索树
 * 从右上角开始搜索，每次淘汰一整行或一整列
 * 复杂度：O(log(m*n))
 */
bool searchMatrix_3(std::vector<std::vector<int>> &matrix, int target)
{
    int m = matrix.size(), n = matrix[0].size();
    int i = 0, j = n - 1;
    while (i < m && j >= 0)
    {
        if (matrix[i][j] == target)
            return true;
        matrix[i][j] > target ? j-- : i++;
    }
    return false;
}

bool (*searchMatrix)(std::vector<std::vector<int>> &, int) = searchMatrix_1;

int main(int argc, char *argv[])
{
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};

    // matrix = {{1, 3}};

    std::cout << (searchMatrix(matrix, 3) ? "True" : "False");

    return 0;
}
