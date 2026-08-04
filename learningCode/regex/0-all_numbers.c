/*
 * 匹配一个字符串是否全是数字
 * 2026-08-04
 *
 * regex.h 流程：
 * 编译 -> 匹配 -> 释放
 */

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
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

    const char *test_str = "12345";
    /* 用编译好的 regex 去匹配字符串
     */
    ret = regexec(&regex, test_str, 0, NULL, 0);
    if (ret == 0)
    {
        printf("匹配成功\n");
    }
    else if (ret == REG_NOMATCH)
    {
        printf("不匹配\n");
    }
    else
    {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "匹配错误：%s\n", errbuf);
    }
    regfree(&regex); // 释放内部状态机内存
    return EXIT_SUCCESS;
}
