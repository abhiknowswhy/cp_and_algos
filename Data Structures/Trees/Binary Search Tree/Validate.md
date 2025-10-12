# Validate Binary Search Tree

## Problem Description

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:
- The left subtree of a node contains only nodes with keys less than the node's key
- The right subtree of a node contains only nodes with keys greater than the node's key
- Both the left and right subtrees must also be binary search trees

**LeetCode Reference:** [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)

## Key Insights

### Common Mistake
Simply checking if `left.val < root.val < right.val` is **NOT** sufficient!

**Why?** Consider this tree:
```
    5
   / \
  1   4
     / \
    3   6
```
- Node 4's children (3, 6) satisfy local condition
- But node 3 violates BST property (3 < 5 but it's in right subtree)

### Correct Approach
Each node must satisfy a **range constraint**:
- Root can be any value: `(-∞, +∞)`
- Left child: `(-∞, root.val)`
- Right child: `(root.val, +∞)`

## C++ Implementation

### Tree Node Definition
```cpp
#include <vector>
#include <iostream>
#include <climits>
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
```

### Approach 1: Range-based Validation (Recursive)
```cpp
#include <climits>
using namespace std;

class Solution {
private:
    bool validate(TreeNode* node, long long minVal, long long maxVal) {
        // Empty tree is valid BST
        if (!node) return true;
        
        // Check if current node violates BST property
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        // Recursively validate left and right subtrees with updated bounds
        return validate(node->left, minVal, node->val) && 
               validate(node->right, node->val, maxVal);
    }
    
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }
};
```

### Approach 2: In-order Traversal
```cpp
#include <vector>
#include <climits>
using namespace std;

class Solution {
private:
    void inorder(TreeNode* root, vector<int>& values) {
        if (!root) return;
        inorder(root->left, values);
        values.push_back(root->val);
        inorder(root->right, values);
    }
    
public:
    bool isValidBST(TreeNode* root) {
        vector<int> values;
        inorder(root, values);
        
        // Check if in-order traversal is strictly increasing
        for (int i = 1; i < values.size(); i++) {
            if (values[i] <= values[i-1]) {
                return false;
            }
        }
        return true;
    }
};
```

### Approach 3: In-order with Previous Value Tracking
```cpp
#include <climits>
using namespace std;

class Solution {
private:
    long long prev = LLONG_MIN;
    
    bool inorder(TreeNode* root) {
        if (!root) return true;
        
        // Check left subtree
        if (!inorder(root->left)) return false;
        
        // Check current node
        if (root->val <= prev) return false;
        prev = root->val;
        
        // Check right subtree
        return inorder(root->right);
    }
    
public:
    bool isValidBST(TreeNode* root) {
        prev = LLONG_MIN; // Reset for multiple test cases
        return inorder(root);
    }
};
```

### Approach 4: Iterative In-order
```cpp
#include <stack>
#include <climits>
using namespace std;

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        long long prev = LLONG_MIN;
        
        while (root || !st.empty()) {
            // Go to leftmost node
            while (root) {
                st.push(root);
                root = root->left;
            }
            
            // Process current node
            root = st.top();
            st.pop();
            
            // Check BST property
            if (root->val <= prev) return false;
            prev = root->val;
            
            // Move to right subtree
            root = root->right;
        }
        
        return true;
    }
};
```

### Approach 5: Morris Traversal (O(1) Space)
```cpp
#include <climits>
using namespace std;

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long long prev = LLONG_MIN;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                // No left child, process current node
                if (current->val <= prev) return false;
                prev = current->val;
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
                    // Thread already exists, process current node
                    predecessor->right = nullptr; // Remove thread
                    if (current->val <= prev) return false;
                    prev = current->val;
                    current = current->right;
                }
            }
        }
        
        return true;
    }
};
```

## Helper Functions

### Create Sample Trees
```cpp
#include <iostream>
using namespace std;

// Helper function to create a new node
TreeNode* newNode(int val) {
    return new TreeNode(val);
}

// Create valid BST
TreeNode* createValidBST() {
    TreeNode* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(1);
    root->left->right = newNode(4);
    root->right->left = newNode(7);
    root->right->right = newNode(9);
    return root;
}

// Create invalid BST
TreeNode* createInvalidBST() {
    TreeNode* root = newNode(5);
    root->left = newNode(1);
    root->right = newNode(4);  // Invalid: 4 < 5 but in right subtree
    root->right->left = newNode(3);
    root->right->right = newNode(6);
    return root;
}
```

### Print Tree Structure
```cpp
#include <iostream>
#include <queue>
using namespace std;

void printLevelOrder(TreeNode* root) {
    if (!root) return;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                cout << node->val << " ";
                q.push(node->left);
                q.push(node->right);
            } else {
                cout << "null ";
            }
        }
        cout << endl;
    }
}
```

## Complete Working Example
```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BST_Validator {
private:
    bool validate(TreeNode* node, long long minVal, long long maxVal) {
        if (!node) return true;
        
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        return validate(node->left, minVal, node->val) && 
               validate(node->right, node->val, maxVal);
    }
    
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LLONG_MIN, LLONG_MAX);
    }
    
    // Alternative: In-order approach
    bool isValidBST_Inorder(TreeNode* root) {
        stack<TreeNode*> st;
        long long prev = LLONG_MIN;
        
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            
            root = st.top();
            st.pop();
            
            if (root->val <= prev) return false;
            prev = root->val;
            
            root = root->right;
        }
        
        return true;
    }
    
    // Morris Traversal approach
    bool isValidBST_Morris(TreeNode* root) {
        long long prev = LLONG_MIN;
        TreeNode* current = root;
        
        while (current) {
            if (!current->left) {
                // No left child, process current node
                if (current->val <= prev) return false;
                prev = current->val;
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
                    // Thread already exists, process current node
                    predecessor->right = nullptr; // Remove thread
                    if (current->val <= prev) return false;
                    prev = current->val;
                    current = current->right;
                }
            }
        }
        
        return true;
    }
};

TreeNode* newNode(int val) {
    return new TreeNode(val);
}

TreeNode* createValidBST() {
    TreeNode* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(1);
    root->left->right = newNode(4);
    root->right->left = newNode(7);
    root->right->right = newNode(9);
    return root;
}

TreeNode* createInvalidBST() {
    TreeNode* root = newNode(5);
    root->left = newNode(1);
    root->right = newNode(4);
    root->right->left = newNode(3);
    root->right->right = newNode(6);
    return root;
}

void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    BST_Validator validator;
    
    // Test valid BST
    TreeNode* validBST = createValidBST();
    cout << "Valid BST inorder: ";
    printInorder(validBST);
    cout << endl;
    cout << "Is valid BST (Range method): " << validator.isValidBST(validBST) << endl;
    cout << "Is valid BST (Inorder method): " << validator.isValidBST_Inorder(validBST) << endl;
    cout << "Is valid BST (Morris method): " << validator.isValidBST_Morris(validBST) << endl;
    
    cout << endl;
    
    // Test invalid BST
    TreeNode* invalidBST = createInvalidBST();
    cout << "Invalid BST inorder: ";
    printInorder(invalidBST);
    cout << endl;
    cout << "Is valid BST (Range method): " << validator.isValidBST(invalidBST) << endl;
    cout << "Is valid BST (Inorder method): " << validator.isValidBST_Inorder(invalidBST) << endl;
    cout << "Is valid BST (Morris method): " << validator.isValidBST_Morris(invalidBST) << endl;
    
    return 0;
}
```

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| Range-based | O(n) | O(h) | h = height of tree (recursion stack) |
| In-order (vector) | O(n) | O(n) | Extra space for storing values |
| In-order (prev tracking) | O(n) | O(h) | Optimal space usage |
| Iterative in-order | O(n) | O(h) | No recursion stack |
| Morris Traversal | O(n) | O(1) | Constant space, modifies tree temporarily |

## Edge Cases to Consider

1. **Empty tree**: Valid BST
2. **Single node**: Valid BST
3. **Duplicate values**: Invalid BST (strict inequality required)
4. **Integer overflow**: Use `long long` for bounds
5. **Negative values**: Handle properly with correct bounds

## Common Pitfalls

1. **Local validation only**: Checking only immediate parent-child relationship
2. **Wrong inequality**: Using `<=` instead of `<` for bounds
3. **Integer overflow**: Using `INT_MIN/INT_MAX` when nodes can have these values
4. **Static variables**: Not resetting between test cases

## Related Problems

- **LeetCode 94:** [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
- **LeetCode 230:** [Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)
- **LeetCode 99:** [Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/)
- **LeetCode 108:** [Convert Sorted Array to BST](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)

## Key Takeaways

1. **Range-based validation** is the most intuitive and efficient approach
2. **In-order traversal** should be strictly increasing for valid BST
3. **Bounds checking** prevents integer overflow issues
4. **Global state** (like prev variable) needs careful handling in multiple test scenarios

## Morris Traversal Explanation

### How Morris Traversal Works:
1. **No Left Child**: Process current node and move right
2. **Has Left Child**: 
   - Find inorder predecessor (rightmost node in left subtree)
   - If predecessor has no right child: Create thread and go left
   - If thread exists: Remove thread, process current node, go right

### Key Benefits:
- **O(1) Space**: No recursion stack or explicit stack needed
- **Tree Integrity**: Temporarily modifies tree but restores it
- **Same Time Complexity**: Still O(n) but with constant space

### Step-by-step for BST `[5,3,8,1,4,7,9]`:
```
Step 1: current=5, create thread 4->5, go to 3
Step 2: current=3, create thread 1->3, go to 1  
Step 3: current=1, no left, process 1, go right (null)
Step 4: current=3, thread exists, remove 1->3, process 3, go to 4
Step 5: current=4, no left, process 4, go right (5 via thread)
Step 6: current=5, thread exists, remove 4->5, process 5, go to 8
Step 7: current=8, create thread 7->8, go to 7
Step 8: current=7, no left, process 7, go right (8 via thread)
Step 9: current=8, thread exists, remove 7->8, process 8, go to 9
Step 10: current=9, no left, process 9, done
```

### When to Use Morris Traversal:
- **Memory constraints**: When O(1) space is critical
- **Large trees**: Where recursion stack might overflow
- **Embedded systems**: Limited memory environments
