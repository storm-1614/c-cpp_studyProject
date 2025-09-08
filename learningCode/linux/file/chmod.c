//这是使用 chmod 函数来修改文件的权限的实例

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    //取文件状态
    struct stat statbuf;

    if (stat("foo", &statbuf) < 0)
        printf("stat error for foo");
    //在 Linux 中文件权限和模式信息存储在 st_mode 的整数中
    // ~ 位取反操作，将 S_IXGRP 所有的 0 变成 1，所有的 1 变成 0。
    // 所以只有 S_IXGRP 是 0 其他都是 1
    // 结合 &，这样就是保留 st_mode 的原位，但是将 S_IXGRP 那一位强制变成 0
    // 这样也就相当于所在组是没有执行权限的
    // 同时添上 S_ISGID 特殊权限
    // 这样之后 foo 的权限为 rw-r-Sr--
    // 这个 S 占据了组的执行权限，文件的所属组没有执行此文件的权限但该文件设置了 SetGID 位
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        printf("chmod error for foo");
    //如果执行成功，此时 bar 的权限为 rw-r--r--
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        printf("chmod error for bar");

    return 0;
}
