# Bitwise Operations for Finding Integers

## 1. Find missing integer

### Problem Description

Given an array of integers from 1 to n where one number is missing, find the missing number using bitwise operations.

### Approach with Bitwise Operations

We can use XOR operation to find the missing number. XOR has the following properties:

- XOR of a number with itself is 0 (a ⊕ a = 0)
- XOR of a number with 0 is the number itself (a ⊕ 0 = a)
- XOR is commutative and associative

If we XOR all numbers from 1 to n with all numbers in the array, all numbers that appear in both sets will cancel out (become 0), and we'll be left with the missing number.

### C++ Implementation

```cpp
#include <iostream>
#include <vector>

int findMissingNumber(const std::vector<int>& nums, int n) {
    int result = 0;
    
    // XOR all numbers from 1 to n
    for (int i = 1; i <= n; i++) {
        result ^= i;
    }
    
    // XOR with all numbers in the array
    for (int num : nums) {
        result ^= num;
    }
    
    return result;
}

int main() {
    std::vector<int> nums = {1, 2, 4, 5}; // Array with missing number 3
    int n = 5; // Range is 1 to 5
    
    std::cout << "Missing number is: " << findMissingNumber(nums, n) << std::endl;
    
    return 0;
}
```

### LeetCode Reference

- [268. Missing Number](https://leetcode.com/problems/missing-number/)

## 2. Find only integer that occurred twice

### Problem Description

Given an array where every element appears exactly once except for one element that appears twice, find the element that appears twice using bitwise operations.

### Approach with Bitwise Operations

Since XOR of a number with itself is 0, and XOR of any number with 0 is the number itself, if we XOR all elements in the array, all elements that appear exactly once will cancel out, and we'll be left with the element that appears twice.

### C++ Implementation

```cpp
#include <iostream>
#include <vector>

int findDuplicate(const std::vector<int>& nums) {
    int result = 0;
    
    // XOR all elements in the array
    for (int num : nums) {
        result ^= num;
    }
    
    return result;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 2}; // Array with duplicate element 2
    
    std::cout << "The duplicate element is: " << findDuplicate(nums) << std::endl;
    
    return 0;
}
```

Wait, the XOR approach works when all numbers except one appear exactly twice (resulting in the odd-occurring number). For the standard case where one number appears twice and all others appear once, we need a different approach.

Here's a solution using a hash set:

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>

int findDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    
    for (int num : nums) {
        // If the number is already in the set, it's the duplicate
        if (seen.find(num) != seen.end()) {
            return num;
        }
        seen.insert(num);
    }
    
    return -1; // No duplicate found
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 2}; // Array with duplicate element 2
    
    std::cout << "The duplicate element is: " << findDuplicate(nums) << std::endl;
    
    return 0;
}
```

Another bitwise approach for this problem when numbers are constrained (e.g., in the range [1, n] for an array of size n+1):

```cpp
#include <iostream>
#include <vector>

// Floyd's Tortoise and Hare (Cycle Detection)
int findDuplicate(const std::vector<int>& nums) {
    int slow = nums[0];
    int fast = nums[0];
    
    // Find meeting point
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    
    // Find cycle entrance
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    
    return slow;
}

int main() {
    std::vector<int> nums = {1, 3, 4, 2, 2}; // Array with duplicate element 2
    
    std::cout << "The duplicate element is: " << findDuplicate(nums) << std::endl;
    
    return 0;
}
```

### LeetCode Reference
- [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)
- [136. Single Number](https://leetcode.com/problems/single-number/) (similar concept, but inverted)

## 3. Find the two integers that occurred twice

### Problem Description
Given an array where all elements appear exactly once except for two elements that appear twice, find these two elements using bitwise operations.

### Approach with Bitwise Operations
1. XOR all elements in the array to get XOR of the two duplicates (since all other elements appear once and cancel out)
2. Find any bit that is set (1) in this XOR result
3. Divide all numbers into two groups based on whether they have that bit set or not
4. XOR each group separately to find the two numbers that appeared twice

### C++ Implementation

```cpp
#include <iostream>
#include <vector>

std::vector<int> findTwoDoubles(const std::vector<int>& nums) {
    int xorResult = 0;
    
    // XOR all elements to get XOR of the two duplicates
    for (int num : nums) {
        xorResult ^= num;
    }
    
    // Find any set bit in the XOR result
    int setBit = xorResult & -xorResult; // Gets the rightmost set bit
    
    // Divide numbers into two groups and XOR separately
    int num1 = 0, num2 = 0;
    for (int num : nums) {
        if (num & setBit) {
            // Group 1: bit is set
            num1 ^= num;
        } else {
            // Group 2: bit is not set
            num2 ^= num;
        }
    }
    
    return {num1, num2};
}

int main() {
    std::vector<int> nums = {1, 2, 1, 3, 4, 5, 4, 6}; // Array with duplicates 1 and 4
    
    std::vector<int> result = findTwoDoubles(nums);
    std::cout << "The two duplicate elements are: " << result[0] << " and " << result[1] << std::endl;
    
    return 0;
}
```

### LeetCode Reference
- [260. Single Number III](https://leetcode.com/problems/single-number-iii/) (similar concept, but inverted)

## Additional Bitwise Tricks for Array Problems

1. **Finding a single element in an array where all other elements appear three times:**
   XOR doesn't work directly, but we can count the number of 1s for each bit position for all numbers.
   If a bit appears 3k times, it's not from our single number.
   If a bit appears 3k+1 times, it means the single number has that bit set.

2. **Find the majority element (appears more than n/2 times):**
   This can be approached using bit counting as well. For each bit position, count how many numbers have that bit set.
   If it's more than n/2, then the majority element must have that bit set.

3. **Counting set bits in an integer:**

```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
```

Brian Kernighan's Algorithm (more efficient):

```cpp
   int countSetBits(int n) {
       int count = 0;
       while (n) {
           n &= (n - 1);  // Clear the least significant set bit
           count++;
       }
       return count;
   }
```
