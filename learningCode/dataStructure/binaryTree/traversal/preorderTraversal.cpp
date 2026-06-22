/*
 * =====================================================================================
 *
 *       Filename:  preorderTraversal.cpp
 *
 *    Description: 二叉树前序遍历
 *
 *        Version:  1.0
 *        Created:  04/14/2026 08:28:41 PM
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
    /*
     * INFO: 迭代实现
     */
    std::vector<int> preorderTraversal(TreeNode *root)
    {
        std::vector<int> result;
        std::stack<TreeNode *> st;
        if (root == nullptr)
            return result;
        TreeNode *node = root;
        st.push(node);

        while (!st.empty())
        {
            node = st.top();
            st.pop();
            result.emplace_back(node->val);
            if (node->right != nullptr)
                st.push(node->right);
            if (node->left != nullptr)
                st.push(node->left);
        }
        return result;
    }

    /*
    * INFO: 递归实现
    */

    void dfs(TreeNode *node, std::vector<int> &res)
    {
        if (node == nullptr)
            return;
        res.emplace_back(node->val);
        dfs(node->left, res);
        dfs(node->right, res);
    }

    std::vector<int> preorderTraversalRecursion(TreeNode *root)
    {
        std::vector<int> res;
        dfs(root, res);
        return res;
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
    std::vector<int> res = s.preorderTraversalRecursion(a);

    for (auto iter : res)
    {
        std::cout << iter << " ";
    }
    return 0;
}
