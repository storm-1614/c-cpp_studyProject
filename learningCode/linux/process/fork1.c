/* 
fork 函数应用实例1
应用代码调用 fork 函数创建一个新的进程，并分别打印进程的标识符

对于父进程而言：函数的返回值是子进程的标识符
对于子进程而言：函数的返回值是 0
这里的返回值是 pid，父子进程的 pid 数值不同

当 fork 函数返回后，子进程和父进程都从调用 fork 函数的下一条语句开始执行

通常来说，fork 所创建的子进程将会从父进程中拷贝父进程的数据空间、堆和堆栈。
并且和父进程一起共享正文段
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int count = 0;
    pid_t pid;      //此时仅有一个进程
    pid = fork();   //此时已有两个进程在同时运行
    if (pid < 0) {
        printf("error in fork!");
        exit(1);
    } else if (pid == 0)
        printf("I am the child process, the count is %d, my process ID is %d\n",
               count, getpid());
    else
        printf(
            "I am the parent process, the count is %d, my process ID is %d\n",
            ++count, getpid());

    return 0;
}


/*
程序输出结果大致如下:

I am the parent process, the count is 1, my process ID is 224849
I am the child process, the count is 0, my process ID is 224850
*/
