/*
 * 匹配日期并提取年、月、日
 * 2026-08-04
 */

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    regex_t regex;
    int ret;
    const char *patten = "^([0-9]{4})-([0-1][0-9])-([0-3][0-9])$";

    ret = regcomp(&regex, patten, REG_EXTENDED);
    if (ret != 0)
    {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "编译失败：%s\n", errbuf);
        return 1;
    }

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

    regfree(&regex);

    return EXIT_SUCCESS;
}
