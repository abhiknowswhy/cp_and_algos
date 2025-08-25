# Binary Search Tree (BST) - Insert and Delete Operations

A **Binary Search Tree (BST)** is a binary tree where for each node:
- All values in the **left subtree** are **less than** the node's value
- All values in the **right subtree** are **greater than** the node's value
- Both left and right subtrees are also BSTs

## BST Node Structure

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Definition for a binary search tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

## 1. BST Insertion

**Key Insight**: Follow BST property to find the correct position
- If value < current node → go left
- If value > current node → go right
- Insert when we reach a null position

### Time Complexity: O(h) where h = height of tree
### Space Complexity: O(h) for recursion, O(1) for iteration

```cpp
class BST {
public:
    TreeNode* root;
    
    BST() : root(nullptr) {}
    
    // Method 1: Recursive Insertion
    // LeetCode: 701. Insert into a Binary Search Tree
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // Base case: found the insertion point
        if (!root) {
            return new TreeNode(val);
        }
        
        // Recursive case: find correct subtree
        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else if (val > root->val) {
            root->right = insertIntoBST(root->right, val);
        }
        // If val == root->val, we don't insert (no duplicates)
        
        return root;
    }
    
    // Method 2: Iterative Insertion
    TreeNode* insertIntoBSTIterative(TreeNode* root, int val) {
        TreeNode* newNode = new TreeNode(val);
        
        // Empty tree case
        if (!root) {
            return newNode;
        }
        
        TreeNode* current = root;
        TreeNode* parent = nullptr;
        
        // Find the insertion point
        while (current) {
            parent = current;
            if (val < current->val) {
                current = current->left;
            } else if (val > current->val) {
                current = current->right;
            } else {
                // Value already exists, don't insert
                delete newNode;
                return root;
            }
        }
        
        // Insert the new node
        if (val < parent->val) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        
        return root;
    }
    
    // Method 3: Insertion with Parent Tracking (useful for deletion)
    TreeNode* insertWithParent(TreeNode* root, int val) {
        if (!root) {
            return new TreeNode(val);
        }
        
        TreeNode* current = root;
        while (true) {
            if (val < current->val) {
                if (!current->left) {
                    current->left = new TreeNode(val);
                    break;
                } else {
                    current = current->left;
                }
            } else if (val > current->val) {
                if (!current->right) {
                    current->right = new TreeNode(val);
                    break;
                } else {
                    current = current->right;
                }
            } else {
                // Value already exists
                break;
            }
        }
        
        return root;
    }
};
```

## 2. BST Deletion

**Three Cases to Handle**:
1. **Node has no children** (leaf) → Simply remove
2. **Node has one child** → Replace node with its child
3. **Node has two children** → Replace with inorder successor (or predecessor)

### Time Complexity: O(h), Space Complexity: O(h) for recursion

```cpp
class BST {
public:
    // Helper function: Find minimum value node (leftmost)
    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function: Find maximum value node (rightmost)
    TreeNode* findMax(TreeNode* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }
    
    // Method 1: Recursive Deletion with Inorder Successor
    // LeetCode: 450. Delete Node in a BST
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return nullptr;
        }
        
        if (key < root->val) {
            // Key is in left subtree
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            // Key is in right subtree
            root->right = deleteNode(root->right, key);
        } else {
            // Found the node to delete
            
            // Case 1: Node has no children (leaf node)
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            
            // Case 2: Node has only right child
            else if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            
            // Case 2: Node has only left child
            else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            
            // Case 3: Node has two children
            else {
                // Find inorder successor (smallest in right subtree)
                TreeNode* successor = findMin(root->right);
                
                // Replace current node's value with successor's value
                root->val = successor->val;
                
                // Delete the successor (which has at most one child)
                root->right = deleteNode(root->right, successor->val);
            }
        }
        
        return root;
    }
    
    // Method 2: Deletion with Inorder Predecessor
    TreeNode* deleteNodeWithPredecessor(TreeNode* root, int key) {
        if (!root) {
            return nullptr;
        }
        
        if (key < root->val) {
            root->left = deleteNodeWithPredecessor(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNodeWithPredecessor(root->right, key);
        } else {
            // Found the node to delete
            
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            } else if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            } else {
                // Use inorder predecessor (largest in left subtree)
                TreeNode* predecessor = findMax(root->left);
                root->val = predecessor->val;
                root->left = deleteNodeWithPredecessor(root->left, predecessor->val);
            }
        }
        
        return root;
    }
    
    // Method 3: Iterative Deletion (more complex but space-efficient)
    TreeNode* deleteNodeIterative(TreeNode* root, int key) {
        if (!root) return nullptr;
        
        TreeNode* current = root;
        TreeNode* parent = nullptr;
        bool isLeftChild = false;
        
        // Find the node to delete and its parent
        while (current && current->val != key) {
            parent = current;
            if (key < current->val) {
                current = current->left;
                isLeftChild = true;
            } else {
                current = current->right;
                isLeftChild = false;
            }
        }
        
        if (!current) {
            return root; // Key not found
        }
        
        TreeNode* replacement = nullptr;
        
        // Case 1: Leaf node
        if (!current->left && !current->right) {
            replacement = nullptr;
        }
        // Case 2: Only right child
        else if (!current->left) {
            replacement = current->right;
        }
        // Case 2: Only left child
        else if (!current->right) {
            replacement = current->left;
        }
        // Case 3: Two children
        else {
            // Find inorder successor
            TreeNode* successor = current->right;
            TreeNode* successorParent = current;
            
            while (successor->left) {
                successorParent = successor;
                successor = successor->left;
            }
            
            // Replace current's value with successor's value
            current->val = successor->val;
            
            // Delete successor (which has at most right child)
            if (successorParent == current) {
                successorParent->right = successor->right;
            } else {
                successorParent->left = successor->right;
            }
            
            delete successor;
            return root;
        }
        
        // Update parent's pointer
        if (!parent) {
            // Deleting root
            delete current;
            return replacement;
        } else if (isLeftChild) {
            parent->left = replacement;
        } else {
            parent->right = replacement;
        }
        
        delete current;
        return root;
    }
};
```

