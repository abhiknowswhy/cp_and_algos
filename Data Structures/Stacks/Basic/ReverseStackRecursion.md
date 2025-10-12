# Reverse a Stack Using Recursion

## Problem Description

Reverse a stack using recursion without using any additional data structure. The only functions allowed on the stack are:
- `push(x)`: To push an element onto the stack.
- `pop()`: To pop an element from the stack.
- `isEmpty()`: To check if the stack is empty.

## Approaches to Solve the Problem

### 1. Using Recursion with Helper Function

#### Intuition

To reverse a stack using recursion, we need two key functions:
1. A function to insert an element at the bottom of the stack
2. A recursive function that pops elements one by one, reverses the rest of the stack, and then inserts the popped elements at the bottom

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

// Function to insert an element at the bottom of the stack
void insertAtBottom(stack<int> &s, int x) {
    // If stack is empty, push the element
    if (s.empty()) {
        s.push(x);
        return;
    }
    
    // Pop all elements, insert x at bottom, then push all back
    int temp = s.top();
    s.pop();
    insertAtBottom(s, x);
    s.push(temp);
}

// Function to reverse the stack using recursion
void reverseStack(stack<int> &s) {
    // Base case: if stack is empty
    if (s.empty()) {
        return;
    }
    
    // Pop the top element
    int x = s.top();
    s.pop();
    
    // Reverse the remaining stack
    reverseStack(s);
    
    // Insert the popped element at the bottom
    insertAtBottom(s, x);
}

