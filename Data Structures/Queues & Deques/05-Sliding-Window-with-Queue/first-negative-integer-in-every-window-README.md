# First Negative Integer in Every Window

## Problem Description
Given an array `arr[]` of size `N` and a positive integer `K`, find the first negative integer for each window of size `K`. If a window does not contain a negative integer, output `0` for that window.

**GeeksforGeeks Link:** [First negative integer in every window](https://practice.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1)

## Approach
This problem can be efficiently solved using a **Queue (Deque)** to store indices of negative integers. The queue helps us track negative integers in the current window and quickly identify the first one.

**Key Insight:** Use a queue to store indices of negative integers, and maintain the queue to only contain indices within the current window.

## Algorithm Steps
1. Use a deque to store indices of negative integers
2. Process first K elements and add negative indices to deque
3. For remaining elements:
   - Remove indices that are outside current window
   - Add current index if element is negative
   - Record first negative (front of deque) or 0 if deque is empty
4. Return the result array

## Implementation

### C++ - Deque Approach
```cpp
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    vector<int> firstNegativeInWindow(vector<int>& arr, int k) {
        if (arr.empty() || k == 0) return {};
        
        vector<int> result;
        deque<int> negIndices; // Store indices of negative numbers
        
        // Process first window
        for (int i = 0; i < k; i++) {
            if (arr[i] < 0) {
                negIndices.push_back(i);
            }
        }
        
        // First window result
        if (!negIndices.empty()) {
            result.push_back(arr[negIndices.front()]);
        } else {
            result.push_back(0);
        }
        
        // Process remaining windows
        for (int i = k; i < arr.size(); i++) {
            // Remove indices outside current window
            while (!negIndices.empty() && negIndices.front() <= i - k) {
                negIndices.pop_front();
            }
            
            // Add current index if negative
            if (arr[i] < 0) {
                negIndices.push_back(i);
            }
            
            // Add result for current window
            if (!negIndices.empty()) {
                result.push_back(arr[negIndices.front()]);
            } else {
                result.push_back(0);
            }
        }
        
        return result;
    }
};
```

### C++ - Two Pointer Approach
```cpp
class Solution {
public:
    vector<int> firstNegativeInWindow(vector<int>& arr, int k) {
        if (arr.empty() || k == 0) return {};
        
        vector<int> result;
        int left = 0, right = 0;
        int firstNegIndex = -1;
        
        while (right < arr.size()) {
            // Expand window
            if (arr[right] < 0 && firstNegIndex == -1) {
                firstNegIndex = right;
            }
            
            // If window size is k
            if (right - left + 1 == k) {
                // Add first negative or 0
                if (firstNegIndex != -1 && firstNegIndex >= left) {
                    result.push_back(arr[firstNegIndex]);
                } else {
                    result.push_back(0);
                }
                
                // Contract window
                if (firstNegIndex == left) {
                    // Find next negative in remaining window
                    firstNegIndex = -1;
                    for (int i = left + 1; i <= right; i++) {
                        if (arr[i] < 0) {
                            firstNegIndex = i;
                            break;
                        }
                    }
                }
                left++;
            }
            right++;
        }
        
        return result;
    }
};
```

### C++ - Brute Force (for comparison)
```cpp
class Solution {
public:
    vector<int> firstNegativeInWindow(vector<int>& arr, int k) {
        if (arr.empty() || k == 0) return {};
        
        vector<int> result;
        
        for (int i = 0; i <= arr.size() - k; i++) {
            int firstNeg = 0;
            for (int j = i; j < i + k; j++) {
                if (arr[j] < 0) {
                    firstNeg = arr[j];
                    break;
                }
            }
            result.push_back(firstNeg);
        }
        
        return result;
    }
};
```

### Time Complexity
- **Deque Approach:** O(n) - Each element is added and removed at most once
- **Two Pointer:** O(n × k) in worst case - May need to scan window for next negative
- **Brute Force:** O((n-k+1) × k) = O(nk)

### Space Complexity
- **Deque Approach:** O(k) - Queue stores at most k indices
- **Two Pointer:** O(1) - Only using pointers
- **Brute Force:** O(1) - Only result space

## Examples

### Example 1
```
Input: arr = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
Output: [-1, -1, -7, -15, -15, 0]
Explanation:
Window [12, -1, -7] -> first negative = -1
Window [-1, -7, 8] -> first negative = -1
Window [-7, 8, -15] -> first negative = -7
Window [8, -15, 30] -> first negative = -15
Window [-15, 30, 16] -> first negative = -15
Window [30, 16, 28] -> first negative = 0 (no negative)
```

### Example 2
```
Input: arr = [-8, 2, 3, -6, 10], k = 2
Output: [-8, 0, -6, -6]
Explanation:
Window [-8, 2] -> first negative = -8
Window [2, 3] -> first negative = 0 (no negative)
Window [3, -6] -> first negative = -6
Window [-6, 10] -> first negative = -6
```

### Example 3
```
Input: arr = [1, 2, 3, 4, 5], k = 3
Output: [0, 0, 0]
Explanation: No negative numbers in any window
```

## Notes
- **Efficient tracking:** Deque maintains only relevant negative indices
- **Window boundary:** Remove indices outside current window from front
- **First occurrence:** Queue front always contains the first negative in window
- **Edge cases:** No negatives, all negatives, k = 1, k = array length

## Related Problems
- [LeetCode 239: Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- [GeeksforGeeks: Sliding Window Maximum](https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)
- [LeetCode 862: Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

## Pattern: 05-Sliding-Window-with-Queue
This problem exemplifies **Sliding Window with Queue** pattern where:
- **Fixed window size:** Window of size K slides through array
- **Queue for tracking:** Deque efficiently tracks relevant elements (negative numbers)
- **Window maintenance:** Remove elements outside current window
- **Efficient queries:** O(1) access to first negative in current window
