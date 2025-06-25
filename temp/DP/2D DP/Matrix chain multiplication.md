# Optimal Matrix Multiplication (Matrix Chain Multiplication)

## Problem Description

Given a sequence of matrices, the goal is to find the most efficient way to multiply these matrices. The problem is not to perform the multiplications, but to decide the sequence of multiplications to minimize the number of operations.

## Understanding Matrix Multiplication

When multiplying two matrices A and B:

- If A is of dimension p×q and B is of dimension q×r, then:
  - The resulting matrix C will be of dimension p×r
  - The number of scalar multiplications needed is p×q×r

For a chain of matrices A₁, A₂, ..., Aₙ, where A₁ is of dimension p₀×p₁, A₂ is of dimension p₁×p₂, and so on, we need to find the optimal way to place parentheses to minimize computations.

## Dynamic Programming Approach

### Key Insight

The matrix chain multiplication problem exhibits:

1. **Optimal Substructure**: The optimal solution can be constructed from optimal solutions of its subproblems.
2. **Overlapping Subproblems**: The same subproblems are solved multiple times.

### Algorithm

1. Let dp[i][j] represent the minimum number of scalar multiplications needed to compute the product of matrices from A_i to A_j.
2. Base case: dp[i][i] = 0 (no cost for a single matrix)
3. For a chain A_i, A_{i+1}, ..., A_j, we try different positions k where we can split the chain:
   - Split between A_k and A_{k+1} for i ≤ k < j
   - Compute dp[i][j] = min(dp[i][k] + dp[k+1][j] + p_{i-1}×p_k×p_j)

### Time and Space Complexity

- Time Complexity: O(n³), where n is the number of matrices
- Space Complexity: O(n²) for the dp table

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to find the most efficient way to multiply matrices
// dimensions[i-1] x dimensions[i] = dimension of matrix i
int matrixChainMultiplication(const vector<int>& dimensions) {
    int n = dimensions.size() - 1; // Number of matrices
  
    // dp[i][j] = Minimum number of scalar multiplications needed
    // to compute the matrix multiplication A_i * A_{i+1} * ... * A_j
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  
    // parenthesis[i][j] = k means the optimal split is between k and k+1
    vector<vector<int>> parenthesis(n + 1, vector<int>(n + 1, 0));
  
    // Compute for chains of increasing length
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
          
            // Try different positions to split the chain
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + 
                          dimensions[i - 1] * dimensions[k] * dimensions[j];
              
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    parenthesis[i][j] = k;
                }
            }
        }
    }
  
    return dp[1][n];
}

// Function to print the optimal parenthesization
void printOptimalParenthesis(const vector<vector<int>>& parenthesis, int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
  
    cout << "(";
    printOptimalParenthesis(parenthesis, i, parenthesis[i][j]);
    cout << " × ";
    printOptimalParenthesis(parenthesis, parenthesis[i][j] + 1, j);
    cout << ")";
}

int main() {
    // Example: Matrix dimensions are 30×35, 35×15, 15×5, 5×10, 10×20, 20×25
    vector<int> dimensions = {30, 35, 15, 5, 10, 20, 25};
    int minOperations = matrixChainMultiplication(dimensions);
  
    cout << "Minimum number of scalar multiplications: " << minOperations << endl;
  
    // For printing optimal parenthesization, we need to compute parenthesis matrix
    vector<vector<int>> parenthesis(dimensions.size(), vector<int>(dimensions.size(), 0));
    int n = dimensions.size() - 1;
  
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
  
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
          
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + 
                          dimensions[i - 1] * dimensions[k] * dimensions[j];
              
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    parenthesis[i][j] = k;
                }
            }
        }
    }
  
    cout << "Optimal parenthesization: ";
    printOptimalParenthesis(parenthesis, 1, n);
    cout << endl;
  
    return 0;
}
```

## Complete Executable Example 2: With Detailed Tracking

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <functional>
using namespace std;

void matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1;
  
    // m[i,j] = Minimum number of scalar multiplications needed
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
  
    // s[i,j] = Index of the matrix after which the product is split in an optimal solution
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));
  
    // l is chain length
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
      
            for (int k = i; k < j; k++) {
                // q = cost of multiplying matrices A_i to A_k and A_{k+1} to A_j
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
          
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
  
    cout << "Minimum scalar multiplications: " << m[1][n] << endl;
  
    // Print dp table
    cout << "\nDP Table (m):" << endl;
    cout << "   ";
    for (int j = 1; j <= n; j++)
        cout << setw(6) << j;
    cout << endl;
  
    for (int i = 1; i <= n; i++) {
        cout << setw(2) << i << " ";
        for (int j = 1; j <= n; j++) {
            if (j < i)
                cout << setw(6) << "-";
            else
                cout << setw(6) << m[i][j];
        }
        cout << endl;
    }
  
    // Print split positions
    cout << "\nSplit Positions (s):" << endl;
    cout << "   ";
    for (int j = 1; j <= n; j++)
        cout << setw(6) << j;
    cout << endl;
  
    for (int i = 1; i <= n; i++) {
        cout << setw(2) << i << " ";
        for (int j = 1; j <= n; j++) {
            if (j <= i)
                cout << setw(6) << "-";
            else
                cout << setw(6) << s[i][j];
        }
        cout << endl;
    }
  
    // Function to print optimal parenthesization
    function<void(int, int)> printOptimalParens = [&](int i, int j) {
        if (i == j)
            cout << "A" << i;
        else {
            cout << "(";
            printOptimalParens(i, s[i][j]);
            cout << "×";
            printOptimalParens(s[i][j] + 1, j);
            cout << ")";
        }
    };
  
    cout << "\nOptimal Parenthesization: ";
    printOptimalParens(1, n);
    cout << endl;
}

int main() {
    // Example: Dimensions of matrices A1, A2, A3, A4, A5
    // A1: 30×35, A2: 35×15, A3: 15×5, A4: 5×10, A5: 10×20
    vector<int> dimensions = {30, 35, 15, 5, 10, 20};
  
    cout << "Matrix Dimensions:" << endl;
    for (int i = 0; i < dimensions.size() - 1; i++) {
        cout << "A" << (i + 1) << ": " << dimensions[i] << "×" << dimensions[i + 1] << endl;
    }
    cout << endl;
  
    matrixChainOrder(dimensions);
  
    return 0;
}
```

## Related LeetCode Problems

1. **LeetCode 312 - Burst Balloons**

   - This problem can be solved using a similar dynamic programming approach where you need to decide the order of bursting balloons to maximize coins.
   - https://leetcode.com/problems/burst-balloons/
2. **LeetCode 1039 - Minimum Score Triangulation of Polygon**

   - Another problem with a similar pattern of deciding the order of operations.
   - https://leetcode.com/problems/minimum-score-triangulation-of-polygon/
3. **LeetCode 1130 - Minimum Cost Tree From Leaf Values**

   - This problem involves finding optimal ways to construct a tree, similar to optimal matrix chain multiplication.
   - https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/
4. **LeetCode 546 - Remove Boxes**

   - A more complex problem that uses a similar DP approach with state transitions.
   - https://leetcode.com/problems/remove-boxes/

## Additional Notes

- Matrix chain multiplication is a classic example of dynamic programming.
- The algorithm uses a bottom-up approach, building solutions for larger subproblems from solutions to smaller subproblems.
- The optimal ordering can significantly reduce computational cost - sometimes by orders of magnitude.
- This technique is applicable to many similar problems involving finding the optimal order of operations.
