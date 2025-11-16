/*
 * 循环链表
 * 约瑟夫环
 */

#include <cstdio>
#include <cstdlib>

typedef int DataType;

// 循环链表结点的定义
typedef struct node
{
    DataType data;
    struct node *link;
} CircNode, *CircList;

// 用后插法建立循环单链表的算法
// 根据数组 `A[n]` 建立一个循环单链表，表中各元素次序与 `A[n]` 中元素次序相同
void createCircList(CircList &first, DataType A[], int n)
{
    first = (CircNode *)malloc(sizeof(CircNode));
    first->link = first; // 构成循环空链表
    CircNode *r = first; // 设置尾指针 r
    for (int i = 0; i < n; i++)
    {
        CircNode *s;
        s = (CircNode *)malloc(sizeof(CircNode));
        if (!s)
        {
            printf("内存分配错误!\n");
            exit(1);
        }
        s->data = A[i];
        s->link = r->link;
        r->link = s; // *s 链 到 *r 后
        r = s;       // r 进到新链尾
    }
}

// 将新元素 x 插入在循环链表中第 i (1 <= i) 个结点的位置。
// 如果插入失败返回 0,否则返回 1
int Insert(CircNode *first, int i, DataType &x)
{
    if (i < 1)
        return 0;

    CircNode *p = first, *q;
    int k = 0;
    while (p->link != first && k < i - 1)
    {
        p = p->link;
        k++;
    }

    if (p->link == first)
        return 0;

    q = p->link;
    p->link = q->link;
    x = q->data;
    free(q);
    return 1;
}

// 将链表中的第 i 个元素删去，通过引用参数 x 返回该元素值。
// 如果 i 不合理则删除失败，函数返回 0 ，否则函数返回 1
int Remove(CircNode *first, int i, DataType &x)
{
    // i 太小不合理
    if (i < 1)
        return 0;
    CircNode *p = first, *q;
    int k = 0;
    while (p->link != NULL && k < i - 1)
    {
        p = p->link;
        k++;
    }
    // i 太大，被删结点不存在
    if (p->link == NULL)
        return 0;
    q = p->link;       // 用 q 保存第 i 号结点
    p->link = q->link; // 从链上摘下第 i 号结点
    x = q->data;       // x 存被删结点数据
    free(q);           // 释放结点
    return 0;
}

/*
 * 约瑟夫环问题
 *  n 个人围成一个环，选取一个正整数 m 作为报告值
 *  第一个人按顺时针方向自 1 开始顺序报数，报到 m 时停止报数，报 m 的人出列
 *  如此下去，直到环中只剩下一个人他就是优胜者
 *
 *  s 是起始结点号
 */
void Josephus(CircList &list, int s, int m, int n)
{
    CircList p = list->link, pr = list;
    int i, j;
    // 指针 p 进到第 s 个结点
    for (int i = 1; i < s; i++)
        p = p->link;
    for (i = 0; i < n; i++)
    // 执行 n 次
    {
        for (j = 0; j < m; j++)
        // 数 m - 1 个人
        {
            pr = p;
            p = p->link;
            if (p == list)
            // 若 *p 为头结点则跳过
            {
                pr = p;
                p = p->link;
            }
        }
        printf("%d ", p->data); // 输出
        // 删去第 m 个结点
        pr->link = p->link;
        free(p);
        // 下一次报数从下一结点开始
        p = pr->link;
        if (p == list)
        // 若 *p 为头结点则跳过
        {
            pr = p;
            p = p->link;
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    CircList L;
    int s = 1, m = 3, n = 8; // 起始位置、报数间隔和人数
    // 人员编号
    int A[30] = {1, 2, 3, 4, 5, 6, 7, 8};
    createCircList(L, A, n); // 建立循环单链表
    for (CircNode *p = L->link; p != L; p = p->link)
    // 输出循环单链表
    {
        printf("%d ", p->data);
    }
    printf("\n");
    Josephus(L, s, m, n); // 执行报数出列算法

    return 0;
}
