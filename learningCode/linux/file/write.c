// This file is an example of read.

// 从参数一的文件复制到参数二中
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//rw-r--r--
#define PERMS 0666
#define MAXSIZE 1024

int main(int argc, char *argv[])
{
    int sourcefileID, targetfileID;
    // readNO: 存储读取的字节数
    int readNO = 0;
    char WRbuf[MAXSIZE];

    if (argc != 3){
        printf("run error\n");
        return 1;
    }
    if ((sourcefileID = open(*(argv + 1), O_RDONLY, PERMS)) == -1){
        printf("Source file open error\n");
        return 2;
    }
    if ((targetfileID = open(*(argv + 2), O_WRONLY | O_CREAT, PERMS)) == -1){
        printf("Target file open error\n");
        return 3;
    }
    while ((readNO = read(sourcefileID, WRbuf, MAXSIZE)) > 0) 
        // write 函数和 read 函数类似
        if(write(targetfileID, WRbuf, readNO) != readNO){
            printf("Target file write error!\n");
            return 4;
        }
    close(sourcefileID);
    close(targetfileID);

    return 0;
}

