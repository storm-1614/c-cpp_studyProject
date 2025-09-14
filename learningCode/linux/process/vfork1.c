//vfork() 函数应用实例
//分别利用子进程和父进程对一个 count 变量进行计数并且输出，用于展示父进程和子进程共享一个数据段
//
//在使用 fork 函数创建一个新进程之后，可以不使用 exec 一系列函数来执行新的程序。如果要执行新的程序则必须手动调用 exec 函数
//在这种情况下可以使用 vfork 函数。 vfork 函数在创建完新进程之后自动实现了 exec 系列函数的功能
//函数返回和 fork 函数类似父进程中返回子进程的进程号，在子进程中返回 0,如果出错则返回 -1
/*
fork 与 vfork 之间的区别如下：
- fork 要拷贝父进程的数据段，而 vfork 则不需要完全拷贝父进程的数据段，在子进程没有调用 exec 系列函数或 exit 函数之前，子进程与父进程共享数据段
- vfork 函数会自动调用 exec 系列函数去执行另外一个程序
- fork 不对父子进程的执行次序进行任何限制，而在 vfork 调用中，子进程先运行，父进程挂起，直到子进程调用了 exec 系列函数或 exit 之后，父进程的执行次序才不再有限制
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int count = 1;
    int child;
    printf("before create son, the father's count is: %d:\n", count);

    // 创建子进程
    if (!(child = vfork())) {
        // 由于子进程会首先执行，以下为子进程执行过程
        for (int i = 0; i < 100; i++) {
            printf("This is son, The i is: %d\n", i);    //反复输出打印结果
            if (i == 70) exit(1);  //实际退出进程
        }
        printf("This is son, his pid is: %d and the count is: %d\n", getpid(),
               ++count);
        exit(1);
    } else {
        //父进程执行区
        printf(
            "After son, This is father, his pid is: %d and the count is: %d, "
            "and child is: %d\n",
            getpid(), count, child);
    }

    return 0;
}
