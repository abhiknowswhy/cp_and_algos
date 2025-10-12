# Jump Game VI

## Pattern: Monotonic Queue

### Problem Statement
You are given a **0-indexed** integer array `nums` and an integer `k`.

You are initially standing at index `0`. In one move, you can jump at most `k` steps forward without going outside the boundaries of the array. That is, you can jump from index `i` to any index in the range `[i + 1, min(i + k, nums.length - 1)]`.

You want to reach the last index of the array (index `nums.length - 1`). Your **score** is the sum of all `nums[j]` for each index `j` you visited in the array.

Return the **maximum score** you can get.

**Constraints:**
- 1 ≤ nums.length, k ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

### Approach 1: DP + Monotonic Deque (Optimal)

This is a classic DP optimization problem. We need to maintain the maximum value in a sliding window of size k.

```python
from collections import deque

def maxResult(nums, k):
    """
    DP with monotonic deque optimization
    dp[i] = maximum score to reach index i
    dp[i] = nums[i] + max(dp[j]) for j in [max(0, i-k), i-1]
    """
    n = len(nums)
    dp = [float('-inf')] * n
    dp[0] = nums[0]
    
    # Monotonic deque to store (dp_value, index) in decreasing order
    dq = deque([(dp[0], 0)])
    
    for i in range(1, n):
        # Remove elements outside current window [i-k, i-1]
        while dq and dq[0][1] < i - k:
            dq.popleft()
        
        # Current position's maximum score
        dp[i] = nums[i] + dq[0][0]
        
        # Add current dp[i] to deque, maintaining monotonic property
        while dq and dq[-1][0] <= dp[i]:
            dq.pop()
        dq.append((dp[i], i))
    
    return dp[n - 1]
```

**Time Complexity:** O(n)
**Space Complexity:** O(n)
```python
# Implementation goes here
```

### Time Complexity
<!-- Add time complexity analysis -->

### Space Complexity
<!-- Add space complexity analysis -->

## Examples

### Example 1
```
Input: 
Output: 
Explanation: 
```

### Example 2
```
Input: 
Output: 
Explanation: 
```

## Notes
<!-- Add any additional notes, edge cases, or variations -->

## Related Problems
<!-- List related problems -->

## Pattern: 12-Monotonic-Queue
<!-- Explain how this problem fits the pattern -->
