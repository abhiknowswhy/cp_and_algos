# Design a Stack that Supports getMin() in O(1) Time

## Problem Description

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time (O(1)).

Implement the MinStack class with the following operations:
- `push(x)` - Push element x onto the stack
- `pop()` - Remove the element on top of the stack
- `top()` - Get the top element of the stack
- `getMin()` - Retrieve the minimum element in the stack

All operations should run in O(1) time complexity.

## Approaches to Solve the Problem

### 1. Auxiliary Stack Approach

#### Intuition

- Maintain two stacks: one for the actual elements and one for tracking minimums
- For each push operation, push the element to the main stack
- For the min stack, push the minimum of the new element and the current minimum
- This ensures the top of the min stack always has the current minimum

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> s;       // Main stack for elements
    stack<int> minStack; // Auxiliary stack for minimums
    
public:
    // Constructor
    MinStack() {
        // Minimum stack is initialized with INT_MAX
        minStack.push(INT_MAX);
    }
    
    // Push element onto the stack
    void push(int val) {
        s.push(val);
        // Push the minimum of new element and current minimum
        minStack.push(min(val, minStack.top()));
    }
    
    // Remove element from the top of the stack
    void pop() {
        s.pop();
        minStack.pop();
    }
    
    // Get the top element of the stack
    int top() {
        return s.top();
    }
    
    // Get the minimum element in the stack
    int getMin() {
        return minStack.top();
    }
};

// Example usage
int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -3
    minStack.pop();
    cout << "Top: " << minStack.top() << endl;       // Returns 0
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -2
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(1) for all operations (push, pop, top, getMin)
- Space Complexity: O(n) where n is the number of elements in the stack

### 2. Pairs Approach

#### Intuition

- Instead of using an auxiliary stack, store pairs of (value, current_min) in a single stack
- For each push operation, calculate the new minimum and store it along with the value
- This reduces the memory overhead by using a single stack

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<pair<int, int>> s; // Stack of (value, current_min) pairs
    
public:
    // Constructor
    MinStack() {
    }
    
    // Push element onto the stack
    void push(int val) {
        if (s.empty()) {
            s.push({val, val});
        } else {
            // Store the value and the minimum between new value and current minimum
            s.push({val, min(val, s.top().second)});
        }
    }
    
    // Remove element from the top of the stack
    void pop() {
        s.pop();
    }
    
    // Get the top element of the stack
    int top() {
        return s.top().first;
    }
    
    // Get the minimum element in the stack
    int getMin() {
        return s.top().second;
    }
};

// Example usage
int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -3
    minStack.pop();
    cout << "Top: " << minStack.top() << endl;       // Returns 0
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -2
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(1) for all operations (push, pop, top, getMin)
- Space Complexity: O(n) where n is the number of elements in the stack

### 3. Space-Optimized Approach

#### Intuition

- Only push a value onto the min stack when it's smaller than or equal to the current minimum
- When popping, check if the popped value is the current minimum; if so, also pop from the min stack
- This reduces the average space used by the min stack

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<int> s;       // Main stack for elements
    stack<int> minStack; // Stack for minimums
    
public:
    // Constructor
    MinStack() {
    }
    
    // Push element onto the stack
    void push(int val) {
        s.push(val);
        // Only push to min stack if empty or value is smaller/equal to current min
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    // Remove element from the top of the stack
    void pop() {
        // If top of main stack is the current minimum, also pop from min stack
        if (s.top() == minStack.top()) {
            minStack.pop();
        }
        s.pop();
    }
    
    // Get the top element of the stack
    int top() {
        return s.top();
    }
    
    // Get the minimum element in the stack
    int getMin() {
        return minStack.top();
    }
};

// Example usage
int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -3
    minStack.pop();
    cout << "Top: " << minStack.top() << endl;       // Returns 0
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -2
    
    return 0;
}
```

### 4. Mathematical Tricks Approach

#### Intuition

- Use a mathematical formula to encode the current minimum in the stack values
- Push modified values to the stack that encode information about the minimum
- This approach uses only a single stack and has constant space overhead

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MinStack {
private:
    stack<long long> s; // Stack for modified elements
    long long minVal;   // Current minimum
    
public:
    // Constructor
    MinStack() {
        minVal = INT_MAX;
    }
    
    // Push element onto the stack
    void push(int val) {
        // If stack is empty, push value and update minVal
        if (s.empty()) {
            s.push(0);  // Push 0 as the difference
            minVal = val;
        } else {
            // Push the difference between value and minimum
            long long diff = (long long)val - minVal;
            s.push(diff);
            
            // If difference is negative, update minVal
            if (diff < 0) {
                minVal = val;  // New minimum
            }
        }
    }
    
    // Remove element from the top of the stack
    void pop() {
        if (s.empty()) return;
        
        long long diff = s.top();
        s.pop();
        
        // If difference is negative, update minVal
        if (diff < 0) {
            minVal = minVal - diff;  // Restore previous minimum
        }
    }
    
    // Get the top element of the stack
    int top() {
        long long diff = s.top();
        
        // If difference is negative, top is minVal
        // Otherwise, top is minVal + diff
        return (diff < 0) ? minVal : (int)(minVal + diff);
    }
    
    // Get the minimum element in the stack
    int getMin() {
        return (int)minVal;
    }
};

// Example usage
int main() {
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -3
    minStack.pop();
    cout << "Top: " << minStack.top() << endl;       // Returns 0
    cout << "Minimum: " << minStack.getMin() << endl; // Returns -2
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 155: Min Stack](https://leetcode.com/problems/min-stack/)
2. [LeetCode 716: Max Stack](https://leetcode.com/problems/max-stack/)
3. [LeetCode 232: Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/) (Similar concept of implementing a data structure with specific operations)

## Applications

1. **Stock Price Tracking**: Track minimum stock price in a trading session
2. **Resource Allocation**: Track minimum available resources in systems
3. **Load Balancing**: Monitor minimum load servers in a distributed system
4. **Browser History**: Track minimum page load times for performance analysis

## Summary

| Approach | Space Complexity | Implementation Complexity | Best For |
| --- | --- | --- | --- |
| Auxiliary Stack | O(n) | Simple | Clarity and reliability |
| Pairs Approach | O(n) | Simple | Single-stack implementation |
| Space-Optimized | O(n) worst-case, often less | Medium | Memory-constrained environments |
| Mathematical Tricks | O(n) with constant overhead | Complex | Minimizing memory overhead |
