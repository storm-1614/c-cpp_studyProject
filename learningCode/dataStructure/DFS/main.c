/*
 * DFS
 *
 * Author: storm1614.top
 * Date: 2026-10-09
 *
 * 标记当前顶点已经访问的
 * 记录当前顶点
 * 遍历当前顶点的邻接点
 * 对尚未访问的邻接点递归执行 DFS
 */

#include <stdbool.h>
#include <stdio.h>

#define MAX_V 10

typedef struct
{
    int adj[MAX_V][MAX_V];
    int degree[MAX_V];
    int n;
} Graph;

void add_edge(Graph *g, int u, int v)
{
    g->adj[u][g->degree[u]++] = v;
    g->adj[v][g->degree[v]++] = u;
}

void dfs_visit(Graph *g, int u, bool visited[])
{
    // 标记已访问
    visited[u] = true;

    // 记录访问顺序
    printf("%d ", u);

    // 遍历所有邻接点
    for (int i = 0; i < g->degree[u]; i++)
    {
        int v = g->adj[u][i];

        // 未访问才递归
        if (!visited[v])
        {
            dfs_visit(g, v, visited);
        }
    }
}

void dfs(Graph *g, int start)
{
    bool visited[MAX_V] = {false};
    dfs_visit(g, start, visited);
}

int main()
{
    Graph g = {.n = 4};

    add_edge(&g, 0, 1);
    add_edge(&g, 0, 2);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);

    dfs(&g, 0);

    return 0;
}
