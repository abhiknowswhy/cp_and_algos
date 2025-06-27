# Binary Tree Zigzag Level Order Traversal

## Problem Description

Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

## Approach

Use BFS level-order traversal and alternate the direction of adding nodes to each level's result. Use a flag to track whether current level should be left-to-right or right-to-left.

## Algorithm Steps

1. If root is null, return empty array
2. Initialize queue with root and direction flag (left-to-right = true)
3. While queue is not empty:
   - Get current level size
   - Process all nodes at current level
   - Add nodes to current level array based on direction
   - Toggle direction for next level
   - Add current level to result
4. Return result array

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
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
    // Approach 1: BFS with direction flag and reverse
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
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
            
            // Reverse if direction is right to left
            if (!leftToRight) {
                reverse(currentLevel.begin(), currentLevel.end());
            }
            
            result.push_back(currentLevel);
            leftToRight = !leftToRight; // Toggle direction
        }
        
        return result;
    }
    
    // Approach 2: Using deque for efficient insertion at both ends
    vector<vector<int>> zigzagLevelOrderDeque(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
        while (!q.empty()) {
            int levelSize = q.size();
            deque<int> currentLevel;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (leftToRight) {
                    currentLevel.push_back(node->val);
                } else {
                    currentLevel.push_front(node->val);
                }
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(vector<int>(currentLevel.begin(), currentLevel.end()));
            leftToRight = !leftToRight;
        }
        
        return result;
    }
    
    // Approach 3: Two stacks for alternating direction
    vector<vector<int>> zigzagLevelOrderTwoStacks(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        stack<TreeNode*> currentLevel;
        stack<TreeNode*> nextLevel;
        bool leftToRight = true;
        
        currentLevel.push(root);
        vector<int> levelValues;
        
        while (!currentLevel.empty()) {
            TreeNode* node = currentLevel.top();
            currentLevel.pop();
            levelValues.push_back(node->val);
            
            if (leftToRight) {
                if (node->left) nextLevel.push(node->left);
                if (node->right) nextLevel.push(node->right);
            } else {
                if (node->right) nextLevel.push(node->right);
                if (node->left) nextLevel.push(node->left);
            }
            
            if (currentLevel.empty()) {
                result.push_back(levelValues);
                levelValues.clear();
                leftToRight = !leftToRight;
                swap(currentLevel, nextLevel);
            }
        }
        
        return result;
    }
};
```

### Time Complexity

- **O(n)** where n is the number of nodes in the tree
- Each node is visited exactly once

### Space Complexity

- **O(w)** where w is the maximum width of the tree
- For queue storage and result array

## Examples

### Example 1

```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
Explanation:
Level 0: [3] (left to right)
Level 1: [20,9] (right to left) 
Level 2: [15,7] (left to right)
```

### Example 2

```
Input: root = [1]
Output: [[1]]
```

### Example 3

```
Input: root = []
Output: []
```

## Notes

- Three different approaches: reverse array, deque insertion, two stacks
- Deque approach is most efficient as it avoids reversing
- Two stacks approach naturally alternates direction by changing child insertion order
- Track direction with boolean flag that toggles each level

## Related Problems

- [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) - LeetCode 102
- [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) - LeetCode 199
- [Reverse Odd Levels of Binary Tree](https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/) - LeetCode 2415

## LeetCode Links

- [Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) - LeetCode 103

## Pattern: 03-Level-by-Level-Processing

This problem demonstrates level-by-level processing with alternating direction. The key insight is maintaining level boundaries while changing the order of processing within each level.
