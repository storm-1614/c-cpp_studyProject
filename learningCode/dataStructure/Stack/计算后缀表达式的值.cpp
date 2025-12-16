#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#define STKSIZE 20

// 算法：从操作数栈 OPND 取两个操作数，根据操作符 op 形成运算指令并计算
int DoOperator(int OPND[], int &top, char op)
{
    int left, right;

    if (top == -1)
    {
        printf("缺少右操作数！\n");
        return 0;
    }
    right = OPND[top--];
    if (top == -1)
    {
        printf("缺少左操作数！\n");
        return 0;
    }
    left = OPND[top--];
    switch (op)
    {
    case '+':
        OPND[++top] = left + right;
        break;
    case '-':
        OPND[++top] = left - right;
        break;
    case '*':
        OPND[++top] = left * right;
        break;
    case '/':
        if (abs(right) < 0.001)
        {
            printf("Divide by 0!\n");
        }
        else
            OPND[++top] = left / right;
        break;
    default:
        return 0;
    }
    return 1;
}

int isp(char ch)
{
    if (ch == '#')
        return 0;
    else if (ch == '(')
        return 1;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 5;
    else if (ch == '+' || ch == '-')
        return 3;
    else if (ch == ')')
        return 6;
    return -1;
}

int icp(char ch)
{
    if (ch == '#')
        return 0;
    else if (ch == '(')
        return 6;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 4;
    else if (ch == '+' || ch == '-')
        return 2;
    else if (ch == ')')
        return 1;
    return -1;
}

// 把从键盘输入的中缀表达式转换成后缀表达式并输出，要求输入的最后一个符号是‘#’
void Infix_to_Postfix()
{
    // 定义操作符栈 OPTR 并初始化
    char OPTR[STKSIZE];
    int top = -1;

    char ch, ch1, op;
    printf("请输入后缀表达式（输入值限于 0 ~ 9）操作符限于 +、-、*、/、#\n");
    OPTR[++top] = '#';
    scanf("%c", &ch);

    while (top != -1 || ch != '#')
    {
        if (isdigit(ch))
        {
            printf("%c", ch);
            scanf("%c", &ch);
        }
        else
        {
            ch1 = OPTR[top];
            if (isp(ch1) < icp(ch))
            {
                OPTR[++top] = ch;
                scanf("%c", &ch);
            }
            else if (isp(ch1) > icp(ch))
            {
                op = OPTR[top--];
                printf("%c", op);
            }
            else
            {
                op = OPTR[top--];
                if (op == '(')
                    scanf("%c", &ch);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int OPND[STKSIZE];
    int top = -1;
    char ch;
    int result;
    printf("请输入后缀表达式（输入值限于 0 ~ 9）操作符限于 +, -, *, /。\n");
    scanf("%c", &ch);
    while (ch == '#')
    {
        if (isdigit(ch))
        {
            OPND[++top] = ch - '0';
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (!DoOperator(OPND, top, ch))
            {
                printf("运算出错！\n");
                exit(1);
            }
        }
        else
        {
            printf("输入了非法字符，请重新输入！\n");
        }
        scanf("%c", &ch);
    }
    result = OPND[top--];
    printf("计算结果是: %d\n", result);

    return 0;
}
