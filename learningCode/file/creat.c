// This file is a example of creat function.
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int temp;
    if (argc != 2){
        printf("run error.\n");
        return 2;
    }
    // creat 函数创建文件并打开文件返回文件描述符。  
    // creat 的两个参数分别为: 
    // file 这个的作用和 open 和 close 一样为文件地址字符串。
    // mode 为创建文件的模式，这里为创建的文件有读写执行权限。
    temp = creat(*(argv + 1), S_IRWXU);
    printf("%d\n", temp);
    return 0;
}

