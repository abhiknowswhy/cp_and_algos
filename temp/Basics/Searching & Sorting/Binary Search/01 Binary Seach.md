# Binary Search

## Definition
Binary Search is an efficient search algorithm that works on sorted arrays. It follows a divide-and-conquer approach by repeatedly dividing the search interval in half until the target value is found or the interval is empty.

## How Binary Search Works
1. Start with the middle element of the sorted array
2. If the target value equals the middle element, return the index
3. If the target value is less than the middle element, search in the left half
4. If the target value is greater than the middle element, search in the right half
5. Repeat steps 1-4 until the element is found or the subarray size becomes zero

## Time and Space Complexity
- **Time Complexity**: O(log n) - we divide the search space in half each time
- **Space Complexity**: O(1) for iterative approach, O(log n) for recursive approach due to call stack

## Prerequisites for Binary Search
- The array must be **sorted**
- Random access to elements is required (which arrays provide)

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Iterative Binary Search
int binarySearch(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right) {
        // Calculate middle index (avoids integer overflow)
        int mid = left + (right - left) / 2;
        
        // Check if target is present at mid
        if (nums[mid] == target)
            return mid;
        
        // If target is greater, ignore left half
        if (nums[mid] < target)
            left = mid + 1;
        // If target is smaller, ignore right half
        else
            right = mid - 1;
    }
    
    // Target not found
    return -1;
}

// Recursive Binary Search
int binarySearchRecursive(vector<int>& nums, int target, int left, int right) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        
        // If target is found at middle index
        if (nums[mid] == target)
            return mid;
        
        // If target is smaller than mid, search in left subarray
        if (nums[mid] > target)
            return binarySearchRecursive(nums, target, left, mid - 1);
        
        // Else search in right subarray
        return binarySearchRecursive(nums, target, mid + 1, right);
    }
    
    // Target not found
    return -1;
}

int main() {
    vector<int> arr = {2, 3, 4, 10, 40, 50, 70};
    int target = 10;
    
    // Using iterative binary search
    int iterResult = binarySearch(arr, target);
    if (iterResult != -1)
        cout << "Iterative Binary Search: Element found at index " << iterResult << endl;
    else
        cout << "Iterative Binary Search: Element not found" << endl;
    
    // Using recursive binary search
    int recResult = binarySearchRecursive(arr, target, 0, arr.size() - 1);
    if (recResult != -1)
        cout << "Recursive Binary Search: Element found at index " << recResult << endl;
    else
        cout << "Recursive Binary Search: Element not found" << endl;
    
    return 0;
}
```

## Common Uses
- Finding an element in a sorted array
- Implementing functions like lower_bound and upper_bound
- Solving problems that require finding a specific value efficiently
- As a building block for more complex algorithms

## Variations and Extensions
- Finding the first occurrence of an element
- Finding the last occurrence of an element
- Finding the floor and ceiling values
- Binary search on answer in optimization problems

## Notes
- Be careful with boundary conditions (left <= right vs left < right)
- To avoid integer overflow when calculating the middle index, use `mid = left + (right - left) / 2` instead of `(left + right) / 2`
- Binary search can be applied to many problems that don't explicitly involve sorted arrays (e.g., finding square root of a number)
