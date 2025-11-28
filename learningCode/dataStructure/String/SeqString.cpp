/*
* 定长顺序存储的字符串
*/

#include <cstdio>
#define MAXSIZE 256 // 串字符数组最大长度

// 字符串的定长顺序的结构定义
typedef struct
{
    char ch[MAXSIZE + 1]; // 顺序串的存储数组
    int n;                // 顺序串的实际长度
} SeqString;

// 建立字符串
void createSeqString(SeqString &s, char c[])
{
    int i = 0;
    while (i < MAXSIZE && c[i] != '\0')
    {
        s.ch[i] = c[i];
        i++;
    }
    s.n = i;
    if (i == MAXSIZE)
    {
        printf("串空间不足以容纳输入字符串!");
        for (i = 0; c[i] != '\0'; i++)
            printf("%c", c[i]);
        printf("\n");
    }
}

// 输出字符串
void printSeqString(SeqString &s)
{
    for (int i = 0; i < s.n; i++)
    {
        if (s.ch[i] == '\0')
            break;
        else
            printf("%c", s.ch[i]);
    }
    printf("\n");
}

// 将 s2 连接到 s1 后，若连接成功函数返回 1；若部分连接成功或不成功，函数返回 0；
int Concat(SeqString &s1, SeqString &s2)
{
    if (s1.n + s2.n < MAXSIZE)
    // 完全连接
    {
        for (int i = 0; i < s2.n; i++)
        {
            s1.ch[s1.n + i] = s2.ch[i];
        }
        s1.n = s1.n + s2.n;
        s1.ch[s1.n] = '\0';
        return 1;
    }
    else if (s1.n < MAXSIZE)
    // 部分连接
    {
        int m = MAXSIZE - s1.n; // 计算可传送字符数
        for (int i = 0; i < m; i++)
        {
            s1.ch[i + s1.n] = s2.ch[i];
        }
        s1.n = MAXSIZE;
        s1.ch[MAXSIZE] = '\0';
        return 0;
    }
    else
        return 0; // s1.n == MAXSIZE 不能连接
}

int main(int argc, char *argv[])
{
    SeqString s1, s2;
    createSeqString(s1, "dadsa");
    createSeqString(s2, "dadsa");
    printSeqString(s1);
    printSeqString(s2);
    Concat(s1, s2);
    printSeqString(s1);
    return 0;
}
