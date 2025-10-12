# Binary tree right side view

## Problem Description
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

**LeetCode Problem:** [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

## Approach
Use level-order traversal and capture the rightmost node at each level. Process each level completely and take the last node processed.

## Algorithm Steps
1. Use BFS with queue to traverse level by level
2. For each level, track the level size
3. Process all nodes at current level
4. The last node processed at each level is the rightmost visible node
5. Add rightmost node value to result

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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // If this is the last node in the level, add to result
                if (i == levelSize - 1) {
                    result.push_back(node->val);
                }
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return result;
    }
};

// Alternative DFS approach
class SolutionDFS {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        dfs(root, 0, result);
        return result;
    }
    
private:
    void dfs(TreeNode* node, int level, vector<int>& result) {
        if (!node) return;
        
        // If this is the first node at this level (rightmost due to order)
        if (level == result.size()) {
            result.push_back(node->val);
        }
        
        // Visit right first, then left
        dfs(node->right, level + 1, result);
        dfs(node->left, level + 1, result);
    }
};
```

### Time Complexity
O(n) where n is the number of nodes

### Space Complexity
O(w) where w is the maximum width of the tree

## Examples

### Example 1
```
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Tree:
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
```

### Example 2
```
Input: root = [1,null,3]
Output: [1,3]

Tree:
1      <---
 \
  3    <---
```

### Example 3
```
Input: root = []
Output: []
```

## Notes
- Can be solved with both BFS and DFS approaches
- BFS: Track position in level to identify rightmost node
- DFS: Visit right subtree first and use level to track first seen node
- Similar pattern works for left side view (just change the condition)

## Related Problems
- [LeetCode 102 - Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- [LeetCode 103 - Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
- [LeetCode 515 - Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)
- [LeetCode 637 - Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/)

## Pattern: 03-Level-by-Level-Processing
This pattern processes each level completely and extracts specific information (rightmost node) from each level. The key is tracking position within the level to identify the target node.
