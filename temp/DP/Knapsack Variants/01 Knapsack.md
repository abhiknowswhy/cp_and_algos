# Knapsack Variants

## 0/1 Knapsack Problem

### Description:
The 0/1 Knapsack problem is a classic optimization problem. Given a set of items, each with a weight and a value, determine which items to include in a collection so that the total weight is less than or equal to a given limit (capacity) and the total value is as large as possible. Each item can either be included (1) or excluded (0) - hence the name "0/1 Knapsack".

**Problem Statement:**
- Input: weights[0...n-1], values[0...n-1], capacity W
- Output: Maximum value that can be obtained while keeping total weight ≤ W

### Key Concepts:

1. **Recursive Solution Approach**:
   - For each item, we have two choices: include it or exclude it.
   - If we include it, we add its value and reduce the available capacity.
   - If we exclude it, the value remains the same and capacity is unchanged.
   - We take the maximum of these two choices.

2. **Dynamic Programming Approach**:
   - Create a 2D DP table where dp[i][w] represents the maximum value that can be obtained using the first i items with a maximum capacity of w.
   - Base case: dp[0][w] = 0 for all w (no items means no value)
   - Recursive formula:
     - If weight[i-1] > w: dp[i][w] = dp[i-1][w] (can't include this item)
     - Else: dp[i][w] = max(value[i-1] + dp[i-1][w-weight[i-1]], dp[i-1][w])
       (maximum of including or excluding the item)

3. **Space Optimization**:
   - Since each row in the DP table only depends on the previous row, we can optimize space by using a 1D array.
   - We iterate from right to left to ensure we're using values from the previous iteration.

### Sample Implementation:

```cpp
// Standard 0/1 Knapsack implementation

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Recursive implementation with memoization
int knapsackRecursive(vector<int>& weights, vector<int>& values, int n, int capacity, 
                      vector<vector<int>>& memo) {
    // Base case
    if (n == 0 || capacity == 0)
        return 0;
        
    // If already computed
    if (memo[n][capacity] != -1)
        return memo[n][capacity];
        
    // If current item is too heavy
    if (weights[n-1] > capacity)
        return memo[n][capacity] = knapsackRecursive(weights, values, n-1, capacity, memo);
    
    // Return max of two cases: include item n-1 or exclude it
    return memo[n][capacity] = max(
        values[n-1] + knapsackRecursive(weights, values, n-1, capacity - weights[n-1], memo),
        knapsackRecursive(weights, values, n-1, capacity, memo)
    );
}

// Bottom-up DP implementation
int knapsackDP(vector<int>& weights, vector<int>& values, int n, int capacity) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    // Fill the dp table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                // Max of including or excluding current item
                dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]], dp[i-1][w]);
            } else {
                // Can't include current item
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

// Space-optimized DP implementation
int knapsackDPOptimized(vector<int>& weights, vector<int>& values, int n, int capacity) {
    vector<int> dp(capacity + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }
    
    return dp[capacity];
}

int main() {
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int capacity = 50;
    int n = values.size();
    
    // Recursive with memoization
    vector<vector<int>> memo(n+1, vector<int>(capacity+1, -1));
    cout << "Maximum value (recursive): " << knapsackRecursive(weights, values, n, capacity, memo) << endl;
    
    // DP approach
    cout << "Maximum value (DP): " << knapsackDP(weights, values, n, capacity) << endl;
    
    // Space-optimized DP
    cout << "Maximum value (optimized): " << knapsackDPOptimized(weights, values, n, capacity) << endl;
    
    return 0;
}
```

### Sample Problems:

1. **Basic 0/1 Knapsack**: [LeetCode 416 - Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
   - This is essentially determining if a subset of numbers can sum to half the total sum, which is a variation of Knapsack.

2. **Bounded Knapsack**: [CSES Problem Set - Book Shop](https://cses.fi/problemset/task/1158)
   - Given n books with prices and page counts, find the maximum number of pages you can buy with a fixed budget.

3. **Target Sum**: [LeetCode 494 - Target Sum](https://leetcode.com/problems/target-sum/)
   - Assign "+" or "-" to each number to make the sum equal to a target value.

4. **Count Subset Sum**: Count the number of subsets with a sum equal to a given value.
   - Variation: Given an array, find the number of different ways to partition it into two subsets with equal sum.

5. **Minimum Subset Sum Difference**: [LeetCode 1049 - Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/)
   - Find the minimum difference between the sums of two subsets of an array.
