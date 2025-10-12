# Minimum Depth of Binary Tree

## Problem Description

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

## Approach

Use BFS level-order traversal to find the first leaf node encountered. Since BFS explores level by level, the first leaf found will be at the minimum depth.

## Algorithm Steps

1. If root is null, return 0
2. Initialize queue with root and depth 1
3. While queue is not empty:
   - Dequeue current node and its depth
   - If current node is a leaf, return current depth
   - Add children to queue with depth + 1
4. Continue until first leaf is found

## Implementation

### C++

```cpp
#include <queue>
using namespace std;

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
    // BFS approach - optimal for minimum depth
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        
        queue<pair<TreeNode*, int>> q; // {node, depth}
        q.push({root, 1});
        
        while (!q.empty()) {
            auto [node, depth] = q.front();
            q.pop();
            
            // If it's a leaf node, return depth
            if (!node->left && !node->right) {
                return depth;
            }
            
            // Add children to queue
            if (node->left) {
                q.push({node->left, depth + 1});
            }
            if (node->right) {
                q.push({node->right, depth + 1});
            }
        }
        
        return 0; // Should never reach here for valid input
    }
    
    // DFS approach - less efficient for minimum depth
    int minDepthDFS(TreeNode* root) {
        if (!root) return 0;
        
        // If only one subtree exists, go deeper into that subtree
        if (!root->left) return 1 + minDepthDFS(root->right);
        if (!root->right) return 1 + minDepthDFS(root->left);
        
        // Both subtrees exist, take minimum
        return 1 + min(minDepthDFS(root->left), minDepthDFS(root->right));
    }
    
    // Alternative DFS with explicit leaf check
    int minDepthDFSAlternative(TreeNode* root) {
        if (!root) return 0;
        
        return dfsHelper(root);
    }
    
private:
    int dfsHelper(TreeNode* node) {
        if (!node) return INT_MAX; // Invalid path
        
        // Leaf node
        if (!node->left && !node->right) {
            return 1;
        }
        
        int leftDepth = INT_MAX;
        int rightDepth = INT_MAX;
        
        if (node->left) {
            leftDepth = dfsHelper(node->left);
        }
        if (node->right) {
            rightDepth = dfsHelper(node->right);
        }
        
        return 1 + min(leftDepth, rightDepth);
    }
};
```

### Time Complexity

- **BFS: O(n)** in worst case, but typically much better for minimum depth
- **DFS: O(n)** always visits all nodes in worst case

### Space Complexity

- **BFS: O(w)** where w is maximum width of tree
- **DFS: O(h)** where h is height of tree

## Examples

### Example 1

```
Input: root = [3,9,20,null,null,15,7]
Output: 2
Explanation: The minimum depth is 2 (root -> 9 or root -> 20)
```

### Example 2

```
Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5
Explanation: This is a skewed tree, minimum depth is 5
```

## Notes

- BFS is preferred for minimum depth as it finds answer as soon as first leaf is encountered
- DFS must explore entire tree to ensure minimum is found
- Handle edge case where one subtree is null (not a leaf condition)
- Leaf node: both left and right children are null

## Related Problems

- [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) - LeetCode 104
- [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) - LeetCode 102
- [Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/) - LeetCode 110

## LeetCode Links

- [Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/) - LeetCode 111

## Pattern: 03-Level-by-Level-Processing

This problem showcases why BFS is particularly effective for minimum depth problems. By processing level by level, we can terminate as soon as we find the first leaf, making it more efficient than DFS for this specific use case.
