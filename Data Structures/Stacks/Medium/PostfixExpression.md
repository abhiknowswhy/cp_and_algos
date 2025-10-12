# Evaluate a Postfix Expression (Reverse Polish Notation)

## Problem Description

Evaluate an arithmetic expression in Reverse Polish Notation (RPN), also known as postfix notation. In postfix notation, operators follow their operands. For example, the infix expression "3 + 4" is written as "3 4 +" in postfix notation.

Valid operators include +, -, *, and /. Each operand can be an integer or another expression.

## Approaches to Solve the Problem

### 1. Stack-based Evaluation

#### Intuition

In postfix notation, when we encounter an operand, we push it onto the stack. When we encounter an operator, we pop the top two operands, perform the operation, and push the result back onto the stack.

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            // If token is an operator
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Pop the top two operands
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                
                // Perform the operation
                if (token == "+") {
                    st.push(a + b);
                } else if (token == "-") {
                    st.push(a - b);
                } else if (token == "*") {
                    st.push(a * b);
                } else if (token == "/") {
                    st.push(a / b);
                }
            }
            // If token is an operand
            else {
                st.push(stoi(token));
            }
        }
        
        // The final result will be the only item left on the stack
        return st.top();
    }
};

// Example usage
int main() {
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    
    Solution sol;
    cout << "Example 1: " << sol.evalRPN(tokens1) << endl; // ((2 + 1) * 3) = 9
    cout << "Example 2: " << sol.evalRPN(tokens2) << endl; // (4 + (13 / 5)) = 6
    cout << "Example 3: " << sol.evalRPN(tokens3) << endl; // Complex expression = 22
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the number of tokens
- Space Complexity: O(n) in the worst case for the stack

### 2. Postfix to Infix Conversion

#### Intuition

Convert a postfix expression to infix notation for better human readability.

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

string postfixToInfix(vector<string>& tokens) {
    stack<string> st;
    
    for (const string& token : tokens) {
        // If token is an operator
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            
            // Create infix expression with parentheses for precedence
            string infix = "(" + a + " " + token + " " + b + ")";
            st.push(infix);
        }
        // If token is an operand
        else {
            st.push(token);
        }
    }
    
    return st.top();
}

int main() {
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    cout << "Postfix: 2 1 + 3 *\nInfix: " << postfixToInfix(tokens) << endl;
    
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    cout << "Postfix: 4 13 5 / +\nInfix: " << postfixToInfix(tokens2) << endl;
    
    return 0;
}
```

### 3. Postfix to Prefix Conversion

#### Intuition

Convert a postfix expression to prefix notation, where operators come before their operands.

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

string postfixToPrefix(vector<string>& tokens) {
    stack<string> st;
    
    for (const string& token : tokens) {
        // If token is an operator
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            
            // Create prefix expression
            string prefix = token + " " + a + " " + b;
            st.push(prefix);
        }
        // If token is an operand
        else {
            st.push(token);
        }
    }
    
    return st.top();
}

int main() {
    vector<string> tokens = {"2", "1", "+", "3", "*"};
    cout << "Postfix: 2 1 + 3 *\nPrefix: " << postfixToPrefix(tokens) << endl;
    
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    cout << "Postfix: 4 13 5 / +\nPrefix: " << postfixToPrefix(tokens2) << endl;
    
    return 0;
}
```

### 4. Infix to Postfix Conversion

#### Intuition

Convert an infix expression to postfix notation, which is needed for expression evaluation.

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype> // For isdigit
using namespace std;

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";
    
    for (int i = 0; i < infix.length(); i++) {
        // If character is an operand, add to output
        if (isalnum(infix[i])) {
            postfix += infix[i];
            // Add space after each operand for readability
            postfix += ' ';
        }
        // If character is '(', push to stack
        else if (infix[i] == '(') {
            st.push(infix[i]);
        }
        // If character is ')', pop and add to output until '(' is found
        else if (infix[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.pop(); // Remove '(' from stack
        }
        // If character is an operator
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(infix[i])) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(infix[i]);
        }
    }
    
    // Pop remaining operators from stack
    while (!st.empty()) {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }
    
    return postfix;
}

int main() {
    string infix = "a+b*(c-d)/e";
    cout << "Infix: " << infix << "\nPostfix: " << infixToPostfix(infix) << endl;
    
    infix = "(3+4)*5";
    cout << "Infix: " << infix << "\nPostfix: " << infixToPostfix(infix) << endl;
    
    return 0;
}
```

### 5. Prefix to Postfix Conversion

#### Intuition

Convert a prefix expression to postfix notation.

#### Implementation

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <cctype> // For isalnum
#include <algorithm> // For reverse
using namespace std;

string prefixToPostfix(string prefix) {
    stack<string> st;
    
    // Reverse the prefix expression
    reverse(prefix.begin(), prefix.end());
    
    for (int i = 0; i < prefix.length(); i++) {
        if (isalnum(prefix[i])) {
            string operand(1, prefix[i]);
            st.push(operand);
        }
        else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/') {
            string op1 = st.top(); st.pop();
            string op2 = st.top(); st.pop();
            
            // Form the postfix expression
            string temp = op1 + op2 + prefix[i];
            st.push(temp);
        }
    }
    
    return st.top();
}

int main() {
    string prefix = "*+AB-CD";
    cout << "Prefix: " << prefix << "\nPostfix: " << prefixToPostfix(prefix) << endl;
    
    prefix = "+*ABC";
    cout << "Prefix: " << prefix << "\nPostfix: " << prefixToPostfix(prefix) << endl;
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 150: Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
2. [LeetCode 224: Basic Calculator](https://leetcode.com/problems/basic-calculator/)
3. [LeetCode 227: Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)
4. [LeetCode 772: Basic Calculator III](https://leetcode.com/problems/basic-calculator-iii/)

## Applications

1. **Compiler Design**: Used in syntax tree construction
2. **Calculator Applications**: Implementing arithmetic operations
3. **Expression Evaluation**: In programming language interpreters
4. **Symbolic Mathematics**: Computer algebra systems

## Summary

| Operation | Time Complexity | Space Complexity | Notes |
| --- | --- | --- | --- |
| Evaluate Postfix | O(n) | O(n) | Simple stack-based approach |
| Postfix to Infix | O(n) | O(n) | Adds parentheses for precedence |
| Postfix to Prefix | O(n) | O(n) | Changes operator position |
| Infix to Postfix | O(n) | O(n) | Requires operator precedence |
| Prefix to Postfix | O(n) | O(n) | Uses reverse iteration |
