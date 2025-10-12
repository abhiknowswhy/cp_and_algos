# Sliding window maximum

## Problem Description
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

**LeetCode Problem:** [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

## Approach
Use a deque to maintain indices of array elements in decreasing order of their values. The front of deque always contains the index of the maximum element in current window.

## Algorithm Steps
1. Use deque to store indices of array elements
2. For each element, remove indices outside current window from front
3. Remove indices of smaller elements from back (maintain decreasing order)
4. Add current index to back of deque
5. The front of deque gives maximum for current window

## Implementation

### C++
```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // stores indices
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove indices outside current window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove indices of smaller elements from back
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Add to result when window is complete
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};

// Alternative approach using multiset
class SolutionMultiset {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> window;
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            window.insert(nums[i]);
            
            if (i >= k) {
                window.erase(window.find(nums[i - k]));
            }
            
            if (i >= k - 1) {
                result.push_back(*window.rbegin());
            }
        }
        
        return result;
    }
};
```

### Time Complexity
- Deque approach: O(n) - each element added and removed at most once
- Multiset approach: O(n log k)

### Space Complexity
O(k) for the deque/multiset

## Examples

### Example 1
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]

Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

### Example 2
```
Input: nums = [1], k = 1
Output: [1]
```

## Notes
- Deque maintains indices in decreasing order of element values
- Key insight: Remove smaller elements as they'll never be maximum while larger element exists
- Window boundary management is crucial
- This pattern extends to other sliding window optimization problems

## Related Problems
- [LeetCode 480 - Sliding Window Median](https://leetcode.com/problems/sliding-window-median/)
- [LeetCode 1438 - Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)
- [LeetCode 862 - Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)
- [LeetCode 1696 - Jump Game VI](https://leetcode.com/problems/jump-game-vi/)

## Pattern: 05-Sliding-Window-with-Queue
This pattern uses a monotonic deque to efficiently track the optimal element (maximum/minimum) in a sliding window. The deque maintains elements in a specific order to enable O(1) queries.
