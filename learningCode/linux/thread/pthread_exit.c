// 退出线程的实例
// Linux 内核提供了 pthread_exit 函数用于主动退出线程，其调用的格式如下
// pthread_exit(void *retval)
// pthread_exit 没有返回值，其参数 retval 是线程的终止状态。
// 其与 pthread_create 函数的 start_routime 类似，都是由用户先指定并传递给函数一个参数。  
// 在 pthread_exit 函数完成之后可以调用这个参数获得进程的退出状态

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

// 打印字符串
void print_message(char *ptr);

int main(int agrc, char **argv) {
    pthread_t thread1, thread2;
    char *msg1 = "This is th first thread!\n";  // 两个字符串
    char *msg2 = "This is the second thread!\n";
    // 创建两个字符串并且休眠
    pthread_create(&thread1, NULL, (void *)print_message, (void *)msg1);
    pthread_create(&thread2, NULL, (void *)print_message, (void *)msg2);
    // 没有 sleep 可能会输出不完整或没有输出
    // 原因：当主进程退出时，整个进程会终止无论是否还有其他子进程在运行
    // sleep 给子线程一些执行时间
    sleep(1);
    return 0;
}

void print_message(char *ptr) {
    int retval;
    //打印线程编号
    printf("Thread ID: %lx\n", pthread_self());
    printf("%s", ptr);
    pthread_exit(&retval);
}
