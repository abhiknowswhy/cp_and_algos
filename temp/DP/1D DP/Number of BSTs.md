# Number of Unique Binary Search Trees

## Problem Description

Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.

**LeetCode Reference:** [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)

## Approach

This problem can be solved using dynamic programming and the concept of Catalan numbers.

### Key Insight

- For n nodes, we can choose any node as root (1 to n)
- If we choose node i as root:
  - Left subtree will have (i-1) nodes
  - Right subtree will have (n-i) nodes
- Total BSTs = sum of (BSTs with left subtree) × (BSTs with right subtree) for all possible roots

### Formula

If G(n) represents number of unique BSTs with n nodes:

- G(0) = 1 (empty tree)
- G(1) = 1 (single node)
- G(n) = Σ(i=1 to n) G(i-1) × G(n-i)

This is the nth Catalan number!

## C++ Implementation

### Approach 1: Dynamic Programming (Bottom-up)

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        // dp[i] represents number of unique BSTs with i nodes
        vector<int> dp(n + 1, 0);
      
        // Base cases
        dp[0] = 1; // empty tree
        if (n >= 1) dp[1] = 1; // single node
      
        // Fill dp table for 2 to n nodes
        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                // Choose 'root' as root node
                // Left subtree: (root-1) nodes
                // Right subtree: (nodes-root) nodes
                dp[nodes] += dp[root - 1] * dp[nodes - root];
            }
        }
      
        return dp[n];
    }
};
```

### Approach 2: Memoized Recursion

```cpp
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_map<int, int> memo;
  
    int solve(int n) {
        if (n <= 1) return 1;
      
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
      
        int result = 0;
        for (int i = 1; i <= n; i++) {
            result += solve(i - 1) * solve(n - i);
        }
      
        return memo[n] = result;
    }
  
public:
    int numTrees(int n) {
        return solve(n);
    }
};
```

### Approach 3: Mathematical Formula (Catalan Number)

```cpp
class Solution {
public:
    int numTrees(int n) {
        // nth Catalan number = C(2n, n) / (n + 1)
        // Using the formula: C(2n, n) = (2n)! / ((n+1)! * n!)
        long long result = 1;
  
        for (int i = 0; i < n; i++) {
            result = result * (n + i + 1) / (i + 1);
        }
  
        return result / (n + 1);
    }
};
```

## Complexity Analysis

### Approach 1 & 2: DP/Memoization

- **Time Complexity:** O(n²)
- **Space Complexity:** O(n)

### Approach 3: Mathematical

- **Time Complexity:** O(n)
- **Space Complexity:** O(1)

## Example Walkthrough

For n = 3:

- Root = 1: Left subtree (0 nodes) = 1 way, Right subtree (2 nodes) = 2 ways → 1 × 2 = 2
- Root = 2: Left subtree (1 node) = 1 way, Right subtree (1 node) = 1 way → 1 × 1 = 1
- Root = 3: Left subtree (2 nodes) = 2 ways, Right subtree (0 nodes) = 1 way → 2 × 1 = 2

Total = 2 + 1 + 2 = 5

## Related Problems

- **LeetCode 95:** [Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/) - Generate all unique BSTs
- **Catalan Numbers Applications:** Parentheses combinations, polygon triangulation

## Key Points

1. This is a classic application of Catalan numbers
2. The DP approach builds the solution bottom-up
3. Mathematical approach is most efficient for large n
4. Pattern: For each possible root, multiply left and right subtree possibilities

# Generating All Unique BSTs

**LeetCode Reference:** [95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)

### Problem Description
Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.

### Tree Node Definition
```cpp
#include <vector>
#include <map>
#include <iostream>
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

### Approach 1: Recursive Generation
```cpp
#include <vector>
using namespace std;

class Solution {
private:
    vector<TreeNode*> generateTrees(int start, int end) {
        vector<TreeNode*> result;
        
        // Base case: empty range
        if (start > end) {
            result.push_back(nullptr);
            return result;
        }
        
        // Try each number as root
        for (int i = start; i <= end; i++) {
            // Generate all possible left subtrees
            vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
            // Generate all possible right subtrees
            vector<TreeNode*> rightTrees = generateTrees(i + 1, end);
            
            // Combine each left subtree with each right subtree
            for (TreeNode* left : leftTrees) {
                for (TreeNode* right : rightTrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        
        return result;
    }
    
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }
};
```

