# Combination Sum / Subset Sum

## Problem Definition

The Combination Sum problem asks for all unique combinations of candidates where the chosen numbers sum to a target. In the classic version:

1. You have a set of distinct positive integers (candidates)
2. You need to find all unique combinations where the chosen numbers sum to a target
3. Each candidate can be used multiple times

A variation called Combination Sum II restricts each candidate to be used only once.

The Subset Sum problem is similar but asks if there exists any subset that sums to a target value.

## Implementations

### 1. Combination Sum (Candidates can be used multiple times)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class CombinationSumSolver {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& candidates, 
                  std::vector<int>& current, int target, int start) {
        // If we've found a valid combination
        if (target == 0) {
            result.push_back(current);
            return;
        }
        
        // If target becomes negative, we can't form a valid combination
        if (target < 0) {
            return;
        }
        
        // Try each candidate starting from the start index
        for (int i = start; i < candidates.size(); i++) {
            // Add current candidate to our combination
            current.push_back(candidates[i]);
            
            // Recurse with the reduced target
            // Note: we still start from index i because we can reuse the same element
            backtrack(result, candidates, current, target - candidates[i], i);
            
            // Backtrack
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        std::sort(candidates.begin(), candidates.end());  // Sorting is optional but helps with pruning
        
        backtrack(result, candidates, current, target, 0);
        
        return result;
    }
};

