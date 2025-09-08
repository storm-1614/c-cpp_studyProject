//utime 应用的一个实例

//使用 utime 函数复位文件的时间信息，然后使用带 O_TRUNC 参数的 open 函数将文件打开，并截断为 0。(其实质是清空文件的所有内容)然后使用 utime 函数复位文件最后访问和修改时间。  

#include <stdio.h>
#include <fcntl.h>
#include <utime.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i, fd;
    struct stat statbuf;
    struct utimbuf timebuf;

    for (int i = 1;i < argc; i++){
        //获得文件信息
        if (stat(argv[i], &statbuf) < 0){
            printf("arg is error");
            continue;
        }
        //用读写和截断参数打开文件
        if ((fd = open(argv[i], O_RDWR | O_TRUNC )) < 0){
            printf("%d, Open file error\n", fd);
            continue;
        }
        close(fd);
        //在 Linux 中每个文件都有 3 个对应的时间信息
        //actime :最后一次访问文件时间              操作函数: read
        //mtime:  最近的修改文件时间                操作函数：write
        //ctime : 最近一次对文件状态进行修改时间    操作函数: chmod
        timebuf.actime = statbuf.st_atime;
        timebuf.modtime = statbuf.st_mtime;
        printf("actime: %ld\n", timebuf.actime);
        printf("modtime: %ld\n", timebuf.modtime);

        //复位时间
        if (utime(argv[i], &timebuf) < 0){
            printf("reset time error\n");
            continue;
        }
    }
    return 0;
}
