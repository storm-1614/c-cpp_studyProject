/*
 * 反转单向链表
 */

#include <cstdlib>
#include <iostream>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr)
    {
    }
    ListNode(int x) : val(x), next(nullptr)
    {
    }
    ListNode(int x, ListNode *next) : val(x), next(next)
    {
    }
};

class Solution
{
  public:
    // 三指针迭代算法
    ListNode *reverseList(ListNode *head)
    {
        ListNode *Prev = NULL, *Curr = head, *Next;
        while (Curr)
        {
            Next = Curr->next;
            Curr->next = Prev;
            Prev = Curr;
            Curr = Next;
        }
        return Prev;
    }
};

void print(ListNode *first)
{
    if (first == NULL)
        return;
    std::cout << first->val << " ";
    print(first->next);
}

int main(int argc, char *argv[])
{
    Solution s;
    // 比较简陋的链表创建
    ListNode *a = new ListNode(1, NULL);
    ListNode *n = new ListNode(2, NULL);
    a->next = n;
    for (int i = 3; i <= 10; i++)
    {
        ListNode *n1 = new ListNode(i, NULL);
        n->next = n1;
        n = n1;
    }


    print(a);
    std::cout << std::endl;

    a = s.reverseList(a);
    print(a);

    return 0;
}
