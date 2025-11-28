/*
 *  堆分配字符串
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define DEFAULTSIZE 128 // 默认串字符数组长度

typedef struct
{
    char *ch;    // 顺序串存储的数组
    int maxSize; // 字符串存储数组的最大长度
    int n;       // 顺序串的实际长度
} HString;

void initString(HString &s, int n)
{
    if (n < DEFAULTSIZE)
        n = DEFAULTSIZE;
    s.ch = (char *)malloc((n + 1) * sizeof(char)); // 动态分配
    if (s.ch == NULL)
        exit(1); // 分配不成功调用 exit() 退出
    s.ch[0] = '\0';
    s.n = 0;       // 字符串 s 当前长度
    s.maxSize = n; // 字符串 s 的最大容量
}

void createHString(HString &s, char c[])
{
    int i, k;
    for (k = 0; c[k] != '\0'; k++) // 统计字符串长度
        ;
    initString(s, k); // 初始化分配空间
    for (i = 0; c[i] != '\0'; i++)
    {
        s.ch[i] = c[i];
    }
    s.n = k;
}

void printHString(HString &s)
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

int Concat(HString &s1, HString &s2)
{
    int i;
    if (s1.n + s2.n > s1.maxSize)
    // 现有空间不足以容纳两个串
    {
        s1.maxSize = s1.n + s2.n; // 新串最大容量，扩展 s1.ch 空间
        char *newAddr = (char *)malloc((s1.maxSize + 1) * sizeof(char));
        if (!newAddr)
        {
            printf("存储分配失败!\n");
            exit(0);
        }
        for (i = 0; i < s1.n; i++) // 传送 s1 的字符序列
            newAddr[i] = s1.ch[i];
        free(s1.ch);     // 删老数组
        s1.ch = newAddr; // 新数组成为 s1 的字符数组
    }
    for (i = 0; i < s2.n; i++) // 传送 s2 的字符序列
        s1.ch[i + s1.n] = s2.ch[i];
    s1.ch[s1.n + i] = '\0';
    s1.n = s1.n + s2.n;
    return 1;
}

int main(int argc, char *argv[])
{
    HString s1, s2;
    createHString(s1, "dadsa");
    createHString(s2, "dadsaf");
    printHString(s1);
    printHString(s2);
    Concat(s1, s2);
    printHString(s1);
    return 0;
}