int main() {
    std::vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    
    CombinationSumSolver solver;
    std::vector<std::vector<int>> combinations = solver.combinationSum(candidates, target);
    
    std::cout << "Combinations that sum to " << target << ":" << std::endl;
    for (const auto& combination : combinations) {
        std::cout << "[";
        for (int i = 0; i < combination.size(); i++) {
            std::cout << combination[i];
            if (i < combination.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(N^(T/M)), where N is the number of candidates, T is the target, and M is the minimum value among candidates. This is because the maximum depth of the recursion tree is T/M.
**Space Complexity**: O(T/M) for the recursion stack.

### 2. Combination Sum II (Each number can be used only once)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class CombinationSumIISolver {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& candidates, 
                  std::vector<int>& current, int target, int start) {
        if (target == 0) {
            result.push_back(current);
            return;
        }
        
        if (target < 0) {
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // Skip duplicates
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            // Add current candidate
            current.push_back(candidates[i]);
            
            // Move to next index (i+1) because each element can be used only once
            backtrack(result, candidates, current, target - candidates[i], i + 1);
            
            // Backtrack
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        // Sort to handle duplicates
        std::sort(candidates.begin(), candidates.end());
        
        backtrack(result, candidates, current, target, 0);
        
        return result;
    }
};

int main() {
    std::vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;
    
    CombinationSumIISolver solver;
    std::vector<std::vector<int>> combinations = solver.combinationSum2(candidates, target);
    
    std::cout << "Combinations that sum to " << target << " (each number used once):" << std::endl;
    for (const auto& combination : combinations) {
        std::cout << "[";
        for (int i = 0; i < combination.size(); i++) {
            std::cout << combination[i];
            if (i < combination.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(2^N), where N is the number of candidates, as each element can either be included or excluded.
**Space Complexity**: O(N) for the recursion stack.

### 3. Subset Sum (Decision Problem)

The classical Subset Sum problem asks if there exists any subset that sums to a target:

```cpp
#include <iostream>
#include <vector>

// Recursive solution
bool subsetSumRecursive(std::vector<int>& nums, int target, int index) {
    // Base cases
    if (target == 0) {
        return true;  // Found a subset that sums to target
    }
    
    if (index >= nums.size() || target < 0) {
        return false;  // No solution possible
    }
    
    // Recursive cases
    // Include the current element
    if (subsetSumRecursive(nums, target - nums[index], index + 1)) {
        return true;
    }
    
    // Exclude the current element
    return subsetSumRecursive(nums, target, index + 1);
}

// Dynamic Programming solution
bool subsetSumDP(std::vector<int>& nums, int target) {
    int n = nums.size();
    // dp[i][j] = true if there is a subset of nums[0...i-1] that sums to j
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));
    
    // Empty subset has sum 0
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    
    // Fill the dp table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j < nums[i - 1]) {
                // Current element is greater than the sum, so exclude it
                dp[i][j] = dp[i - 1][j];
            } else {
                // Either include or exclude the current element
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            }
        }
    }
    
    return dp[n][target];
}

// Space-optimized DP solution
bool subsetSumDPOptimized(std::vector<int>& nums, int target) {
    std::vector<bool> dp(target + 1, false);
    dp[0] = true;  // Empty subset has sum 0
    
    for (int num : nums) {
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    
    return dp[target];
}

int main() {
    std::vector<int> nums = {3, 34, 4, 12, 5, 2};
    int target = 9;
    
    std::cout << "Using recursion - Can form subset with sum " << target << ": " 
              << (subsetSumRecursive(nums, target, 0) ? "Yes" : "No") << std::endl;
              
    std::cout << "Using DP - Can form subset with sum " << target << ": " 
              << (subsetSumDP(nums, target) ? "Yes" : "No") << std::endl;
              
    std::cout << "Using optimized DP - Can form subset with sum " << target << ": " 
              << (subsetSumDPOptimized(nums, target) ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Time Complexity**:
- Recursive: O(2^N)
- DP: O(N×T), where N is the number of elements and T is the target sum
- Optimized DP: O(N×T)

**Space Complexity**:
- Recursive: O(N) for the recursion stack
- DP: O(N×T)
- Optimized DP: O(T)

## Variants and Extensions

### 1. Combination Sum III

Find all possible combinations of k numbers that add up to a number n, with digits 1 through 9 used only once:

```cpp
#include <iostream>
#include <vector>

class CombinationSumIIISolver {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& current, 
                  int k, int n, int start) {
        // If we have selected k numbers and they sum to n
        if (current.size() == k && n == 0) {
            result.push_back(current);
            return;
        }
        
        // If we have selected k numbers but the sum is not n, or if n < 0
        if (current.size() == k || n < 0) {
            return;
        }
        
        // Try numbers from start to 9
        for (int i = start; i <= 9; i++) {
            current.push_back(i);
            backtrack(result, current, k, n - i, i + 1);
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        backtrack(result, current, k, n, 1);
        
        return result;
    }
};

int main() {
    int k = 3;
    int n = 7;
    
    CombinationSumIIISolver solver;
    std::vector<std::vector<int>> combinations = solver.combinationSum3(k, n);
    
    std::cout << "All combinations of " << k << " numbers that sum to " << n << ":" << std::endl;
    for (const auto& combination : combinations) {
        std::cout << "[";
        for (int i = 0; i < combination.size(); i++) {
            std::cout << combination[i];
            if (i < combination.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

### 2. Combination Sum IV (Permutations)

Count all possible combinations (permutations actually) that add up to a target:

```cpp
#include <iostream>
#include <vector>

int combinationSum4(std::vector<int>& nums, int target) {
    // dp[i] = number of ways to form sum i
    std::vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1;  // There's one way to form sum 0 (empty set)
    
    for (int i = 1; i <= target; i++) {
        for (int num : nums) {
            if (i >= num) {
                dp[i] += dp[i - num];
            }
        }
    }
    
    return dp[target];
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    int target = 4;
    
    std::cout << "Number of combinations (permutations) that sum to " << target << ": " 
              << combinationSum4(nums, target) << std::endl;
    
    return 0;
}
```

## Common Pitfalls

1. **Handling Duplicates**: When the input contains duplicates, you need to ensure you don't generate duplicate combinations.
2. **Order Matters**: Be clear whether you're counting combinations (order doesn't matter) or permutations (order matters).
3. **Integer Overflow**: For problems like Combination Sum IV, the number of combinations can be very large, potentially causing overflow.
4. **Time Complexity**: Naive recursive solutions can be inefficient for large inputs. Consider using dynamic programming or memoization.

## Related LeetCode Problems

1. [39. Combination Sum](https://leetcode.com/problems/combination-sum/) - Find all unique combinations that sum to a target (with reuse)
2. [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) - Find all unique combinations that sum to a target (no reuse)
3. [216. Combination Sum III](https://leetcode.com/problems/combination-sum-iii/) - Find combinations of k numbers that sum to n
4. [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/) - Count permutations that sum to a target
5. [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) - Variant of subset sum
6. [494. Target Sum](https://leetcode.com/problems/target-sum/) - Assign + or - to elements to achieve a target sum
