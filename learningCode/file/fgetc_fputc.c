//使用 fputc()  和 fgetc() 函数建立一个名为 "file1.txt" 的文本文件，并在屏幕上显示文件中的内容

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *fp1, *fp2;
    char c;
    //以只写方式新建文件，并测试是否成功
    if ((fp1 = fopen("file1.txt", "w")) == 0) {
        printf("不能打开文件\n");
        exit(0);
    }

    //接收从键盘中输入的字符串，输入回车结束循环
    printf("输入字符: \n");
    while ((c = getchar()) != '\n') fputc(c, fp1);
    fclose(fp1);

    //以只读的方式打开文件,测试是否成功
    if ((fp2 = fopen("file1.txt", "r")) == 0){
        printf("不能打开文件\n");
        exit(0);
    }
    //从文件的开头处读字符一个个放入 c  中然后一个个把 c 中的值输出到屏幕上。 
    while ((c = fgetc(fp2)) != EOF) putchar(c);
    printf("\n");
    fclose(fp2);

    return 0;
}
