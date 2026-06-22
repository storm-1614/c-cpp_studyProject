/*
 * =====================================================================================
 *
 *       Filename:  inorderTraversal.cpp
 *
 *    Description: 二叉树中序遍历
 *
 *        Version:  1.0
 *        Created:  04/14/2026 08:48:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  storm-1614
 *   Organization:
 *
 * =====================================================================================
 */
#include <iostream>
#include <stack>
#include <vector>

/**
 * Definition for a binary tree node.
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr)
    {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {
    }
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right)
    {
    }
};

class Solution
{
  public:
    std::vector<int> inorderTraversal(TreeNode *root)
    {
        std::vector<int> result;
        std::stack<TreeNode *> st;
        TreeNode *current = root;
        if (root == nullptr)
            return result;
        while (current != nullptr || !st.empty())
        {
            while (current != nullptr)
            {
                st.push(current);
                current = current->left;
            }
            current = st.top();
            st.pop();
            result.emplace_back(current->val);
            current = current->right;
        }
        return result;
    }
};

int main(int argc, char *argv[])
{
    TreeNode *a = new TreeNode(4);
    TreeNode *b = new TreeNode(2);
    TreeNode *c = new TreeNode(5);
    a->left = b;
    a->right = c;

    TreeNode *d = new TreeNode(1);
    TreeNode *e = new TreeNode(3);
    b->left = d;
    b->right = e;

    Solution s;
    std::vector<int> res = s.inorderTraversal(a);

    for (auto iter : res)
    {
        std::cout << iter << " ";
    }
    return 0;
}
