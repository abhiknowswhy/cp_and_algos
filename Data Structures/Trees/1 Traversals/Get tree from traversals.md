# Tree Reconstruction from Traversals

We can reconstruct the tree correctly only when one of the traversals given is inorder.

We can reconstruct the tree from:
- Inorder and preorder
- Inorder and postorder
- Inorder and levelorder

We cannot construct the tree from:
- Postorder and preorder
- Levelorder and preorder
- Levelorder and postorder

**Why Inorder is Required?**
Inorder traversal helps us identify the left and right subtrees. Without it, we cannot uniquely determine the tree structure.

## 1. Construct Tree from Inorder and Preorder

### Algorithm:
1. First element in preorder is always root
2. Find root position in inorder to split left and right subtrees
3. Recursively build left and right subtrees

### Time Complexity: O(n), Space Complexity: O(n)

```cpp
// C++ Implementation
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Construct Binary Tree from Preorder and Inorder Traversal
    // LeetCode: 105. Construct Binary Tree from Preorder and Inorder Traversal
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return build(preorder, 0, preorder.size() - 1, 
                    inorder, 0, inorder.size() - 1, inorderMap);
    }
    
private:
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                   vector<int>& inorder, int inStart, int inEnd,
                   unordered_map<int, int>& inorderMap) {
        if (preStart > preEnd) return nullptr;
        
        // Root is first element in preorder range
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);
        
        // Find root position in inorder
        int rootIdx = inorderMap[rootVal];
        
        // Calculate left subtree size
        int leftSize = rootIdx - inStart;
        
        // Build left subtree
        root->left = build(preorder, preStart + 1, preStart + leftSize,
                          inorder, inStart, rootIdx - 1, inorderMap);
        
        // Build right subtree
        root->right = build(preorder, preStart + leftSize + 1, preEnd,
                           inorder, rootIdx + 1, inEnd, inorderMap);
        
        return root;
    }
    
public:
    // Alternative implementation using global preorder index
    TreeNode* buildTreeV2(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int preIdx = 0;
        return buildHelper(preorder, inorder, 0, inorder.size() - 1, 
                          preIdx, inorderMap);
    }
    
private:
    TreeNode* buildHelper(vector<int>& preorder, vector<int>& inorder,
                         int start, int end, int& preIdx,
                         unordered_map<int, int>& inorderMap) {
        if (start > end) return nullptr;
        
        int rootVal = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootVal);
        
        if (start == end) return root;
        
        int rootIdx = inorderMap[rootVal];
        
        // Build left first, then right (preorder nature)
        root->left = buildHelper(preorder, inorder, start, rootIdx - 1, 
                                preIdx, inorderMap);
        root->right = buildHelper(preorder, inorder, rootIdx + 1, end, 
                                 preIdx, inorderMap);
        
        return root;
    }
};
```

## 2. Construct Tree from Inorder and Postorder

### Algorithm:
1. Last element in postorder is always root
2. Find root position in inorder to split left and right subtrees
3. Recursively build right and left subtrees (reverse order)

### Time Complexity: O(n), Space Complexity: O(n)

```cpp
// C++ Implementation
class Solution {
public:
    // Construct Binary Tree from Inorder and Postorder Traversal
    // LeetCode: 106. Construct Binary Tree from Inorder and Postorder Traversal
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        return build(inorder, 0, inorder.size() - 1,
                    postorder, 0, postorder.size() - 1, inorderMap);
    }
    
private:
    TreeNode* build(vector<int>& inorder, int inStart, int inEnd,
                   vector<int>& postorder, int postStart, int postEnd,
                   unordered_map<int, int>& inorderMap) {
        if (inStart > inEnd) return nullptr;
        
        // Root is last element in postorder range
        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);
        
        // Find root position in inorder
        int rootIdx = inorderMap[rootVal];
        
        // Calculate left subtree size
        int leftSize = rootIdx - inStart;
        
        // Build left subtree
        root->left = build(inorder, inStart, rootIdx - 1,
                          postorder, postStart, postStart + leftSize - 1,
                          inorderMap);
        
        // Build right subtree
        root->right = build(inorder, rootIdx + 1, inEnd,
                           postorder, postStart + leftSize, postEnd - 1,
                           inorderMap);
        
        return root;
    }
    
public:
    // Alternative implementation using global postorder index
    TreeNode* buildTreeV2(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inorderMap;
        for (int i = 0; i < inorder.size(); i++) {
            inorderMap[inorder[i]] = i;
        }
        
        int postIdx = postorder.size() - 1;
        return buildHelper(inorder, postorder, 0, inorder.size() - 1,
                          postIdx, inorderMap);
    }
    
private:
    TreeNode* buildHelper(vector<int>& inorder, vector<int>& postorder,
                         int start, int end, int& postIdx,
                         unordered_map<int, int>& inorderMap) {
        if (start > end) return nullptr;
        
        int rootVal = postorder[postIdx--];
        TreeNode* root = new TreeNode(rootVal);
        
        if (start == end) return root;
        
        int rootIdx = inorderMap[rootVal];
        
        // Build right first, then left (postorder nature - reverse)
        root->right = buildHelper(inorder, postorder, rootIdx + 1, end,
                                 postIdx, inorderMap);
        root->left = buildHelper(inorder, postorder, start, rootIdx - 1,
                                postIdx, inorderMap);
        
        return root;
    }
};
```

## 3. Construct Tree from Inorder and Level Order

### Algorithm:
1. First element in level order is root
2. Find root in inorder to split left and right subtrees
3. Filter level order elements for left and right subtrees
4. Recursively build subtrees