// Utility function to print the stack
void printStack(stack<int> s) {
    if (s.empty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    
    cout << "Stack contents: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    
    cout << "Original ";
    printStack(s);
    
    reverseStack(s);
    
    cout << "Reversed ";
    printStack(s);
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n²), where n is the number of elements in the stack. Each insertAtBottom operation is O(n) and it's called for n elements.
- Space Complexity: O(n) for the recursion call stack

### 2. Detailed Step-by-Step Execution

To better understand the recursion process, let's trace through an example with a stack containing [1, 2, 3, 4] (4 at the top):

1. Call `reverseStack([1, 2, 3, 4])`
   - Pop 4, stack becomes [1, 2, 3]
   - Call `reverseStack([1, 2, 3])`
     - Pop 3, stack becomes [1, 2]
     - Call `reverseStack([1, 2])`
       - Pop 2, stack becomes [1]
       - Call `reverseStack([1])`
         - Pop 1, stack becomes []
         - Call `reverseStack([])`
           - Stack is empty, return
         - Call `insertAtBottom([], 1)`
           - Stack is empty, push 1, stack becomes [1]
       - Call `insertAtBottom([1], 2)`
         - Pop 1, stack becomes []
         - Call `insertAtBottom([], 2)`
           - Stack is empty, push 2, stack becomes [2]
         - Push 1, stack becomes [2, 1]
     - Call `insertAtBottom([2, 1], 3)`
       - Pop 1, stack becomes [2]
       - Call `insertAtBottom([2], 3)`
         - Pop 2, stack becomes []
         - Call `insertAtBottom([], 3)`
           - Stack is empty, push 3, stack becomes [3]
         - Push 2, stack becomes [3, 2]
       - Push 1, stack becomes [3, 2, 1]
   - Call `insertAtBottom([3, 2, 1], 4)`
     - Pop 1, stack becomes [3, 2]
     - Call `insertAtBottom([3, 2], 4)`
       - Pop 2, stack becomes [3]
       - Call `insertAtBottom([3], 4)`
         - Pop 3, stack becomes []
         - Call `insertAtBottom([], 4)`
           - Stack is empty, push 4, stack becomes [4]
         - Push 3, stack becomes [4, 3]
       - Push 2, stack becomes [4, 3, 2]
     - Push 1, stack becomes [4, 3, 2, 1]

Final stack: [4, 3, 2, 1] (1 at the top)

### 3. Visual Representation of the Algorithm

For stack [1, 2, 3, 4]:

```
Original Stack:
top -> 4
       3
       2
       1

Step 1: Pop 4 and reverse [1, 2, 3]
    Step 1.1: Pop 3 and reverse [1, 2]
        Step 1.1.1: Pop 2 and reverse [1]
            Step 1.1.1.1: Pop 1 and reverse []
                Empty stack: []
                Insert 1 at bottom: [1]
            Insert 2 at bottom: [2, 1]
        Insert 3 at bottom: [3, 2, 1]
    Insert 4 at bottom: [4, 3, 2, 1]

Reversed Stack:
top -> 1
       2
       3
       4
```

## Related LeetCode Problems

1. [LeetCode 1047: Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)
2. [LeetCode 844: Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/)

## Applications

1. **Recursive function processing**: In interpreters where function call states are maintained in a stack
2. **Expression parsing**: Reversing the order of expressions for evaluation
3. **Undoing operations**: In systems with undo functionality
4. **Browser history**: Reversing navigation history

## Recursive Stack Operations

When working with recursion and stacks, it's important to understand the pattern of recursive calls:

### 1. insertAtBottom(stack, x)

This function inserts an element at the bottom of the stack:
- If the stack is empty, push the element
- Otherwise:
  1. Save the top element
  2. Pop the top element
  3. Call insertAtBottom recursively to insert x at the bottom of the smaller stack
  4. Push back the saved element

### 2. reverseStack(stack)

This function reverses the entire stack:
- If the stack is empty, return
- Otherwise:
  1. Pop the top element
  2. Reverse the rest of the stack recursively
  3. Insert the popped element at the bottom of the reversed stack

## Extensions and Variations

### 1. Reverse Every K Elements in a Stack

```cpp
#include <iostream>
#include <stack>
using namespace std;

// Function to insert at bottom
void insertAtBottom(stack<int> &s, int x) {
    if (s.empty()) {
        s.push(x);
        return;
    }
    
    int temp = s.top();
    s.pop();
    insertAtBottom(s, x);
    s.push(temp);
}

// Function to reverse first k elements of the stack
void reverseFirstK(stack<int> &s, int k) {
    if (k == 0) {
        return;
    }
    
    // Pop the top element
    int x = s.top();
    s.pop();
    
    // Reverse first (k-1) elements
    reverseFirstK(s, k - 1);
    
    // Insert the popped element at the bottom
    insertAtBottom(s, x);
}

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    
    int k = 3; // Reverse first 3 elements
    
    reverseFirstK(s, k);
    
    cout << "Stack after reversing first " << k << " elements: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    
    return 0;
}
```

### 2. Reverse the Stack in Place Without Using Extra Functions

This approach is more efficient but requires a slightly different recursive logic:

```cpp
#include <iostream>
#include <stack>
using namespace std;

void reverseStackInPlace(stack<int> &s, stack<int> &temp) {
    // Base case: if original stack is empty
    if (s.empty()) {
        return;
    }
    
    // Move all elements to temp stack (in reverse order)
    while (!s.empty()) {
        temp.push(s.top());
        s.pop();
    }
    
    // Copy back to the original stack (this is the result)
    while (!temp.empty()) {
        s.push(temp.top());
        temp.pop();
    }
}

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    
    cout << "Original stack: ";
    // Create a copy for display
    stack<int> display = s;
    while (!display.empty()) {
        cout << display.top() << " ";
        display.pop();
    }
    cout << endl;
    
    stack<int> temp;
    reverseStackInPlace(s, temp);
    
    cout << "Reversed stack: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    
    return 0;
}
```

## Summary

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| Recursion with Helper | O(n²) | O(n) | Uses two recursive functions |
| Step-by-Step Recursion | O(n²) | O(n) | Detailed tracing of the recursive calls |
| Using Extra Stack | O(n) | O(n) | Not purely recursive but more efficient |
