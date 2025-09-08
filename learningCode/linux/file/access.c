// access() 实例

//access() 第一个参数为文件路径，第二个参数为需要检查的属性。
//如果有这个属性存在返回 0， 否则返回 -1
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int temp;
    if (argc != 2){
        printf("run error!\n");
        return 1;
    }
    temp = access(*(argv + 1), F_OK);
    if (temp == -1){
        printf("File is not exist");
        return 2;
    }

    temp = access(*(argv + 1), R_OK);
    if(temp == 0){
        printf("File can be read.\n");
    } else {
        printf("File can not be read.\n");
    }

    temp = access(*(argv + 1), W_OK);
    if (temp == 0){
        printf("File can be write.\n");
    } else {
        printf("File can not be write.\n");
    }

    temp = access(*(argv + 1), X_OK);
    if (temp == 0){
        printf("file can be run!\n");
    } else {
        printf("file can not be run.\n");
    }
    return 0;
}