### Time Complexity: O(n²), Space Complexity: O(n)

```cpp
// C++ Implementation
#include <unordered_set>
#include <algorithm>
class Solution {
public:
    // Construct Binary Tree from Inorder and Level Order Traversal
    TreeNode* buildTree(vector<int>& inorder, vector<int>& levelorder) {
        if (inorder.empty() || levelorder.empty()) return nullptr;
        
        return build(inorder, levelorder);
    }
    
private:
    TreeNode* build(vector<int>& inArr, vector<int>& levelArr) {
        if (inArr.empty() || levelArr.empty()) return nullptr;
        
        // Root is first element in level order
        int rootVal = levelArr[0];
        TreeNode* root = new TreeNode(rootVal);
        
        if (inArr.size() == 1) return root;
        
        // Find root position in inorder
        auto rootIt = find(inArr.begin(), inArr.end(), rootVal);
        int rootIdx = rootIt - inArr.begin();
        
        // Split inorder array
        vector<int> leftInorder(inArr.begin(), inArr.begin() + rootIdx);
        vector<int> rightInorder(inArr.begin() + rootIdx + 1, inArr.end());
        
        // Create sets for faster lookup
        unordered_set<int> leftSet(leftInorder.begin(), leftInorder.end());
        unordered_set<int> rightSet(rightInorder.begin(), rightInorder.end());
        
        // Filter level order for left and right subtrees
        vector<int> leftLevel, rightLevel;
        for (int val : levelArr) {
            if (leftSet.count(val)) leftLevel.push_back(val);
            else if (rightSet.count(val)) rightLevel.push_back(val);
        }
        
        // Build subtrees
        root->left = build(leftInorder, leftLevel);
        root->right = build(rightInorder, rightLevel);
        
        return root;
    }
};
```

## 4. Why Some Combinations Don't Work

### Preorder + Postorder (without inorder):
```cpp
// C++ Example showing ambiguity
class AmbiguityDemo {
public:
    void demonstrateAmbiguity() {
        // Example showing ambiguity:
        // Preorder: [1, 2]  Postorder: [2, 1]
        // Could be:    1        OR      1
        //             /                  \
        //            2                    2
        // Both trees give same preorder and postorder!
        
        vector<int> preorder = {1, 2};
        vector<int> postorder = {2, 1};
        
        cout << "Preorder: ";
        for (int val : preorder) cout << val << " ";
        cout << "\nPostorder: ";
        for (int val : postorder) cout << val << " ";
        cout << "\nAmbiguous - cannot determine unique tree!" << endl;
    }
};
```

## Example Usage and Testing:

```cpp
// C++ Example Usage and Testing
#include <iostream>
class TreeTester {
public:
    void printTreeTraversals(TreeNode* root) {
        cout << "Inorder: ";
        vector<int> inorder = getInorder(root);
        for (int val : inorder) cout << val << " ";
        cout << endl;
        
        cout << "Preorder: ";
        vector<int> preorder = getPreorder(root);
        for (int val : preorder) cout << val << " ";
        cout << endl;
        
        cout << "Postorder: ";
        vector<int> postorder = getPostorder(root);
        for (int val : postorder) cout << val << " ";
        cout << endl;
    }
    
private:
    vector<int> getInorder(TreeNode* node) {
        if (!node) return {};
        vector<int> result;
        vector<int> left = getInorder(node->left);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(node->val);
        vector<int> right = getInorder(node->right);
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }
    
    vector<int> getPreorder(TreeNode* node) {
        if (!node) return {};
        vector<int> result = {node->val};
        vector<int> left = getPreorder(node->left);
        result.insert(result.end(), left.begin(), left.end());
        vector<int> right = getPreorder(node->right);
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }
    
    vector<int> getPostorder(TreeNode* node) {
        if (!node) return {};
        vector<int> result;
        vector<int> left = getPostorder(node->left);
        result.insert(result.end(), left.begin(), left.end());
        vector<int> right = getPostorder(node->right);
        result.insert(result.end(), right.begin(), right.end());
        result.push_back(node->val);
        return result;
    }
};

int main() {
    // Original tree:    3
    //                  / \
    //                 9   20
    //                    /  \
    //                   15   7
    
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    vector<int> levelorder = {3, 9, 20, 15, 7};
    
    Solution sol;
    TreeTester tester;
    
    // Test 1: Inorder + Preorder
    TreeNode* tree1 = sol.buildTree(preorder, inorder);
    cout << "From Inorder + Preorder:" << endl;
    tester.printTreeTraversals(tree1);
    
    // Test 2: Inorder + Postorder
    TreeNode* tree2 = sol.buildTree(inorder, postorder);
    cout << "\nFrom Inorder + Postorder:" << endl;
    tester.printTreeTraversals(tree2);
    
    return 0;
}
```

## Related LeetCode Problems:
- 105. Construct Binary Tree from Preorder and Inorder Traversal
- 106. Construct Binary Tree from Inorder and Postorder Traversal
- 889. Construct Binary Tree from Preorder and Postorder Traversal (Special case)
- 297. Serialize and Deserialize Binary Tree
- 449. Serialize and Deserialize BST

## Key Insights:
1. **Inorder is crucial** - it helps identify left and right subtrees
2. **Preorder gives root first** - useful for top-down construction
3. **Postorder gives root last** - useful for bottom-up construction
4. **Level order gives breadth-first** - requires careful filtering
5. **Without inorder, tree construction is often ambiguous**
