# Sort a Stack Using Recursion

## Problem Description

Sort a stack in ascending order (with the smallest elements on top) using only recursive functions. The only stack operations allowed are:
- `push(x)`: To push an element onto the stack
- `pop()`: To pop an element from the stack
- `peek()` or `top()`: To view the top element of the stack
- `isEmpty()`: To check if the stack is empty

## Approaches to Solve the Problem

### 1. Recursive Sorting with Helper Function

#### Intuition

The idea is to use recursion to sort the stack one element at a time:
1. Pop an element from the stack
2. Sort the remaining elements recursively
3. Insert the popped element in its correct sorted position in the stack

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

// Function to insert an element in sorted order in a sorted stack
void sortedInsert(stack<int> &s, int x) {
    // Base case: if stack is empty or current element is greater than top,
    // push the element
    if (s.empty() || x > s.top()) {
        s.push(x);
        return;
    }
    
    // If x is smaller than top, remove top and recur
    int temp = s.top();
    s.pop();
    
    // Recursively insert x in the smaller stack
    sortedInsert(s, x);
    
    // Push the removed item back
    s.push(temp);
}

// Function to sort a stack using recursion
void sortStack(stack<int> &s) {
    // Base case: stack is sorted if it's empty or has only one element
    if (s.empty()) {
        return;
    }
    
    // Remove the top element
    int x = s.top();
    s.pop();
    
    // Sort the remaining stack recursively
    sortStack(s);
    
    // Insert the removed element in sorted order
    sortedInsert(s, x);
}

