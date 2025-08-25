# Bitonic Search

## What is a Bitonic Array?

A Bitonic array is an array that first increases and then decreases. In other words, it has a single peak element. For example:
```
[1, 3, 8, 12, 4, 2]
```
In this array, 12 is the peak element, with the array increasing up to 12 and decreasing afterward.

## Bitonic Search Algorithm

Searching in a bitonic array involves three key steps:
1. Find the peak element
2. Perform binary search on the increasing part (left of peak)
3. Perform binary search on the decreasing part (right of peak)

### Step 1: Finding the Peak Element

The peak element can be found using a modified binary search algorithm:

```cpp
int findPeak(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[mid + 1]) {
            // We are in the decreasing part
            right = mid;
        } else {
            // We are in the increasing part
            left = mid + 1;
        }
    }
    
    return left; // Peak index
}
```

### Step 2 & 3: Searching in Sorted Subarrays

Once we have the peak element, we can perform binary search on both sides:

## Complete Implementation

Here's a complete implementation of the Bitonic Search algorithm:

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Function to find the peak element in a bitonic array
int findPeak(const vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] > arr[mid + 1]) {
            // We are in the decreasing part
            right = mid;
        } else {
            // We are in the increasing part
            left = mid + 1;
        }
    }
    
    return left; // Peak index
}

// Binary search in ascending order part
int ascendingBinarySearch(const vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

// Binary search in descending order part
int descendingBinarySearch(const vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

// Bitonic search function
int bitonicSearch(const vector<int>& arr, int target) {
    if (arr.empty()) {
        return -1;
    }
    
    int peakIndex = findPeak(arr);
    
    // Check if the target is the peak element
    if (arr[peakIndex] == target) {
        return peakIndex;
    }
    
    // Search in the left (ascending) part
    int leftResult = ascendingBinarySearch(arr, 0, peakIndex - 1, target);
    if (leftResult != -1) {
        return leftResult;
    }
    
    // Search in the right (descending) part
    return descendingBinarySearch(arr, peakIndex + 1, arr.size() - 1, target);
}

// Example usage
int main() {
    vector<int> bitonicArray = {1, 3, 8, 12, 4, 2};
    int target = 4;
    
    int result = bitonicSearch(bitonicArray, target);
    
    if (result != -1) {
        cout << "Element " << target << " found at index " << result << endl;
    } else {
        cout << "Element " << target << " not found in the array" << endl;
    }
    
    return 0;
}
```

## Time and Space Complexity

- **Time Complexity**: O(log n) - We perform three binary search operations, each taking O(log n) time
- **Space Complexity**: O(1) - We use a constant amount of extra space

## Applications and Variations

1. **Finding in Rotated Bitonic Arrays**: In some cases, a bitonic array might be rotated. The search becomes more complex but follows similar principles.

2. **Finding the Bitonic Point in Unsorted Arrays**: Sometimes, the goal is to find the peak element itself, which can be done with the `findPeak` function.

3. **Finding Maximum/Minimum in Bitonic Arrays**: The maximum is always the peak element. The minimum would be either the first or last element.

## Related LeetCode Problems

1. **[LeetCode #162: Find Peak Element](https://leetcode.com/problems/find-peak-element/)**
   - This problem asks to find a peak element in an array where a peak element is greater than its neighbors.

2. **[LeetCode #852: Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/)**
   - Directly asks for the peak in a bitonic array (called a mountain array in the problem).

3. **[LeetCode #1095: Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/)**
   - This problem specifically asks to find an element in a mountain (bitonic) array with the minimum number of calls to the API.

4. **[LeetCode #153: Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)**
   - While not exactly a bitonic array, the concepts are related.

5. **[LeetCode #33: Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)**
   - Similar concepts apply when searching in a rotated sorted array.

6. **[LeetCode #81: Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)**
   - Similar concepts apply when searching in a rotated sorted array.

## Conclusion

Bitonic search is a powerful algorithm for searching in arrays with a specific pattern. By leveraging the properties of bitonic arrays (increasing then decreasing), we can achieve logarithmic search time even though the array is not entirely sorted in one direction.