#include <iostream>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *lowestCommonAncestorBST(TreeNode *root, TreeNode *p, TreeNode *q)
{
    while (root)
    {
        if (p->val < root->val && q->val < root->val)
            root = root->left; // Move left
        else if (p->val > root->val && q->val > root->val)
            root = root->right; // Move right
        else
            return root; // Found the split point
    }
    return nullptr;
}

// Test Function
int main()
{
    TreeNode *root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);

    TreeNode *p = root->left;  // Node 2
    TreeNode *q = root->right; // Node 8

    TreeNode *lca = lowestCommonAncestorBST(root, p, q);
    std::cout << "LCA in BST: " << lca->val << std::endl; // Output: LCA in BST: 6

    return 0;
}
