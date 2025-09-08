//进程有对应的实际用户 ID、实际组 ID、有效用户 ID、有效组 ID。
//Linu 提供了相应函数用于获取这些标识符

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("The current process ID is %d\n", getpid());
    printf("The father process ID is %d\n", getppid());
    printf("The user true ID is %d\n", getuid());
    printf("The vaild user ID is %d\n", geteuid());
    printf("The group ID is %d\n", getgid());
    printf("The vaild group ID is %d\n", getegid());

    return 0;
}

