
# K Pairs with Smallest Sum

## Problem Statement

Given two integer arrays `nums1` and `nums2` sorted in ascending order and an integer `k`, return the `k` pairs `(u,v)` with the smallest sums where `u` is an element from `nums1` and `v` is an element from `nums2`.

## Related LeetCode Problems:
* **[373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)**
* **[378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)**
* **[668. Kth Smallest Number in Multiplication Table](https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/)**

## Approach

### 1. Brute Force Approach

The naive approach would be to generate all pairs, sort them by their sum, and return the first k pairs. However, this would be inefficient for large arrays.

Time complexity: O((n*m) * log(n*m)), where n is the length of nums1 and m is the length of nums2.
Space complexity: O(n*m) for storing all pairs.

### 2. Min Heap Approach

A more efficient approach uses a min heap (priority queue):

1. Initialize a min heap to store pairs sorted by their sum
2. Start with pairs from the first element of nums1 and all elements of nums2
3. Pop the pair with the smallest sum from the heap
4. Add the next pair to consider to the heap
5. Repeat steps 3-4 until we have k pairs

Time complexity: O(k * log(min(k, n*m)))
Space complexity: O(min(k, n*m))

### 3. Optimized Min Heap Approach

We can optimize further by only considering necessary pairs:

1. Start with only the pair (0,0) - the first elements of both arrays
2. When we pop a pair (i,j), add pairs (i+1,j) and (i,j+1) to the heap
3. Use a visited set to avoid duplicates
4. Continue until we have k pairs

## Solution

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

// Custom hash function for pair<int, int>
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

class Solution {
public:
    // Function to find k pairs with smallest sums
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<vector<int>> result;
        if (nums1.empty() || nums2.empty() || k <= 0) return result;
        
        // Min heap to store pairs sorted by their sum
        // Format: {sum, {i, j}} where i is index in nums1 and j is index in nums2
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> minHeap;
        
        // Set to keep track of visited pairs
        unordered_set<pair<int, int>, PairHash> visited;
        
        // Start with the smallest pair (0,0)
        minHeap.push({nums1[0] + nums2[0], {0, 0}});
        visited.insert({0, 0});
        
        // Process the heap until we have k pairs or the heap is empty
        while (k > 0 && !minHeap.empty()) {
            auto current = minHeap.top();
            minHeap.pop();
            
            int i = current.second.first;
            int j = current.second.second;
            
            // Add the pair to the result
            result.push_back({nums1[i], nums2[j]});
            
            // Add the next pairs to the heap if they haven't been visited
            // Add pair (i+1, j)
            if (i + 1 < nums1.size() && visited.count({i + 1, j}) == 0) {
                minHeap.push({nums1[i + 1] + nums2[j], {i + 1, j}});
                visited.insert({i + 1, j});
            }
            
            // Add pair (i, j+1)
            if (j + 1 < nums2.size() && visited.count({i, j + 1}) == 0) {
                minHeap.push({nums1[i] + nums2[j + 1], {i, j + 1}});
                visited.insert({i, j + 1});
            }
            
            k--;
        }
        
        return result;
    }
};

// Helper function to print the result
void printResult(const vector<vector<int>>& pairs) {
    cout << "[ ";
    for (const auto& pair : pairs) {
        cout << "[" << pair[0] << "," << pair[1] << "] ";
    }
    cout << "]" << endl;
}

// Main function to test the solution
int main() {
    // Example 1
    vector<int> nums1_1 = {1, 7, 11};
    vector<int> nums2_1 = {2, 4, 6};
    int k1 = 3;
    Solution sol;
    vector<vector<int>> result1 = sol.kSmallestPairs(nums1_1, nums2_1, k1);
    cout << "Example 1 Output: ";
    printResult(result1);
    
    // Example 2
    vector<int> nums1_2 = {1, 1, 2};
    vector<int> nums2_2 = {1, 2, 3};
    int k2 = 2;
    vector<vector<int>> result2 = sol.kSmallestPairs(nums1_2, nums2_2, k2);
    cout << "Example 2 Output: ";
    printResult(result2);
    
    // Example 3
    vector<int> nums1_3 = {1, 2};
    vector<int> nums2_3 = {3};
    int k3 = 3;
    vector<vector<int>> result3 = sol.kSmallestPairs(nums1_3, nums2_3, k3);
    cout << "Example 3 Output: ";
    printResult(result3);
    
    return 0;
}
```

## Explanation of Complexity

- **Time Complexity**: O(k * log(min(k, n*m)))
  - Each heap operation costs O(log(size of heap))
  - We perform at most O(k) heap operations
  - The heap size is bounded by O(min(k, n*m))

- **Space Complexity**: O(min(k, n*m))
  - For storing elements in the heap and the visited set

## Key Insights

1. We leverage the fact that both arrays are sorted to efficiently find pairs with small sums.
2. Using a min heap allows us to always process the next smallest pair first.
3. The visited set helps avoid duplicates and ensures we don't add the same pair multiple times.
4. This approach can be generalized to find k smallest elements in a conceptually 2D sorted structure.

## Variations

This pattern can be used for several related problems:
- Finding the kth smallest element in a sorted matrix
- Finding the kth smallest sum of elements from multiple sorted arrays
- Finding the kth smallest product of elements from two sorted arrays
