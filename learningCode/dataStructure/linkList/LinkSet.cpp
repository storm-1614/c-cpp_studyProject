#include <cstdio>
#include <cstdlib>

typedef int DataType;

// 集合的结点定义
typedef struct node
{
    DataType data;     // 数据
    struct node *link; // 链接指针
} SetNode;

// 集合的定义
typedef struct
{
    SetNode *first; // 表头
    SetNode *last;  // 表尾
} LinkSet;

// 如果 x 是集合 s 的成员，则函数返回与 x 匹配的集合结点的地址，否则函数返回 NULL
SetNode *Contains(LinkSet &S, DataType x)
{
    SetNode *p = S.first->link; // 链的扫描指针
    while (p != NULL && p->data < x)
    // 循链搜索
    {
        p = p->link;
    }
    if (p != NULL && p->data == x) // 找到
        return p;
    else
        return NULL; // 未找到
}

// 把新元素 x 加入到集合中，若集合中已有此元素，则函数返回 0，否则函数返回 1
int addMember(LinkSet &S, DataType x)
{
    SetNode *p = S.first->link, *pre = S.first;
    while (p != NULL && p->data < x)
    {
        pre = p;
        p = p->link;
    }
    if (p != NULL && p->data == x) // 这里检查指针是为了防止后面检查出现段错误
        return 0;

    // 创建结点用 q 表示
    SetNode *q = (SetNode *)malloc(sizeof(SetNode));

    // 新结点的插入
    q->data = x;
    q->link = p;
    p->link = q;
    // 新元素加在链尾时改尾指针
    if (!p)
        S.last = q;

    return 1;
}

// 集合并运算的实现
void Merge(const LinkSet &LA, const LinkSet &LB, LinkSet &LC)
{
    // LA 与 LB 集合的扫描指针
    SetNode *pa = LA.first->link;
    SetNode *pb = LB.first->link;

    SetNode *p, *pc = LC.first; // 结果链 LC 的存放指针
    while (pa != NULL && pb != NULL)
    // 当两个集合都未检测完
    {
        if (pa->data <= pb->data)
        // LA 集合的元素值小于或相等于 LB
        {
            pc->link = (node *)malloc(sizeof(node));
            pc->link->data = pa->data;  // 把 LA 的元素复制到 LC
            pa = pa->link;
        }
        else
        // LB 集合的元素值小
        {
            pc->link = (node *)malloc(sizeof(node));
            pc->link->data = pa->data;  // 把 LB 的元素复制到 LC
            pb = pb->link;
        }
        pc = pc->link;
    }

    // 处理未处理完的集合
    p = (pa != NULL) ? pa : pb;
    while (p != NULL)
    // 向结果链逐个复制
    {
        pc->link = (node *)malloc(sizeof(node));
        pc->link->data = p->data;
        pc = pc->link;
        p = p->link;
    }
    // 结果链收尾
    pc->link = NULL;
    LC.last = pc;
}
