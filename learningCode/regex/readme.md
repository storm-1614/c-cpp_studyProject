# Standard C library regex.h 笔记

## 基本流程
regex.h 使用主要流程为：编译正则表达式->匹配正则表达式->释放正则表达式。  

### 编译正则表达式
在将字符串与正则表达式比较之前，需要使用 `regcomp()` 对表达式进行编译转化为 `regex_t` 结构。  
``` c
int regcomp(regex_t *restrict preg, const char *restrict regex,
            int cflags);
```
成功返回 0。`regex_t * preg` 将会被初始化。  

这里的 cflags 一般传入宏，配置参数：  
- `REG_EXTENDED`：扩展的正则表达式  
- `REG_ICASE`：不区分大小写  
……  


例：  
``` c
regex_t regex;
int ret;
const char *pattern = "^[0-9]+$";

ret = regcomp(&regex, pattern, REG_EXTENDED); // 使用扩展模式编译正则
if (ret != 0)
{
    char errbuf[256];
    regerror(ret, &regex, errbuf, sizeof(errbuf)); // 把 regcomp 返回的错误码变成可读字符串
    fprintf(stderr, "编译失败：%s\n", errbuf);
    return -1;
}
```

### 匹配正则表达式
用 `regcomp()` 成功编译正则表达式后，就可以调用 `regexec()` 进行匹配。  
主要有结构体： `regmatch_t` 存放匹配结果，`regexec()` 匹配函数。  

``` c
typedef struct {
    regoff_t  rm_so; /* 匹配子串的起始偏移量 */
    regoff_t  rm_eo; /* 匹配子串的结束偏移量 */
} regmatch_t;

int regexec(const regex_t *restrict preg,
            const char *restrict string,
            size_t n, regmatch_t pmatch[_Nullable restrict n],
            int eflags);
```
`preg` 指向编译后的正则表达式，`string` 为将要进行匹配的字符串，`n` 表示 `pmatch` 的元素个数，`pmatch` 为一个 `regmatch_t` 数组,`eflags` 为执行标志。  
特别需要注意的是，regmatch_t 是左闭右开的：`[rm_so, rm_eo)`  

例：
``` c
const char *text = "2026-08-04";
regmatch_t matches[4];

ret = regexec(&regex, text, 4, matches, 0);

if (ret == 0)
{
    printf("匹配成功\n");
    for (int i = 0; i < 4; i++)
    {
        if (matches[i].rm_so != -1)
        {
            int start = matches[i].rm_so;
            int end = matches[i].rm_eo;
            int len = end - start;
            printf("组 %d: %.*s\n", i, len, text + start);
        }
    }
}
else if (ret == REG_NOMATCH)
{
    printf("不匹配\n");
}
```

## 释放正则表达式
当不再需要已经编译过的正则表达式时，都应该用 `regfree()` 将其释放，以免产生内存泄漏。  
``` c
void regfree(regex_t *preg);
```
