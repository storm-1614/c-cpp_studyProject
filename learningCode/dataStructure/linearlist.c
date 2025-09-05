//创建顺序表并追加、插入、删除元素

#include <stdio.h>
#include <stdlib.h>
#define MAXLISTSIZE 1024  // 定义顺序表最大容量

typedef struct {
    int data[MAXLISTSIZE];  // 顺序表
    int last;               // 顺序表元素个数
} linearlist;

// 打印线性顺序表
void ListList(linearlist *list) {
    int i;
    printf("当前线性表状态： \n");
    if (list->last == 0)  // 顺序表为空
        printf("当前顺序表为空");
    else
        for (i = 0; i < (list->last); i++)   // 循环遍历顺序表
            printf("[%4d]", list->data[i]);  // 输出元素
    printf("\n");
}

// 打印说明文档
void Output(linearlist *list) {
    system("clear");           // 清屏
    printf("-\t顺序表\t-\n");  // 输出功能菜单
    printf("- a:追加一个节点 i:插入一个节点 -\n");
    printf("- d:删除一个节点 e:退出         -\n");
    ListList(list);
}

// 创建线性顺序表
linearlist *CreateList() {
    linearlist *list = (linearlist *)malloc(sizeof(linearlist));  // 分配空间
    list->last = 0;  // 初始化头节点值
    return list;     // 返回初始化头节点指针
}

// 追加节点
void AppendNode(linearlist *list, int n) {
    if (list->last < MAXLISTSIZE)  // 确保顺序表不溢出
    {
        list->data[list->last] = n;  // 初始化节点值
        list->last += 1;             // 顺序表长度加 1
    }
}

// 插入节点
void InsertNode(linearlist *list, int n, int pos) {
    int j;
    if (pos < 0 || pos > list->last)
        printf("所插入位置超出顺序表的范围\n");
    else {
        // 逆向遍历顺序表
        for (j = list->last; j >= pos; j--)
            list->data[j + 1] = list->data[j];  // 元素后移
        list->data[pos] = n;                    // 指向节点赋值
        list->last++;                           // 顺序表加 1
    }
}

void DeleteNode(linearlist *list, int pos) {
    int j;
    // 删除位置超出顺序表的范围
    if ((pos < 0) || (pos > list->last))
        printf("所要删除的位置超出顺序表的范围\n");
    else {
        // 遍历顺序表
        for (j = pos; j < list->last; j++)
            list->data[j] = list->data[j + 1];  // 元素前移
        list->last--;                           // 顺序表减 1
    }
}

int main(int argc, char *argv[]) {
    int key, pos;
    char ch;
    linearlist *list;
    list = CreateList();
    while (1) {
        Output(list);
        printf("请选择: ");
        ch = getchar();
        fflush(stdin);
        if (ch == 'a') {
            printf("请输入要追加的数据： ");
            scanf("%d", &key);
            AppendNode(list, key);
        } else if (ch == 'i') {
            printf("请输入要插入的位置：");
            scanf("%d", &pos);
            printf("请输入要插入的数据：");
            scanf("%d", &key);
            InsertNode(list, key, pos);
        } else if (ch == 'd') {
            printf("请输入要删除的位置：");
            scanf("%d", &pos);
            DeleteNode(list, pos);
        } else if (ch == 'e')
            exit(0);
        Output(list);
        fflush(stdin);
    }

    return 0;
}
