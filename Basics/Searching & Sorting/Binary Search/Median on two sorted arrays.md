# Median of Two Sorted Arrays & Kth Element

## Problem Definition

### Median of Two Sorted Arrays

Given two sorted arrays `nums1` and `nums2` of sizes `m` and `n` respectively, find the median of the merged array without actually merging them.

The overall run time complexity should be O(log(m+n)).

### Kth Element in Two Sorted Arrays

Given two sorted arrays `nums1` and `nums2` of sizes `m` and `n` respectively, find the kth smallest element in the union of these two arrays.

## Algorithm Approach

Both problems can be solved using a binary search approach. The key insight is to find the right partition points in both arrays that divide them in such a way that:

1. All elements to the left of the partition points are smaller than or equal to all elements to the right
2. The total number of elements to the left equals the desired position (median position or k)

### Intuition for the Solution

1. Instead of merging the arrays, we find the correct partition by performing a binary search on the smaller array to minimize operations
2. For each partition point in the first array, we can calculate the corresponding partition point in the second array
3. We check if the partition is valid by comparing the maximum element on the left side with the minimum element on the right side
4. If the partition is valid, we've found our solution; otherwise, we adjust the partition

## Implementation for Median of Two Sorted Arrays

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Ensure nums1 is the smaller array for efficiency
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int x = nums1.size();
    int y = nums2.size();
    
    int low = 0;
    int high = x;
    
    while (low <= high) {
        // Partition point for smaller array (nums1)
        int partitionX = (low + high) / 2;
        
        // Partition point for larger array (nums2)
        // We ensure that: partitionX + partitionY = (x + y + 1) / 2
        int partitionY = (x + y + 1) / 2 - partitionX;
        
        // Edge cases: if partition is at the beginning or end of array
        int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        
        int minX = (partitionX == x) ? INT_MAX : nums1[partitionX];
        int minY = (partitionY == y) ? INT_MAX : nums2[partitionY];
        
        // Check if we found the correct partition
        if (maxX <= minY && maxY <= minX) {
            // Even total length
            if ((x + y) % 2 == 0) {
                return (max(maxX, maxY) + min(minX, minY)) / 2.0;
            } 
            // Odd total length
            else {
                return max(maxX, maxY);
            }
        } 
        // If maxX is too large, move partition to the left
        else if (maxX > minY) {
            high = partitionX - 1;
        } 
        // If maxY is too large, move partition to the right
        else {
            low = partitionX + 1;
        }
    }
    
    // Should not reach here for valid inputs
    return 0.0;
}