## 3. Complete BST Class with All Operations

```cpp
class CompleteBST {
private:
    TreeNode* root;
    
    // Helper for inorder traversal
    void inorderHelper(TreeNode* node, vector<int>& result) {
        if (!node) return;
        inorderHelper(node->left, result);
        result.push_back(node->val);
        inorderHelper(node->right, result);
    }
    
    // Helper for tree deletion
    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    CompleteBST() : root(nullptr) {}
    
    ~CompleteBST() {
        deleteTree(root);
    }
    
    // Insert operation
    void insert(int val) {
        root = insertIntoBST(root, val);
    }
    
    // Delete operation
    void remove(int val) {
        root = deleteNode(root, val);
    }
    
    // Search operation
    // LeetCode: 700. Search in a Binary Search Tree
    bool search(int val) {
        TreeNode* current = root;
        while (current) {
            if (val == current->val) {
                return true;
            } else if (val < current->val) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }
    
    // Find minimum value
    int findMinValue() {
        if (!root) throw runtime_error("Tree is empty");
        TreeNode* min = findMin(root);
        return min->val;
    }
    
    // Find maximum value
    int findMaxValue() {
        if (!root) throw runtime_error("Tree is empty");
        TreeNode* max = findMax(root);
        return max->val;
    }
    
    // Get inorder traversal (sorted order)
    vector<int> getInorder() {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }
    
    // Check if tree is valid BST
    // LeetCode: 98. Validate Binary Search Tree
    bool isValidBST() {
        return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
    }
    
private:
    bool isValidBSTHelper(TreeNode* node, long minVal, long maxVal) {
        if (!node) return true;
        
        if (node->val <= minVal || node->val >= maxVal) {
            return false;
        }
        
        return isValidBSTHelper(node->left, minVal, node->val) &&
               isValidBSTHelper(node->right, node->val, maxVal);
    }
    
    // Include previous helper functions here...
    TreeNode* insertIntoBST(TreeNode* root, int val) { /* ... */ }
    TreeNode* deleteNode(TreeNode* root, int key) { /* ... */ }
    TreeNode* findMin(TreeNode* node) { /* ... */ }
    TreeNode* findMax(TreeNode* node) { /* ... */ }
};
```

## 4. Advanced BST Operations

```cpp
class AdvancedBST {
public:
    // Find kth smallest element
    // LeetCode: 230. Kth Smallest Element in a BST
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        return kthSmallestHelper(root, k, count);
    }
    
private:
    int kthSmallestHelper(TreeNode* root, int k, int& count) {
        if (!root) return -1;
        
        // Search in left subtree
        int left = kthSmallestHelper(root->left, k, count);
        if (left != -1) return left;
        
        // Process current node
        count++;
        if (count == k) return root->val;
        
        // Search in right subtree
        return kthSmallestHelper(root->right, k, count);
    }
    
public:
    // Convert sorted array to BST
    // LeetCode: 108. Convert Sorted Array to Binary Search Tree
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBSTHelper(nums, 0, nums.size() - 1);
    }
    
private:
    TreeNode* sortedArrayToBSTHelper(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        
        root->left = sortedArrayToBSTHelper(nums, left, mid - 1);
        root->right = sortedArrayToBSTHelper(nums, mid + 1, right);
        
        return root;
    }
    
public:
    // Lowest Common Ancestor in BST
    // LeetCode: 235. Lowest Common Ancestor of a Binary Search Tree
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            } else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            } else {
                return root;
            }
        }
        return nullptr;
    }
    
    // Range Sum of BST
    // LeetCode: 938. Range Sum of BST
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (!root) return 0;
        
        int sum = 0;
        if (root->val >= low && root->val <= high) {
            sum += root->val;
        }
        
        if (root->val > low) {
            sum += rangeSumBST(root->left, low, high);
        }
        
        if (root->val < high) {
            sum += rangeSumBST(root->right, low, high);
        }
        
        return sum;
    }
};
```

