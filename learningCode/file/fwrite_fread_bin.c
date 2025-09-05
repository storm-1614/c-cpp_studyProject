//使用fwrite() 和 fread() 函数对 stud.bin 文件进行写入和读取操作
//
//程序定义了两个结构体数组 stud 和 stud1，并对 stud 进行了初始化。以读写方式新建并打开二进制文件 stud.bin。
//利用 for 循环语句把初始化过的结构体数组 stud 中的数据写入文件 stud.bin 中，
//写数据结束后文件指针之后文件指针指向文件的结尾处。由于后面还要从文件中读取数据，所以需要使用 rewind() 重置文件指针于文件开头处
//最后利用 while 语句把文件 stud.bin 中的数据写入结构体数组 stud1 中，并在屏幕上输出


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    // 定义结构体并初始化
    struct student {
        char num[8];
        int score;
    } stud[] = {{"101", 86}, {"102", 60}, {"103", 94},
                {"104", 76}, {"105", 50}, {"106", 58}},
      stud1[5];

    int i;
    // 以读写方式新建并打开文件 stud.binn 测试是否成功
    if ((fp = fopen("stud.bin", "wb+")) == 0) {
        printf("不能打开文件\n");
        exit(0);
    }
    // 向 fp 指向的文件中写入数据
    for (i = 0; i < 5; i++) fwrite(&stud[i], sizeof(struct student), 1, fp);
    // 重置文件位置指针于文件的开始处， 以便读取文件
    rewind(fp);

    // 读取文件内容打印到屏幕上
    printf("学号 成绩\n");
    // 循环读取文件中的数据，直到检测到文件结束标志
    while (!feof(fp)) {
        // 读取 fp 指向的文件中的数据并写入到结构体数组 stud1 中
        fread(&stud1[i], sizeof(struct student), 1, fp);
        // 向屏幕上输出结构体数组 stud1 中的数据
        printf("%s %d\n", stud1[i].num, stud1[i].score);
    }
    fclose(fp);

    return 0;
}
