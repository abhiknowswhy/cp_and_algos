# Optimal Binary Search Tree

## Problem Statement
Given a sorted array of keys `keys[0...n-1]` and their corresponding frequency of access `freq[0...n-1]`, construct a Binary Search Tree (BST) such that the total cost of all searches is minimum.

The cost of searching an element is proportional to its depth in the BST. The goal is to arrange the nodes in such a way that frequently accessed elements are closer to the root, thus minimizing the overall search cost.

## Algorithm Explanation

The Optimal BST problem can be solved using dynamic programming. Let's denote:

- `keys[i...j]`: A subarray containing keys from index i to j
- `freq[i...j]`: Corresponding frequencies
- `cost[i][j]`: Cost of optimal BST containing keys from i to j

The key observations are:
1. Any key in the range `keys[i...j]` can be chosen as the root
2. The optimal cost will be the sum of:
   - The root node's frequency * 1 (depth 0)
   - The optimal cost of the left subtree with added depth
   - The optimal cost of the right subtree with added depth
   - The sum of all frequencies in this range (to account for the increased depth)

### Recurrence Relation

```
cost[i][j] = min { 
                   sum(freq[i...j]) + cost[i][r-1] + cost[r+1][j] 
                 } for all r where i ≤ r ≤ j
```

Where `sum(freq[i...j])` is the sum of all frequencies in the range, which represents the additional cost added when these nodes are pushed one level deeper in the tree.

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to construct optimal BST
int optimalBST(vector<int>& keys, vector<int>& freq, int n) {
    // Create a 2D table to store costs of optimal BST
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    
    // Initialize for sequences of length 1
    for (int i = 0; i < n; i++)
        dp[i][i] = freq[i];
    
    // Fill the dp table for different lengths of sequences
    for (int L = 2; L <= n; L++) {
        // For each possible starting position
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            
            // Try each key as root and find the minimum cost
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += freq[k];
                
            for (int r = i; r <= j; r++) {
                // Calculate cost when keys[r] is the root
                int left = (r > i) ? dp[i][r-1] : 0;
                int right = (r < j) ? dp[r+1][j] : 0;
                int cost = sum + left + right;
                
                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }
    
    return dp[0][n-1];
}

// Complete executable example
int main() {
    vector<int> keys = {10, 12, 20, 35, 46};
    vector<int> freq = {34, 8, 50, 21, 16};
    int n = keys.size();
    
    cout << "Cost of Optimal BST is: " << optimalBST(keys, freq, n) << endl;
    return 0;
}
```

## Extended Implementation with Tree Construction

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure to represent a node of the optimal BST
struct Node {
    int key;
    Node* left;
    Node* right;
    
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Function to construct optimal BST and return its cost and root
pair<int, vector<vector<int>>> optimalBSTWithRoot(vector<int>& keys, vector<int>& freq, int n) {
    // Create tables to store costs and roots of optimal BST
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    vector<vector<int>> root(n, vector<int>(n, 0));
    
    // Initialize for sequences of length 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = freq[i];
        root[i][i] = i;
    }
    
    // Fill the dp table for different lengths of sequences
    for (int L = 2; L <= n; L++) {
        // For each possible starting position
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            
            // Calculate sum of frequencies from i to j
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += freq[k];
                
            // Try each key as root and find the minimum cost
            for (int r = i; r <= j; r++) {
                // Calculate cost when keys[r] is the root
                int left = (r > i) ? dp[i][r-1] : 0;
                int right = (r < j) ? dp[r+1][j] : 0;
                int cost = sum + left + right;
                
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    root[i][j] = r;  // Store the root that gives minimum cost
                }
            }
        }
    }
    
    return {dp[0][n-1], root};
}

// Function to build the optimal BST from the root table
Node* buildOptimalBST(vector<int>& keys, const vector<vector<int>>& root, int i, int j) {
    if (i > j) return nullptr;
    
    int r = root[i][j];
    Node* node = new Node(keys[r]);
    
    node->left = buildOptimalBST(keys, root, i, r-1);
    node->right = buildOptimalBST(keys, root, r+1, j);
    
    return node;
}

// Function to print inorder traversal of the BST
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Complete executable example
int main() {
    vector<int> keys = {10, 12, 20, 35, 46};
    vector<int> freq = {34, 8, 50, 21, 16};
    int n = keys.size();
    
    auto [cost, rootTable] = optimalBSTWithRoot(keys, freq, n);
    cout << "Cost of Optimal BST is: " << cost << endl;
    
    Node* optimalRoot = buildOptimalBST(keys, rootTable, 0, n-1);
    cout << "Inorder traversal of Optimal BST: ";
    inorder(optimalRoot);
    cout << endl;
    
    // Cleanup memory (ideally should use a proper cleanup function)
    // This is simplified for clarity
    
    return 0;
}
```

## Time and Space Complexity

- **Time Complexity**: O(n³) where n is the number of keys
- **Space Complexity**: O(n²) for the DP table

## Optimization

The algorithm can be optimized to O(n²) time complexity by using the property that the root of the optimal BST for keys[i..j] lies between the roots of optimal BSTs for keys[i..j-1] and keys[i+1..j].

## Related LeetCode Problems

1. **LeetCode 1130 - Minimum Cost Tree From Leaf Values**:
   - Similar concept of minimizing the cost while building a tree
   - [https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/](https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/)

2. **LeetCode 1039 - Minimum Score Triangulation of Polygon**:
   - Uses a similar DP approach to find the minimum cost
   - [https://leetcode.com/problems/minimum-score-triangulation-of-polygon/](https://leetcode.com/problems/minimum-score-triangulation-of-polygon/)

3. **LeetCode 96 - Unique Binary Search Trees**:
   - Although not directly about optimal BST, it's related to the number of possible BSTs
   - [https://leetcode.com/problems/unique-binary-search-trees/](https://leetcode.com/problems/unique-binary-search-trees/)

4. **LeetCode 95 - Unique Binary Search Trees II**:
   - Generates all structurally unique BSTs for values 1 to n
   - [https://leetcode.com/problems/unique-binary-search-trees-ii/](https://leetcode.com/problems/unique-binary-search-trees-ii/)

## Applications

Optimal BST is useful in:
1. Compiler design - for optimal symbol table organization
2. Search engines - to organize frequently searched terms
3. Database indexing - for efficient query execution

## References

1. Introduction to Algorithms by Cormen, Leiserson, Rivest, and Stein
2. Dynamic Programming & Optimal Control by Dimitri P. Bertsekas
