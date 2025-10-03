/*
* storm-1614
* 2025-10-02 12:07
* 删除指定字符
*/

#include <stdio.h>
#include <string.h>

void delete_char(char a[], char c)
{
    long long size = strlen(a), delCount = 0;
    for (long long i = 0; i < size; i++)
    {
        if (a[i] == c){
            for (long long j = i; j < size; j++)
                a[j] = a[j + 1];
            delCount++;
            //以防连续需要删除
            i--;
        }
    }
    a[size-delCount] = '\0';
}

int main(){
    static char buf[10001];
    fgets(buf, 10001, stdin);
    int len = strlen(buf);
    len --;
    buf[len]='\0';
    char c;
    scanf("%c",&c);
    delete_char(buf, c);
    printf("%s\n", buf);
    return 0;
}


