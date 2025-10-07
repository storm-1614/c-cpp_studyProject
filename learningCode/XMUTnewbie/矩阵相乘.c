/*
 * storm-1614
 * 2025-10-04 10:13
 * 矩阵相乘
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int m, n, k;
    scanf("%d%d%d", &m, &n, &k);
    int matrix1[m][n], matrix2[n][k];
    int res[m][k];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix1[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            scanf("%d", &matrix2[i][j]);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int temp = 0;
            for (int l = 0; l < n;l++)
            {
                temp += matrix1[i][l]*matrix2[l][j];
            }
            res[i][j] = temp;
        }
    }

    for (int i = 0; i < m;i++)
    {
        for (int j = 0; j < k;j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }


    return 0;
}
