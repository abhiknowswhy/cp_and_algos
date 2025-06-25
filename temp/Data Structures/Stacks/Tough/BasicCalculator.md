# Basic Calculator

## Problem Description

The Basic Calculator problem involves implementing a calculator that can evaluate mathematical expressions with various operations. There are several variations of this problem:

1. **Basic Calculator I**: Evaluate expressions with integers, plus (+), minus (-), and parentheses.
2. **Basic Calculator II**: Evaluate expressions with integers, plus (+), minus (-), multiply (*), divide (/), and no parentheses.
3. **Basic Calculator III**: Evaluate expressions with integers, plus (+), minus (-), multiply (*), divide (/), and parentheses.

## Approaches to Solve the Problem

### 1. Stack-based Approach for Basic Calculator I

#### Intuition

We can use a stack to handle parentheses and evaluate the expression from left to right:
- Process the expression character by character
- Use a stack to keep track of the results within parentheses
- When we encounter a closing parenthesis, we pop and calculate the result inside those parentheses

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int calculate(string s) {
    stack<int> st; // Stack to store intermediate results and signs
    int result = 0; // Current result
    int sign = 1;   // Current sign, 1 means positive, -1 means negative
    int n = s.length();
    
    for (int i = 0; i < n; i++) {
        char c = s[i];
        
        if (isdigit(c)) {
            // Extract the complete number
            int num = 0;
            while (i < n && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--; // Adjust index since for loop will increment it
            
            // Apply the sign and add to result
            result += sign * num;
        } 
        else if (c == '+') {
            sign = 1;
        } 
        else if (c == '-') {
            sign = -1;
        } 
        else if (c == '(') {
            // Push current result and sign onto stack before starting a new evaluation
            st.push(result);
            st.push(sign);
            
            // Reset result and sign for new sub-expression
            result = 0;
            sign = 1;
        } 
        else if (c == ')') {
            // Retrieve sign and previous result from stack
            int prevSign = st.top(); st.pop();
            int prevResult = st.top(); st.pop();
            
            // Apply the sign to the current result and add to previous result
            result = prevResult + prevSign * result;
        }
        // Skip spaces
    }
    
    return result;
}
```

### 2. Stack-based Approach for Basic Calculator II

#### Intuition

- For expressions without parentheses but with multiplication and division
- Process the expression left to right
- Handle operator precedence by deferring addition and subtraction
- Perform multiplication and division immediately

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int calculate2(string s) {
    stack<int> st;
    int num = 0;
    char operation = '+'; // Default first operation
    int n = s.length();
    
    for (int i = 0; i < n; i++) {
        char c = s[i];
        
        if (isdigit(c)) {
            // Extract the complete number
            num = num * 10 + (c - '0');
        }
        
        // When we hit an operator or the end of the expression, process the previous operation
        if ((!isdigit(c) && c != ' ') || i == n - 1) {
            if (operation == '+') {
                st.push(num);
            } 
            else if (operation == '-') {
                st.push(-num);
            } 
            else if (operation == '*') {
                int top = st.top();
                st.pop();
                st.push(top * num);
            } 
            else if (operation == '/') {
                int top = st.top();
                st.pop();
                st.push(top / num);
            }
            
            operation = c;
            num = 0;
        }
    }
    
    // Sum up all values in the stack to get the final result
    int result = 0;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    
    return result;
}
```

### 3. Recursive Approach for Basic Calculator III

#### Intuition

- Combine techniques from previous calculators
- Use recursion to handle nested parentheses
- Handle operator precedence for all operations

#### Implementation

```cpp
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class BasicCalculator {
private:
    // Helper function to determine operator precedence
    int getPrecedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }
    
    // Apply operation
    int applyOp(int a, int b, char op) {
        switch(op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }
    
    // Helper function to process a substring
    pair<int, int> processExpression(const string& s, int index) {
        stack<int> values;     // Stack to store values
        stack<char> ops;       // Stack to store operators
        int num = 0;
        bool hasNum = false;
        
        for (int i = index; i < s.length(); i++) {
            char c = s[i];
            
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
                hasNum = true;
            }
            else if (c == '(') {
                // Process the sub-expression recursively
                auto [val, nextIndex] = processExpression(s, i + 1);
                values.push(val);
                i = nextIndex;  // Skip the already processed substring
                hasNum = false;
            }
            else if (c == ')') {
                // End of current sub-expression
                if (hasNum) {
                    values.push(num);
                    num = 0;
                    hasNum = false;
                }
                
                // Process remaining operators in the current scope
                while (!ops.empty()) {
                    char op = ops.top(); ops.pop();
                    int val2 = values.top(); values.pop();
                    int val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op));
                }
                
                return {values.top(), i};
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                // Process the current number before the operator
                if (hasNum) {
                    values.push(num);
                    num = 0;
                    hasNum = false;
                }
                
                // Process operators with higher precedence
                while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(c)) {
                    char op = ops.top(); ops.pop();
                    int val2 = values.top(); values.pop();
                    int val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op));
                }
                
                ops.push(c);
            }
            // Skip spaces
        }
        
        // Process the last number
        if (hasNum) {
            values.push(num);
        }
        
        // Process any remaining operators
        while (!ops.empty()) {
            char op = ops.top(); ops.pop();
            int val2 = values.top(); values.pop();
            int val1 = values.top(); values.pop();
            values.push(applyOp(val1, val2, op));
        }
        
        return {values.top(), s.length() - 1};
    }

public:
    int calculate(string s) {
        return processExpression(s, 0).first;
    }
};
```

### 4. Two-Stack Approach for Basic Calculator III

#### Intuition

- Use two stacks: one for values and one for operators
- Process the expression left to right
- Handle parentheses and operator precedence

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

int calculate3(string s) {
    stack<int> values;
    stack<char> ops;
    unordered_map<char, int> precedence = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2}
    };
    
    int i = 0;
    while (i < s.length()) {
        if (s[i] == ' ') {
            i++;
            continue;
        }
        
        if (isdigit(s[i])) {
            int num = 0;
            while (i < s.length() && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            values.push(num);
            continue;
        }
        
        if (s[i] == '(') {
            ops.push(s[i]);
        }
        else if (s[i] == ')') {
            while (ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                
                if (op == '+') values.push(val1 + val2);
                else if (op == '-') values.push(val1 - val2);
                else if (op == '*') values.push(val1 * val2);
                else if (op == '/') values.push(val1 / val2);
            }
            ops.pop(); // Remove '('
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            // Process operators with higher or equal precedence
            while (!ops.empty() && ops.top() != '(' && 
                   precedence[ops.top()] >= precedence[s[i]]) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                
                if (op == '+') values.push(val1 + val2);
                else if (op == '-') values.push(val1 - val2);
                else if (op == '*') values.push(val1 * val2);
                else if (op == '/') values.push(val1 / val2);
            }
            ops.push(s[i]);
        }
        
        i++;
    }
    
    // Process any remaining operators
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        
        if (op == '+') values.push(val1 + val2);
        else if (op == '-') values.push(val1 - val2);
        else if (op == '*') values.push(val1 * val2);
        else if (op == '/') values.push(val1 / val2);
    }
    
    return values.top();
}
```

## Complexity Analysis

### Basic Calculator I
- **Time Complexity**: O(n), where n is the length of the string. We process each character once.
- **Space Complexity**: O(n), in the worst case we might push all characters onto the stack.

### Basic Calculator II
- **Time Complexity**: O(n), where n is the length of the string.
- **Space Complexity**: O(n), as we might need to store all numbers in the stack.

### Basic Calculator III (Recursive Approach)
- **Time Complexity**: O(n), where n is the length of the string.
- **Space Complexity**: O(n), due to recursion stack and the stacks used for values and operators.

### Basic Calculator III (Two-Stack Approach)
- **Time Complexity**: O(n), where n is the length of the string.
- **Space Complexity**: O(n), for the two stacks.

## Step-by-Step Execution

Let's trace through the Basic Calculator I implementation with an example:

Input: `"(1+(4+5+2)-3)+(6+8)"`

1. Process '(':
   - Push result (0) and sign (1) onto stack
   - Reset result = 0, sign = 1

2. Process '1':
   - Update result = 0 + 1 × 1 = 1

3. Process '+':
   - Update sign = 1

4. Process '(':
   - Push result (1) and sign (1) onto stack
   - Reset result = 0, sign = 1

5. Process '4':
   - Update result = 0 + 1 × 4 = 4

6. Process '+':
   - Update sign = 1

7. Process '5':
   - Update result = 4 + 1 × 5 = 9

8. Process '+':
   - Update sign = 1

9. Process '2':
   - Update result = 9 + 1 × 2 = 11

10. Process ')':
    - Pop sign (1) and previous result (1)
    - Update result = 1 + 1 × 11 = 12

11. Process '-':
    - Update sign = -1

12. Process '3':
    - Update result = 12 + (-1) × 3 = 9

13. Process ')':
    - Pop sign (1) and previous result (0)
    - Update result = 0 + 1 × 9 = 9

14. Process '+':
    - Update sign = 1

15. Process '(':
    - Push result (9) and sign (1) onto stack
    - Reset result = 0, sign = 1

16. Process '6':
    - Update result = 0 + 1 × 6 = 6

17. Process '+':
    - Update sign = 1

18. Process '8':
    - Update result = 6 + 1 × 8 = 14

19. Process ')':
    - Pop sign (1) and previous result (9)
    - Update result = 9 + 1 × 14 = 23

Final result: `23`

## Related LeetCode Problems

- [LeetCode 224: Basic Calculator](https://leetcode.com/problems/basic-calculator/)
- [LeetCode 227: Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)
- [LeetCode 772: Basic Calculator III](https://leetcode.com/problems/basic-calculator-iii/)
- [LeetCode 770: Basic Calculator IV](https://leetcode.com/problems/basic-calculator-iv/)
- [LeetCode 150: Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
- [LeetCode 71: Simplify Path](https://leetcode.com/problems/simplify-path/)

## Applications

- **Programming Language Compilers**: Parsing and evaluating mathematical expressions
- **Spreadsheet Applications**: Calculating cell formulas in applications like Excel
- **Scientific Calculators**: Handling complex mathematical expressions
- **Computer Algebra Systems**: Parsing and manipulating symbolic expressions
- **Expression Evaluators in Web Applications**: Evaluating user input formulas

## Summary

| Approach | Time Complexity | Space Complexity | Pros | Cons | Best For |
|----------|-----------------|------------------|------|------|----------|
| Stack-based (Calculator I) | O(n) | O(n) | Simple, handles basic operations | Limited to +/- operations | Expressions with parentheses |
| Stack-based (Calculator II) | O(n) | O(n) | Handles operator precedence | No parentheses support | Expressions with all operations but no parentheses |
| Recursive (Calculator III) | O(n) | O(n) | Clean approach for nested expressions | Deeper call stack for complex expressions | Complete expressions with all operations |
| Two-Stack (Calculator III) | O(n) | O(n) | Handles all operations and parentheses | More complex implementation | Complete expressions with all operations |

The choice of approach depends on the specific requirements of the calculator:
- Use the simple stack approach for basic addition and subtraction with parentheses
- Use the stack-based approach with operator precedence for expressions with all operations but no parentheses
- Use the recursive or two-stack approach for complete expressions with all operations and parentheses

For production-level calculator implementations, the shunting yard algorithm is often used as an efficient way to parse and evaluate infix expressions.
