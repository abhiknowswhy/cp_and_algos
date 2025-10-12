# In-Place Array Shuffling Algorithm

## Problem Statement

Given an array of the form `[a1, a2, a3, ..., an, b1, b2, b3, ..., bn]`, shuffle it in-place to get `[a1, b1, a2, b2, a3, b3, ..., an, bn]`.

## Algorithm Explanation

### Approach 1: Cyclic Replacement (Optimal Space)

The most efficient in-place solution uses cyclic replacement with O(1) extra space.

**Key Insights:**

1. For position `i` in the final array, we need to determine where the element should come from in the original array
2. Use mathematical mapping to find the correct source position
3. Handle cycles to ensure all elements are moved correctly

**Position Mapping:**

* For even indices (0, 2, 4, ...): Elements come from first half of array
* For odd indices (1, 3, 5, ...): Elements come from second half of array
* Original position for final position `i`:
  * If `i` is even: `i/2`
  * If `i` is odd: `n + (i-1)/2`

**Time Complexity:** O(n)

**Space Complexity:** O(1)

### Approach 2: Reverse and Rotate (Alternative)

Another in-place approach using array reversal and rotation techniques.

**Steps:**

1. Reverse segments of the array
2. Perform rotations to achieve the desired pattern
3. Repeat until the entire array is shuffled

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ShuffleArray {
public:
    // Approach 1: Cyclic Replacement - Most Efficient
    vector<int> shuffle_cyclic(vector<int>& nums) {
        int n = nums.size() / 2;
      
        for (int start = 1; start < n; start <<= 1) {
            int curr = start;
            int prev = nums[curr];
          
            do {
                int next = (curr < n) ? 2 * curr : 2 * (curr - n) + 1;
                swap(prev, nums[next]);
                curr = next;
            } while (curr != start);
        }
      
        return nums;
    }
  
    // Approach 2: Simple O(n) space solution for comparison
    vector<int> shuffle_simple(vector<int>& nums) {
        int n = nums.size() / 2;
        vector<int> result(nums.size());
      
        for (int i = 0; i < n; i++) {
            result[2 * i] = nums[i];         // a1, a2, a3, ...
            result[2 * i + 1] = nums[i + n]; // b1, b2, b3, ...
        }
      
        return result;
    }
  
    // Approach 3: In-place using reverse operations
    vector<int> shuffle_reverse(vector<int>& nums) {
        int n = nums.size() / 2;
      
        for (int i = 1; i < n; i++) {
            // Reverse the segment from i to n+i-1
            reverse(nums.begin() + i, nums.begin() + n + i);
            // Reverse the first part of that segment
            reverse(nums.begin() + i, nums.begin() + i + i);
            // Reverse the second part
            reverse(nums.begin() + i + i, nums.begin() + n + i);
        }
      
        return nums;
    }
  
    // Helper function to print array
    void printArray(const vector<int>& nums) {
        for (int num : nums) {
            cout << num << " ";
        }
        cout << endl;
    }
};

// Test function
int main() {
    ShuffleArray solution;
  
    // Test case 1: [1,2,3,4,5,6] -> [1,4,2,5,3,6]
    vector<int> nums1 = {1, 2, 3, 4, 5, 6};
    cout << "Original: ";
    solution.printArray(nums1);
  
    vector<int> result1 = solution.shuffle_simple(nums1);
    cout << "Simple shuffle: ";
    solution.printArray(result1);
  
    // Test case 2: [1,2,3,4,5,6,7,8] -> [1,5,2,6,3,7,4,8]
    vector<int> nums2 = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << "\nOriginal: ";
    solution.printArray(nums2);
  
    vector<int> result2 = solution.shuffle_simple(nums2);
    cout << "Simple shuffle: ";
    solution.printArray(result2);
  
    // Test case 3: Using cyclic approach
    vector<int> nums3 = {1, 2, 3, 4, 5, 6};
    cout << "\nOriginal: ";
    solution.printArray(nums3);
  
    vector<int> result3 = solution.shuffle_cyclic(nums3);
    cout << "Cyclic shuffle: ";
    solution.printArray(result3);
  
    return 0;
}
```

## LeetCode References

### Related Problems:

1. **[LeetCode 1470: Shuffle the Array](https://leetcode.com/problems/shuffle-the-array/)**
   * Exact same problem as described above
   * Difficulty: Easy
   * Tags: Array, Simulation
2. **[LeetCode 384: Shuffle an Array](https://leetcode.com/problems/shuffle-an-array/)**
   * Random shuffling of array elements
   * Difficulty: Medium
   * Tags: Array, Random, Algorithm
3. **[LeetCode 1007: Minimum Domino Rotations For Equal Row](https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/)**
   * Array manipulation and rotation concepts
   * Difficulty: Medium

### LeetCode 1470 Specific Solution:

```cpp
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> result(2 * n);
      
        for (int i = 0; i < n; i++) {
            result[2 * i] = nums[i];
            result[2 * i + 1] = nums[i + n];
        }
      
        return result;
    }
};
```

## Advanced In-Place Solution (True O(1) Space)

For a true in-place solution with O(1) extra space, we can use the following approach:

```cpp
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        // Encode two numbers in one using a base
        int base = 1001; // Since nums[i] <= 1000
      
        // First pass: encode
        for (int i = 0; i < n; i++) {
            int originalB = nums[i + n];
            nums[2 * i] = nums[2 * i] + (originalB * base);
            if (2 * i + 1 < 2 * n) {
                int originalA = nums[i] % base;
                nums[2 * i + 1] = nums[2 * i + 1] + (originalA * base);
            }
        }
      
        // Second pass: decode
        for (int i = 0; i < 2 * n; i++) {
            nums[i] = nums[i] / base;
        }
      
        return nums;
    }
};
```

## Performance Analysis

| Approach           | Time Complexity | Space Complexity | In-Place |
| ------------------ | --------------- | ---------------- | -------- |
| Simple             | O(n)            | O(n)             | No       |
| Cyclic Replacement | O(n)            | O(1)             | Yes      |
| Encoding Method    | O(n)            | O(1)             | Yes      |

## Key Takeaways

1. The simple approach is easiest to understand and implement
2. For true in-place solutions, consider encoding/decoding techniques
3. Cyclic replacement is mathematically elegant but complex to implement
4. Choose the approach based on space constraints and code clarity requirements
