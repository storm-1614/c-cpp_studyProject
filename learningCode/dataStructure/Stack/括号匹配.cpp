#include <bits/stdc++.h>

#include <cstdio>
#define stkSize 10

// 参数 expr 应是已存在的表达式字符串，算法给出括号匹配的过程
void PrintMtchedPairs(const char expr[])
{
    // 设置栈 S 并置空
    int S[stkSize];
    int top = -1;

    int j, i = 0;
    char ch = expr[i];
    while (ch != '\0')
    // 在表达式中搜索 '(' 和 ')'
    {
        if (ch == '(')
        // 左括号进栈
        {
            S[++top] = i;
        }
        else if (ch == ')')
        // 右括号
        {
            if (top != -1)
            // 如果栈不空有括号匹配则退栈
            {
                j = S[top--]; // 退栈
                printf("位置 %d 的左括号与位置 %d 的右括号匹配！\n", j, i);
            }
            else
            {
                printf("栈空，没有与位置 %d 的右括号匹配的左括号！\n", i);
            }
        }
        ch = expr[++i]; // 跳过，取下一字符
    }
    while (top != -1)
    // 串已处理完，但栈中还有左括号
    {
        j = S[top--]; // 报错次数等于栈中左括号数目
        printf("没有与位置 %d 的左括号匹配的右括号!\n", j);
    }
}

int main(int argc, char *argv[])
{
    std::string input;
    std::cin >> input;

    PrintMtchedPairs(input.c_str());

    return 0;
}
