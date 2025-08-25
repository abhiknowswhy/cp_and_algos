# Morris Traversal

Morris Traversal is a tree traversal technique that allows us to traverse binary trees **without using extra space** for stack or recursion. It achieves **O(1) space complexity** while maintaining **O(n) time complexity**.

**Key Concept**: Uses **threaded binary trees** by creating temporary links to inorder successors.

## Why Morris Traversal?
- **Space Efficient**: O(1) space complexity (no stack/recursion)
- **Time Efficient**: O(n) time complexity
- **In-place**: Modifies tree temporarily, then restores original structure

## 1. Morris Inorder Traversal

**Algorithm**: 
1. Create links to inorder successor when going left
2. Use these links to return to parent after processing left subtree
3. Remove links to restore original tree structure

### Time Complexity: O(n), Space Complexity: O(1)

```cpp
// C++ Implementation
#include <vector>
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
    // Morris Inorder Traversal
    // LeetCode: 94. Binary Tree Inorder Traversal
    vector<int> morrisInorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                // No left subtree, process current and go right
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find inorder predecessor
                TreeNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                if (!predecessor->right) {
                    // Create threaded link and go left
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Thread exists, remove it and process current
                    predecessor->right = nullptr;
                    result.push_back(current->val);
                    current = current->right;
                }
            }
        }
        
        return result;
    }
};
```

## 2. Morris Preorder Traversal

**Algorithm**:
1. Similar to inorder, but process node **before** going to left subtree
2. Process current node when creating thread (first visit)

### Time Complexity: O(n), Space Complexity: O(1)

```cpp
class Solution {
public:
    // Morris Preorder Traversal
    // LeetCode: 144. Binary Tree Preorder Traversal
    vector<int> morrisPreorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                // No left subtree, process current and go right
                result.push_back(current->val);
                current = current->right;
            } else {
                // Find inorder predecessor
                TreeNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                if (!predecessor->right) {
                    // First visit: process current, create thread, go left
                    result.push_back(current->val);  // Process before going left
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Second visit: remove thread, go right
                    predecessor->right = nullptr;
                    current = current->right;
                }
            }
        }
        
        return result;
    }
};
```

## 3. Morris Postorder Traversal

**Algorithm**:
1. Most complex Morris traversal
2. Uses **reverse** of right edge traversal
3. Process nodes in reverse order when removing threads

### Time Complexity: O(n), Space Complexity: O(1)

```cpp
class Solution {
public:
    // Morris Postorder Traversal
    // LeetCode: 145. Binary Tree Postorder Traversal
    vector<int> morrisPostorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* dummy = new TreeNode(0);
        dummy->left = root;
        TreeNode* current = dummy;
        
        while (current) {
            if (!current->left) {
                current = current->right;
            } else {
                // Find inorder predecessor
                TreeNode* predecessor = current->left;
                while (predecessor->right && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                if (!predecessor->right) {
                    // Create thread
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Remove thread and process path
                    predecessor->right = nullptr;
                    addPath(result, current->left);
                    current = current->right;
                }
            }
        }
        
        delete dummy;
        return result;
    }
    
private:
    // Add path from 'from' to 'to' in reverse order
    void addPath(vector<int>& result, TreeNode* node) {
        vector<int> temp;
        while (node) {
            temp.push_back(node->val);
            node = node->right;
        }
        // Add in reverse order
        for (int i = temp.size() - 1; i >= 0; i--) {
            result.push_back(temp[i]);
        }
    }
    
public:
    // Alternative implementation with path reversal
    vector<int> morrisPostorderV2(TreeNode* root) {
        vector<int> result;
        TreeNode* dummy = new TreeNode(0);
        dummy->left = root;
        TreeNode* current = dummy;
        
        while (current) {
            if (current->left == nullptr) {
                current = current->right;
            } else {
                TreeNode* predecessor = current->left;
                while (predecessor->right != nullptr && predecessor->right != current) {
                    predecessor = predecessor->right;
                }
                
                if (predecessor->right == nullptr) {
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Process the path from current->left to predecessor
                    TreeNode* node = current->left;
                    reverseAddPath(result, node, predecessor);
                    predecessor->right = nullptr;
                    current = current->right;
                }
            }
        }
        
        delete dummy;
        return result;
    }
    
private:
    void reverseAddPath(vector<int>& result, TreeNode* from, TreeNode* to) {
        // Reverse the path from 'from' to 'to'
        reversePath(from, to);
        
        // Add nodes to result
        TreeNode* node = to;
        while (true) {
            result.push_back(node->val);
            if (node == from) break;
            node = node->right;
        }
        
        // Reverse back to original structure
        reversePath(to, from);
    }
    
    void reversePath(TreeNode* from, TreeNode* to) {
        if (from == to) return;
        
        TreeNode* prev = from;
        TreeNode* current = from->right;
        
        while (prev != to) {
            TreeNode* next = current->right;
            current->right = prev;
            prev = current;
            current = next;
        }
    }
};
```

