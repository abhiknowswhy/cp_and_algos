# Longest Increasing Subsequence (LIS)

The Longest Increasing Subsequence is a classic dynamic programming problem that asks for the length of the longest subsequence in a given array such that all elements of the subsequence are in strictly increasing order.

## Problem Statement

Given an array of integers, find the length of the longest subsequence such that all elements of the subsequence are sorted in strictly increasing order.

> Note: A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements.

## Approaches

### 1. Dynamic Programming Approach - O(n²)

The basic dynamic programming approach uses an array `dp` where `dp[i]` represents the length of the longest increasing subsequence ending at index `i`.

**Algorithm:**
1. Initialize a DP array of the same length as the input array, with all values set to 1 (as each element by itself forms an LIS of length 1)
2. For each position i, check all previous positions j < i
3. If nums[i] > nums[j], then we can extend the subsequence ending at j, so dp[i] = max(dp[i], dp[j] + 1)
4. The maximum value in the DP array is the length of the LIS

**C++ Implementation:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    
    // dp[i] represents the length of the LIS ending at index i
    vector<int> dp(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    // Find the maximum value in dp array
    return *max_element(dp.begin(), dp.end());
}

int main() {
    // Example usage
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Length of LIS: " << lengthOfLIS(nums) << endl; // Output: 4 (for the subsequence [2, 5, 7, 101])
    
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Length of LIS: " << lengthOfLIS(nums2) << endl; // Output: 4 (for the subsequence [0, 1, 2, 3])
    
    return 0;
}
```

### 2. Binary Search Approach - O(n log n)

A more efficient approach uses binary search to build the LIS.

**Algorithm:**
1. Maintain a list `tails` where `tails[i]` represents the smallest tail of all increasing subsequences of length i+1
2. For each number in the array:
   - If it's larger than all tails, append it to create a longer subsequence
   - Otherwise, replace the tail of the smallest subsequence that is greater than or equal to this number
3. The length of the `tails` list is the length of the LIS

**C++ Implementation:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lengthOfLIS_BinarySearch(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    vector<int> tails;
    
    for (int num : nums) {
        // Find the first element in tails that is greater than or equal to num
        auto it = lower_bound(tails.begin(), tails.end(), num);
        
        if (it == tails.end()) {
            // All elements in tails are smaller than num, so append num
            tails.push_back(num);
        } else {
            // Replace the found element with num
            *it = num;
        }
    }
    
    return tails.size();
}

int main() {
    // Example usage
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Length of LIS (Binary Search): " << lengthOfLIS_BinarySearch(nums) << endl; // Output: 4
    
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Length of LIS (Binary Search): " << lengthOfLIS_BinarySearch(nums2) << endl; // Output: 4
    
    return 0;
}
```

### 3. Finding the Actual LIS (not just length)

To reconstruct the actual subsequence:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> findLIS(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};
    
    vector<int> dp(n, 1);
    vector<int> prev(n, -1);  // To track predecessors
    
    int maxLength = 1;
    int endIndex = 0;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            endIndex = i;
        }
    }
    
    // Reconstruct the LIS
    vector<int> lis;
    while (endIndex != -1) {
        lis.push_back(nums[endIndex]);
        endIndex = prev[endIndex];
    }
    
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> lis = findLIS(nums);
    
    cout << "Longest Increasing Subsequence: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;  // Output: 2 5 7 101
    
    return 0;
}
```

### 4. LIS Using LCS (Longest Common Subsequence)

Another approach to solve the LIS problem is to use the Longest Common Subsequence algorithm between the original array and its sorted version. However, this approach requires handling duplicates properly.

**Algorithm:**
1. Create a copy of the original array and sort it
2. Remove duplicates from the sorted array
3. Find the LCS between the original array and the sorted array without duplicates
4. The length of this LCS is the length of the LIS

**C++ Implementation:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find LCS
int lcs(vector<int>& arr1, vector<int>& arr2) {
    int m = arr1.size();
    int n = arr2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr1[i-1] == arr2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}

// Find LIS using LCS
int lengthOfLIS_LCS(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    // Create a copy of the array
    vector<int> sortedNums = nums;
    
    // Sort the copy
    sort(sortedNums.begin(), sortedNums.end());
    
    // Remove duplicates
    sortedNums.erase(unique(sortedNums.begin(), sortedNums.end()), sortedNums.end());
    
    // Find LCS between original array and sorted array without duplicates
    return lcs(nums, sortedNums);
}

// Function to reconstruct the actual LIS using LCS approach
vector<int> findLIS_LCS(vector<int>& nums) {
    if (nums.empty()) return {};
    
    // Create a copy of the array
    vector<int> sortedNums = nums;
    
    // Sort the copy
    sort(sortedNums.begin(), sortedNums.end());
    
    // Remove duplicates
    sortedNums.erase(unique(sortedNums.begin(), sortedNums.end()), sortedNums.end());
    
    int m = nums.size();
    int n = sortedNums.size();
    
    // Create DP table for LCS
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (nums[i-1] == sortedNums[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Reconstruct LIS
    vector<int> lis;
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        if (nums[i-1] == sortedNums[j-1]) {
            lis.push_back(nums[i-1]);
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    // Example usage
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    
    cout << "Length of LIS (using LCS): " << lengthOfLIS_LCS(nums) << endl;
    
    vector<int> lis = findLIS_LCS(nums);
    cout << "LIS using LCS approach: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Comparison with Other Approaches

The LCS-based approach has some disadvantages compared to the previous methods:

1. **Time Complexity**: O(n²), which is the same as the standard DP approach but worse than the binary search method
2. **Space Complexity**: O(n²) for the LCS DP table, which is worse than both previous methods
3. **Implementation**: More complex, requiring the LCS algorithm

However, it provides an interesting perspective on the relationship between LIS and LCS problems and demonstrates how the same problem can be approached from different angles.

## Time and Space Complexity

1. **DP Approach**:
   - Time Complexity: O(n²)
   - Space Complexity: O(n)

2. **Binary Search Approach**:
   - Time Complexity: O(n log n)
   - Space Complexity: O(n)

3. **LCS Approach**:
   - Time Complexity: O(n²)
   - Space Complexity: O(n²)

## Related LeetCode Problems

1. [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) - The basic LIS problem.
2. [673. Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/) - Count the number of LIS in an array.
3. [674. Longest Continuous Increasing Subsequence](https://leetcode.com/problems/longest-continuous-increasing-subsequence/) - Find the length of the longest continuous increasing subsequence.
4. [1048. Longest String Chain](https://leetcode.com/problems/longest-string-chain/) - A variant where the subsequence is defined differently.
5. [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) - A 2D extension of the LIS problem.

## Variants and Extensions

1. **Longest Decreasing Subsequence**: Reverse the comparison condition.
2. **Longest Bitonic Subsequence**: Find a subsequence that first increases, then decreases.
3. **Longest Common Subsequence**: A related problem that finds the longest subsequence common to two sequences.
4. **Box Stacking Problem**: A 3D extension of the LIS problem.
