/*
 *   双栈共享同一栈空间
 */

#define M 20

typedef int SElemType; // 栈元素类型
typedef int DataType;

// 双栈的结构定义
typedef struct
{
    int top[2], bot[2];
    SElemType V[M]; // 栈元素存储数组
} DblStack;

// 初始化函数：建立一个大小为 m 的空栈
void InitStack(DblStack &S)
{
    S.top[0] = S.bot[0] = -1;
    S.top[1] = S.bot[1] = M;
}

// 进栈运算
int Push(DblStack &S, SElemType x, int i)
{
    if (S.top[0] + 1 == S.top[1])
    // 两个栈指针相遇，栈满
    {
        return 0;
    }

    if (i == 0)
    // 栈 0：栈顶指针先加 1 再进栈
    {
        S.V[++S.top[0]] = x;
    }
    else
    // 栈 1：栈顶指针先减 1 再进栈
    {
        S.V[--S.top[1]] = x;
    }
    return 1;
}

// 函数通过引用参数 x 返回退出栈 i 栈顶元素的元素值，前提是栈不为空
int Pop(DblStack &S, int i, SElemType &x)
{
    // 第 i 个栈为空不能退栈
    if (S.top[i] == S.bot[i])
        return 0;

    if (i == 0)
    //栈 0：先出栈，栈顶指针减 1
    {
        x = S.V[S.top[0]--];
    }
    else
    // 栈 1：先出栈，栈顶指针加 1
    {
        x = S.V[S.top[1]++];
    }
    return 1;
}

int main(int argc, char *argv[])
{

    return 0;
}
