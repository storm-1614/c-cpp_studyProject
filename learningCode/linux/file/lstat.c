// 使用 lseek 获取当前文件类型

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int i;
    struct stat buf;
    char *ptr;

    //遍历输入的参数
    for (int i = 1; i < argc; i++) {
        printf("%s: ", argv[i]);
        if (lstat(argv[i], &buf) < 0) {
            printf("lstat error\n");
            continue;
        }
        //普通文件
        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        //目录
        else if (S_ISDIR(buf.st_mode))
            ptr = "directory";
        //特殊字符设备：设备文件(一般在 /dev 内)
        else if (S_ISCHR(buf.st_mode))
            ptr = "charactor special";
        //特殊块设备： 块设备硬盘啥的比如 /dev/sda1
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        //命名管道
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        //链接文件
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        //套接字文件
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "** unknown mode **";

        printf("%s\n", ptr);
    }
    return 0;
}
