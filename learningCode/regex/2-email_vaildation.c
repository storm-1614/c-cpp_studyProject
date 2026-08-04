/*
 * 简单邮箱校验
 * 2026-08-04
 */

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    regex_t regex;

    const char *pattern = "^([A-Za-z0-9][A-Za-z0-9.%+-]*)@([A-Za-z0-9.-]*\\.[A-Za-z]{2,6})$";

    int ret = regcomp(&regex, pattern, REG_EXTENDED);

    if (ret)
    {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        printf("编译错误：%s\n", errbuf);
        return 1;
    }
    const char *tests[] = {
        "test@example.com",         //
        "user.name+tag@mail.co.uk", //
        "@bad.com",                 //
        "no-at-sign"                //
    };

    regmatch_t m[3];

    for (int i = 0; i < 4; i++)
    {
        ret = regexec(&regex, tests[i], 3, m, 0);

        if (ret == 0)
        {
            printf("[匹配] %s\n", tests[i]);
            printf("  用户名: %.*s\n", m[1].rm_eo - m[1].rm_so, tests[i] + m[1].rm_so);
            printf("  域名  : %.*s\n", m[2].rm_eo - m[2].rm_so, tests[i] + m[2].rm_so);
        }
        else
        {
            printf("[不匹配] %s\n", tests[i]);
        }
    }
    regfree(&regex);
    return EXIT_SUCCESS;
}
