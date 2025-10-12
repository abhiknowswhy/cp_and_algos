# Local Minima Search

## Problem Definition

A **local minimum** in an array is an element that is smaller than or equal to its neighbors. For a one-dimensional array:

- For an internal element (not at the edges): `A[i]` is a local minimum if `A[i] <= A[i-1]` and `A[i] <= A[i+1]`
- For boundary elements:
  - `A[0]` is a local minimum if `A[0] <= A[1]`
  - `A[n-1]` is a local minimum if `A[n-1] <= A[n-2]`

Similarly, in a two-dimensional array (matrix), a local minimum is an element that is smaller than or equal to all of its adjacent neighbors (up, down, left, right).

## Algorithm Approach

The naive approach is to check every element in the array, which takes O(n) time. However, we can use a binary search-like approach to find a local minimum in O(log n) time for a one-dimensional array.

### Key Insight

If we examine the middle element of the array:

- If it's a local minimum, we've found our answer
- If not, at least one of its neighbors will be smaller than it
- We can move in the direction of the smaller neighbor, and guarantee that a local minimum exists in that half

## 1D Local Minima Search

```cpp
#include <iostream>
#include <vector>

using namespace std;

// Returns the index of a local minimum in the array
int findLocalMinimum(const vector<int>& nums) {
    int n = nums.size();
  
    // Handle empty array
    if (n == 0) return -1;
  
    // Handle single element array
    if (n == 1) return 0;
  
    // Check if first element is local minimum
    if (nums[0] <= nums[1]) return 0;
  
    // Check if last element is local minimum
    if (nums[n-1] <= nums[n-2]) return n-1;
  
    // Binary search for local minimum
    int left = 1;
    int right = n-2;
  
    while (left <= right) {
        int mid = left + (right - left) / 2;
      
        // Check if mid is a local minimum
        if (nums[mid] <= nums[mid-1] && nums[mid] <= nums[mid+1])
            return mid;
      
        // If left neighbor is smaller, go left
        else if (nums[mid-1] < nums[mid])
            right = mid - 1;
      
        // Otherwise, go right
        else
            left = mid + 1;
    }
  
    // This should never happen if the array has a valid input
    return -1;
}

int main() {
    // Example arrays
    vector<int> arr1 = {9, 6, 3, 14, 5, 7, 4};
    vector<int> arr2 = {5, 4, 3, 2, 1, 2};
    vector<int> arr3 = {1, 2, 3};
  
    int idx1 = findLocalMinimum(arr1);
    int idx2 = findLocalMinimum(arr2);
    int idx3 = findLocalMinimum(arr3);
  
    cout << "Local minimum in arr1 is at index " << idx1 << " with value " << arr1[idx1] << endl;
    cout << "Local minimum in arr2 is at index " << idx2 << " with value " << arr2[idx2] << endl;
    cout << "Local minimum in arr3 is at index " << idx3 << " with value " << arr3[idx3] << endl;
  
    return 0;
}
```

## 2D Local Minima Search

For a two-dimensional matrix, the approach is more complex but follows a similar binary search strategy:

```cpp
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Helper function to find minimum element in a column
pair<int, int> findMinInColumn(const vector<vector<int>>& matrix, int col) {
    int min_val = INT_MAX;
    int min_row = -1;
  
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][col] < min_val) {
            min_val = matrix[i][col];
            min_row = i;
        }
    }
  
    return {min_row, min_val};
}

// Returns the coordinates (row, col) of a local minimum in the matrix
pair<int, int> find2DLocalMinimum(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return {-1, -1};
  
    int cols = matrix[0].size();
    if (cols == 0) return {-1, -1};
  
    // If matrix is 1x1
    if (rows == 1 && cols == 1) return {0, 0};
  
    int left = 0;
    int right = cols - 1;
  
    while (left <= right) {
        int mid = left + (right - left) / 2;
      
        // Find the minimum element in the middle column
        auto [min_row, min_val] = findMinInColumn(matrix, mid);
      
        // Check if we're at the edge columns
        bool is_left_bigger = (mid == 0 || matrix[min_row][mid-1] >= min_val);
        bool is_right_bigger = (mid == cols-1 || matrix[min_row][mid+1] >= min_val);
      
        // If both left and right neighbors are bigger or equal, we found a local min
        if (is_left_bigger && is_right_bigger) {
            return {min_row, mid};
        }
      
        // Move towards the smaller neighbor
        if (!is_left_bigger) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
  
    // This should never happen with valid inputs
    return {-1, -1};
}

int main() {
    // Example matrix
    vector<vector<int>> matrix = {
        {10, 8,  10, 10},
        {14, 13, 12, 11},
        {15, 9,  11, 21},
        {16, 17, 19, 20}
    };
  
    auto [row, col] = find2DLocalMinimum(matrix);
  
    if (row != -1 && col != -1) {
        cout << "Local minimum found at position (" << row << ", " << col << ") ";
        cout << "with value " << matrix[row][col] << endl;
    } else {
        cout << "No local minimum found" << endl;
    }
  
    return 0;
}
```

## Time and Space Complexity

### 1D Local Minima Search:

- Time Complexity: O(log n)
- Space Complexity: O(1)

### 2D Local Minima Search:

- Time Complexity: O(m log n) where m is the number of rows and n is the number of columns
- Space Complexity: O(1)

## Related LeetCode Problems

1. **[162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)**

   - Very similar to the local minima problem, but searches for local maxima instead
   - Can use the same binary search approach, just with different conditions
2. **[852. Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/)**

   - Simpler version of the peak finding problem
   - Array is guaranteed to have a single peak (like a mountain)
3. **[1901. Find a Peak Element II](https://leetcode.com/problems/find-a-peak-element-ii/)**

   - 2D version of the peak finding problem
   - Similar to our 2D local minima search approach
4. **[153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)**

   - While not directly about local minima, it uses similar binary search techniques to find the global minimum in a rotated sorted array
   - The minimum element is also a local minimum in this case

## Notes and Tips

1. The binary search approach works because of a key guarantee: if an element is not a local minimum, then moving towards a smaller neighbor will eventually lead to a local minimum.
2. For the 2D version, other approaches include:

   - Divide-and-conquer: recursively dividing the matrix into quadrants
   - Row-by-row or column-by-column search: selecting a minimum element in a row/column, then checking its neighbors
3. These algorithms can be modified to find local maxima by inverting the comparison operators.
4. Be careful with boundary conditions, especially when handling the edges of arrays or matrices.
