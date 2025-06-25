# Balanced Parentheses / Valid Parentheses

## Problem Description

Given a string containing just the characters `(`, `)`, `{`, `}`, `[`, and `]`, determine if the input string is valid. An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

## Approaches to Solve the Problem

### 1. Stack-based Approach

#### Intuition

- Use a stack to keep track of opening brackets
- When encountering a closing bracket, check if it matches the most recent opening bracket
- If all brackets are matched and the stack is empty at the end, the string is valid

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> brackets = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        for (char c : s) {
            // If it's an opening bracket, push to stack
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            }
            // If it's a closing bracket
            else if (c == ')' || c == '}' || c == ']') {
                // Check if stack is empty or the top doesn't match
                if (st.empty() || st.top() != brackets[c]) {
                    return false;
                }
                st.pop(); // Remove the matching opening bracket
            }
        }
        
        // If stack is empty, all brackets were matched
        return st.empty();
    }
};

int main() {
    Solution sol;
    
    string s1 = "()";
    cout << s1 << " is " << (sol.isValid(s1) ? "valid" : "invalid") << endl;
    
    string s2 = "()[]{}";
    cout << s2 << " is " << (sol.isValid(s2) ? "valid" : "invalid") << endl;
    
    string s3 = "(]";
    cout << s3 << " is " << (sol.isValid(s3) ? "valid" : "invalid") << endl;
    
    string s4 = "([)]";
    cout << s4 << " is " << (sol.isValid(s4) ? "valid" : "invalid") << endl;
    
    string s5 = "{[]}";
    cout << s5 << " is " << (sol.isValid(s5) ? "valid" : "invalid") << endl;
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the length of the string
- Space Complexity: O(n) for the stack in the worst case

### 2. Counter-based Approach (Limited Variant)

#### Intuition

For a simpler version with only one type of brackets (e.g., just parentheses), we can use a counter:
- Increment counter for opening brackets
- Decrement for closing brackets
- The string is valid if the counter is always non-negative and ends at 0

#### Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Function to check if parentheses are balanced
// Note: This only works for a single type of bracket
bool isValidParentheses(string s) {
    int count = 0;
    
    for (char c : s) {
        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
            // If at any point we have more closing brackets than opening
            if (count < 0) {
                return false;
            }
        }
    }
    
    // String is valid if count is zero (all brackets are matched)
    return count == 0;
}

int main() {
    string s1 = "()";
    cout << s1 << " is " << (isValidParentheses(s1) ? "valid" : "invalid") << endl;
    
    string s2 = "(())";
    cout << s2 << " is " << (isValidParentheses(s2) ? "valid" : "invalid") << endl;
    
    string s3 = ")(";
    cout << s3 << " is " << (isValidParentheses(s3) ? "valid" : "invalid") << endl;
    
    string s4 = "(()";
    cout << s4 << " is " << (isValidParentheses(s4) ? "valid" : "invalid") << endl;
    
    return 0;
}
```

### 3. Stack-based with Character Replacement

#### Intuition

An alternative approach that is more memory-efficient is to replace matching pairs in the string and check if the string becomes empty:
- Use a stack to keep track of positions
- When a matching pair is found, remove both characters
- The string is valid if all characters can be removed

#### Implementation

```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isValidWithReplacement(string s) {
    stack<int> st; // Store indices of opening brackets
    
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            st.push(i);
        } else {
            if (st.empty()) {
                return false; // No matching opening bracket
            }
            
            int top = st.top();
            st.pop();
            
            // Check if the brackets match
            if ((s[top] == '(' && s[i] != ')') || 
                (s[top] == '{' && s[i] != '}') || 
                (s[top] == '[' && s[i] != ']')) {
                return false;
            }
        }
    }
    
    return st.empty(); // All brackets must be matched
}

int main() {
    string s1 = "()[]{}";
    cout << s1 << " is " << (isValidWithReplacement(s1) ? "valid" : "invalid") << endl;
    
    string s2 = "([)]";
    cout << s2 << " is " << (isValidWithReplacement(s2) ? "valid" : "invalid") << endl;
    
    return 0;
}
```

### 4. Extended Problem: Maximum Nesting Depth

#### Intuition

Find the maximum depth of nested valid parentheses in a given string.

#### Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

int maxDepth(string s) {
    int currentDepth = 0;
    int maxDepth = 0;
    
    for (char c : s) {
        if (c == '(') {
            currentDepth++;
            maxDepth = max(maxDepth, currentDepth);
        } else if (c == ')') {
            currentDepth--;
        }
        
        // Assuming the input is valid, we don't need to check if currentDepth < 0
    }
    
    return maxDepth;
}

int main() {
    string s1 = "((()))";
    cout << "Maximum nesting depth of " << s1 << ": " << maxDepth(s1) << endl;
    
    string s2 = "(()(()))";
    cout << "Maximum nesting depth of " << s2 << ": " << maxDepth(s2) << endl;
    
    return 0;
}
```

### 5. Extended Problem: Minimum Insertions to Balance

#### Intuition

Find the minimum number of insertions needed to make the parentheses string valid.

#### Implementation

```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int minInsertionsToBalance(string s) {
    int insertions = 0;
    stack<char> st;
    
    for (char c : s) {
        if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            if (st.empty()) {
                // Need to insert an opening bracket
                insertions++;
            } else {
                st.pop();
            }
        }
    }
    
    // Add closing brackets for remaining opening brackets
    insertions += st.size();
    
    return insertions;
}

int main() {
    string s1 = "())";
    cout << "Minimum insertions for " << s1 << ": " << minInsertionsToBalance(s1) << endl;
    
    string s2 = "(((";
    cout << "Minimum insertions for " << s2 << ": " << minInsertionsToBalance(s2) << endl;
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 20: Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
2. [LeetCode 22: Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)
3. [LeetCode 32: Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
4. [LeetCode 1249: Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/)
5. [LeetCode 856: Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/)
6. [LeetCode 921: Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)

## Applications

1. **Compiler Design**: Checking for balanced brackets in code
2. **Text Editors**: Matching brackets feature
3. **Expression Parsing**: Validating mathematical expressions
4. **JSON/XML Parsing**: Ensuring properly nested tags

## Summary

| Approach | Time Complexity | Space Complexity | Best For |
| --- | --- | --- | --- |
| Stack-based | O(n) | O(n) | General case with multiple bracket types |
| Counter-based | O(n) | O(1) | Single bracket type validation |
| Stack with Replacement | O(n) | O(n) | Memory-efficient solution |
| Maximum Nesting Depth | O(n) | O(1) | Finding level of nesting |
| Minimum Insertions | O(n) | O(n) | Determining corrections needed |
