# Populating Next Right Pointers

## Problem Description

You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

## Approach

Use BFS level-order traversal to process nodes level by level. For each level, connect consecutive nodes using their next pointers.

## Algorithm Steps

1. If root is null, return null
2. Initialize queue with root
3. While queue is not empty:
   - Get current level size
   - Process all nodes at current level
   - For each node (except last), set next pointer to the next node in queue
   - Add children to queue for next level
4. Return root

## Implementation

### C++

```cpp
#include <queue>
using namespace std;

// Definition for a Node
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    // BFS approach using queue
    Node* connect(Node* root) {
        if (!root) return nullptr;
        
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            for (int i = 0; i < levelSize; i++) {
                Node* node = q.front();
                q.pop();
                
                // Connect to next node in same level (except for last node)
                if (i < levelSize - 1) {
                    node->next = q.front();
                }
                
                // Add children to queue
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return root;
    }
    
    // Optimized O(1) space approach using existing next pointers
    Node* connectOptimal(Node* root) {
        if (!root) return nullptr;
        
        Node* levelStart = root;
        
        while (levelStart->left) { // While not at leaf level
            Node* current = levelStart;
            
            // Connect all nodes at next level
            while (current) {
                // Connect left child to right child
                current->left->next = current->right;
                
                // Connect right child to next node's left child
                if (current->next) {
                    current->right->next = current->next->left;
                }
                
                current = current->next;
            }
            
            levelStart = levelStart->left; // Move to next level
        }
        
        return root;
    }
    
    // Recursive approach
    Node* connectRecursive(Node* root) {
        if (!root || !root->left) return root;
        
        // Connect left child to right child
        root->left->next = root->right;
        
        // Connect right child to cousin (if parent has next)
        if (root->next) {
            root->right->next = root->next->left;
        }
        
        // Recursively connect subtrees
        connectRecursive(root->left);
        connectRecursive(root->right);
        
        return root;
    }
};

// For non-perfect binary tree (LeetCode 117)
class SolutionGeneral {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        
        Node* levelStart = root;
        
        while (levelStart) {
            Node* current = levelStart;
            Node* nextLevelStart = nullptr;
            Node* nextLevelPrev = nullptr;
            
            while (current) {
                if (current->left) {
                    if (nextLevelPrev) {
                        nextLevelPrev->next = current->left;
                    } else {
                        nextLevelStart = current->left;
                    }
                    nextLevelPrev = current->left;
                }
                
                if (current->right) {
                    if (nextLevelPrev) {
                        nextLevelPrev->next = current->right;
                    } else {
                        nextLevelStart = current->right;
                    }
                    nextLevelPrev = current->right;
                }
                
                current = current->next;
            }
            
            levelStart = nextLevelStart;
        }
        
        return root;
    }
};
```

### Time Complexity

- **O(n)** where n is the number of nodes in the tree
- Each node is visited exactly once

### Space Complexity

- **BFS: O(w)** where w is maximum width of tree
- **Optimal: O(1)** using existing next pointers

## Examples

### Example 1

```
Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Level connections are made as shown
```

### Example 2

```
Input: root = []
Output: []
```

## Notes

- Perfect binary tree allows O(1) space solution using existing next pointers
- For general binary tree, need to handle cases where nodes may have 0, 1, or 2 children
- BFS naturally processes level by level, making connections straightforward
- Recursive solution elegant but uses O(h) space due to call stack

## Related Problems

- [Populating Next Right Pointers in Each Node II](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/) - LeetCode 117
- [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) - LeetCode 102
- [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) - LeetCode 199

## LeetCode Links

- [Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/) - LeetCode 116
- [Populating Next Right Pointers in Each Node II](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/) - LeetCode 117

## Pattern: 03-Level-by-Level-Processing

This problem demonstrates level-by-level processing where we need to establish connections between nodes at the same level. The BFS approach naturally groups nodes by level, making it straightforward to connect them.
