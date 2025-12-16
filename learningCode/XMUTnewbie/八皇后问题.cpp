/*
 * storm-1614
 * 八皇后问题
 * 2025-12-05 21:54
 */

#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
    std::vector<std::pair<int, int>> hi;
    int matrix[8][8] = {0};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 1)
            {
                hi.emplace_back(i, j);
            }
        }
    }

    for (auto a : hi)
    {
        for (auto b : hi)
        {
            if (a == b)
                continue;
            if (b.second == a.second)
            {
                printf("false");
                return 0;
            }
            if (abs(b.second - a.second) == abs(a.first - b.first))
            {
                printf("false");
                return 0;
            }
        }
    }
    printf("true");
    return 0;
}
