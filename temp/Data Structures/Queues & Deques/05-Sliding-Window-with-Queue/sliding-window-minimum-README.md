# Sliding Window Minimum

## Problem Description
Given an array of integers `nums` and a sliding window of size `k`, find the minimum element in each window as the window slides from left to right.

Return an array where each element represents the minimum value in the corresponding window.

**Similar Problems:**
- [LeetCode 239: Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- Custom variation of the classic sliding window pattern

## Approach
Use a **Monotonic Deque** (double-ended queue) to efficiently track the minimum element in each sliding window. The deque maintains elements in increasing order, ensuring the front always contains the minimum.

**Key Insight:** For each window, we only care about elements that could potentially be the minimum in current or future windows.

## Algorithm Steps
1. Use a deque to store indices of array elements in increasing order of their values
2. For each element, remove indices that are outside the current window
3. Remove indices from the back if their values are greater than current element
4. Add current index to the back of deque
5. The front of deque contains the index of minimum element in current window

## Implementation

### C++ - Monotonic Deque
```cpp
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    vector<int> slidingWindowMinimum(vector<int>& nums, int k) {
        if (nums.empty() || k == 0) return {};
        
        vector<int> result;
        deque<int> dq; // Store indices
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove indices outside current window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove indices whose values are greater than current
            // (they can never be minimum while current element is in window)
            while (!dq.empty() && nums[dq.back()] >= nums[i]) {
                dq.pop_back();
            }
            
            // Add current index
            dq.push_back(i);
            
            // Add minimum to result (front of deque has minimum)
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};
```

### C++ - Segment Tree Approach
```cpp
#include <vector>
#include <climits>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;
    
    void build(vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node, start, mid);
            build(nums, 2 * node + 1, mid + 1, end);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INT_MAX;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        return min(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }
    
public:
    SegmentTree(vector<int>& nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }
    
    int rangeMin(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

class Solution {
public:
    vector<int> slidingWindowMinimum(vector<int>& nums, int k) {
        if (nums.empty() || k == 0) return {};
        
        SegmentTree st(nums);
        vector<int> result;
        
        for (int i = 0; i <= nums.size() - k; i++) {
            result.push_back(st.rangeMin(i, i + k - 1));
        }
        
        return result;
    }
};
```

### C++ - Brute Force (for comparison)
```cpp
class Solution {
public:
    vector<int> slidingWindowMinimum(vector<int>& nums, int k) {
        if (nums.empty() || k == 0) return {};
        
        vector<int> result;
        
        for (int i = 0; i <= nums.size() - k; i++) {
            int minVal = nums[i];
            for (int j = i + 1; j < i + k; j++) {
                minVal = min(minVal, nums[j]);
            }
            result.push_back(minVal);
        }
        
        return result;
    }
};
```

### Time Complexity
- **Monotonic Deque:** O(n) - Each element is added and removed at most once
- **Segment Tree:** O(n log n) for building + O((n-k+1) log n) for queries
- **Brute Force:** O((n-k+1) × k) = O(nk)

### Space Complexity
- **Monotonic Deque:** O(k) - Deque stores at most k elements
- **Segment Tree:** O(n) - Tree storage
- **Brute Force:** O(1) - Only result space

## Examples

### Example 1
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [-3,-3,-3,-3,3,3]
Explanation: 
Window [1,3,-1] -> min = -1
Window [3,-1,-3] -> min = -3
Window [-1,-3,5] -> min = -3
Window [-3,5,3] -> min = -3
Window [5,3,6] -> min = 3
Window [3,6,7] -> min = 3
```

### Example 2
```
Input: nums = [1], k = 1
Output: [1]
Explanation: Single element window
```

### Example 3
```
Input: nums = [1,2,3,4,5], k = 2
Output: [1,2,3,4]
Explanation:
Window [1,2] -> min = 1
Window [2,3] -> min = 2
Window [3,4] -> min = 3
Window [4,5] -> min = 4
```

## Notes
- **Monotonic Deque:** Most efficient approach, maintains increasing order
- **Key optimization:** Remove elements that can never be minimum in future windows
- **Index storage:** Store indices instead of values to handle window boundaries
- **Edge cases:** Empty array, k = 0, k > array length, all elements equal

## Related Problems
- [LeetCode 239: Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- [LeetCode 862: Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)
- [LeetCode 1438: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)

## Pattern: 05-Sliding-Window-with-Queue
This problem demonstrates **Sliding Window with Queue** pattern where:
- **Sliding window:** Fixed-size window moves through array
- **Monotonic deque:** Maintains order property to enable O(1) queries
- **Efficient updates:** Add/remove elements as window slides
- **Index tracking:** Use indices to handle window boundary conditions