## 3. Morris Postorder Traversal (Simplified)

**Algorithm**:
1. Uses a simpler approach with deque/reversing array to simulate postorder
2. Processes nodes in the order: Right → Root → Left
3. Reverses the result at the end to achieve correct postorder

### Time Complexity: O(n), Space Complexity: O(1) (for output)

```cpp
class Solution {
public:
    // Simple Morris Postorder using Deque (Reverse Inorder)
    // Process Right → Root → Left, then reverse result
    vector<int> morrisPostorderSimple(TreeNode* root) {
        deque<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->right) {
                // No right subtree, process current and go left
                result.push_front(current->val);  // Insert at front for reverse effect
                current = current->left;
            } else {
                // Find inorder successor (leftmost in right subtree)
                TreeNode* successor = current->right;
                while (successor->left && successor->left != current) {
                    successor = successor->left;
                }
                
                if (!successor->left) {
                    // First visit: process current, create thread, go right
                    result.push_front(current->val);  // Process before going right
                    successor->left = current;
                    current = current->right;
                } else {
                    // Second visit: remove thread, go left
                    successor->left = nullptr;
                    current = current->left;
                }
            }
        }
        
        return vector<int>(result.begin(), result.end());
    }
    
    // Alternative: Morris Postorder using reverse of modified preorder
    vector<int> morrisPostorderReverse(TreeNode* root) {
        vector<int> result;
        TreeNode* current = root;
        
        while (current) {
            if (!current->right) {
                result.push_back(current->val);
                current = current->left;
            } else {
                TreeNode* successor = current->right;
                while (successor->left && successor->left != current) {
                    successor = successor->left;
                }
                
                if (!successor->left) {
                    result.push_back(current->val);
                    successor->left = current;
                    current = current->right;
                } else {
                    successor->left = nullptr;
                    current = current->left;
                }
            }
        }
        
        // Reverse the result to get postorder
        reverse(result.begin(), result.end());
        return result;
    }
};
```

## Algorithm Comparison

| Traversal | When to Process Node | Key Insight | Complexity |
|-----------|---------------------|-------------|------------|
| **Inorder** | When removing thread (2nd visit) | Left → **Node** → Right | Simple |
| **Preorder** | When creating thread (1st visit) | **Node** → Left → Right | Simple |
| **Postorder (Complex)** | Process path in reverse when removing thread | Left → Right → **Node** | Complex |
| **Postorder (Simple)** | Reverse of modified preorder (Right → Root → Left) | **Reverse Pattern** | Simple |

## Detailed Morris Postorder Explanation

### Method 1: Simple Reverse Approach
```cpp
// This approach mimics preorder but processes Right → Root → Left
// Then uses deque.push_front() or vector.reverse() to get correct order

void morrisPostorderExplanation() {
    /*
    Key Insight: Postorder = Reverse of (Root → Right → Left)
    
    Instead of: Left → Right → Root (postorder)
    We do:      Root → Right → Left (reverse preorder on mirrored tree)
    Then reverse the result!
    
    Tree:     1
             / \
            2   3
           / \
          4   5
    
    Normal Postorder: [4, 5, 2, 3, 1]
    
    Our approach:
    1. Process like preorder but go Right → Root → Left: [1, 3, 2, 5, 4]
    2. Reverse the result: [4, 5, 2, 3, 1] ✓
    
    OR use deque.push_front() while processing to avoid final reverse
    */
}
```

