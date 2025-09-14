// fork() 2
// 子进程所拷贝的仅仅是以一个副本和父进程相应部分是完全独立的
// 此代码可以看到子进程对变量的修改不会影响到父进程

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int glob = 6;                      // 外部变量
char buf[] = "Write to stdout\n";  // 缓冲区

int main(int argc, char *argv[]) {
    int var;    // 内部变量
    pid_t pid;  // 文件标识符
    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != (sizeof(buf) - 1))
        perror("write error");
    printf("before fork\n");  // 没有冲洗标准输出
    if ((pid = fork()) < 0)
        perror("fork error");  // 如果调用失败
    else if (pid == 0) {
        glob++;  // 对子进程操作
        var++;   // 修改变量
    } else
        sleep(2);  // 父进程
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

    return 0;
}

/*
执行结果：
Write to stdout
before fork
pid = 315458, glob = 7, var = 89
pid = 315457, glob = 6, var = 88
*/
