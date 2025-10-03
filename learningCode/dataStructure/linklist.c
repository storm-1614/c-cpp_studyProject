#include <stdio.h>
#include <stdlib.h>

// 链表结构声明
// linknode 是动态指针结构
typedef struct linknode {
    int data;               // 存储结点数据
    struct linknode* next;  // 指向下一个结点
} LinkNode;


// 链表的创建
LinkNode* CreatLinkNode() {
    int i;
    // 链表结点
    // head 是链表的结构指针
    LinkNode *head, *ptr, *p;
    // 分配内存
    head = (LinkNode*)malloc(sizeof(LinkNode));
    // 检查指针内存是否分配成功
    if (!head) {
        printf("内存分配失败\n");
        exit(1);  // 退出
    }
    // 创建结点内容
    printf("输入第 1 个数据: ");
    scanf("%d", &head->data);
    head->next = NULL;  // 初始化该指针变量指向的下一个结点为空
    ptr = head;         // ptr 指向链表开始

    // 循环创建结点
    for (i = 1; i < 5; i++) {
        p = (LinkNode*)malloc(sizeof(LinkNode));
        if (!p) {
            printf("内存分配失败\n");
            exit(1);
        }
        printf("请输入第 %d 个数据:", i + 1);
        scanf("%d", &p->data);
        p->next = NULL;
        // 连接结点
        ptr->next = p;
        // 指向下一个结点
        ptr = ptr->next;
    }
    return head;
}

// 链表的遍历
LinkNode* FindNode(LinkNode* head, int num) {
    LinkNode* ptr;
    // 指向链表起始
    ptr = head;
    // 遍历链表
    while (ptr != NULL) {
        if (ptr->data == num) return ptr;  // 查找编号
        ptr = ptr->next;                   // 指向下一个结点
    }
    return ptr;
}

// 链表的结点的插入
LinkNode* InsertNode(LinkNode* head, LinkNode* ptr, int value) {
    LinkNode* newnode = (LinkNode*)malloc(sizeof(LinkNode));
    if (!newnode) return NULL;
    newnode->data = value;  // 创建结点内容
    newnode->next = NULL;   // 设置指针初值

    if (ptr == NULL) {
        newnode->next = head;  // 新结点成为链表开始
        return newnode;
    } else {
        if (ptr->next == NULL)
            ptr->next = newnode;  // 是否是链表结束，如果是则指向新节点
        else {
            newnode->next = ptr->next;
            ptr->next = newnode;
        }
    }
    return head;
}

// 链表节点删除
// 删除链表的第 1 个结点，只需要将链表结构指针指向下一个结点即可
// 删除链表的最后一个结点，只要将指向最后一个结点的结构指针指向 NULL 即可
// 删除链表中间节点，只要将删除结点的结构指针指向删除结点的下一个结点即可
// 记得释放被删除节点的内存
LinkNode* DeleteNode(LinkNode* head, LinkNode* ptr) {
    LinkNode* pre;          // 指向前一个结点
    if (ptr == NULL)        // 是否是链表的开始
        return head->next;  // 输出第 2 个结点
    else {
        pre = head;
        while (pre->next != ptr) pre = pre->next;  // 找结点 ptr 的前结点
        if (ptr->next == NULL)                     // 是否是链表的结束
            pre->next = NULL;                      // 最后一个结点
        else
            pre->next = ptr->next;  // 中间结点
    }
    free(ptr);
    return head;
}

// 链表输出
void PrintNode(LinkNode* ptr) {
    while (ptr != NULL) {
        printf("%d\t", ptr->data);  // 输出结点数据
        ptr = ptr->next;            // 指向下一个结点
    }
    printf("\n");
}

// 链表的内存释放
void FreeLinkNode(LinkNode* head) {
    LinkNode* ptr;
    while (head != NULL) {
        ptr = head;
        head = head->next;
        free(ptr);
    }
}

int main(int argc, char* argv[]) {
    int num, value;
    LinkNode *head, *ptr;
    head = CreatLinkNode();  // 指向链表开始创建链表
    PrintNode(head);         // 输出链表
    printf("请输入要查找的数据: \n");
    scanf("%d", &num);
    ptr = FindNode(head, num);  //查询数据
    if (!ptr)
        printf("没有找到\n");
    else {
        printf("找到啦!\n请输入要插入的数据：\n");
        scanf("%d", &value);
        head = InsertNode(head, ptr, value);
        PrintNode(head);
    }
    printf("请输入要查找并删除的数据：\n");
    scanf("%d", &num);
    ptr = FindNode(head, num);
    if (!ptr)
        printf("没有找到\n");
    else {
        printf("找到啦!\n");
        head = DeleteNode(head, ptr);
        PrintNode(head);
    }
    FreeLinkNode(head);  //释放链表

    return 0;
}
