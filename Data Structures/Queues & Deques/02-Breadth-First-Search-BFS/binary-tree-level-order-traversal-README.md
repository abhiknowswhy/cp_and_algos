# Binary tree level order traversal

## Problem Description
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

**LeetCode Problem:** [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

## Approach
Use BFS with a queue to traverse the tree level by level. For each level, process all nodes currently in the queue before adding their children.

## Algorithm Steps
1. Initialize queue with root node and result vector
2. While queue is not empty, get current level size
3. Process all nodes at current level, adding values to level vector
4. Add children of current nodes to queue for next level
5. Add completed level to result

## Implementation

### C++
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                currentLevel.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
};
```

### Time Complexity
O(n) where n is the number of nodes in the tree

### Space Complexity
O(w) where w is the maximum width of the tree (for the queue)

## Examples

### Example 1
```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Tree:
    3
   / \
  9  20
    /  \
   15   7
```

### Example 2
```
Input: root = [1]
Output: [[1]]

Tree:
1
```

### Example 3
```
Input: root = []
Output: []
```

## Notes
- Level size tracking is crucial for separating levels
- Queue stores nodes, not values
- Children are added left to right for next level processing
- This is the foundation for many other tree BFS problems

## Related Problems
- [LeetCode 103 - Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
- [LeetCode 107 - Binary Tree Level Order Traversal II](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/)
- [LeetCode 199 - Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)
- [LeetCode 637 - Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/)
- [LeetCode 515 - Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)

## Pattern: 02-Breadth-First-Search-BFS
This is the classic BFS pattern for trees. The level-by-level processing using queue size tracking is fundamental to many tree problems and serves as the template for BFS traversals.
