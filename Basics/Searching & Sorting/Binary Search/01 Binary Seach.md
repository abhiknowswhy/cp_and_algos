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

---

# Interpolation Search

## Definition

Interpolation Search is an improved variant of binary search that works efficiently on uniformly distributed sorted arrays. Instead of always checking the middle element, it estimates the position of the target value based on its value and the values at the boundaries of the current search space.

## How Interpolation Search Works

1. Calculate the probable position of the target element using the formula:

   ```plaintext
   pos = left + ((target - arr[left]) * (right - left)) / (arr[right] - arr[left])
   ```

2. If the element at the calculated position matches the target, return the position
3. If the target is less than the element at the calculated position, search in the left subarray
4. If the target is greater than the element at the calculated position, search in the right subarray
5. Repeat until the element is found or the search space is exhausted

## Time and Space Complexity

- **Time Complexity**:
  - Average Case: O(log log n) when elements are uniformly distributed
  - Worst Case: O(n) when elements are not uniformly distributed
- **Space Complexity**: O(1) for iterative approach, O(log n) for recursive approach due to call stack

## Prerequisites for Interpolation Search

- The array must be **sorted**
- The array elements should be **uniformly distributed** for optimal performance
- Random access to elements is required

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Iterative Interpolation Search
int interpolationSearch(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    
    while (left <= right && target >= nums[left] && target <= nums[right]) {
        // If array has only one element
        if (left == right) {
            if (nums[left] == target)
                return left;
            return -1;
        }
        
        // Calculate the probable position using the formula
        int pos = left + ((double)(target - nums[left]) * (right - left)) / (nums[right] - nums[left]);
        
        // Target found
        if (nums[pos] == target)
            return pos;
        
        // If target is larger, it's in right subarray
        if (nums[pos] < target)
            left = pos + 1;
        // If target is smaller, it's in left subarray
        else
            right = pos - 1;
    }
    
    // Target not found
    return -1;
}

// Recursive Interpolation Search
int interpolationSearchRecursive(vector<int>& nums, int target, int left, int right) {
    // Base cases
    if (left <= right && target >= nums[left] && target <= nums[right]) {
        // Calculate position
        int pos = left + ((double)(target - nums[left]) * (right - left)) / (nums[right] - nums[left]);
        
        // Target found
        if (nums[pos] == target)
            return pos;
        
        // If target is larger, search in right subarray
        if (nums[pos] < target)
            return interpolationSearchRecursive(nums, target, pos + 1, right);
        
        // If target is smaller, search in left subarray
        return interpolationSearchRecursive(nums, target, left, pos - 1);
    }
    
    // Target not found
    return -1;
}

// Example usage
void testInterpolationSearch() {
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int target = 70;
    
    // Using iterative interpolation search
    int iterResult = interpolationSearch(arr, target);
    if (iterResult != -1)
        cout << "Iterative Interpolation Search: Element found at index " << iterResult << endl;
    else
        cout << "Iterative Interpolation Search: Element not found" << endl;
    
    // Using recursive interpolation search
    int recResult = interpolationSearchRecursive(arr, target, 0, arr.size() - 1);
    if (recResult != -1)
        cout << "Recursive Interpolation Search: Element found at index " << recResult << endl;
    else
        cout << "Recursive Interpolation Search: Element not found" << endl;
}
```

## Binary Search vs Interpolation Search

| Aspect | Binary Search | Interpolation Search |
|--------|---------------|---------------------|
| Time Complexity (Average) | O(log n) | O(log log n) for uniformly distributed data |
| Time Complexity (Worst) | O(log n) | O(n) |
| Space Complexity | O(1) or O(log n) | O(1) or O(log n) |
| Data Distribution | Works well with any distribution | Works best with uniform distribution |
| Reliability | Consistently efficient | Performance depends on data distribution |

## When to use Interpolation Search

- When the data is sorted and uniformly distributed
- When the dataset is large (the O(log log n) advantage becomes significant)
- When the cost of probing is high (reduces number of comparisons)

## When to use Binary Search instead

- When the data distribution is unknown or non-uniform
- When you need predictable worst-case performance
- When the array is small (binary search is simpler to implement)

## Related LeetCode Problems

### Binary Search Problems

1. [704. Binary Search](https://leetcode.com/problems/binary-search/) - Classic binary search implementation
2. [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/) - Find position where target should be inserted
3. [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) - Binary search in a rotated array
4. [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) - Find minimum element in a rotated array
5. [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/) - Find any peak element in an array
6. [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/) - Binary search in a 2D sorted matrix
7. [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/) - Compute the square root of an integer using binary search
8. [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) - Find range of target in sorted array

### Advanced Binary Search / Interpolation Search Applications

1. [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) - Binary search on answer
2. [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) - Binary search on answer
3. [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) - Hard problem using binary search principles
4. [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/) - Binary search with custom comparator
5. [1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/) - Binary search on answer

## Practice Tips

1. Identify if a problem can be solved with binary search (sorted data or monotonic function)
2. Pay attention to boundary conditions (when to use `left <= right` vs `left < right`)
3. Practice implementing both iterative and recursive versions
4. For interpolation search, test with different data distributions to understand its behavior
5. Learn to recognize problems where "binary search on answer" can be applied
6. Practice finding the first and last occurrences of an element
