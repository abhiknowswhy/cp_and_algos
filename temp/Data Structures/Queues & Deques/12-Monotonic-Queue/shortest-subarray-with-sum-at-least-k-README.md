# Shortest Subarray with Sum at Least K

## Problem Description
Given an integer array `nums` and an integer `k`, return the length of the shortest non-empty **subarray** of `nums` with a sum of at least `k`. If there is no such **subarray**, return `-1`.

A **subarray** is a **contiguous** part of an array.

**LeetCode Link:** [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

## Approach
This problem requires finding the shortest subarray with sum ≥ k. Since the array can contain negative numbers, we cannot use a simple sliding window. We need to use a **Monotonic Deque** with prefix sums.

**Key Insight:** Use prefix sums and maintain a monotonic deque to efficiently find the shortest subarray ending at each position.

## Algorithm Steps
1. Calculate prefix sums
2. Use a deque to maintain indices in increasing order of prefix sums
3. For each position, remove indices from front where sum condition is satisfied
4. Remove indices from back that have larger prefix sums (they're not useful)
5. Add current index to deque
6. Track minimum length found

## Implementation

### C++ - Monotonic Deque
```cpp
#include <vector>
#include <deque>
#include <climits>
using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefixSum(n + 1, 0);
        
        // Calculate prefix sums
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }
        
        deque<int> dq; // Store indices
        int minLength = INT_MAX;
        
        for (int i = 0; i <= n; i++) {
            // Check if we can form a valid subarray
            while (!dq.empty() && prefixSum[i] - prefixSum[dq.front()] >= k) {
                minLength = min(minLength, i - dq.front());
                dq.pop_front();
            }
            
            // Maintain monotonic property (increasing prefix sums)
            while (!dq.empty() && prefixSum[i] <= prefixSum[dq.back()]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
        }
        
        return minLength == INT_MAX ? -1 : minLength;
    }
};
```

### Time Complexity
- **Monotonic Deque:** O(n) - Each element is added and removed at most once

### Space Complexity
- **Monotonic Deque:** O(n) - Prefix sum array and deque

## Examples

### Example 1
```
Input: nums = [1], k = 1
Output: 1
Explanation: The subarray [1] has sum 1 ≥ 1.
```

### Example 2
```
Input: nums = [1,2], k = 4
Output: -1
Explanation: No subarray has sum ≥ 4.
```

## Notes
- **Negative numbers:** Standard sliding window doesn't work due to negative elements
- **Prefix sums:** Convert to finding prefixSum[j] - prefixSum[i] ≥ k
- **Monotonic property:** Maintain deque with increasing prefix sums
- **Optimization:** Remove useless indices that can never give better results

## Related Problems
- [LeetCode 209: Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
- [LeetCode 239: Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

## Pattern: 12-Monotonic-Queue
This problem demonstrates **Monotonic Queue** pattern where:
- **Monotonic property:** Deque maintains indices in increasing order of prefix sums
- **Efficient removal:** Remove indices from front when they satisfy the condition
- **Pruning optimization:** Remove indices from back that are dominated by current index
- **Sliding window optimization:** Use deque to maintain optimal candidates efficiently
