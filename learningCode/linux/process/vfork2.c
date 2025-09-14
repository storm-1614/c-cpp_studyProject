// vfork 函数应用实例2
//
// 由于 vfork 会自动让子进程先运行，所以不需要父进程调用 sleep 函数阻止自身运行

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int glob = 6;  // 全局变量

int main(int argc, char *argv[]) {
    int var;    // 内部变量
    pid_t pid;  // 进程标识符

    var = 88;
    printf("Before vfork\n");   // 父进程，准备调用 vfork 函数
    if ((pid = vfork()) < 0) {  // 如果调用失败
        perror("vfork error");  // 报错
    } else if (pid == 0) {      // 以下是子进程
        glob++;                 // 这是一个父进程中的全局变量
        var++;
        _exit(0);
        //_exit 与 exit 相比不冲洗相应的缓冲区
    }

    // 以下回到父进程
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    //可以看到子进程对变量 glob 和 var 进行操作改变了父进程中的变量值
    //这是因为 vfork 函数所创建的子进程是在父进程的内存空间中运行的
    return 0;
}
