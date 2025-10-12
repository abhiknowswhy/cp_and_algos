# Subset Generation (Power Set)

## What is a Power Set?

The power set of a set S is the set of all subsets of S, including the empty set and S itself. For a set with n elements, the power set has 2^n elements.

## Problem Definition

Given a set of distinct integers or characters, return all possible subsets (the power set).

## Implementations

### 1. Recursive Backtracking Approach

We can generate all subsets by recursively deciding whether to include each element:

```cpp
#include <iostream>
#include <vector>

class SubsetGenerator {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& nums, 
                  std::vector<int>& current, int index) {
        // Add the current subset
        result.push_back(current);
        
        // Try including elements starting from index
        for (int i = index; i < nums.size(); i++) {
            // Include the element
            current.push_back(nums[i]);
            
            // Recursive call for the next elements
            backtrack(result, nums, current, i + 1);
            
            // Backtrack (exclude the element)
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        backtrack(result, nums, current, 0);
        
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 3};
    SubsetGenerator generator;
    
    std::vector<std::vector<int>> subsets = generator.subsets(nums);
    
    std::cout << "All subsets of [1, 2, 3]:" << std::endl;
    for (const auto& subset : subsets) {
        std::cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            std::cout << subset[i];
            if (i < subset.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(N × 2^N), where N is the length of the array. There are 2^N subsets, and each subset takes O(N) time to construct.
**Space Complexity**: O(N) for the recursion stack, excluding the space for storing all subsets.

### 2. Iterative Approach

We can also generate all subsets iteratively by adding one element at a time:

```cpp
#include <iostream>
#include <vector>

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> result = {{}};  // Start with the empty subset
    
    for (int num : nums) {
        int n = result.size();
        for (int i = 0; i < n; i++) {
            std::vector<int> subset = result[i];
            subset.push_back(num);
            result.push_back(subset);
        }
    }
    
    return result;
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    
    std::vector<std::vector<int>> allSubsets = subsets(nums);
    
    std::cout << "All subsets of [1, 2, 3] (iterative approach):" << std::endl;
    for (const auto& subset : allSubsets) {
        std::cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            std::cout << subset[i];
            if (i < subset.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(N × 2^N)
**Space Complexity**: O(1) excluding the space required for storing all subsets.

### 3. Bit Manipulation Approach

We can use the binary representation of numbers from 0 to 2^N-1 to generate all subsets:

```cpp
#include <iostream>
#include <vector>

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    int n = nums.size();
    int subsetCount = 1 << n;  // 2^n subsets
    std::vector<std::vector<int>> result;
    
    for (int i = 0; i < subsetCount; i++) {
        std::vector<int> subset;
        for (int j = 0; j < n; j++) {
            // If the jth bit of i is set, include the jth element
            if ((i & (1 << j)) != 0) {
                subset.push_back(nums[j]);
            }
        }
        result.push_back(subset);
    }
    
    return result;
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    
    std::vector<std::vector<int>> allSubsets = subsets(nums);
    
    std::cout << "All subsets of [1, 2, 3] (bit manipulation approach):" << std::endl;
    for (const auto& subset : allSubsets) {
        std::cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            std::cout << subset[i];
            if (i < subset.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(N × 2^N)
**Space Complexity**: O(1) excluding the space for storing all subsets.

## Handling Duplicates

If the input contains duplicates and we want unique subsets:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class UniqueSubsetGenerator {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& nums, 
                  std::vector<int>& current, int index) {
        // Add the current subset
        result.push_back(current);
        
        // Try including elements starting from index
        for (int i = index; i < nums.size(); i++) {
            // Skip duplicates
            if (i > index && nums[i] == nums[i - 1]) {
                continue;
            }
            
            // Include the element
            current.push_back(nums[i]);
            
            // Recursively generate subsets
            backtrack(result, nums, current, i + 1);
            
            // Backtrack
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());  // Sort to group duplicates together
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        backtrack(result, nums, current, 0);
        
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 2, 2};
    UniqueSubsetGenerator generator;
    
    std::vector<std::vector<int>> uniqueSubsets = generator.subsetsWithDup(nums);
    
    std::cout << "Unique subsets of [1, 2, 2]:" << std::endl;
    for (const auto& subset : uniqueSubsets) {
        std::cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            std::cout << subset[i];
            if (i < subset.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(N × 2^N)
**Space Complexity**: O(N) for the recursion stack.

## Applications of Power Set

1. **Combination Problems**: Finding all possible combinations that meet certain criteria.
2. **Subset Sum Problems**: Finding subsets that sum up to a specific value.
3. **State Space Search**: In problems where you need to explore all possible states.
4. **Boolean Logic**: Representing all possible combinations of boolean variables.

## Common Pitfalls

1. **Memory Issues**: Generating the power set requires O(N × 2^N) memory, which can be prohibitive for large sets.
2. **Not Handling Duplicates**: If the input contains duplicates, generating unique subsets requires additional handling.
3. **Runtime Complexity**: The power set has exponential size, so any algorithm that generates it will have exponential time complexity.

## Related LeetCode Problems

1. [78. Subsets](https://leetcode.com/problems/subsets/) - Generate all subsets of a set of distinct integers
2. [90. Subsets II](https://leetcode.com/problems/subsets-ii/) - Generate all unique subsets of a set that may contain duplicates
3. [77. Combinations](https://leetcode.com/problems/combinations/) - Generate all combinations of k elements from a set of size n
4. [39. Combination Sum](https://leetcode.com/problems/combination-sum/) - Find all combinations of candidates that sum to a target
5. [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) - Similar to above, but with each number used only once
