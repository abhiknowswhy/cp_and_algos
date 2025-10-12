# Maximum Sum Submatrix

## Problem Description

Given a 2D matrix, find the submatrix with the largest sum. A submatrix is a rectangular region of the original matrix.

## Approaches to Solve the Problem

### 1. Kadane's Algorithm Extension (For unconstrained submatrix)

#### Intuition

We can extend the 1D Kadane's algorithm (used for maximum subarray sum) to 2D by:
1. Fixing left and right column boundaries
2. For each (left, right) pair, compute the sum of elements for each row between these boundaries
3. Use 1D Kadane's algorithm on this 1D array to find the maximum subarray sum
4. Keep track of the maximum sum encountered

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// 1D Kadane's Algorithm
int kadane(vector<int>& arr, int& start, int& end) {
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    int s = 0;  // Potential start of the subarray
    
    end = -1;  // If no positive elements exist, return 0
    
    for (int i = 0; i < arr.size(); i++) {
        max_ending_here += arr[i];
        
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
        
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
    }
    
    // Handle case when all elements are negative
    if (end == -1) {
        max_so_far = arr[0];
        start = end = 0;
        
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > max_so_far) {
                max_so_far = arr[i];
                start = end = i;
            }
        }
    }
    
    return max_so_far;
}

// Function to find maximum sum submatrix
pair<int, vector<int>> findMaximumSumSubmatrix(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return {0, {0, 0, 0, 0}};
    
    int cols = matrix[0].size();
    if (cols == 0) return {0, {0, 0, 0, 0}};
    
    int maxSum = INT_MIN;
    vector<int> result(4, 0);  // left, top, right, bottom
    
    for (int left = 0; left < cols; left++) {
        vector<int> temp(rows, 0);
        
        for (int right = left; right < cols; right++) {
            // Calculate temporary sum for each row
            for (int i = 0; i < rows; i++) {
                temp[i] += matrix[i][right];
            }
            
            // Apply 1D Kadane's algorithm on temp[]
            int start, end;
            int sum = kadane(temp, start, end);
            
            if (sum > maxSum) {
                maxSum = sum;
                result[0] = left;       // left
                result[1] = start;      // top
                result[2] = right;      // right
                result[3] = end;        // bottom
            }
        }
    }
    
    return {maxSum, result};
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, -1, -4, -20},
        {-8, -3, 4, 2, 1},
        {3, 8, 10, 1, 3},
        {-4, -1, 1, 7, -6}
    };
    
    auto result = findMaximumSumSubmatrix(matrix);
    int maxSum = result.first;
    vector<int> coords = result.second;
    
    cout << "Maximum sum submatrix:" << endl;
    cout << "Sum: " << maxSum << endl;
    cout << "Position: Top left=(" << coords[1] << "," << coords[0] 
         << "), Bottom right=(" << coords[3] << "," << coords[2] << ")" << endl;
    
    cout << "Submatrix:" << endl;
    for (int i = coords[1]; i <= coords[3]; i++) {
        for (int j = coords[0]; j <= coords[2]; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

#### Time and Space Complexity
- Time Complexity: O(cols² × rows), where cols is the number of columns and rows is the number of rows in the matrix
- Space Complexity: O(rows) for the temporary array

### 2. Prefix Sum Approach (For constrained submatrix)

#### Intuition

If we're looking for a submatrix with constraints (like a fixed size k×k), we can use prefix sums:
1. Compute the 2D prefix sum for the matrix
2. For each possible submatrix, compute its sum using the prefix sums
3. Keep track of the maximum sum encountered

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Function to find maximum sum k×k submatrix
pair<int, vector<int>> findMaximumSumKxKSubmatrix(vector<vector<int>>& matrix, int k) {
    int rows = matrix.size();
    if (rows == 0 || rows < k) return {0, {0, 0}};
    
    int cols = matrix[0].size();
    if (cols == 0 || cols < k) return {0, {0, 0}};
    
    // Compute prefix sum for the matrix
    vector<vector<int>> prefixSum(rows + 1, vector<int>(cols + 1, 0));
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            prefixSum[i][j] = matrix[i-1][j-1] + 
                              prefixSum[i-1][j] + 
                              prefixSum[i][j-1] - 
                              prefixSum[i-1][j-1];
        }
    }
    
    int maxSum = INT_MIN;
    vector<int> result(2, 0);  // top-left corner coordinates
    
    // Check all possible k×k submatrices
    for (int i = k; i <= rows; i++) {
        for (int j = k; j <= cols; j++) {
            // Calculate sum of submatrix using prefix sums
            int submatrixSum = prefixSum[i][j] - 
                               prefixSum[i-k][j] - 
                               prefixSum[i][j-k] + 
                               prefixSum[i-k][j-k];
                               
            if (submatrixSum > maxSum) {
                maxSum = submatrixSum;
                result[0] = i - k;  // top
                result[1] = j - k;  // left
            }
        }
    }
    
    return {maxSum, result};
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, -1, -4, -20},
        {-8, -3, 4, 2, 1},
        {3, 8, 10, 1, 3},
        {-4, -1, 1, 7, -6}
    };
    
    int k = 2;  // Size of the submatrix
    
    auto result = findMaximumSumKxKSubmatrix(matrix, k);
    int maxSum = result.first;
    vector<int> topLeft = result.second;
    
    cout << "Maximum sum " << k << "x" << k << " submatrix:" << endl;
    cout << "Sum: " << maxSum << endl;
    cout << "Position: Top left=(" << topLeft[0] << "," << topLeft[1] << ")" << endl;
    
    cout << "Submatrix:" << endl;
    for (int i = topLeft[0]; i < topLeft[0] + k; i++) {
        for (int j = topLeft[1]; j < topLeft[1] + k; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

#### Time and Space Complexity
- Time Complexity: O(rows × cols), where rows is the number of rows and cols is the number of columns
- Space Complexity: O(rows × cols) for the prefix sum matrix

### 3. Complete Example with Both Approaches

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// 1D Kadane's Algorithm
int kadane(vector<int>& arr, int& start, int& end) {
    int max_so_far = INT_MIN;
    int max_ending_here = 0;
    int s = 0;
    
    end = -1;
    
    for (int i = 0; i < arr.size(); i++) {
        max_ending_here += arr[i];
        
        if (max_ending_here < 0) {
            max_ending_here = 0;
            s = i + 1;
        }
        
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }
    }
    
    if (end == -1) {
        max_so_far = arr[0];
        start = end = 0;
        
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > max_so_far) {
                max_so_far = arr[i];
                start = end = i;
            }
        }
    }
    
    return max_so_far;
}

