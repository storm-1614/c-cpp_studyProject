#include <cstdio>
#include <cstdlib>

#define MAXSIZE 30

typedef int DataType;

// 双向链表的定义
typedef struct node
{
    DataType data;      // 结点数据
    int freq;           // 访问记数
    struct node *lLink; // 前序结点指针
    struct node *rLink; // 后续结点指针
} DblNode, *DblList;

// 顺序输入 `A[m]` 中的数据，使用尾插法沿右链方向建立循环双链表
// 每插入一个结点，需要在前趋和后续方向的两个链中进行链接
void createListR(DblList &first, DataType A[], int m)
{
    first = (DblNode *)malloc(sizeof(DblNode)); // 建立头结点
    // 初始化
    first->rLink = first;
    first->lLink = first;
    DblNode *s, *q, *r = first;
    for (int i = 0; i < m; i++)
    // 使用尾插法顺序建立链表
    {
        s = (DblNode *)malloc(sizeof(DblNode)); // 建立新结点
        // 新结点赋值
        s->data = A[i];
        s->freq = 0;
        // 前趋方向链接  

        q = r->rLink;
        s->lLink = r; // s 的左指针是 r
        q->lLink = s; // q 的左指针是 s
        // 后继方向链接
        r->rLink = s; // r 的右指针是 s
        s->rLink = q; // s 的右指针是 q
        r = s;   // r 前移到新的结点
    }
}

// 输出循环双链表所有元素的值， d = 0 按前趋方向， d = 1 按后继方向
void printList(DblList first, int d)
{
    DblList p;                                  // 遍历指针
    p = (d == 0) ? first->lLink : first->rLink; // 按前趋或后继方向输出
    while (p != first)
    // 循链输出
    {
        printf("%d", p->data);
        p = (d == 0) ? first->lLink : first->rLink;
        if (p != first)
            printf(" ");
    }
    printf("\n"); // 输出收尾
}

// 在带头结点的循环双链表中寻找其值等于 x 的结点，若找到，则函数返回该结点地址
// 否则函数返回 NULL。参数 d = 0，按前趋方向查找；d != 0 按后续方向查找
// WARN: 这里的三元运算符用得太好了
DblNode *Search(DblList &first, DataType x, int d)
{
    DblNode *p = (d == 0) ? first->lLink : first->rLink;
    while (p != first && p->data != x)
        p = (d == 0) ? p->lLink : p->rLink;
    return (p != first) ? p : NULL; // 返回查找结果
}

// 在带头结点的循环双链表中按 d 所指方向寻找第 i 个结点
// 若 d = 0，在前趋方向寻找第 i 个结点；若 d != 0，在后继方向寻找第 i 个结点
DblNode *Locate(DblList &first, int i, int d)
{
    // i 不合理，返回 NULL
    if (i <= 0)
        return NULL;
    // i = 0,定位于头结点
    if (i == 0)
        return first;
    DblNode *p = (d == 0) ? first->lLink : first->rLink;
    // 逐个结点检测
    for (int j = 1; j < i; j++)
        if (p == first) // 链太短退出搜索
            break;
        else
            p = (d == 0) ? p->lLink : p->rLink;
    return (p != first) ? p : NULL; // 返回查找结果
}

// 建立一个包含值 x 的新结点，并将其按 d 指定的方向插入到第 i 个结点的位置
int Insert(DblList &first, int i, DataType x, int d)
{
    DblNode *p = Locate(first, i - 1, d);
    if (p == NULL)
        return 0;

    DblNode *s = (DblNode *)malloc(sizeof(DblNode));
    s->data = x;

    if (d == 0)
    // 在前趋方向插入
    {
        // 前趋链
        s->lLink = p->lLink;
        p->lLink = s;
        // 后继链
        s->lLink->rLink = s;
        s->rLink = p;
    }
    else
    // 在后继方向输入
    {
        // 后继链
        s->rLink = p->rLink;
        p->rLink = s;
        // 前趋链
        s->rLink->lLink = s;
        s->lLink = p;
    }
    return 1; // 插入成功
}

// 在带头结点的循环双链表中按照 d 所指方向删除第 i 个结点
// 被删元素的值通过引用参数 x 返回，如果删除成功，则函数返回 1 ，否则函数返回 0
int Remove(DblList &first, int i, DataType &x, int d)
{
    DblNode *p = Locate(first, i, d); // 按 d 所指方向定位于第 i 个结点

    if (p == NULL) // 空表或 i 不合理，删除失败
        return 0;
    p->rLink->lLink = p->lLink; // 从 lLink 链中摘下
    p->lLink->rLink = p->rLink; // 从 rLink 链中摘下
    x = p->data;
    free(p);  // 删除
    return 1; // 删除成功
}

int main(int argc, char *argv[])
{

    return 0;
}