// Utility function to print stack elements
void printStack(stack<int> s) {
    if (s.empty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    
    cout << "Stack contents (top to bottom): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    stack<int> s;
    s.push(30);
    s.push(-5);
    s.push(18);
    s.push(14);
    s.push(-3);
    
    cout << "Original ";
    printStack(s);
    
    sortStack(s);
    
    cout << "Sorted ";
    printStack(s);
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n²), where n is the number of elements in the stack
- Space Complexity: O(n) for the recursion call stack

### 2. Detailed Step-by-Step Execution

Let's trace through an example with a stack containing [30, -5, 18, 14, -3] (with -3 at the top):

1. Call `sortStack([30, -5, 18, 14, -3])`
   - Pop -3, stack becomes [30, -5, 18, 14]
   - Call `sortStack([30, -5, 18, 14])`
     - Pop 14, stack becomes [30, -5, 18]
     - Call `sortStack([30, -5, 18])`
       - Pop 18, stack becomes [30, -5]
       - Call `sortStack([30, -5])`
         - Pop -5, stack becomes [30]
         - Call `sortStack([30])`
           - Pop 30, stack becomes []
           - Call `sortStack([])`
             - Stack is empty, return
           - Call `sortedInsert([], 30)`
             - Stack is empty, push 30, stack becomes [30]
         - Call `sortedInsert([30], -5)`
           - -5 < 30, so pop 30, stack becomes []
           - Call `sortedInsert([], -5)`
             - Stack is empty, push -5, stack becomes [-5]
           - Push 30, stack becomes [-5, 30]
       - Call `sortedInsert([-5, 30], 18)`
         - 18 > -5, but 18 < 30, so pop -5, stack becomes [30]
         - Call `sortedInsert([30], 18)`
           - 18 < 30, so pop 30, stack becomes []
           - Call `sortedInsert([], 18)`
             - Stack is empty, push 18, stack becomes [18]
           - Push 30, stack becomes [18, 30]
         - Push -5, stack becomes [-5, 18, 30]
     - Call `sortedInsert([-5, 18, 30], 14)`
       - 14 > -5, continue
       - 14 < 18, so pop -5, stack becomes [18, 30]
       - Call `sortedInsert([18, 30], 14)`
         - 14 < 18, so pop 18, stack becomes [30]
         - Call `sortedInsert([30], 14)`
           - 14 < 30, so pop 30, stack becomes []
           - Call `sortedInsert([], 14)`
             - Stack is empty, push 14, stack becomes [14]
           - Push 30, stack becomes [14, 30]
         - Push 18, stack becomes [14, 18, 30]
       - Push -5, stack becomes [-5, 14, 18, 30]
   - Call `sortedInsert([-5, 14, 18, 30], -3)`
     - -3 > -5, so pop -5, stack becomes [14, 18, 30]
     - Call `sortedInsert([14, 18, 30], -3)`
       - -3 < 14, so pop 14, stack becomes [18, 30]
       - Call `sortedInsert([18, 30], -3)`
         - -3 < 18, so pop 18, stack becomes [30]
         - Call `sortedInsert([30], -3)`
           - -3 < 30, so pop 30, stack becomes []
           - Call `sortedInsert([], -3)`
             - Stack is empty, push -3, stack becomes [-3]
           - Push 30, stack becomes [-3, 30]
         - Push 18, stack becomes [-3, 18, 30]
       - Push 14, stack becomes [-3, 14, 18, 30]
     - Push -5, stack becomes [-5, -3, 14, 18, 30]

Final sorted stack: [-5, -3, 14, 18, 30] (with -5 at the top)

### 3. Visual Representation of the Algorithm

For stack [30, -5, 18, 14, -3]:

```
Original Stack (top to bottom):
-3
14
18
-5
30

Step 1: Pop -3, sort the remaining stack [30, -5, 18, 14], and insert -3
    Step 1.1: Pop 14, sort [30, -5, 18], and insert 14
        Step 1.1.1: Pop 18, sort [30, -5], and insert 18
            Step 1.1.1.1: Pop -5, sort [30], and insert -5
                Step 1.1.1.1.1: Pop 30, sort [], and insert 30
                    Empty stack: []
                    Insert 30: [30]
                Insert -5: [-5, 30]
            Insert 18: [-5, 18, 30]
        Insert 14: [-5, 14, 18, 30]
    Insert -3: [-5, -3, 14, 18, 30]

Sorted Stack (top to bottom):
-5
-3
14
18
30
```

### 4. Alternative Implementation with Temporary Stack

While not a pure recursive solution, we can use a temporary stack to sort elements:

```cpp
#include <iostream>
#include <stack>
using namespace std;

void sortStackWithTemp(stack<int> &input) {
    stack<int> tmpStack;
    
    while (!input.empty()) {
        // Pop an element from the input stack
        int temp = input.top();
        input.pop();
        
        // While temporary stack is not empty and top of temp stack is greater than temp
        while (!tmpStack.empty() && tmpStack.top() > temp) {
            // Pop from temporary stack and push it to the input stack
            input.push(tmpStack.top());
            tmpStack.pop();
        }
        
        // Push temp in temporary stack
        tmpStack.push(temp);
    }
    
    // Copy the elements from tmpStack back to input stack
    while (!tmpStack.empty()) {
        input.push(tmpStack.top());
        tmpStack.pop();
    }
}

int main() {
    stack<int> s;
    s.push(30);
    s.push(-5);
    s.push(18);
    s.push(14);
    s.push(-3);
    
    cout << "Original stack (top to bottom): ";
    // Create a copy for display
    stack<int> display = s;
    while (!display.empty()) {
        cout << display.top() << " ";
        display.pop();
    }
    cout << endl;
    
    sortStackWithTemp(s);
    
    cout << "Sorted stack (top to bottom): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 946: Validate Stack Sequences](https://leetcode.com/problems/validate-stack-sequences/)
2. [LeetCode 1019: Next Greater Node In Linked List](https://leetcode.com/problems/next-greater-node-in-linked-list/) (Uses the concept of maintaining a sorted stack)
3. [LeetCode 155: Min Stack](https://leetcode.com/problems/min-stack/) (Similar concept of maintaining stack order)

## Applications

1. **Expression Evaluation**: Sorting operators based on precedence
2. **Priority Management**: Maintaining tasks in order of priority
3. **Backtracking Algorithms**: Maintaining states in sorted order
4. **Memory Management**: Organizing memory blocks by size

## Analysis of Recursive Functions

The recursive sorting of a stack involves two key operations:

### 1. sortedInsert(stack, x)

This function inserts an element `x` into an already sorted stack such that the stack remains sorted:
- If the stack is empty or `x` is greater than the top element, push `x`
- Otherwise, temporarily remove the top element, recursively insert `x` in the remaining stack, then push the removed element back

### 2. sortStack(stack)

This function sorts the entire stack:
- If the stack is empty, it's already sorted
- Otherwise, remove the top element, recursively sort the rest of the stack, then insert the removed element in its correct sorted position

## Optimizations and Variations

### 1. Sort a Stack in Descending Order

To sort in descending order (largest elements on top), we modify the `sortedInsert` function:

```cpp
void sortedInsertDescending(stack<int> &s, int x) {
    if (s.empty() || x < s.top()) {
        s.push(x);
        return;
    }
    
    int temp = s.top();
    s.pop();
    sortedInsertDescending(s, x);
    s.push(temp);
}

void sortStackDescending(stack<int> &s) {
    if (s.empty()) {
        return;
    }
    
    int x = s.top();
    s.pop();
    
    sortStackDescending(s);
    sortedInsertDescending(s, x);
}
```

### 2. Sort a Stack Using Recursion Without Helper Function

While less efficient, we can sort without a separate helper function:

```cpp
void sortStackSimple(stack<int> &s) {
    if (!s.empty()) {
        int x = s.top();
        s.pop();
        
        sortStackSimple(s);
        
        stack<int> temp;
        while (!s.empty() && s.top() < x) {
            temp.push(s.top());
            s.pop();
        }
        
        s.push(x);
        
        while (!temp.empty()) {
            s.push(temp.top());
            temp.pop();
        }
    }
}
```

## Summary

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| Recursive with Helper | O(n²) | O(n) | Pure recursive solution with helper function |
| Recursive Step-by-Step | O(n²) | O(n) | Same algorithm with detailed execution |
| Using Temporary Stack | O(n²) | O(n) | Iterative solution with temporary storage |
| Without Helper Function | O(n²) | O(n) | Less efficient recursive solution |
