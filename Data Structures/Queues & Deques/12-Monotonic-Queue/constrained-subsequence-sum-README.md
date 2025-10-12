# Constrained Subsequence Sum

## Problem Description
Given an integer array `nums` and an integer `k`, return the maximum sum of a **non-empty** subsequence of that array such that for every two **consecutive** integers in the subsequence, `nums[i]` and `nums[j]`, where `i < j`, the condition `j - i <= k` is satisfied.

A **subsequence** of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.

**Constraints:**
- 1 ≤ k ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

**LeetCode Link**: [1425. Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)

## Approach
This problem can be approached using Dynamic Programming (DP) with a sliding window maximum optimization, which can be efficiently implemented using a Monotonic Queue (Deque). The main idea is to maintain a DP array where `dp[i]` represents the maximum sum of a subsequence ending at index `i`. We then use a deque to keep track of the indices of the `dp` array, in a way that allows us to quickly retrieve the maximum value of `dp[j]` for `j` in the range `[i-k, i-1]`. This way, we can compute each `dp[i]` in constant time, leading to an overall time complexity of O(n).

### Monotonic Queue (Deque) Explanation
A Monotonic Queue is a double-ended queue that maintains its elements in a specific order (monotonicity). In this problem, we maintain the deque in a decreasing order of `dp` values. This allows us to efficiently get the maximum `dp` value for the current index while also ensuring that we can remove indices that are out of the current window of consideration (`[i-k, i-1]`).

## Algorithm Steps
1. Initialize a DP array of the same length as `nums`, and a deque for maintaining indices.
2. Iterate over each element in `nums`:
   - Remove indices from the front of the deque if they are out of the current window `[i-k, i-1]`.
   - Compute `dp[i]` as the maximum of `nums[i]` and `nums[i]` plus the `dp` value of the index at the front of the deque (if the deque is not empty).
   - Update the maximum sum found so far.
   - Maintain the monotonicity of the deque by removing indices from the back of the deque while the `dp` value at those indices is less than or equal to `dp[i]`.
   - Add the current index `i` to the deque.
3. The result is the maximum sum found.

## Implementation

### Python
```python
from collections import deque

def constrainedSubsetSum(nums, k):
    """
    Python implementation using monotonic deque
    """
    n = len(nums)
    dp = [0] * n
    dq = deque()  # Store indices
    
    max_sum = nums[0]
    
    for i in range(n):
        # Remove expired elements
        while dq and dq[0] < i - k:
            dq.popleft()
        
        # Calculate dp[i]
        dp[i] = nums[i]
        if dq:
            dp[i] = max(dp[i], nums[i] + dp[dq[0]])
        
        max_sum = max(max_sum, dp[i])
        
        # Maintain monotonic property and add current
        if dp[i] > 0:
            while dq and dp[dq[-1]] <= dp[i]:
                dq.pop()
            dq.append(i)
    
    return max_sum
```

### C++
```cpp
#include <vector>
#include <deque>
#include <algorithm>

class Solution {
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> dp(n);
        std::deque<int> dq; // Monotonic deque storing indices
        
        int maxSum = nums[0];
        
        for (int i = 0; i < n; i++) {
            // Remove elements outside window [i-k, i-1]
            while (!dq.empty() && dq.front() < i - k) {
                dq.pop_front();
            }
            
            // dp[i] = nums[i] + max(0, max(dp[j])) for j in [i-k, i-1]
            dp[i] = nums[i];
            if (!dq.empty()) {
                dp[i] = std::max(dp[i], nums[i] + dp[dq.front()]);
            }
            
            maxSum = std::max(maxSum, dp[i]);
            
            // Maintain monotonic decreasing property
            while (!dq.empty() && dp[dq.back()] <= dp[i]) {
                dq.pop_back();
            }
            
            // Only add if dp[i] > 0 (positive contribution)
            if (dp[i] > 0) {
                dq.push_back(i);
            }
        }
        
        return maxSum;
    }
};
```

### Time Complexity
O(n) - We process each element once, and each element is added and removed from the deque at most once.

### Space Complexity
O(n) - We use a deque and a DP array, both of which can grow to the size of the input array in the worst case.

## Examples

### Example 1
```
Input: nums = [10, 2, -10, 5, 20], k = 2
Output: 37
Explanation: The subsequence [10, 2, 5, 20] has the maximum sum with the given constraints.
```

### Example 2
```
Input: nums = [-1, -2, -3], k = 1
Output: -1
Explanation: The maximum sum is -1, taken by the subsequence [-1].
```

## Notes
- This problem can be solved using various approaches, including Segment Trees, Priority Queues, and Recursive DP with Memoization. However, the Monotonic Queue approach is the most efficient in terms of time complexity for this problem.
- Care must be taken to handle the constraints correctly, especially the condition `j - i <= k`.

