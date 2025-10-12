# Next Greater Element (NGE)

## Problem Description

Given an array of integers, find the next greater element for each element in the array. The next greater element for an element x is the first greater element on the right side of x in the array. If no such element exists, output -1 for that element.

For example, given the array [4, 5, 2, 25], the next greater elements for each element are:
- 4 → 5 (the next element greater than 4 is 5)
- 5 → 25 (the next element greater than 5 is 25)
- 2 → 25 (the next element greater than 2 is 25)
- 25 → -1 (there is no element greater than 25)

## Approaches to Solve the Problem

### 1. Brute Force Approach

#### Intuition

For each element, iterate through the array to find the next greater element.

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> nextGreaterElementBruteForce(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1); // Initialize all elements to -1
    
    // For each element, find its next greater element
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[j] > nums[i]) {
                result[i] = nums[j];
                break; // Found the next greater element
            }
        }
    }
    
    return result;
}

int main() {
    vector<int> nums = {4, 5, 2, 25};
    vector<int> result = nextGreaterElementBruteForce(nums);
    
    cout << "Element\tNGE" << endl;
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << "\t" << result[i] << endl;
    }
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n²), where n is the size of the array
- Space Complexity: O(n) for storing the result

### 2. Stack-based Approach

#### Intuition

Use a stack to keep track of elements that don't have a next greater element yet. Process the array from right to left (or reverse order).

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1); // Initialize all elements to -1
    stack<int> s; // Stack to store indices
    
    // Process array from right to left
    for (int i = n - 1; i >= 0; i--) {
        // Remove elements from stack that are smaller than or equal to current
        while (!s.empty() && nums[s.top()] <= nums[i]) {
            s.pop();
        }
        
        // If stack is not empty, the top element is the NGE
        if (!s.empty()) {
            result[i] = nums[s.top()];
        }
        
        // Push current element index to stack
        s.push(i);
    }
    
    return result;
}

int main() {
    vector<int> nums = {4, 5, 2, 25};
    vector<int> result = nextGreaterElement(nums);
    
    cout << "Element\tNGE" << endl;
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << "\t" << result[i] << endl;
    }
    
    return 0;
}
```

#### Alternative Stack-based Approach (Processing from Left to Right)

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextGreaterElementLeftToRight(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1); // Initialize all elements to -1
    stack<int> s; // Stack to store indices
    
    for (int i = 0; i < n; i++) {
        // If the current element is greater than the element at stack top,
        // it is the next greater element for the element at stack top
        while (!s.empty() && nums[i] > nums[s.top()]) {
            result[s.top()] = nums[i]; // Set the NGE
            s.pop();
        }
        
        // Push the current element's index to the stack
        s.push(i);
    }
    
    return result;
}

int main() {
    vector<int> nums = {4, 5, 2, 25};
    vector<int> result = nextGreaterElementLeftToRight(nums);
    
    cout << "Element\tNGE" << endl;
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << "\t" << result[i] << endl;
    }
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the size of the array
- Space Complexity: O(n) for the stack and result array

### 3. Circular Array Next Greater Element

#### Intuition

The problem can be extended to a circular array, where we need to consider the array as circular (the last element's next is the first element). 

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextGreaterElementCircular(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> s;
    
    // Process array twice to handle circular property
    for (int i = 2 * n - 1; i >= 0; i--) {
        // Get the actual index in the array
        int idx = i % n;
        
        // Remove elements from stack that are smaller than current
        while (!s.empty() && nums[s.top()] <= nums[idx]) {
            s.pop();
        }
        
        // If stack is not empty, the top element is the NGE
        if (!s.empty()) {
            result[idx] = nums[s.top()];
        }
        
        // Push current element index to stack
        s.push(idx);
    }
    
    return result;
}

int main() {
    vector<int> nums = {4, 5, 2, 25};
    vector<int> result = nextGreaterElementCircular(nums);
    
    cout << "Element\tNGE (Circular)" << endl;
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << "\t" << result[i] << endl;
    }
    
    return 0;
}
```

### 4. Next Greater Element II: Two Arrays

#### Intuition

A variation where we need to find the next greater element in the second array for each element in the first array.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

vector<int> nextGreaterElementTwoArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();
    vector<int> result(n1, -1);
    unordered_map<int, int> nextGreater; // Maps element to its NGE
    stack<int> s;
    
    // Find NGE for all elements in nums2
    for (int i = n2 - 1; i >= 0; i--) {
        while (!s.empty() && s.top() <= nums2[i]) {
            s.pop();
        }
        
        if (!s.empty()) {
            nextGreater[nums2[i]] = s.top();
        } else {
            nextGreater[nums2[i]] = -1;
        }
        
        s.push(nums2[i]);
    }
    
    // Populate result for nums1
    for (int i = 0; i < n1; i++) {
        result[i] = nextGreater[nums1[i]];
    }
    
    return result;
}

int main() {
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};
    vector<int> result = nextGreaterElementTwoArrays(nums1, nums2);
    
    cout << "Element\tNGE" << endl;
    for (int i = 0; i < nums1.size(); i++) {
        cout << nums1[i] << "\t" << result[i] << endl;
    }
    
    return 0;
}
```

### 5. Next Greater Frequency Element

#### Intuition

Find the next element in the array with a higher frequency than the current element.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

vector<int> nextGreaterFrequency(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    
    // Count frequency of each element
    unordered_map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    // Use stack to find next greater frequency
    stack<int> s; // Stack stores indices
    for (int i = 0; i < n; i++) {
        while (!s.empty() && freq[nums[s.top()]] < freq[nums[i]]) {
            result[s.top()] = nums[i];
            s.pop();
        }
        s.push(i);
    }
    
    return result;
}

int main() {
    vector<int> nums = {1, 1, 2, 3, 4, 2, 1};
    vector<int> result = nextGreaterFrequency(nums);
    
    cout << "Element\tNGF" << endl;
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << "\t" << result[i] << endl;
    }
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 496: Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
2. [LeetCode 503: Next Greater Element II (Circular Array)](https://leetcode.com/problems/next-greater-element-ii/)
3. [LeetCode 739: Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
4. [LeetCode 901: Online Stock Span](https://leetcode.com/problems/online-stock-span/)
5. [LeetCode 1019: Next Greater Node In Linked List](https://leetcode.com/problems/next-greater-node-in-linked-list/)

## Applications

1. **Stock Price Analysis**: Find the next day when the stock price is higher
2. **Temperature Analysis**: Find the next day with a higher temperature
3. **Resource Monitoring**: Identify when resource usage exceeds a threshold
4. **Traffic Flow Analysis**: Find the next time point with higher traffic volume

## Summary

| Approach | Time Complexity | Space Complexity | Notes |
| --- | --- | --- | --- |
| Brute Force | O(n²) | O(n) | Simple but inefficient for large arrays |
| Stack-based (Right to Left) | O(n) | O(n) | Efficient stack-based solution |
| Stack-based (Left to Right) | O(n) | O(n) | Alternative approach processing array from left |
| Circular Array NGE | O(n) | O(n) | Handles arrays as if they were circular |
| Two Arrays NGE | O(n₁ + n₂) | O(n₂) | Useful for finding NGE across different arrays |
| Next Greater Frequency | O(n) | O(n) | Variation that considers element frequency |
