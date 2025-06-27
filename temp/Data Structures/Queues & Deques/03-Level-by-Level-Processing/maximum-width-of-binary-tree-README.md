# Maximum Width of Binary Tree

## Problem Description

Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

## Approach

Use BFS level-order traversal while tracking the position/index of each node. For each level, calculate the width as the difference between rightmost and leftmost positions plus 1.

## Algorithm Steps

1. If root is null, return 0
2. Initialize queue with root and its position (index 0)
3. For each level:
   - Track the first and last positions seen
   - Calculate width as (last - first + 1)
   - Update maximum width
   - Add children with calculated positions to queue
4. Return maximum width found

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
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        
        queue<pair<TreeNode*, unsigned long long>> q; // {node, position}
        q.push({root, 0});
        unsigned long long maxWidth = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            unsigned long long levelStart = q.front().second;
            unsigned long long first = 0, last = 0;
            
            for (int i = 0; i < levelSize; i++) {
                auto [node, pos] = q.front();
                q.pop();
                
                // Normalize position to prevent overflow
                pos -= levelStart;
                
                if (i == 0) first = pos;
                if (i == levelSize - 1) last = pos;
                
                if (node->left) {
                    q.push({node->left, 2 * pos});
                }
                if (node->right) {
                    q.push({node->right, 2 * pos + 1});
                }
            }
            
            maxWidth = max(maxWidth, last - first + 1);
        }
        
        return maxWidth;
    }
    
    // Alternative implementation using DFS
    int widthOfBinaryTreeDFS(TreeNode* root) {
        if (!root) return 0;
        
        vector<unsigned long long> leftmost;
        return dfs(root, 0, 0, leftmost);
    }
    
private:
    int dfs(TreeNode* node, int level, unsigned long long pos, vector<unsigned long long>& leftmost) {
        if (!node) return 0;
        
        // First node at this level
        if (level >= leftmost.size()) {
            leftmost.push_back(pos);
        }
        
        // Current width at this level
        int currentWidth = pos - leftmost[level] + 1;
        
        // Recursively check left and right subtrees
        int leftWidth = dfs(node->left, level + 1, 2 * pos, leftmost);
        int rightWidth = dfs(node->right, level + 1, 2 * pos + 1, leftmost);
        
        return max({currentWidth, leftWidth, rightWidth});
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
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9)
```

### Example 2

```
Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7)
```

### Example 3

```
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2)
```

## Notes

- Use unsigned long long to handle large position values
- Normalize positions at each level to prevent integer overflow
- Position calculation: left child = 2*pos, right child = 2*pos + 1
- Width = rightmost_position - leftmost_position + 1

## Related Problems

- [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) - LeetCode 102
- [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) - LeetCode 199
- [Find Bottom Left Tree Value](https://leetcode.com/problems/find-bottom-left-tree-value/) - LeetCode 513

## LeetCode Links

- [Maximum Width of Binary Tree](https://leetcode.com/problems/maximum-width-of-binary-tree/) - LeetCode 662

## Pattern: 03-Level-by-Level-Processing

This problem demonstrates level-by-level processing where we need to track positional information within each level. The key insight is assigning indices to nodes and calculating width based on the leftmost and rightmost positions at each level.