// Function to find maximum sum submatrix (unconstrained)
pair<int, vector<int>> findMaximumSumSubmatrix(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return {0, {0, 0, 0, 0}};
    
    int cols = matrix[0].size();
    if (cols == 0) return {0, {0, 0, 0, 0}};
    
    int maxSum = INT_MIN;
    vector<int> result(4, 0);  // left, top, right, bottom
    
    for (int left = 0; left < cols; left++) {
        vector<int> temp(rows, 0);
        
        for (int right = left; right < cols; right++) {
            for (int i = 0; i < rows; i++) {
                temp[i] += matrix[i][right];
            }
            
            int start, end;
            int sum = kadane(temp, start, end);
            
            if (sum > maxSum) {
                maxSum = sum;
                result[0] = left;
                result[1] = start;
                result[2] = right;
                result[3] = end;
            }
        }
    }
    
    return {maxSum, result};
}

// Function to find maximum sum k×k submatrix (constrained)
pair<int, vector<int>> findMaximumSumKxKSubmatrix(vector<vector<int>>& matrix, int k) {
    int rows = matrix.size();
    if (rows == 0 || rows < k) return {0, {0, 0}};
    
    int cols = matrix[0].size();
    if (cols == 0 || cols < k) return {0, {0, 0}};
    
    vector<vector<int>> prefixSum(rows + 1, vector<int>(cols + 1, 0));
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            prefixSum[i][j] = matrix[i-1][j-1] + prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1];
        }
    }
    
    int maxSum = INT_MIN;
    vector<int> result(2, 0);
    
    for (int i = k; i <= rows; i++) {
        for (int j = k; j <= cols; j++) {
            int submatrixSum = prefixSum[i][j] - prefixSum[i-k][j] - prefixSum[i][j-k] + prefixSum[i-k][j-k];
            
            if (submatrixSum > maxSum) {
                maxSum = submatrixSum;
                result[0] = i - k;
                result[1] = j - k;
            }
        }
    }
    
    return {maxSum, result};
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, -1, -4, -20},
        {-8, -3, 4, 2, 1},
        {3, 8, 10, 1, 3},
        {-4, -1, 1, 7, -6}
    };
    
    cout << "Example Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Unconstrained maximum sum submatrix
    auto result1 = findMaximumSumSubmatrix(matrix);
    int maxSum1 = result1.first;
    vector<int> coords = result1.second;
    
    cout << "Unconstrained maximum sum submatrix:" << endl;
    cout << "Sum: " << maxSum1 << endl;
    cout << "Position: Top left=(" << coords[1] << "," << coords[0] 
         << "), Bottom right=(" << coords[3] << "," << coords[2] << ")" << endl;
    
    cout << "Submatrix:" << endl;
    for (int i = coords[1]; i <= coords[3]; i++) {
        for (int j = coords[0]; j <= coords[2]; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Constrained maximum sum submatrix (2×2)
    int k = 2;
    auto result2 = findMaximumSumKxKSubmatrix(matrix, k);
    int maxSum2 = result2.first;
    vector<int> topLeft = result2.second;
    
    cout << "Maximum sum " << k << "x" << k << " submatrix:" << endl;
    cout << "Sum: " << maxSum2 << endl;
    cout << "Position: Top left=(" << topLeft[0] << "," << topLeft[1] << ")" << endl;
    
    cout << "Submatrix:" << endl;
    for (int i = topLeft[0]; i < topLeft[0] + k; i++) {
        for (int j = topLeft[1]; j < topLeft[1] + k; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 363: Max Sum of Rectangle No Larger Than K](https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/) - A more complex variant where the sum must not exceed K
2. [LeetCode 85: Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) - Find the largest rectangle containing only 1's in a binary matrix
3. [LeetCode 1074: Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/) - Count the number of submatrices with sum equals target
4. [LeetCode 1292: Maximum Side Length of a Square with Sum Less than or Equal to Threshold](https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/)

## Summary

| Approach | Time Complexity | Space Complexity | Use Case |
|----------|-----------------|------------------|----------|
| Kadane's Algorithm Extension | O(cols² × rows) | O(rows) | Finding any size submatrix with maximum sum |
| Prefix Sum | O(rows × cols) | O(rows × cols) | Finding fixed-size submatrices or optimized queries |

## Applications

- Image processing: finding regions of interest in image matrices
- Data analysis: identifying correlated data points in 2D datasets
- Geographic information systems: analyzing "hotspots" in spatial data
- Financial analysis: finding periods of correlated stock behavior in time-series data
