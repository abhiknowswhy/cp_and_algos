# Linked List to BST Conversion

## Problem Overview
Converting between linked lists and binary search trees is a common algorithmic problem that demonstrates understanding of both data structures and tree balancing concepts.

## LeetCode References
- **LeetCode 109**: Convert Sorted List to Binary Search Tree
- **LeetCode 108**: Convert Sorted Array to Binary Search Tree (related)
- **LeetCode 114**: Flatten Binary Tree to Linked List

## Data Structure Definitions

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

## 1. Convert Sorted Linked List to Balanced BST

### Approach 1: Convert to Array First (O(n) space)

```cpp
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> values;
        
        // Convert linked list to array
        ListNode* curr = head;
        while (curr) {
            values.push_back(curr->val);
            curr = curr->next;
        }
        
        return buildBST(values, 0, values.size() - 1);
    }
    
private:
    TreeNode* buildBST(vector<int>& values, int left, int right) {
        if (left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(values[mid]);
        
        root->left = buildBST(values, left, mid - 1);
        root->right = buildBST(values, mid + 1, right);
        
        return root;
    }
};
```

### Approach 2: Two-Pointer Technique (O(1) extra space)

```cpp
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return new TreeNode(head->val);
        
        // Find the middle node using slow-fast pointers
        ListNode* prev = nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Disconnect the left half
        if (prev) prev->next = nullptr;
        
        // Create root with middle element
        TreeNode* root = new TreeNode(slow->val);
        
        // Recursively build left and right subtrees
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(slow->next);
        
        return root;
    }
};
```

### Approach 3: Inorder Simulation (Most Efficient)

```cpp
class Solution {
private:
    ListNode* current;
    
    int getLength(ListNode* head) {
        int length = 0;
        while (head) {
            length++;
            head = head->next;
        }
        return length;
    }
    
    TreeNode* buildBST(int left, int right) {
        if (left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        
        // Build left subtree first
        TreeNode* leftChild = buildBST(left, mid - 1);
        
        // Create root with current list node
        TreeNode* root = new TreeNode(current->val);
        current = current->next;
        
        // Build right subtree
        TreeNode* rightChild = buildBST(mid + 1, right);
        
        root->left = leftChild;
        root->right = rightChild;
        
        return root;
    }
    
public:
    TreeNode* sortedListToBST(ListNode* head) {
        current = head;
        int length = getLength(head);
        return buildBST(0, length - 1);
    }
};
```

## 2. Convert BST to Sorted Linked List

### Approach 1: Inorder Traversal with Array

```cpp
class Solution {
public:
    ListNode* bstToSortedList(TreeNode* root) {
        vector<int> values;
        inorderTraversal(root, values);
        
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* curr = head;
        
        for (int i = 1; i < values.size(); i++) {
            curr->next = new ListNode(values[i]);
            curr = curr->next;
        }
        
        return head;
    }
    
private:
    void inorderTraversal(TreeNode* root, vector<int>& values) {
        if (!root) return;
        
        inorderTraversal(root->left, values);
        values.push_back(root->val);
        inorderTraversal(root->right, values);
    }
};
```

### Approach 2: Direct Conversion (O(1) space)

```cpp
class Solution {
private:
    ListNode* head = nullptr;
    ListNode* prev = nullptr;
    
public:
    ListNode* bstToSortedList(TreeNode* root) {
        if (!root) return nullptr;
        
        head = nullptr;
        prev = nullptr;
        
        inorderConvert(root);
        return head;
    }
    
private:
    void inorderConvert(TreeNode* root) {
        if (!root) return;
        
        // Process left subtree
        inorderConvert(root->left);
        
        // Process current node
        ListNode* newNode = new ListNode(root->val);
        
        if (!head) {
            head = newNode;
            prev = newNode;
        } else {
            prev->next = newNode;
            prev = newNode;
        }
        
        // Process right subtree
        inorderConvert(root->right);
    }
};
```

## 3. BST to Doubly Linked List (Flatten BST)

```cpp
class Solution {
private:
    TreeNode* first = nullptr;
    TreeNode* last = nullptr;
    
public:
    TreeNode* treeToDoublyList(TreeNode* root) {
        if (!root) return nullptr;
        
        first = nullptr;
        last = nullptr;
        
        inorderHelper(root);
        
        // Connect first and last to make it circular
        last->right = first;
        first->left = last;
        
        return first;
    }
    
private:
    void inorderHelper(TreeNode* node) {
        if (!node) return;
        
        // Process left subtree
        inorderHelper(node->left);
        
        // Process current node
        if (last) {
            // Link the previous node with current node
            last->right = node;
            node->left = last;
        } else {
            // Keep track of the first node
            first = node;
        }
        last = node;
        
        // Process right subtree
        inorderHelper(node->right);
    }
};
```

## 4. Utility Functions for Testing

```cpp
class Utils {
public:
    // Create linked list from array
    static ListNode* createLinkedList(vector<int>& values) {
        if (values.empty()) return nullptr;
        
        ListNode* head = new ListNode(values[0]);
        ListNode* curr = head;
        
        for (int i = 1; i < values.size(); i++) {
            curr->next = new ListNode(values[i]);
            curr = curr->next;
        }
        
        return head;
    }
    
    // Print linked list
    static void printLinkedList(ListNode* head) {
        while (head) {
            cout << head->val;
            if (head->next) cout << " -> ";
            head = head->next;
        }
        cout << endl;
    }
    
    // Print BST (level order)
    static void printBST(TreeNode* root) {
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
    
    // Validate BST
    static bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
        if (!root) return true;
        
        if (root->val <= minVal || root->val >= maxVal) {
            return false;
        }
        
        return isValidBST(root->left, minVal, root->val) && 
               isValidBST(root->right, root->val, maxVal);
    }
};
```

## 5. Complete Test Example

```cpp
int main() {
    Solution solution;
    Utils utils;
    
    // Test 1: Convert sorted linked list to BST
    cout << "=== Test 1: Sorted List to BST ===" << endl;
    vector<int> values = {-10, -3, 0, 5, 9};
    ListNode* head = utils.createLinkedList(values);
    
    cout << "Original List: ";
    utils.printLinkedList(head);
    
    TreeNode* bst = solution.sortedListToBST(head);
    cout << "Converted BST (level order): " << endl;
    utils.printBST(bst);
    
    cout << "Is valid BST: " << (utils.isValidBST(bst) ? "Yes" : "No") << endl;
    
    // Test 2: Convert BST back to sorted list
    cout << "\n=== Test 2: BST to Sorted List ===" << endl;
    ListNode* convertedList = solution.bstToSortedList(bst);
    cout << "Converted back to list: ";
    utils.printLinkedList(convertedList);
    
    return 0;
}
```

## Complexity Analysis

### Sorted List to BST:
- **Approach 1 (Array)**: Time O(n), Space O(n)
- **Approach 2 (Two-pointer)**: Time O(n log n), Space O(log n)
- **Approach 3 (Inorder simulation)**: Time O(n), Space O(log n)

### BST to Sorted List:
- **Both approaches**: Time O(n), Space O(log n) for recursion stack

## Key Insights

1. **Balance is crucial**: When converting list to BST, always choose the middle element as root
2. **Inorder traversal**: Natural choice for BST to sorted list conversion
3. **Space optimization**: Approach 3 for list-to-BST is most efficient
4. **Edge cases**: Handle empty inputs, single nodes, and maintain proper linking

## Related Problems
- Convert sorted array to BST
- Serialize and deserialize BST
- Flatten binary tree to linked list
- Convert BST to greater tree
