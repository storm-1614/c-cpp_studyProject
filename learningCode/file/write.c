// This file is an example of write funnction.

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fileID, temp;
    // 创建字符串作为缓冲区存储要写入的内容
    char wbuf[15] = "This is a test!";
    //打开文件，如果没有就创建一个带读写执行
    fileID = open(*(argv + 1), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    printf("%d\n", fileID);
    // write 函数三个参数中:  
    // fd：文件描述符
    // buf: 指向写入缓冲区的指针，待写入数据必须存放在该缓冲区内。  
    // n: 本次要写入数据的字节数
    temp = write(fileID, wbuf, 15);
    // write 返回输入了多少字符
    printf("%d\n", temp);
    close(fileID);
    return 0;

    return 0;
}
