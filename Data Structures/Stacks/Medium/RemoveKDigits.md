# Remove K Digits to Make Smallest Number

## Problem Description

Given a non-negative integer represented as a string `num` and an integer `k`, the task is to remove `k` digits from `num` to form the smallest possible number (without leading zeros). We need to return the resulting number as a string.

## Approaches to Solve the Problem

### 1. Greedy Approach with Stack

#### Intuition

The key insight for this problem is to use a greedy approach:
- We want to remove digits that create "peaks" in the number
- When we encounter a digit that is smaller than the previous digit, we should remove the previous digit
- We use a stack to keep track of the selected digits

#### Implementation

```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;

string removeKdigits(string num, int k) {
    // If k is equal to the length of num, return "0"
    if (k >= num.length()) {
        return "0";
    }
    
    // If k is 0, no removal needed
    if (k == 0) {
        return num;
    }
    
    stack<char> st;
    
    // Iterate through each digit
    for (char digit : num) {
        // While we still have digits to remove and the current digit is smaller than the top of the stack
        while (k > 0 && !st.empty() && st.top() > digit) {
            st.pop();
            k--;
        }
        
        // Push current digit to stack (unless it's a leading zero)
        if (!st.empty() || digit != '0') {
            st.push(digit);
        }
    }
    
    // If we still have digits to remove, remove from the end
    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }
    
    // Build the result string from stack
    string result = "";
    while (!st.empty()) {
        result = st.top() + result; // Prepend to result
        st.pop();
    }
    
    // Handle edge case of empty result
    return result.empty() ? "0" : result;
}
```

#### Explanation

1. If `k` is greater than or equal to the length of the input string, we return "0" since removing all digits would result in an empty string, which should be interpreted as "0".
2. We use a stack to maintain the digits of the result in ascending order from bottom to top.
3. For each digit in the input:
   - If the current digit is smaller than the top of the stack and we can still remove digits, we remove the top digit from the stack.
   - We push the current digit onto the stack (unless it would be a leading zero).
4. If we haven't removed `k` digits yet after processing all digits, we remove digits from the end of the number (top of the stack).
5. We build the result by popping digits from the stack and prepending them to our result string.
6. If the result is empty, we return "0".

### 2. String-based Greedy Approach

#### Intuition

The same greedy approach can be implemented using a string instead of a stack, which might be more intuitive and efficient:
- We build the result string directly
- We remove digits that create "peaks" in the number
- This avoids the need to reverse the result at the end

#### Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

string removeKdigits(string num, int k) {
    string result = "";
    int n = num.size();
    
    // If k is equal to the length of num, return "0"
    if (k >= n) {
        return "0";
    }
    
    // Process each digit
    for (char digit : num) {
        // If the current digit is smaller than the last digit in result,
        // and we still have digits to remove, remove the last digit
        while (k > 0 && !result.empty() && result.back() > digit) {
            result.pop_back();
            k--;
        }
        
        // Add current digit to result (avoid leading zeros)
        if (!result.empty() || digit != '0') {
            result.push_back(digit);
        }
    }
    
    // If we still have digits to remove, remove from the end
    while (k > 0 && !result.empty()) {
        result.pop_back();
        k--;
    }
    
    // Handle edge case of empty result
    return result.empty() ? "0" : result;
}
```

### 3. Monotonic Stack Approach

#### Intuition

This approach is similar to the first one but explicitly highlights the monotonic stack property:
- We maintain a monotonically increasing stack (non-decreasing)
- This ensures that the smallest possible number is formed

#### Implementation

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string removeKdigits(string num, int k) {
    // If k is equal to the length of num, return "0"
    if (k >= num.length()) {
        return "0";
    }
    
    // Use vector as stack for better performance
    vector<char> monoStack;
    
    for (char digit : num) {
        // Maintain monotonic increasing stack
        while (k > 0 && !monoStack.empty() && monoStack.back() > digit) {
            monoStack.pop_back();
            k--;
        }
        monoStack.push_back(digit);
    }
    
    // If we still have digits to remove, remove from the end
    while (k > 0 && !monoStack.empty()) {
        monoStack.pop_back();
        k--;
    }
    
    // Build the result, skipping leading zeros
    string result = "";
    bool leadingZero = true;
    
    for (char digit : monoStack) {
        if (leadingZero && digit == '0') {
            continue;
        }
        leadingZero = false;
        result.push_back(digit);
    }
    
    // Handle edge case of empty result
    return result.empty() ? "0" : result;
}
```

