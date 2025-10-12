# 2D Staircase Search

## Introduction

Staircase Search (also known as Search Space Reduction or Elimination Method) is an efficient algorithm for searching in matrices that are sorted both row-wise and column-wise. This method takes advantage of the matrix's sorted property to eliminate portions of the search space in each step.

## Matrix Properties Required for Staircase Search

For a matrix to be suitable for staircase search:
- Each row must be sorted in ascending order from left to right
- Each column must be sorted in ascending order from top to bottom

Example of such a matrix:
```
[
  [10, 20, 30, 40],
  [15, 25, 35, 45],
  [27, 29, 37, 48],
  [32, 33, 39, 50]
]
```

## The Staircase Search Algorithm (O(m + n))

The algorithm works by starting at a "strategic" corner of the matrix and making a decision at each step to eliminate either a row or column from consideration.

### Algorithm Steps:

1. Start from the top-right corner (or alternatively, the bottom-left corner)
2. Compare the current element with the target:
   - If equal: We found the target
   - If current element > target: Move left (eliminate the current column)
   - If current element < target: Move down (eliminate the current row)
3. Repeat until we find the target or go out of bounds

### Visual Representation

Imagine searching for 29 in the above matrix:
1. Start at top-right (40): 40 > 29, move left
2. Check 30: 30 > 29, move left
3. Check 20: 20 < 29, move down
4. Check 25: 25 < 29, move down
5. Check 29: Found!

The search creates a staircase-like path through the matrix, hence the name.

## Implementation

```cpp
// Check if target exists in a row and column sorted matrix
bool staircaseSearch(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) 
        return false;
  
    int rows = matrix.size();
    int cols = matrix[0].size();
  
    // Start from top-right corner
    int row = 0, col = cols - 1;
  
    while (row < rows && col >= 0) {
        if (matrix[row][col] == target) {
            // Found the target
            cout << "Found at position: (" << row << ", " << col << ")" << endl;
            return true;
        } else if (matrix[row][col] > target) {
            // Target is smaller, eliminate current column
            col--;
        } else {
            // Target is larger, eliminate current row
            row++;
        }
    }
  
    return false;  // Target not found
}
```

## Alternative: Starting from Bottom-Left

We could also start the search from the bottom-left corner:

```cpp
bool staircaseSearchBottomLeft(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) 
        return false;
  
    int rows = matrix.size();
    int cols = matrix[0].size();
  
    // Start from bottom-left corner
    int row = rows - 1, col = 0;
  
    while (row >= 0 && col < cols) {
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] > target) {
            row--;  // Move up
        } else {
            col++;  // Move right
        }
    }
  
    return false;  // Target not found
}
```

## Complete Implementation with Example

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Staircase Search Method (O(m + n))
bool staircaseSearch(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) 
        return false;
  
    int rows = matrix.size();
    int cols = matrix[0].size();
  
    // Start from top-right corner
    int row = 0, col = cols - 1;
  
    while (row < rows && col >= 0) {
        if (matrix[row][col] == target) {
            cout << "Found at position: (" << row << ", " << col << ")" << endl;
            return true;
        } else if (matrix[row][col] > target) {
            col--;  // Move left
        } else {
            row++;  // Move down
        }
    }
  
    return false;
}

int main() {
    // Example: Row and column sorted matrix
    vector<vector<int>> matrix = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {27, 29, 37, 48},
        {32, 33, 39, 50}
    };
  
    int target1 = 29;
    int target2 = 100;
  
    cout << "Searching for " << target1 << ":" << endl;
    bool found1 = staircaseSearch(matrix, target1);
    cout << (found1 ? "Target found!" : "Target not found!") << endl;
  
    cout << "\nSearching for " << target2 << ":" << endl;
    bool found2 = staircaseSearch(matrix, target2);
    cout << (found2 ? "Target found!" : "Target not found!") << endl;
  
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity: O(m + n)
- In the worst case, we might need to traverse m rows and n columns
- This is much better than the naive O(m*n) approach
- Each step eliminates either a row or column, creating a path of at most m+n steps

### Space Complexity: O(1)
- We only use a constant amount of extra space regardless of input size

## Comparison with Binary Search Approaches

- **Staircase Search**: O(m + n) time complexity, simpler to implement
- **Binary Search on Rows, then Columns**: O(log(m) + log(n)) time complexity, more complex
- **Treat as 1D Array**: O(log(m*n)) time complexity, only works for fully sorted matrices

The staircase search is often preferred for row and column sorted matrices because of its simplicity and good performance on real-world data.

## When to Use Staircase Search

- When the matrix is sorted both row-wise and column-wise
- When you need a simple, non-recursive solution
- When the matrix is large and you want a predictable linear time algorithm

## Limitations

- Only works for matrices with the specific sorted property mentioned
- Not optimal for fully sorted matrices (where binary search would be better)
- May not be as efficient as binary search approaches for very large matrices

## Practice Problems

- Leetcode 240: Search a 2D Matrix II (perfect for staircase search)
- Counting elements less than a given value in a row-column sorted matrix
- Finding the median in a row-wise sorted matrix

Staircase search is a powerful technique that showcases how understanding data structure properties can lead to efficient algorithms.
