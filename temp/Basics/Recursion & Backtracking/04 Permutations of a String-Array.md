# Permutations of a String/Array

## What are Permutations?

A permutation is an arrangement of all elements of a set in different order. For example, permutations of "abc" are "abc", "acb", "bac", "bca", "cab", and "cba". For a set with n elements, there are n! (n factorial) possible permutations.

## Problem Definition

Given a string or array of distinct elements, generate all possible permutations of the elements.

## Implementations

### 1. Recursive Backtracking Approach

The most intuitive way to generate all permutations is using recursive backtracking:

```cpp
#include <iostream>
#include <vector>
#include <string>

class PermutationGenerator {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& nums, std::vector<int>& current, std::vector<bool>& used) {
        // If the current permutation is complete
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        // Try each number that hasn't been used yet
        for (int i = 0; i < nums.size(); i++) {
            // Skip if this number is already used
            if (used[i]) continue;
            
            // Use this number
            used[i] = true;
            current.push_back(nums[i]);
            
            // Recurse
            backtrack(result, nums, current, used);
            
            // Backtrack (undo the choice)
            current.pop_back();
            used[i] = false;
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        std::vector<bool> used(nums.size(), false);
        
        backtrack(result, nums, current, used);
        
        return result;
    }
};

// For strings specifically
class StringPermutationGenerator {
private:
    void backtrack(std::vector<std::string>& result, std::string& s, int start) {
        // If we've fixed all positions
        if (start == s.length()) {
            result.push_back(s);
            return;
        }
        
        // Try placing each character at the current position
        for (int i = start; i < s.length(); i++) {
            // Swap characters
            std::swap(s[start], s[i]);
            
            // Recurse for next positions
            backtrack(result, s, start + 1);
            
            // Backtrack (restore the original string)
            std::swap(s[start], s[i]);
        }
    }

public:
    std::vector<std::string> permute(std::string s) {
        std::vector<std::string> result;
        backtrack(result, s, 0);
        return result;
    }
};

int main() {
    // Array example
    std::vector<int> nums = {1, 2, 3};
    PermutationGenerator permGen;
    
    std::vector<std::vector<int>> permutations = permGen.permute(nums);
    
    std::cout << "Permutations of the array [1, 2, 3]:" << std::endl;
    for (const auto& perm : permutations) {
        std::cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            std::cout << perm[i];
            if (i < perm.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // String example
    std::string s = "abc";
    StringPermutationGenerator strPermGen;
    
    std::vector<std::string> strPermutations = strPermGen.permute(s);
    
    std::cout << "\nPermutations of the string \"abc\":" << std::endl;
    for (const auto& perm : strPermutations) {
        std::cout << perm << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(n × n!), where n is the length of the array/string. We have n! permutations, and each takes O(n) time to construct.
**Space Complexity**: O(n) for the recursion stack and to store intermediate states, excluding the space required to store all permutations.

### 2. Heap's Algorithm

Heap's Algorithm is an efficient way to generate all permutations of n objects:

```cpp
#include <iostream>
#include <vector>
#include <string>

