// This file is an example of offseek function.

// 该文件打开参数字符串指定的文件，如果没有则创建一个。
// 然后打开这个文件对该文件连续写入字符串
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // i 为循环次数，j 为偏移量
    int temp, seektemp, i, j;
    int fileID;
    char wbuf[17] = "This is a test!\n";

    // 如果没有参数就返回错误
    if (argc != 2) {
        printf("run error!\n");
        return 1;
    }
    fileID = open(*(argv + 1), O_RDWR | O_CREAT, S_IRWXU);
    temp = write(fileID, wbuf, 17);
    // lseek 指定文件偏移量的位置，操作成功就返回新的文件偏移量
    // fd 是文件描述符
    // offset 是文件偏移量指的是每一次对文件的读写所需移动的距离，单位是字节
    //        offset 的取值可正可负，正值指的是向前移动，负值指的是向后移动
    seektemp = lseek(fileID, 0, SEEK_CUR);
    for (i = 0; i < 10; i++) {
        // 计算下一次的偏移量
        j = sizeof(wbuf) * (i + 1);
        seektemp = lseek(fileID, j, SEEK_SET);
        temp = write(fileID, wbuf, sizeof(wbuf));
    }
    close(fileID);
    return 0;
}
