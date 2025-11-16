/*
 * 单链表
 */

#include <cstdio>
#include <cstdlib>
typedef int DataType; // 每个表元素的数据类型定义

// 链表结点的结构定义
typedef struct node
{
    DataType data;     // 结点保存的元素数据
    struct node *link; // 链接指针
} LinkNode, *LinkList; // 单链表的结构定义

// 初始化单链表，建立只有头结点的空链表
void initList(LinkList &first)
{
    first = (LinkNode *)malloc(sizeof(LinkNode)); // 创建头结点
    if (!first)
    {
        printf("存储分配错误!\n");
        exit(1);
    }
    first->link = NULL; // 置空
}

// 清空单链表，仅保留链表的头结点
void clearList(LinkList &first)
{
    LinkNode *q;
    while (first->link != NULL)
    // 当链不空时，删去链中所有结点
    {
        q = first->link;       // 用指针 q 保存被删结点地址
        first->link = q->link; // 从链表上摘下该结点
        free(q);               // 删除该结点
    }
}

// 计算表的长度，函数返回表的长度
int Length(LinkList &first)
{
    LinkNode *p = first->link;
    int count = 0;
    while (p != NULL)
    {
        p = p->link;
        count++;
    }
    return count;
}

// 在单链表中查找与 x 匹配的元素，查找成功时函数返回该结点地址，否则返回 NULL 值
LinkNode *Search(LinkList &first, DataType x)
{
    LinkNode *p = first->link;
    // TODO: 两个条件不能调换位置。 why?
    while (p != NULL && p->data != x)
    // 循链逐个找含 x 结点
    {
        p = p->link;
    }
    return p; // 若成功指针 p 返回找到的结点地址
}

// 在单链表中对第 i (1 <= i) 个结点定位。函数返回表中第 i 个结点的地址。
// 若 i < 0 或 i 超出表中结点个数，则返回 NULL
LinkNode *Locate(LinkList &first, int i)
{
    if (i < 0) // 找头结点时， i <= 0 不合理
        return NULL;

    LinkNode *p = first->link;
    int k;

    while (p != NULL && k < i)
    // 循链找第 i 个结点， k 做结点计数
    {
        p = p->link;
        k++;
    }
    return p; // 若返回 NULL 表示 i 值太大
}

// 将新元素 x 插入到第 i 个结点位置，i 从 1 开始， i = 1 表示插入到原首结点之前
int Insert(LinkList &first, int i, DataType x)
{

    if (!first || i == 1)
    // 插入到空表或非空表的首元结点之前
    {
        LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 新建结点
        if (!newNode)
        {
            printf("存储分配错误!\n");
            exit(1);
        }

        newNode->data = x;
        newNode->link = first;
        first = newNode; // 新结点成为首元结点
    }
    // 插入到中间或尾部
    else
    {
        LinkNode *p = first;
        int k = 1; // 从首元结点开始检测
        // 循环寻找第 i - 1 个结点
        while (p != NULL && k < i - 1)
        {
            p = p->link;
            k++;
        }
        if (p == NULL && first != NULL)
        // 非空表且链太短
        {
            printf("无效的插入位置!\n");
            return 0;
        }
        else
        {
            LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 建新结点
            if (!newNode)
            {
                printf("存储分配错误!\n");
                exit(1);
            }
            newNode->data = x;
            newNode->link = p->link;
            p->link = newNode;
        }
    }
    return 1; // 正常插入
}

// 将链表中的第 i 个元素删去，i 从 1 开始，引用参数 x 返回被删除元素的值。
int Remove(LinkNode *first, int i, DataType &x)
{
    LinkNode *q, *p;
    int k;
    if (i <= 1)
    {
        q = first;
        first = first->link; // 删除首元结点时表头退到下一结点
    }
    else
    // 删中间结点时重新拉链
    {
        p = first;
        k = 1;
        while (p != NULL && k < i - 1)
        // 循环找第 i - 1 号结点
        {
            p = p->link;
            k++;
        }
        if (p == NULL || p->link == NULL)
        // 空表或链太短
        {
            printf("无效的删除位置！\n");
            return 0;
        }
        q = p->link;       // 保存第 i 号结点地址
        p->link = q->link; // 第 i 号结点从链上摘下
    }
    x = q->data; // 取出被删结点中的数据值
    free(q);
    return 1;
}

// 正向输出链表个结点值的递归算法
void printList(LinkNode *first)
{
    // 递归到底，空表返回
    if (first == NULL)
        return;
    printf("%d\n", first->data); // 输出当前结点的值
    printList(first->link);      // 以下一结点为表头继续递归输出
}

// 正向输出单链表各结点值的非递归算法
void printListIter(LinkNode *first)
{
    while (first->link != NULL)
    {
        printf("%d ", first->link->data);
        first = first->link;
    }
    printf("\n");
}

// 用尾插法创建一个单链表
void createListRear(LinkList &last, DataType endTag)
{
    DataType val;
    scanf("%d", &val); // 输入结点元素数据

    if (val == endTag)
        // 链表收尾，停止创建
        last = NULL;
    else
    {
        // 创建新结点
        last = (LinkNode *)malloc(sizeof(LinkList));
        if (!last)
        {
            printf("存储分配错误!\n");
            exit(1);
        }
        last->data = val;                   // last 结点赋值
        createListRear(last->link, endTag); // 递归创建后续链表
    }
}

// 用前插法创建一个单链表
void createListFront(LinkList &first, DataType endTag)
{
    DataType vel;
    scanf("%d", &vel);
    if (vel == endTag)
        // 数据输入结束，停止创建
        return;
    else
    {
        LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode)); // 创建新结点 *s
        s->data = vel;                                      // s 结点赋值
        // 作为首元结点链入头结点
        s->link = first->link;
        first->link = s;
        createListFront(first, endTag); // 递归创建后续链表
    }
}

int main()
{
    LinkList L;
    DataType endTag;
    scanf("%d", &endTag);                     // 输入约定的输入结束标志
    L = (LinkNode *)malloc(sizeof(LinkList)); // 创建头结点
    if (!L)
    {
        printf("存储分配错误!\n");
        exit(1);
    }
    LinkNode *rear = L;                 // 尾指针，初始时指向头结点
    createListRear(rear->link, endTag); // 递归建立单链表
    printf("================\n");
    printList(L->link);
    return 0;
}
