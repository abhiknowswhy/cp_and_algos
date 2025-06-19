# 2D Binary Search for Fully Sorted Matrices

## Introduction

2D Binary Search is an extension of the standard binary search algorithm to two-dimensional arrays (matrices). It's particularly effective when dealing with sorted matrices, allowing us to search for values in O(log(m*n)) time compared to O(m*n) for a linear search.

## Types of Sorted Matrices

### 1. Row and Column Sorted Matrix

- Each row is sorted in ascending order from left to right
- Each column is sorted in ascending order from top to bottom

For this type of matrix, staircase search (O(m+n)) is effective. See the separate document on staircase search for details.

Example:

```
[
  [10, 20, 30, 40],
  [15, 25, 35, 45],
  [27, 29, 37, 48],
  [32, 33, 39, 50]
]
```

### 2. Fully Sorted Matrix

- The entire matrix, when flattened, would form a single sorted array

We can search in O(log(mn)) - more efficient than other approaches for this specific case

Example:

```
[
  [1,  2,  3,  4],
  [5,  6,  7,  8],
  [9, 10, 11, 12]
]
```

## Binary Search for Fully Sorted Matrices

### Approach: Treat as 1D Array (O(log(m*n)))

For fully sorted matrices, we can map 2D indices to 1D and perform a standard binary search.

```cpp
// Search in a fully sorted matrix
bool searchSortedMatrix(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty())
        return false;
  
    int rows = matrix.size();
    int cols = matrix[0].size();
  
    int left = 0;
    int right = rows * cols - 1;
  
    while (left <= right) {
        int mid = left + (right - left) / 2;
      
        // Convert 1D index to 2D coordinates
        int r = mid / cols; 
        int c = mid % cols;
      
        if (matrix[r][c] == target) {
            return true;
        } else if (matrix[r][c] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
  
    return false;  // Target not found
}
```

## Complete Implementation with Example

Below is a complete C++ implementation for searching in fully sorted matrices:

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Approach: Treat as 1D Array (O(log(m*n)))
pair<int, int> searchMatrixAs1D(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty())
        return {-1, -1};
  
    int rows = matrix.size();
    int cols = matrix[0].size();
  
    int left = 0;
    int right = rows * cols - 1;
  
    while (left <= right) {
        int mid = left + (right - left) / 2;
      
        // Convert 1D index to 2D coordinates
        int r = mid / cols; 
        int c = mid % cols;
      
        if (matrix[r][c] == target) {
            return {r, c};
        } else if (matrix[r][c] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
  
    return {-1, -1};
}

int main() {
    // Example: Fully sorted matrix
    vector<vector<int>> matrix = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };
  
    int target = 7;
    int notPresent = 100;
  
    cout << "Testing Binary Search on Fully Sorted Matrix:" << endl;
    pair<int, int> res = searchMatrixAs1D(matrix, target);
    if (res.first != -1) {
        cout << "Target " << target << " found at position: (" << res.first << ", " << res.second << ")" << endl;
    } else {
        cout << "Target " << target << " not found" << endl;
    }
  
    res = searchMatrixAs1D(matrix, notPresent);
    if (res.first != -1) {
        cout << "Target " << notPresent << " found at position: (" << res.first << ", " << res.second << ")" << endl;
    } else {
        cout << "Target " << notPresent << " not found" << endl;
    }
  
    return 0;
}
```

## Time Complexity Analysis

**Treat as 1D Array**: O(log(m*n))
- Single binary search on m*n elements
- Very efficient for fully sorted matrices

## When to Use This Approach

- Best for matrices where the entire matrix is sorted in row-major order
- Most efficient when you know the matrix follows this specific sorting pattern
- Can be adapted for column-major order by adjusting the index calculation

## Practice Problems

- Leetcode 74: Search a 2D Matrix (specifically asks for this approach)
- Finding kth smallest element in a fully sorted matrix
- Binary search on matrices with special patterns or properties

Understanding the 2D Binary Search technique for fully sorted matrices is essential for solving matrix-based search problems efficiently.
