/*
 *   顺序栈
 */

#include <cstdio>
#include <stdlib.h>

#define initSize 20 // 栈空间初始大小

typedef int SElemType; // 栈元素类型
typedef int DataType;

// 顺序栈结构定义
typedef struct
{
    SElemType *elem; // 栈元素存储数组
    int maxSize;     // 栈空间最大容量
    int top;         // 栈顶指针（下标）
} SeqStack;

// 建立一个最大尺寸为 initSize 的空栈，若分配不成功则进行错误处理
void InitStack(SeqStack &S)
{
    S.elem = (SElemType *)malloc(initSize * sizeof(SElemType)); // 创建栈空间
    if (S.elem == NULL)
    {
        printf("存储分配失败!\n");
        exit(1);
    }
    S.maxSize = initSize;
    S.top = -1;
}

// 进栈操作：若栈不满，则将元素 x 插入栈顶，函数返回 1；否则栈溢出，函数返回 0
int Push(SeqStack &S, DataType x)
{
    if (S.top == S.maxSize - 1) // 栈满则溢出处理
        return 0;
    S.elem[++S.top] = x; // 栈顶指针先加 1 ，再进栈
    return 1;
}

// 退栈：若栈不空则哈暗示通过引用参数 x 返回栈顶元素值，栈顶指针退 1，函数返回 1
// 否则函数返回 0。
int Pop(SeqStack &S, SElemType &x)
{
    if (S.top == -1)
        return 0;
    x = S.elem[S.top--];
    return 1;
}

// 读取栈顶元素值；若栈不空函数返回栈顶元素的值且函数返回 1，否则函数返回 0
int GetTop(SeqStack &S, SElemType &x)
{
    // 判断是否栈空，栈空返回 0
    if (S.top == -1)
        return 0;
    // 返回栈顶元素的值
    x = S.elem[S.top];
    return 1;
}

// 判断是否栈空，栈空返回 1，否则返回 0
int StackEmpty(SeqStack &S)
{
    return S.top == -1;
}

// 判断是否栈满，栈满返回 1，否则返回 0
int StackFull(SeqStack &S)
{
    return S.top == S.maxSize;
}

// 函数返回栈 S 的长度
int StackSize(SeqStack &S)
{
    return S.top + 1;
}

int main(int argc, char *argv[])
{
    return 0;
}