class HeapPermutationGenerator {
private:
    void heapPermutation(std::vector<int>& nums, int size, std::vector<std::vector<int>>& result) {
        // If size becomes 1, we've found a permutation
        if (size == 1) {
            result.push_back(nums);
            return;
        }
        
        for (int i = 0; i < size; i++) {
            // Recursively generate permutations with reduced size
            heapPermutation(nums, size - 1, result);
            
            // If size is odd, swap first and last element
            // If size is even, swap ith and last element
            if (size % 2 == 1) {
                std::swap(nums[0], nums[size - 1]);
            } else {
                std::swap(nums[i], nums[size - 1]);
            }
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        heapPermutation(nums, nums.size(), result);
        return result;
    }
};

class StringHeapPermutationGenerator {
private:
    void heapPermutation(std::string& s, int size, std::vector<std::string>& result) {
        if (size == 1) {
            result.push_back(s);
            return;
        }
        
        for (int i = 0; i < size; i++) {
            heapPermutation(s, size - 1, result);
            
            if (size % 2 == 1) {
                std::swap(s[0], s[size - 1]);
            } else {
                std::swap(s[i], s[size - 1]);
            }
        }
    }

public:
    std::vector<std::string> permute(std::string s) {
        std::vector<std::string> result;
        heapPermutation(s, s.length(), result);
        return result;
    }
};

int main() {
    // Array example
    std::vector<int> nums = {1, 2, 3};
    HeapPermutationGenerator permGen;
    
    std::vector<std::vector<int>> permutations = permGen.permute(nums);
    
    std::cout << "Permutations of the array [1, 2, 3] using Heap's algorithm:" << std::endl;
    for (const auto& perm : permutations) {
        std::cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            std::cout << perm[i];
            if (i < perm.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // String example
    std::string s = "abc";
    StringHeapPermutationGenerator strPermGen;
    
    std::vector<std::string> strPermutations = strPermGen.permute(s);
    
    std::cout << "\nPermutations of the string \"abc\" using Heap's algorithm:" << std::endl;
    for (const auto& perm : strPermutations) {
        std::cout << perm << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(n!)
**Space Complexity**: O(n) for the recursion stack

### 3. Using Lexicographic Ordering (Non-Recursive)

This approach generates permutations in lexicographic order:

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // For next_permutation

std::vector<std::vector<int>> generateAllPermutations(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    
    // Sort the array first (needed for next_permutation)
    std::sort(nums.begin(), nums.end());
    
    do {
        result.push_back(nums);
    } while (std::next_permutation(nums.begin(), nums.end()));
    
    return result;
}

std::vector<std::string> generateAllStringPermutations(std::string s) {
    std::vector<std::string> result;
    
    // Sort the string first
    std::sort(s.begin(), s.end());
    
    do {
        result.push_back(s);
    } while (std::next_permutation(s.begin(), s.end()));
    
    return result;
}

int main() {
    // Array example
    std::vector<int> nums = {1, 2, 3};
    std::vector<std::vector<int>> permutations = generateAllPermutations(nums);
    
    std::cout << "Permutations of the array [1, 2, 3] using next_permutation:" << std::endl;
    for (const auto& perm : permutations) {
        std::cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            std::cout << perm[i];
            if (i < perm.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // String example
    std::string s = "abc";
    std::vector<std::string> strPermutations = generateAllStringPermutations(s);
    
    std::cout << "\nPermutations of the string \"abc\" using next_permutation:" << std::endl;
    for (const auto& perm : strPermutations) {
        std::cout << perm << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(n × n!), where n is the length of the array/string.
**Space Complexity**: O(1) excluding the space for storing all permutations.

## Handling Duplicates

If the input array or string contains duplicates, the approaches above will generate duplicate permutations. Here's how to handle that:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

class UniquePermutationGenerator {
private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& nums, int start) {
        // If we've reached the end
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        std::unordered_set<int> used; // To track unique values at this position
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates at the same position
            if (used.count(nums[i])) continue;
            
            used.insert(nums[i]);
            
            // Swap
            std::swap(nums[start], nums[i]);
            
            // Recursively generate permutations
            backtrack(result, nums, start + 1);
            
            // Backtrack
            std::swap(nums[start], nums[i]);
        }
    }

public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        backtrack(result, nums, 0);
        return result;
    }
};

int main() {
    std::vector<int> nums = {1, 1, 2};
    UniquePermutationGenerator gen;
    
    std::vector<std::vector<int>> uniquePermutations = gen.permuteUnique(nums);
    
    std::cout << "Unique permutations of [1, 1, 2]:" << std::endl;
    for (const auto& perm : uniquePermutations) {
        std::cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            std::cout << perm[i];
            if (i < perm.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(n × n!)
**Space Complexity**: O(n)

## Common Pitfalls

1. **Not Handling Duplicates**: If the input contains duplicates, a naive approach will generate duplicate permutations.
2. **Memory Management**: Generating all permutations requires a lot of memory for large inputs, as there are n! permutations.
3. **Efficiency**: The standard recursive approach can be inefficient for large inputs. Consider using Heap's algorithm or the built-in `next_permutation()` function.

## Related LeetCode Problems

1. [46. Permutations](https://leetcode.com/problems/permutations/) - Generate all permutations of an array with distinct integers
2. [47. Permutations II](https://leetcode.com/problems/permutations-ii/) - Generate all unique permutations of an array which may contain duplicates
3. [31. Next Permutation](https://leetcode.com/problems/next-permutation/) - Implement the next_permutation function
4. [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/) - Find the kth permutation sequence
