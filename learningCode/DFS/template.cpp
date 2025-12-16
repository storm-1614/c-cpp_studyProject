/*
* 广度优先搜索算法模板
* 使用多维数组
*/

#include <bits/stdc++.h>

using namespace std;
int a[110][110]; // 迷宫数组
int p[10010][4]; // 记录数组
int n, m;
int head = 1;
int tail = 1;

int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, 1, 0, -1, 0};

int tx, ty;
int k = 1;

void print(int x)
{
    cout << "(" << p[x][1] << ", " << p[x][2] << ") ";
    if (p[x][3] != 0)
    {
        print(p[x][3]);
    }
}

int main()
{
    cin >> n >> m;
    a[1][1] = 1;
    p[1][1] = 1;
    p[1][2] = 1;
    p[1][3] = 0;
    while (head <= tail)
    {
        for (int i = 1; i <= 4; i++)
        {
            tx = p[head][1] + dx[i];
            ty = p[head][2] + dy[i];
            if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && a[tx][ty] == 0)
            {
                tail++;
                p[tail][1] = tx;
                p[tail][2] = ty;
                p[tail][3] = head;
                a[tx][ty] = k + 1;
                k++;
                if (tx == n && ty == m)
                    print(tail);
            }
        }
        head++;
    }
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
