# Sum of Minimum and Maximum Elements of All Subarrays

## Problem Description
Given an array `arr[]` of size `n`, find the sum of (minimum element + maximum element) of all possible subarrays of the given array.

**GeeksforGeeks Link:** [Sum of minimum and maximum elements of all subarrays](https://practice.geeksforgeeks.org/problems/sum-of-minimum-and-maximum-elements-of-all-subarrays-of-size-k3101/1)

**Variations:**
- Sum for all subarrays
- Sum for all subarrays of size K
- Sum for all subarrays of variable sizes

## Approach
This problem can be solved using **Monotonic Deques** to efficiently find minimum and maximum elements for each subarray. We maintain two deques - one for minimums (increasing order) and one for maximums (decreasing order).

**Key Insight:** For each ending position, calculate the contribution of minimum and maximum elements in all subarrays ending at that position.

## Algorithm Steps
1. Use two deques to maintain minimum and maximum candidates
2. For each element, extend all previous subarrays and start a new subarray
3. Update deques to maintain monotonic properties
4. Calculate sum contribution for current position
5. Add contributions to total sum

## Implementation

### C++ - All Subarrays
```cpp
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    long long sumOfMinMax(vector<int>& arr) {
        if (arr.empty()) return 0;
        
        int n = arr.size();
        long long totalSum = 0;
        
        // For each subarray arr[i...j]
        for (int i = 0; i < n; i++) {
            int minVal = arr[i], maxVal = arr[i];
            
            for (int j = i; j < n; j++) {
                minVal = min(minVal, arr[j]);
                maxVal = max(maxVal, arr[j]);
                totalSum += (minVal + maxVal);
            }
        }
        
        return totalSum;
    }
};
```

### C++ - Optimized using Monotonic Deques
```cpp
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    long long sumOfMinMaxOptimized(vector<int>& arr) {
        if (arr.empty()) return 0;
        
        int n = arr.size();
        long long totalSum = 0;
        
        // Calculate contribution of each element as minimum
        totalSum += sumOfMins(arr);
        
        // Calculate contribution of each element as maximum  
        totalSum += sumOfMaxs(arr);
        
        return totalSum;
    }
    
private:
    long long sumOfMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> left(n), right(n);
        deque<int> dq;
        
        // Find previous smaller element for each element
        for (int i = 0; i < n; i++) {
            while (!dq.empty() && arr[dq.back()] >= arr[i]) {
                dq.pop_back();
            }
            left[i] = dq.empty() ? -1 : dq.back();
            dq.push_back(i);
        }
        
        dq.clear();
        
        // Find next smaller element for each element
        for (int i = n - 1; i >= 0; i--) {
            while (!dq.empty() && arr[dq.back()] > arr[i]) {
                dq.pop_back();
            }
            right[i] = dq.empty() ? n : dq.back();
            dq.push_back(i);
        }
        
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            long long count = (long long)(i - left[i]) * (right[i] - i);
            sum += arr[i] * count;
        }
        
        return sum;
    }
    
    long long sumOfMaxs(vector<int>& arr) {
        int n = arr.size();
        vector<int> left(n), right(n);
        deque<int> dq;
        
        // Find previous larger element for each element
        for (int i = 0; i < n; i++) {
            while (!dq.empty() && arr[dq.back()] <= arr[i]) {
                dq.pop_back();
            }
            left[i] = dq.empty() ? -1 : dq.back();
            dq.push_back(i);
        }
        
        dq.clear();
        
        // Find next larger element for each element
        for (int i = n - 1; i >= 0; i--) {
            while (!dq.empty() && arr[dq.back()] < arr[i]) {
                dq.pop_back();
            }
            right[i] = dq.empty() ? n : dq.back();
            dq.push_back(i);
        }
        
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            long long count = (long long)(i - left[i]) * (right[i] - i);
            sum += arr[i] * count;
        }
        
        return sum;
    }
};
```

### C++ - Sliding Window of Size K
```cpp
class Solution {
public:
    long long sumOfMinMaxInWindowK(vector<int>& arr, int k) {
        if (arr.empty() || k == 0) return 0;
        
        int n = arr.size();
        if (k > n) return 0;
        
        deque<int> minDq, maxDq; // Store indices
        long long sum = 0;
        
        // Process first window
        for (int i = 0; i < k; i++) {
            // Maintain increasing order for minimum
            while (!minDq.empty() && arr[minDq.back()] >= arr[i]) {
                minDq.pop_back();
            }
            minDq.push_back(i);
            
            // Maintain decreasing order for maximum
            while (!maxDq.empty() && arr[maxDq.back()] <= arr[i]) {
                maxDq.pop_back();
            }
            maxDq.push_back(i);
        }
        
        // Add first window sum
        sum += arr[minDq.front()] + arr[maxDq.front()];
        
        // Process remaining windows
        for (int i = k; i < n; i++) {
            // Remove elements outside current window
            while (!minDq.empty() && minDq.front() <= i - k) {
                minDq.pop_front();
            }
            while (!maxDq.empty() && maxDq.front() <= i - k) {
                maxDq.pop_front();
            }
            
            // Add current element
            while (!minDq.empty() && arr[minDq.back()] >= arr[i]) {
                minDq.pop_back();
            }
            minDq.push_back(i);
            
            while (!maxDq.empty() && arr[maxDq.back()] <= arr[i]) {
                maxDq.pop_back();
            }
            maxDq.push_back(i);
            
            // Add current window sum
            sum += arr[minDq.front()] + arr[maxDq.front()];
        }
        
        return sum;
    }
};
```

### Time Complexity
- **Brute Force:** O(n²) - Check all subarrays
- **Optimized (All subarrays):** O(n) - Each element processed once in deque operations
- **Sliding Window (Size K):** O(n) - Each element added/removed once

### Space Complexity
- **All approaches:** O(n) - Deque space and auxiliary arrays

## Examples

### Example 1
```
Input: arr = [2, 5, -1, 7, -3, -1, -2]
Output: 63
Explanation: All subarrays and their min+max:
[2]: 2+2 = 4
[2,5]: 2+5 = 7
[2,5,-1]: -1+5 = 4
[2,5,-1,7]: -1+7 = 6
... (continue for all subarrays)
Total sum = 63
```

### Example 2 (Window size K=3)
```
Input: arr = [2, 5, -1, 7, -3], k = 3
Output: 14
Explanation: 
Window [2,5,-1]: min=-1, max=5, sum = 4
Window [5,-1,7]: min=-1, max=7, sum = 6  
Window [-1,7,-3]: min=-3, max=7, sum = 4
Total = 4 + 6 + 4 = 14
```

### Example 3
```
Input: arr = [1, 2, 3], k = 2
Output: 8
Explanation:
Window [1,2]: min=1, max=2, sum = 3
Window [2,3]: min=2, max=3, sum = 5
Total = 3 + 5 = 8
```

## Notes
- **Contribution technique:** Calculate how many subarrays each element contributes to as min/max
- **Monotonic deques:** Maintain order to quickly find min/max in sliding windows
- **Handle duplicates:** Be careful with equality conditions in deque maintenance
- **Edge cases:** Empty array, single element, all elements equal

## Related Problems
- [LeetCode 239: Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- [LeetCode 907: Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)
- [LeetCode 2104: Sum of Subarray Ranges](https://leetcode.com/problems/sum-of-subarray-ranges/)
- [GeeksforGeeks: Sliding Window Maximum](https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)

## Pattern: 05-Sliding-Window-with-Queue
This problem demonstrates **Sliding Window with Queue** pattern where:
- **Multiple deques:** Use separate deques for tracking minimums and maximums
- **Monotonic property:** Maintain increasing/decreasing order for efficient queries
- **Window operations:** Add/remove elements as window slides
- **Contribution calculation:** Count how many subarrays each element affects
