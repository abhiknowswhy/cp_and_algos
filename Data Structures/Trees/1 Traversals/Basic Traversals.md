# Tree Traversals

## 1. Inorder Traversal
**Order**: Left → Root → Right
**Use Case**: In BST, gives sorted order

### Algorithm:
1. Traverse left subtree
2. Visit root
3. Traverse right subtree

### Time Complexity: O(n), Space Complexity: O(h) where h is height

```cpp
// C++ Implementation
#include <vector>
#include <stack>
using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Recursive Inorder Traversal
    // LeetCode: 94. Binary Tree Inorder Traversal
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }
    
private:
    void inorder(TreeNode* node, vector<int>& result) {
        if (node) {
            inorder(node->left, result);    // Left
            result.push_back(node->val);    // Root
            inorder(node->right, result);   // Right
        }
    }
    
public:
    // Iterative Inorder Traversal using Stack
    vector<int> inorderIterative(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* current = root;
        
        while (!stk.empty() || current) {
            // Go to leftmost node
            while (current) {
                stk.push(current);
                current = current->left;
            }
            
            // Process current node
            current = stk.top();
            stk.pop();
            result.push_back(current->val);
            
            // Move to right subtree
            current = current->right;
        }
        
        return result;
    }
};
```

## 2. Preorder Traversal
**Order**: Root → Left → Right
**Use Case**: Creating copy of tree, prefix expression

### Algorithm:
1. Visit root
2. Traverse left subtree
3. Traverse right subtree

### Time Complexity: O(n), Space Complexity: O(h)

```cpp
// C++ Implementation
class Solution {
public:
    // Recursive Preorder Traversal
    // LeetCode: 144. Binary Tree Preorder Traversal
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorder(root, result);
        return result;
    }
    
private:
    void preorder(TreeNode* node, vector<int>& result) {
        if (node) {
            result.push_back(node->val);    // Root
            preorder(node->left, result);   // Left
            preorder(node->right, result);  // Right
        }
    }
    
public:
    // Iterative Preorder Traversal using Stack
    vector<int> preorderIterative(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        stack<TreeNode*> stk;
        stk.push(root);
        
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            result.push_back(node->val);
            
            // Push right first, then left (stack is LIFO)
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
        }
        
        return result;
    }
};
```

## 3. Postorder Traversal
**Order**: Left → Right → Root
**Use Case**: Deleting tree, postfix expression

### Algorithm:
1. Traverse left subtree
2. Traverse right subtree
3. Visit root

### Time Complexity: O(n), Space Complexity: O(h)

```cpp
// C++ Implementation
class Solution {
public:
    // Recursive Postorder Traversal
    // LeetCode: 145. Binary Tree Postorder Traversal
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        postorder(root, result);
        return result;
    }
    
private:
    void postorder(TreeNode* node, vector<int>& result) {
        if (node) {
            postorder(node->left, result);  // Left
            postorder(node->right, result); // Right
            result.push_back(node->val);    // Root
        }
    }
    
public:
    // Iterative Postorder Traversal using Two Stacks
    vector<int> postorderIterative(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        stack<TreeNode*> stack1, stack2;
        stack1.push(root);
        
        // First stack for traversal, second for result
        while (!stack1.empty()) {
            TreeNode* node = stack1.top();
            stack1.pop();
            stack2.push(node);
            
            if (node->left) stack1.push(node->left);
            if (node->right) stack1.push(node->right);
        }
        
        // Pop from second stack to get postorder
        while (!stack2.empty()) {
            result.push_back(stack2.top()->val);
            stack2.pop();
        }
        
        return result;
    }
    
    // Alternative: Single Stack with Last Visited Node
    vector<int> postorderSingleStack(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* lastVisited = nullptr;
        
        while (!stk.empty() || root) {
            if (root) {
                stk.push(root);
                root = root->left;
            } else {
                TreeNode* peekNode = stk.top();
                // If right child exists and hasn't been processed yet
                if (peekNode->right && lastVisited != peekNode->right) {
                    root = peekNode->right;
                } else {
                    result.push_back(peekNode->val);
                    lastVisited = stk.top();
                    stk.pop();
                }
            }
        }
        
        return result;
    }
};
```

## 4. Level Order Traversal
**Order**: Level by level (BFS)
**Use Case**: Print tree level by level, shortest path

### Algorithm:
1. Use queue for BFS
2. Process nodes level by level

### Time Complexity: O(n), Space Complexity: O(w) where w is max width

```cpp
// C++ Implementation
#include <queue>
class Solution {
public:
    // Level Order Traversal (BFS)
    // LeetCode: 102. Binary Tree Level Order Traversal
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(level);
        }
        
        return result;
    }
    
    // Level Order Traversal - Flat Result
    // LeetCode: 107. Binary Tree Level Order Traversal II
    vector<int> levelOrderFlat(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            result.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        return result;
    }
};
```

## Example Usage:

```cpp
// C++ Example Usage
#include <iostream>
int main() {
    // Create a sample tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    Solution sol;
    
    vector<int> inorder = sol.inorderTraversal(root);     // [4, 2, 5, 1, 3]
    vector<int> preorder = sol.preorderTraversal(root);   // [1, 2, 4, 5, 3]
    vector<int> postorder = sol.postorderTraversal(root); // [4, 5, 2, 3, 1]
    vector<vector<int>> levelorder = sol.levelOrder(root); // [[1], [2, 3], [4, 5]]
    
    // Print results
    cout << "Inorder: ";
    for (int val : inorder) cout << val << " ";
    cout << endl;
    
    cout << "Preorder: ";
    for (int val : preorder) cout << val << " ";
    cout << endl;
    
    cout << "Postorder: ";
    for (int val : postorder) cout << val << " ";
    cout << endl;
    
    cout << "Level Order: ";
    for (auto& level : levelorder) {
        cout << "[";
        for (int val : level) cout << val << " ";
        cout << "] ";
    }
    cout << endl;
    
    return 0;
}
```

## Related LeetCode Problems:
- 94. Binary Tree Inorder Traversal
- 144. Binary Tree Preorder Traversal
- 145. Binary Tree Postorder Traversal
- 102. Binary Tree Level Order Traversal
- 107. Binary Tree Level Order Traversal II
- 103. Binary Tree Zigzag Level Order Traversal
- 199. Binary Tree Right Side View
- 637. Average of Levels in Binary Tree