## 5. Example Usage and Testing

```cpp
int main() {
    CompleteBST bst;
    
    // Insert nodes
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    cout << "Inserting values: ";
    for (int val : values) {
        cout << val << " ";
        bst.insert(val);
    }
    cout << endl;
    
    // Print inorder (should be sorted)
    vector<int> inorder = bst.getInorder();
    cout << "Inorder traversal: ";
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl; // Output: 20 30 40 50 60 70 80
    
    // Test search
    cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (bst.search(90) ? "Found" : "Not Found") << endl;
    
    // Test min/max
    cout << "Min value: " << bst.findMinValue() << endl; // 20
    cout << "Max value: " << bst.findMaxValue() << endl; // 80
    
    // Test deletions
    cout << "\nDeleting 20 (leaf node)..." << endl;
    bst.remove(20);
    inorder = bst.getInorder();
    cout << "After deleting 20: ";
    for (int val : inorder) cout << val << " ";
    cout << endl; // Output: 30 40 50 60 70 80
    
    cout << "\nDeleting 30 (node with one child)..." << endl;
    bst.remove(30);
    inorder = bst.getInorder();
    cout << "After deleting 30: ";
    for (int val : inorder) cout << val << " ";
    cout << endl; // Output: 40 50 60 70 80
    
    cout << "\nDeleting 50 (node with two children)..." << endl;
    bst.remove(50);
    inorder = bst.getInorder();
    cout << "After deleting 50: ";
    for (int val : inorder) cout << val << " ";
    cout << endl; // Output: 40 60 70 80
    
    return 0;
}
```

## Deletion Cases Detailed Example

```cpp
void deletionCasesExample() {
    /*
    Original Tree:        50
                         /  \
                       30    70
                      /  \   /  \
                    20   40 60  80
    
    Case 1: Delete 20 (leaf node)
    - Simply remove the node
    - Parent's left pointer becomes null
    
    Case 2: Delete 30 (one child - has right child 40)
    - Replace 30 with its child 40
    - 40 becomes left child of 50
    
    Case 3: Delete 50 (two children)
    - Find inorder successor: 60 (smallest in right subtree)
    - Replace 50's value with 60's value
    - Delete original 60 node (which has at most one child)
    
    Alternative: Use inorder predecessor
    - Find inorder predecessor: 40 (largest in left subtree)
    - Replace 50's value with 40's value  
    - Delete original 40 node
    */
}
```

## Time and Space Complexity Analysis

| Operation | Average Case | Worst Case | Best Case | Space |
|-----------|--------------|------------|-----------|-------|
| **Insert** | O(log n) | O(n) | O(1) | O(log n) recursive, O(1) iterative |
| **Delete** | O(log n) | O(n) | O(1) | O(log n) recursive, O(1) iterative |
| **Search** | O(log n) | O(n) | O(1) | O(1) |

**Note**: Worst case O(n) occurs when tree becomes skewed (like a linked list)

## Related LeetCode Problems

### Core BST Operations:
- **700. Search in a Binary Search Tree** - Basic search
- **701. Insert into a Binary Search Tree** - Basic insertion
- **450. Delete Node in a BST** - Basic deletion
- **98. Validate Binary Search Tree** - Tree validation

### Advanced BST Problems:
- **230. Kth Smallest Element in a BST** - Inorder traversal application
- **235. Lowest Common Ancestor of a Binary Search Tree** - BST property utilization
- **108. Convert Sorted Array to Binary Search Tree** - Balanced BST construction
- **938. Range Sum of BST** - Range queries in BST
- **99. Recover Binary Search Tree** - BST property restoration
- **173. Binary Search Tree Iterator** - Iterator implementation
- **669. Trim a Binary Search Tree** - Range-based deletion
- **783. Minimum Distance Between BST Nodes** - Tree traversal
- **1038. Binary Search Tree to Greater Sum Tree** - Tree transformation

### Advanced Applications:
- **315. Count of Smaller Numbers After Self** - BST for counting
- **218. The Skyline Problem** - Balanced BST applications
- **732. My Calendar III** - Interval tree (BST variant)

## Key Insights and Best Practices

### ✅ Best Practices:
1. **Always maintain BST property** during insertions/deletions
2. **Handle all three deletion cases** properly
3. **Use iterative approach** when possible to save space
4. **Consider tree balancing** for better performance
5. **Validate inputs** and handle edge cases

### 🔑 Key Insights:
1. **Inorder traversal** of BST gives sorted sequence
2. **Successor/Predecessor** finding is crucial for deletion
3. **BST property** enables O(log n) operations in balanced trees
4. **Tree can degenerate** to linked list in worst case
5. **Space-time tradeoffs** between recursive and iterative approaches

### ⚠️ Common Pitfalls:
- Forgetting to update parent pointers in iterative approaches
- Not handling all deletion cases properly
- Memory leaks when not deleting nodes properly
- Breaking BST property during operations
- Not considering duplicate values policy
