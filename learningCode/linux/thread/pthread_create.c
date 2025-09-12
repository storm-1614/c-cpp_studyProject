// 调用 pthread_create 来创建线程并且打印其线程标识符

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

pthread_t ntid;

// 打印标识符的函数
void printids(const char *s) {
    pid_t pid;      // 进程标识符
    pthread_t tid;  // 线程标识符

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid,
           (unsigned int)tid);
}

// 线程中开始运行的函数
void *thr_fn(void *arg) {
    printids("new threads; ");
    return ((void *)0);
}

int main(int argc, char *argv[]) {
    int err;
    // 创建一个线程
    // pthread_create:
    // pthread_create(pthread_t *__restrict newthread, *__restrict attr,
    // void *(*start_routine)(void *), void *__restrict arg)
    // 1: newthread: 线程的标识符，这个参数不是用户所确定的，用户需要声明一个
    //               pthread_t 类型的数据变量，并将其传递给 pthread_create 函数
    //               函数在创建新线程的同时会将新线程的标识符放到这个变量中
    // 2: attr: 指定线程的属性，也可以设置为 NULL
    // 3: start_routine:
    // 用于指定开始运行时的函数，新创建的线程就是从这个函数开始运行
    // 4. arg: 函数 start_routine 所需的参数，一个无类型指针。
    // 如果需要传递的参数不止一个，需要将参数放到一个结构中，将这个结构地址传给arg
    // pthread_create 函数调用失败后会返回错误编码

    err = pthread_create(&ntid, NULL, thr_fn, NULL);

    if (err != 0)  // 如果出错则打印错误编号
    {
        printf("can't create thread: %s\n", strerror(err));
    }
    printids("main threads:");  // 打印主线程号
    sleep(1);

    return 0;
}