## Related Problems
- **[LeetCode 1425 - Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)** - This problem
- **[LeetCode 239 - Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)** - Core pattern
- **[LeetCode 1696 - Jump Game VI](https://leetcode.com/problems/jump-game-vi/)** - Similar DP optimization  
- **[LeetCode 862 - Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)** - Monotonic deque
- **[LeetCode 1499 - Max Value of Equation](https://leetcode.com/problems/max-value-of-equation/)** - Sliding window maximum
- **[LeetCode 368 - Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)** - DP with constraints

## Pattern: Monotonic Queue

### Problem Statement
Given an integer array `nums` and an integer `k`, return the maximum sum of a **non-empty** subsequence of that array such that for every two **consecutive** integers in the subsequence, `nums[i]` and `nums[j]`, where `i < j`, the condition `j - i <= k` is satisfied.

A **subsequence** of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.

**Constraints:**
- 1 ≤ k ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4

**LeetCode Link**: [1425. Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)

### Approach 1: DP + Monotonic Deque (Optimal)

This problem is a classic DP optimization using monotonic deque to maintain sliding window maximum.

```cpp
#include <vector>
#include <deque>
#include <algorithm>

class Solution {
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> dp(n);
        std::deque<int> dq; // Monotonic deque storing indices
        
        int maxSum = nums[0];
        
        for (int i = 0; i < n; i++) {
            // Remove elements outside window [i-k, i-1]
            while (!dq.empty() && dq.front() < i - k) {
                dq.pop_front();
            }
            
            // dp[i] = nums[i] + max(0, max(dp[j])) for j in [i-k, i-1]
            dp[i] = nums[i];
            if (!dq.empty()) {
                dp[i] = std::max(dp[i], nums[i] + dp[dq.front()]);
            }
            
            maxSum = std::max(maxSum, dp[i]);
            
            // Maintain monotonic decreasing property
            while (!dq.empty() && dp[dq.back()] <= dp[i]) {
                dq.pop_back();
            }
            
            // Only add if dp[i] > 0 (positive contribution)
            if (dp[i] > 0) {
                dq.push_back(i);
            }
        }
        
        return maxSum;
    }
};
```

**Time Complexity:** O(n)  
**Space Complexity:** O(n)

### Approach 2: Space-Optimized DP

Since we only need previous k elements, we can optimize space:

```cpp
class Solution {
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::deque<std::pair<int, int>> dq; // {value, index}
        
        int maxSum = nums[0];
        dq.push_back({nums[0], 0});
        
        for (int i = 1; i < n; i++) {
            // Remove elements outside window
            while (!dq.empty() && dq.front().second < i - k) {
                dq.pop_front();
            }
            
            // Current maximum sum ending at i
            int currentMax = nums[i];
            if (!dq.empty()) {
                currentMax = std::max(currentMax, nums[i] + dq.front().first);
            }
            
            maxSum = std::max(maxSum, currentMax);
            
            // Add to deque if positive
            if (currentMax > 0) {
                // Maintain monotonic decreasing property
                while (!dq.empty() && dq.back().first <= currentMax) {
                    dq.pop_back();
                }
                dq.push_back({currentMax, i});
            }
        }
        
        return maxSum;
    }
};
```

### Approach 3: Segment Tree with Lazy Propagation

For more complex queries or updates:

```cpp
class SegmentTree {
private:
    std::vector<int> tree;
    int n;
    
    void build(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = std::max(tree[2*node], tree[2*node+1]);
        }
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2*node, start, mid, idx, val);
            } else {
                update(2*node+1, mid+1, end, idx, val);
            }
            tree[node] = std::max(tree[2*node], tree[2*node+1]);
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return INT_MIN;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2*node, start, mid, l, r);
        int p2 = query(2*node+1, mid+1, end, l, r);
        return std::max(p1, p2);
    }
    
public:
    SegmentTree(int size) : n(size) {
        tree.resize(4 * n, INT_MIN);
    }
    
    void build(const std::vector<int>& arr) {
        build(arr, 1, 0, n-1);
    }
    
    void update(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }
    
    int query(int l, int r) {
        if (l > r) return INT_MIN;
        return query(1, 0, n-1, l, r);
    }
};

class SolutionSegTree {
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k) {
        int n = nums.size();
        SegmentTree st(n);
        
        std::vector<int> dp(n);
        dp[0] = nums[0];
        st.update(0, dp[0]);
        
        int maxSum = dp[0];
        
        for (int i = 1; i < n; i++) {
            int maxPrev = st.query(std::max(0, i-k), i-1);
            dp[i] = nums[i] + std::max(0, maxPrev);
            maxSum = std::max(maxSum, dp[i]);
            st.update(i, dp[i]);
        }
        
        return maxSum;
    }
};
```

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

### Approach 4: Priority Queue (Less Efficient)

Using max heap with lazy deletion:

```cpp
#include <queue>

class SolutionPQ {
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<int> dp(n);
        
        // Max heap: {value, index}
        std::priority_queue<std::pair<int, int>> pq;
        
        dp[0] = nums[0];
        pq.push({dp[0], 0});
        
        int maxSum = dp[0];
        
        for (int i = 1; i < n; i++) {
            // Remove elements outside window
            while (!pq.empty() && pq.top().second < i - k) {
                pq.pop();
            }
            
            dp[i] = nums[i];
            if (!pq.empty()) {
                dp[i] = std::max(dp[i], nums[i] + pq.top().first);
            }
            
            maxSum = std::max(maxSum, dp[i]);
            
            if (dp[i] > 0) {
                pq.push({dp[i], i});
            }
        }
        
        return maxSum;
    }
};
```

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

### Approach 5: Recursive DP with Memoization

Top-down approach for better understanding:

```cpp
#include <unordered_map>

class SolutionRecursive {
private:
    std::unordered_map<int, int> memo;
    std::vector<int> nums;
    int k;
    
    int dp(int i) {
        if (i < 0) return 0;
        if (memo.count(i)) return memo[i];
        
        int result = nums[i]; // Include current element
        int maxPrev = 0;
        
        // Check all valid previous positions
        for (int j = std::max(0, i - k); j < i; j++) {
            maxPrev = std::max(maxPrev, dp(j));
        }
        
        result += maxPrev;
        return memo[i] = result;
    }
    
public:
    int constrainedSubsetSum(std::vector<int>& nums, int k) {
        this->nums = nums;
        this->k = k;
        
        int maxSum = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            maxSum = std::max(maxSum, dp(i));
        }
        
        return maxSum;
    }
};
```

### Example Usage and Testing

```cpp
#include <iostream>
#include <vector>

void testConstrainedSubsetSum() {
    Solution sol;
    
    // Test Case 1
    std::vector<int> nums1 = {10, 2, -10, 5, 20};
    int k1 = 2;
    std::cout << "Test 1: " << sol.constrainedSubsetSum(nums1, k1) << std::endl;
    // Expected: 37 (10 + 2 + 5 + 20)
    
    // Test Case 2
    std::vector<int> nums2 = {-1, -2, -3};
    int k2 = 1;
    std::cout << "Test 2: " << sol.constrainedSubsetSum(nums2, k2) << std::endl;
    // Expected: -1
    
    // Test Case 3
    std::vector<int> nums3 = {10, -2, -10, -5, 20};
    int k3 = 2;
    std::cout << "Test 3: " << sol.constrainedSubsetSum(nums3, k3) << std::endl;
    // Expected: 23 (10 + 20, can skip -2, -10, -5)
}

int main() {
    testConstrainedSubsetSum();
    return 0;
}
```

### Performance Analysis

```cpp
#include <chrono>
#include <random>

void benchmark() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100, 100);
    
    std::vector<int> nums(10000);
    for (int& num : nums) {
        num = dis(gen);
    }
    
    Solution sol;
    
    auto start = std::chrono::high_resolution_clock::now();
    int result = sol.constrainedSubsetSum(nums, 100);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Monotonic Deque: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Result: " << result << std::endl;
}
```

### Pattern Analysis: DP + Sliding Window Maximum

This problem exemplifies the **DP optimization with sliding window maximum** pattern:

1. **State Definition**: `dp[i]` = maximum sum of subsequence ending at index i
2. **Transition**: `dp[i] = nums[i] + max(0, max(dp[j]))` for valid j
3. **Constraint**: j must be in range `[i-k, i-1]` 
4. **Optimization**: Use monotonic deque for O(1) range maximum queries

### Key Insights

1. **Only Positive DP Values Matter**: Negative sums don't contribute to future solutions
2. **Monotonic Property**: Maintain decreasing order in deque for maximum tracking
3. **Window Management**: Efficiently remove expired elements
4. **Space-Time Tradeoff**: Can optimize space but at cost of code complexity

### Common Mistakes

1. **Including Negative Values**: Don't add elements with negative DP values to deque
2. **Window Boundaries**: Correctly handle the constraint `j - i <= k`
3. **Edge Cases**: Single element arrays, all negative numbers
4. **Index Management**: Off-by-one errors in window calculation

### Related LeetCode Problems

1. **[LeetCode 1425 - Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)** - This problem
2. **[LeetCode 239 - Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)** - Core pattern
3. **[LeetCode 1696 - Jump Game VI](https://leetcode.com/problems/jump-game-vi/)** - Similar DP optimization  
4. **[LeetCode 862 - Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)** - Monotonic deque
5. **[LeetCode 1499 - Max Value of Equation](https://leetcode.com/problems/max-value-of-equation/)** - Sliding window maximum
6. **[LeetCode 368 - Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)** - DP with constraints

### Real-World Applications

1. **Financial Optimization**: Portfolio selection with time constraints
2. **Game Development**: Optimal path selection with limited moves
3. **Resource Allocation**: Selecting resources with availability windows
4. **Scheduling Problems**: Task selection with temporal dependencies
5. **Network Routing**: Path optimization with hop limits
6. **Supply Chain**: Supplier selection with delivery windows

### Advanced Optimizations

1. **Parallel Processing**: Segment the array for parallel DP computation
2. **Memory Access Patterns**: Optimize cache locality
3. **SIMD Instructions**: Vectorize maximum finding operations
4. **Approximate Solutions**: Use sampling for very large datasets

This problem demonstrates how monotonic data structures can transform an O(nk) DP solution into an optimal O(n) algorithm, making it crucial for competitive programming and system design interviews.