## Complexity Analysis

### Greedy Approach with Stack
- **Time Complexity**: O(n), where n is the length of the input string. Each digit is pushed and popped at most once.
- **Space Complexity**: O(n) for the stack in the worst case.

### String-based Greedy Approach
- **Time Complexity**: O(n), where n is the length of the input string.
- **Space Complexity**: O(n) for the result string.

### Monotonic Stack Approach
- **Time Complexity**: O(n), where n is the length of the input string.
- **Space Complexity**: O(n) for the monotonic stack.

## Step-by-Step Execution

Let's trace through the string-based greedy approach with an example:

Input: `num = "1432219", k = 3`

1. Process '1':
   - result = "1"

2. Process '4':
   - '4' > '1', so we keep both
   - result = "14"

3. Process '3':
   - '3' < '4', so we remove '4' (k = 2)
   - result = "13"

4. Process '2':
   - '2' < '3', so we remove '3' (k = 1)
   - result = "12"

5. Process '2':
   - '2' = '2', so we keep both
   - result = "122"

6. Process '1':
   - '1' < '2', so we remove '2' (k = 0)
   - result = "121"

7. Process '9':
   - We've used all removals (k = 0), so we just append
   - result = "1219"

Final result: `"1219"`

Let's try another example:

Input: `num = "10200", k = 1`

1. Process '1':
   - result = "1"

2. Process '0':
   - '0' < '1', so we remove '1' (k = 0)
   - result = "" (empty)
   - Since result is empty, we add '0'
   - result = "0"

3. Process '2':
   - We've used all removals (k = 0), so we just append
   - result = "02"

4. Process '0':
   - We've used all removals, so we just append
   - result = "020"

5. Process '0':
   - We've used all removals, so we just append
   - result = "0200"

Now we need to remove leading zeros: result = "200"

Final result: `"200"`

## Related LeetCode Problems

- [LeetCode 402: Remove K Digits](https://leetcode.com/problems/remove-k-digits/)
- [LeetCode 316: Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/)
- [LeetCode 1081: Smallest Subsequence of Distinct Characters](https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/)
- [LeetCode 321: Create Maximum Number](https://leetcode.com/problems/create-maximum-number/)
- [LeetCode 84: Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
- [LeetCode 496: Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)

## Applications

- **Number Optimization**: Finding optimal representations of numbers under constraints
- **Financial Applications**: Optimizing transaction amounts by removing certain digits
- **Data Compression**: Reducing digits while preserving magnitude order
- **Network Routing**: Optimizing routing numbers or identifiers
- **Numerical Analysis**: Simplifying numerical representations while minimizing error

## Summary

| Approach | Time Complexity | Space Complexity | Pros | Cons |
|----------|-----------------|------------------|------|------|
| Greedy with Stack | O(n) | O(n) | Intuitive stack operations, easy to understand | Requires reversing at the end |
| String-based Greedy | O(n) | O(n) | More efficient, builds result directly | Same core algorithm |
| Monotonic Stack | O(n) | O(n) | Explicitly maintains stack property, easier to extend | Slightly more code |

The greedy approach is optimal for this problem because:

1. Local optimality leads to global optimality: By always removing the digit that creates a "peak" (i.e., a digit that is larger than the next digit), we ensure that the resulting number is as small as possible.

2. We can prove this works by contradiction: If we didn't remove a digit that forms a peak, the resulting number would be larger than if we had removed it.

3. The stack/string-based implementation efficiently tracks which digits to keep and which to remove.

Key insights to remember:
- Always try to maintain a non-decreasing sequence of digits
- Handle leading zeros carefully
- If you still have removals left after processing all digits, remove from the end
