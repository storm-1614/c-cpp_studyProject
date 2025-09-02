// This file is a example of open and close function.
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int temp;
    // open 函数返回文件标识符（整数）  
    // 各项参数:
    // file: 指针变量，用来传递路径包含的完整文件名称
    // oflag: int 型变量，指定文件的打开方式 这里的 O_RDWR 是读写。O_CREAT 当文件不存在时创建文件，这里会用到第三个参数
    // mode: 如果考虑到文件不存在打开之前要创建就要用到这个参数，这里的 S_IRWXU 是创建的文件具有读写执行的权限。
    temp = open("./file1.txt", O_RDWR | O_CREAT, S_IRWXU);
    // 这里打印出文件描述符，前 2 被标准输入输出占用，新打开文件从第三个开始分配。
    printf("%d\n", temp);
    // close 函数用来关闭文件，返回 0，参数为文件描述符。
    temp = close(temp);
    return 0;
}