int main() {
    // Example 1
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Median is: " << findMedianSortedArrays(nums1, nums2) << endl;  // Expected output: 2.0
    
    // Example 2
    vector<int> nums3 = {1, 2};
    vector<int> nums4 = {3, 4};
    cout << "Median is: " << findMedianSortedArrays(nums3, nums4) << endl;  // Expected output: 2.5
    
    // Example 3
    vector<int> nums5 = {0, 0};
    vector<int> nums6 = {0, 0};
    cout << "Median is: " << findMedianSortedArrays(nums5, nums6) << endl;  // Expected output: 0.0
    
    // Example 4
    vector<int> nums7 = {};
    vector<int> nums8 = {1};
    cout << "Median is: " << findMedianSortedArrays(nums7, nums8) << endl;  // Expected output: 1.0
    
    return 0;
}
```

## Implementation for Kth Element in Two Sorted Arrays

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to find the kth element in two sorted arrays
int findKthElement(vector<int>& nums1, vector<int>& nums2, int k) {
    // Ensure nums1 is the smaller array for efficiency
    if (nums1.size() > nums2.size()) {
        return findKthElement(nums2, nums1, k);
    }
    
    int n1 = nums1.size();
    int n2 = nums2.size();
    
    // Handle edge cases
    if (n1 == 0) {
        return nums2[k-1];
    }
    
    if (k == 1) {
        return min(nums1[0], nums2[0]);
    }
    
    // Binary search
    int i = min(n1, k/2);
    int j = min(n2, k/2);
    
    if (nums1[i-1] > nums2[j-1]) {
        // Discard j smallest elements from nums2
        vector<int> newNums2(nums2.begin() + j, nums2.end());
        return findKthElement(nums1, newNums2, k - j);
    } else {
        // Discard i smallest elements from nums1
        vector<int> newNums1(nums1.begin() + i, nums1.end());
        return findKthElement(newNums1, nums2, k - i);
    }
}

// Iterative version of the algorithm for better efficiency
int findKthElementIterative(vector<int>& nums1, vector<int>& nums2, int k) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    
    // Ensure nums1 is the smaller array
    if (n1 > n2) {
        return findKthElementIterative(nums2, nums1, k);
    }
    
    // Handle edge cases
    if (n1 == 0) {
        return nums2[k-1];
    }
    
    if (k == 1) {
        return min(nums1[0], nums2[0]);
    }
    
    int left = max(0, k - n2);  // We must take at least k-n2 elements from nums1
    int right = min(k, n1);     // We can take at most k elements from nums1
    
    while (left <= right) {
        int mid1 = (left + right) / 2;  // Number of elements taken from nums1
        int mid2 = k - mid1;            // Number of elements taken from nums2
        
        // Calculate values at the partition
        int maxLeft1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
        int minRight1 = (mid1 == n1) ? INT_MAX : nums1[mid1];
        
        int maxLeft2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
        int minRight2 = (mid2 == n2) ? INT_MAX : nums2[mid2];
        
        // Check if we found the correct partition
        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            // Found the partition
            // The kth element would be the maximum of maxLeft1 and maxLeft2
            return max(maxLeft1, maxLeft2);
        }
        else if (maxLeft1 > minRight2) {
            // Take fewer elements from nums1
            right = mid1 - 1;
        }
        else {
            // Take more elements from nums1
            left = mid1 + 1;
        }
    }
    
    // Should not reach here for valid inputs
    return -1;
}

int main() {
    // Example 1
    vector<int> nums1 = {2, 3, 6, 7, 9};
    vector<int> nums2 = {1, 4, 8, 10};
    int k = 5;
    cout << "The " << k << "th element is: " << findKthElementIterative(nums1, nums2, k) << endl;  // Expected: 6
    
    // Example 2
    vector<int> nums3 = {1, 3, 5, 7, 9};
    vector<int> nums4 = {2, 4, 6, 8, 10};
    k = 6;
    cout << "The " << k << "th element is: " << findKthElementIterative(nums3, nums4, k) << endl;  // Expected: 6
    
    // Example 3
    vector<int> nums5 = {1, 2, 3, 4, 5};
    vector<int> nums6 = {6, 7, 8, 9, 10};
    k = 7;
    cout << "The " << k << "th element is: " << findKthElementIterative(nums5, nums6, k) << endl;  // Expected: 7
    
    return 0;
}
```

## Time and Space Complexity

For both problems:
- **Time Complexity**: O(log(min(m,n))) where m and n are the sizes of the two arrays
- **Space Complexity**: O(1) for the iterative solution, O(log(min(m,n))) for the recursive solution due to the call stack

## Related LeetCode Problems

1. **[4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)**
   - Exactly the first problem we solved
   - Hard difficulty
   - The problem constraints include finding a solution with O(log(m+n)) time complexity

2. **[Kth Smallest Element in Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)** 
   - While not a direct LeetCode problem, this is a generalization of the median problem
   - The median is actually just the (n+m+1)/2 th smallest element for odd total length
   - Can be solved with the same approach

3. **[378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)**
   - Related problem with a different setup (matrix instead of two arrays)
   - Uses binary search in a slightly different way

4. **[668. Kth Smallest Number in Multiplication Table](https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/)**
   - Similar binary search approach but in an implicit multiplication table

5. **[719. Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)**
   - Uses binary search for finding the kth smallest pair distance

## Notes and Tips

1. **Handling Edge Cases**: Always check edge cases like empty arrays, arrays of different sizes, and k values at the extremes.

2. **Binary Search Invariants**: Be careful with the binary search conditions and make sure your invariants are maintained.

3. **Optimization**: Always perform the binary search on the smaller array to minimize operations.

4. **Partition Placement**: The key to both problems is finding the correct partition point that satisfies all conditions.

5. **Interview Tips**: This is a common hard-level interview question. Be prepared to explain the intuition behind your solution and why the time complexity is logarithmic.

6. **Generalization**: The median-finding algorithm can be easily generalized to find any kth element:
   - For odd total length arrays, median is the ((n+m+1)/2)th element
   - For even total length arrays, median is the average of ((n+m)/2)th and ((n+m)/2+1)th elements