#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    regex_t regex;
    int ret;
    char msgbuf[100];
    const char *text = "数值是 0x1aF";

    ret = regcomp(&regex, "0[xX][0-9a-fA-F]+", REG_EXTENDED);
    if (ret)
    {
        fprintf(stderr, "无法编译\n");
        return 1;
    }
    ret = regexec(&regex, text, 0, NULL, 0);
    if (!ret)
    {
        printf("匹配成功!\n");
    }
    else if (ret == REG_NOMATCH)
    {
        printf("没有匹配到。\n");
    }
    else
    {
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "正则匹配错误: %s\n", msgbuf);
        return 1;
    }
    return EXIT_SUCCESS;
}
