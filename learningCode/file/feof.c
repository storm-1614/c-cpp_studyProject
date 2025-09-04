/*feof() 的实例
 * feof() 检测文件是否结束
 * 它的参数如下
 * feof(FILE *stream)
 * 实际上 feof 检测的是文件偏移量的位置
 * 若读取到文件末尾返回 1，否则返回值是 0
*/
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* fp;
    char c;
    if ((fp = fopen("./foo", "r")) == 0){
        printf("fopen error!\n");
        return 0;
    };
    //在进行读文件的操作时需要检测是否读到文件末尾处，常使用 feof 来判断。
    //比如以下循环用于读取 fp 所指向文件的内容并打印出来。
    while (!feof(fp)){
        c = fgetc(fp);
        printf("%c", c);
    }

    fclose(fp);
    return 0;
}
