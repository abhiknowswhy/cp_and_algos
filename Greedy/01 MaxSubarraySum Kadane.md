# Kadane's Algorithm - Maximum Subarray Sum

## Problem Description

Given an array of integers, find the contiguous subarray with the largest sum.

## Explanation

Kadane's algorithm is an efficient algorithm for finding the maximum sum subarray in a one-dimensional array. It uses dynamic programming to solve the problem with O(n) time complexity.

### Key Insight

The key insight in Kadane's algorithm is to recognize that:
- At each position, we have two choices:
  1. Start a new subarray beginning at the current element
  2. Extend the previous subarray by including the current element
- We choose whichever gives us a larger sum at each step

### How It Works

1. Initialize two variables:
   - `current_sum` to track the maximum sum ending at the current position
   - `max_sum` to track the maximum sum found so far
   
2. Iterate through the array:
   - For each element, update `current_sum` to be the maximum of:
     - The current element (starting a new subarray)
     - The current element plus the previous `current_sum` (extending the previous subarray)
   - Update `max_sum` if the new `current_sum` is larger

3. At the end, `max_sum` contains the maximum subarray sum

## Implementation (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSubarraySum(const vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int current_sum = nums[0];
    int max_sum = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        // Either start a new subarray or extend the existing one
        current_sum = max(nums[i], current_sum + nums[i]);
        // Update the maximum sum found so far
        max_sum = max(max_sum, current_sum);
    }
    
    return max_sum;
}

// Driver code for testing
int main() {
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum subarray sum is: " << maxSubarraySum(arr) << endl;
    // Expected output: 6 (from subarray [4, -1, 2, 1])
    
    return 0;
}
```

## Time and Space Complexity

- **Time Complexity**: O(n) - a single pass through the array
- **Space Complexity**: O(1) - only using a constant amount of extra space

## Handling Edge Cases

- **All Negative Numbers**: The algorithm correctly returns the largest (least negative) element
- **Empty Array**: The implementation above returns 0 for an empty array

## Extensions

1. **Finding the Subarray**: We can modify the algorithm to track start and end indices of the maximum subarray
2. **Circular Array**: To find the maximum subarray sum in a circular array, we need to consider both the standard case and the "wraparound" case

### Kadane's Algorithm for Circular Arrays

For circular arrays, the maximum subarray sum can be either:
1. The maximum subarray sum without wrapping around (standard Kadane's algorithm)
2. The total sum of the array minus the minimum subarray sum (this represents the "wraparound" case)

Here's the C++ implementation for finding the maximum subarray sum in a circular array:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int maxSubarraySumCircular(const vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int current_max = nums[0];
    int max_sum = nums[0];
    int current_min = nums[0];
    int min_sum = nums[0];
    int total_sum = nums[0];
    
    // Start from the second element (if it exists)
    for (int i = 1; i < nums.size(); i++) {
        // Update total sum
        total_sum += nums[i];
        
        // Kadane's algorithm for maximum subarray sum
        current_max = max(nums[i], current_max + nums[i]);
        max_sum = max(max_sum, current_max);
        
        // Kadane's algorithm for minimum subarray sum
        current_min = min(nums[i], current_min + nums[i]);
        min_sum = min(min_sum, current_min);
    }
    
    // If all elements are negative, max_sum will have the largest (least negative) element
    // In that case, the "wraparound" case doesn't apply
    if (max_sum < 0) return max_sum;
    
    // The maximum circular subarray sum is the maximum of:
    // 1. The maximum subarray sum without wrapping (max_sum)
    // 2. The total sum minus the minimum subarray sum (represents the "wraparound" case)
    return max(max_sum, total_sum - min_sum);
}

// Driver code for testing
int main() {
    vector<int> arr = {8, -1, 3, 4};
    cout << "Maximum circular subarray sum is: " << maxSubarraySumCircular(arr) << endl;
    // Expected output: 15 (from subarray [4, 8, -1, 3] with wraparound)
    
    vector<int> arr2 = {-3, -2, -1};
    cout << "Maximum circular subarray sum with all negatives: " << maxSubarraySumCircular(arr2) << endl;
    // Expected output: -1 (single element, no wraparound)
    
    return 0;
}
```

#### Key Points for Circular Array Version:

1. We run two versions of Kadane's algorithm simultaneously:
   - One to find the maximum subarray sum (standard case)
   - One to find the minimum subarray sum (to help calculate the wraparound case)

2. The maximum circular subarray sum is the maximum of:
   - The standard maximum subarray sum (no wraparound)
   - The total sum of the array minus the minimum subarray sum (wraparound)

3. Special case: If all elements are negative, the result is simply the maximum element (represented by max_sum).

This algorithm also maintains O(n) time complexity and O(1) space complexity.

## Related LeetCode Problems

1. [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) - Direct application of Kadane's algorithm
2. [918. Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) - Extension of Kadane's algorithm for circular arrays
3. [1186. Maximum Subarray Sum with One Deletion](https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/) - Variation where you can delete one element
4. [1749. Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/) - Finding maximum absolute sum using Kadane's concept
5. [1191. K-Concatenation Maximum Sum](https://leetcode.com/problems/k-concatenation-maximum-sum/) - Using Kadane's with repetitions

## Interview Tips

- Make sure to understand the algorithm's handling of all-negative arrays
- Practice implementing the variation that also returns the subarray itself
- Be prepared to explain the greedy aspect of the algorithm and how it achieves linear time complexity
- Consider edge cases: empty array, single element array, all negative elements

## References

- Bentley, J. (1984). "Programming Pearls: Algorithm Design Techniques"
- Introduction to Algorithms (CLRS) - Dynamic Programming chapter
