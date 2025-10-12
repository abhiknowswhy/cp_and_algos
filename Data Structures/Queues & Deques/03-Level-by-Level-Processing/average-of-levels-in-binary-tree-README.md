# Average of Levels in Binary Tree

## Problem Description

Given the root of a binary tree, return the average value of the nodes on each level in the form of an array.

## Approach

Use level-order traversal (BFS) to process the tree level by level. For each level, calculate the sum of all nodes and divide by the count to get the average.

## Algorithm Steps

1. If root is null, return empty array
2. Initialize queue with root
3. While queue is not empty:
   - Get current level size
   - Initialize sum and count for current level
   - Process all nodes at current level
   - Calculate average and add to result
   - Add children of current level nodes to queue
4. Return result array

## Implementation

### C++

```cpp
#include <vector>
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            long long sum = 0; // Use long long to prevent overflow
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                sum += node->val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            double average = (double)sum / levelSize;
            result.push_back(average);
        }
        
        return result;
    }
    
    // Alternative approach using DFS with level tracking
    vector<double> averageOfLevelsDFS(TreeNode* root) {
        vector<long long> sums;
        vector<int> counts;
        
        dfs(root, 0, sums, counts);
        
        vector<double> result;
        for (int i = 0; i < sums.size(); i++) {
            result.push_back((double)sums[i] / counts[i]);
        }
        
        return result;
    }
    
private:
    void dfs(TreeNode* node, int level, vector<long long>& sums, vector<int>& counts) {
        if (!node) return;
        
        if (level >= sums.size()) {
            sums.push_back(0);
            counts.push_back(0);
        }
        
        sums[level] += node->val;
        counts[level]++;
        
        dfs(node->left, level + 1, sums, counts);
        dfs(node->right, level + 1, sums, counts);
    }
};
```

### Time Complexity

- **O(n)** where n is the number of nodes in the tree
- Each node is visited exactly once

### Space Complexity

- **O(w)** where w is the maximum width of the tree (for BFS queue)
- **O(h)** for DFS approach where h is the height of the tree

## Examples

### Example 1

```
Input: root = [3,9,20,null,null,15,7]
Output: [3.00000,14.50000,11.00000]
Explanation: 
Level 0: [3] → average = 3
Level 1: [9,20] → average = 14.5  
Level 2: [15,7] → average = 11
```

### Example 2

```
Input: root = [3,9,20,15,7]
Output: [3.00000,14.50000,11.00000]
```

## Notes

- Use `long long` for sum to prevent integer overflow
- BFS approach is more intuitive for level-by-level processing
- DFS approach uses extra space to track sums and counts per level
- Handle edge case of empty tree

## Related Problems

- [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) - LeetCode 102
- [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) - LeetCode 104
- [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) - LeetCode 199

## LeetCode Links

- [Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/) - LeetCode 637

## Pattern: 03-Level-by-Level-Processing

This problem exemplifies level-by-level processing where we need to aggregate information (calculate average) for each level of the tree. The key is tracking the level size to process exactly one level at a time.