### Approach 2: Memoized Recursion
```cpp
#include <vector>
#include <map>
#include <utility>
using namespace std;

class Solution {
private:
    map<pair<int, int>, vector<TreeNode*>> memo;
    
    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) {
            return {nullptr};
        }
        
        pair<int, int> key = {start, end};
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        vector<TreeNode*> result;
        
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i + 1, end);
            
            for (TreeNode* left : leftTrees) {
                for (TreeNode* right : rightTrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        
        return memo[key] = result;
    }
    
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }
};
```

### Approach 3: Clone-based Generation (Space Optimized)
```cpp
#include <vector>
using namespace std;

class Solution {
private:
    TreeNode* clone(TreeNode* root, int offset) {
        if (!root) return nullptr;
        
        TreeNode* newRoot = new TreeNode(root->val + offset);
        newRoot->left = clone(root->left, offset);
        newRoot->right = clone(root->right, offset);
        return newRoot;
    }
    
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        
        vector<vector<TreeNode*>> dp(n + 1);
        dp[0] = {nullptr};
        
        for (int numNodes = 1; numNodes <= n; numNodes++) {
            for (int root = 1; root <= numNodes; root++) {
                int leftNodes = root - 1;
                int rightNodes = numNodes - root;
                
                for (TreeNode* left : dp[leftNodes]) {
                    for (TreeNode* right : dp[rightNodes]) {
                        TreeNode* rootNode = new TreeNode(root);
                        rootNode->left = left;
                        rootNode->right = clone(right, root);
                        dp[numNodes].push_back(rootNode);
                    }
                }
            }
        }
        
        return dp[n];
    }
};
```

## Helper Functions for Testing

### Print Tree (In-order)
```cpp
#include <vector>
#include <iostream>
using namespace std;

void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

void printTree(TreeNode* root) {
    vector<int> result;
    inorderTraversal(root, result);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
}
```

### Print All Trees
```cpp
#include <vector>
#include <iostream>
using namespace std;

void printAllTrees(vector<TreeNode*>& trees) {
    cout << "Total unique BSTs: " << trees.size() << endl;
    for (int i = 0; i < trees.size(); i++) {
        cout << "Tree " << (i + 1) << ": ";
        printTree(trees[i]);
    }
}
```

### Complete Working Example
```cpp
#include <vector>
#include <map>
#include <iostream>
#include <utility>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BST_Counter {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        if (n >= 1) dp[1] = 1;
        
        for (int nodes = 2; nodes <= n; nodes++) {
            for (int root = 1; root <= nodes; root++) {
                dp[nodes] += dp[root - 1] * dp[nodes - root];
            }
        }
        return dp[n];
    }
};

class BST_Generator {
private:
    vector<TreeNode*> generateTrees(int start, int end) {
        vector<TreeNode*> result;
        if (start > end) {
            result.push_back(nullptr);
            return result;
        }
        
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i + 1, end);
            
            for (TreeNode* left : leftTrees) {
                for (TreeNode* right : rightTrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        return result;
    }
    
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }
};

void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

void printTree(TreeNode* root) {
    vector<int> result;
    inorderTraversal(root, result);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    int n = 3;
    
    // Count unique BSTs
    BST_Counter counter;
    cout << "Number of unique BSTs with " << n << " nodes: " << counter.numTrees(n) << endl;
    
    // Generate all unique BSTs
    BST_Generator generator;
    vector<TreeNode*> trees = generator.generateTrees(n);
    
    cout << "\nAll unique BSTs:" << endl;
    for (int i = 0; i < trees.size(); i++) {
        cout << "Tree " << (i + 1) << ": ";
        printTree(trees[i]);
    }
    
    return 0;
}
```

## Complexity Analysis for Tree Generation

### Approach 1 & 2: Recursive/Memoized
- **Time Complexity:** O(4^n / √n) - Related to nth Catalan number
- **Space Complexity:** O(4^n / √n) - For storing all trees

### Approach 3: Clone-based DP
- **Time Complexity:** O(4^n / √n)
- **Space Complexity:** O(4^n / √n)

## Example for n = 3

The 5 unique BSTs are:
```
   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

## Comparison: Count vs Generate

| Aspect | Count BSTs (Problem 96) | Generate BSTs (Problem 95) |
|--------|------------------------|---------------------------|
| Output | Integer count | Vector of TreeNode* |
| Space | O(n) | O(Catalan(n)) |
| Use Case | When only count needed | When actual trees needed |
| Efficiency | Much faster | Exponential space/time |
