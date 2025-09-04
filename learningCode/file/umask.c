// umask

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, char *argv[]) {
    //0 不会减去任何，也就是创建的文件权限完全按 RWRWRW 常量
    umask(0);
    if (creat("foo", RWRWRW) < 0) printf("Creat error for foo\n");

    //这里掩码为 066
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    //显然权限是 666 - 066 = 600， 事实也是如此
    if (creat("bar", RWRWRW) < 0)
        printf("creat error for bar\n");

    return 0;
}
