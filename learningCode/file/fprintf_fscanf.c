/* 使用 fprintf() 函数和 fscanf() 函数建立文本文件 file3.txt，并读取其中的信息输出到屏幕上。  
*  
*  fprintf()  相较 printf() 多了一个文件指针参数。其实质是将输出的内容放在一个制定的文件中
*  
*    fprintf(FILE *restrict, const char *restrict, ...)
*  
*  如果 fprintf() 执行成功则返回所写的字节数,否则返回一个负数
*  
*  fscanf() 也是多处了一个文件指针参数。相较于 scanf(),输入的数据来自文本文件
*  
*    fscanf(FILE *restrict, const char *restrict, ...)
*  
*   它从文件指针所指向的文本文件中读取数据，按格式串所描述的格式输出到指定的变量中。  
*/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    FILE *fp;
    char name1[4][8], name2[4];
    int i, score1[4], score2;

    if ((fp = fopen("file3.txt", "w")) == 0){
        printf("不能打开文件\n");
        exit(0);
    }
    printf("输入数据：姓名 成绩\n");
    for (i = 1; i < 4; i++){
        scanf("%s %d", name1[i], &score1[i]);
        //向文本文件写入一行信息
        fprintf(fp, "%s %d\n", name1[i], score1[i]);
    }
    fclose(fp);

    if ((fp = fopen("file3.txt", "r")) == 0){
        printf("不能打开文件\n");
        exit(0);
    }
    printf("输出数据:\n");
    while(!feof(fp)){
        //从文件中按格式读取数据存放到 name2 数组和变量 score2 中
        fscanf(fp, "%s %d\n", name2, &score2);
        printf("%s %d\n", name2, score2);
    }
    fclose(fp);

    return 0;
}
