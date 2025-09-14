// 阻塞进程应用实例 1
// 使用 pthread_join 函数来实现线程阻塞，其使用 pthread_join
//     函数来等待两个线程结束，以保证完成工作后主进程才会退出

#include <pthread.h>
#include <stdio.h>

void print_msg(char *ptr);

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2;
    int i, j;
    void *retval;
    char *msg1 = "This is the first thread\n";
    char *msg2 = "This is the second thread\n";

    // 创建两个线程
    pthread_create(&thread1, NULL, (void *)(&print_msg), (void *)msg1);
    pthread_create(&thread2, NULL, (void *)(&print_msg), (void *)msg2);

    pthread_join(thread1, &retval);
    pthread_join(thread2, &retval);

    return 0;
}

// 打印函数，线程从这个函数开始运行
void print_msg(char *ptr) {
    int i;
    // 连续输出 10 个字符串
    for (i = 0; i < 10; i++) {
        printf("%s\n", ptr);
    }
}