### Method 2: Traditional Complex Approach
```cpp
// Uses dummy node and path reversal - more complex but true O(1) space
// (if we don't count the output array)
```

## Step-by-Step Example: Simple Morris Postorder

```cpp
// Example tree:    1
//                 / \
//                2   3

// Step-by-step Simple Morris Postorder execution:
void morrisPostorderSimpleExample() {
    /*
    Using deque approach (Right → Root → Left with push_front):
    
    Initial: current = 1, result = []
    
    Step 1: current = 1, has right child? YES (3)
            Find successor of 1 in right subtree = 3
            3->left == null? YES
            Add 1 to front: result = [1]
            Create thread: 3->left = 1
            Move right: current = 3
    
    Step 2: current = 3, has right child? NO
            Add 3 to front: result = [3, 1]
            Move left (follow thread): current = 1
    
    Step 3: current = 1, has right child? YES (3)
            Find successor = 3
            3->left == 1? YES (thread exists)
            Remove thread: 3->left = null
            Move left: current = 2
    
    Step 4: current = 2, has right child? NO
            Add 2 to front: result = [2, 3, 1]
            Move left: current = null
    
    Final result: [2, 3, 1] = correct postorder!
    */
}
```

## Example Usage and Testing:

```cpp
// Example Usage
#include <iostream>
#include <deque>
#include <algorithm>
int main() {
    // Create sample tree:
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
    
    // Morris Traversals
    vector<int> morrisInorder = sol.morrisInorderTraversal(root);
    vector<int> morrisPreorder = sol.morrisPreorderTraversal(root);
    vector<int> morrisPostorderSimple = sol.morrisPostorderSimple(root);
    vector<int> morrisPostorderReverse = sol.morrisPostorderReverse(root);
    vector<int> morrisPostorderComplex = sol.morrisPostorderTraversal(root);
    
    cout << "Morris Inorder: ";
    for (int val : morrisInorder) cout << val << " ";
    cout << endl;  // Output: 4 2 5 1 3
    
    cout << "Morris Preorder: ";
    for (int val : morrisPreorder) cout << val << " ";
    cout << endl;  // Output: 1 2 4 5 3
    
    cout << "Morris Postorder (Simple): ";
    for (int val : morrisPostorderSimple) cout << val << " ";
    cout << endl;  // Output: 4 5 2 3 1
    
    cout << "Morris Postorder (Reverse): ";
    for (int val : morrisPostorderReverse) cout << val << " ";
    cout << endl;  // Output: 4 5 2 3 1
    
    cout << "Morris Postorder (Complex): ";
    for (int val : morrisPostorderComplex) cout << val << " ";
    cout << endl;  // Output: 4 5 2 3 1
    
    return 0;
}
```

## Advantages and Disadvantages

### ✅ Advantages:
- **O(1) Space Complexity** - No extra stack or recursion
- **O(n) Time Complexity** - Each edge traversed at most twice
- **Memory Efficient** - Great for memory-constrained environments
- **Iterative** - No stack overflow issues
- **Simple Postorder** - Deque/reverse approach much easier to understand

### ❌ Disadvantages:
- **Complex Implementation** - Traditional postorder is complex
- **Temporary Modification** - Changes tree structure temporarily
- **Not Thread-Safe** - Cannot be used in multi-threaded environments
- **Harder to Debug** - More complex logic flow
- **Deque Overhead** - Simple postorder uses deque (still O(n) space for output)

## Related LeetCode Problems:
- **94. Binary Tree Inorder Traversal** - Morris Inorder
- **144. Binary Tree Preorder Traversal** - Morris Preorder  
- **145. Binary Tree Postorder Traversal** - Morris Postorder
- **99. Recover Binary Search Tree** - Uses Morris traversal for O(1) space
- **230. Kth Smallest Element in a BST** - Can use Morris for O(1) space

## Key Insights:
1. **Threading Concept** - Temporarily use null right pointers to store return paths
2. **Two-Phase Process** - Create threads while going down, remove while coming up
3. **Predecessor Finding** - Rightmost node in left subtree becomes the thread source
4. **Space-Time Tradeoff** - Achieves O(1) space by adding temporary links
5. **Restoration Important** - Always restore original tree structure
6. **Postorder Simplification** - Use reverse of modified preorder for easier implementation
