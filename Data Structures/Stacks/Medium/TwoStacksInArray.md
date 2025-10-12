# Implement Two Stacks in an Array

## Problem Description

Implement two stacks in a single array such that operations on both stacks work correctly and efficiently.

## Approaches to Solve the Problem

### 1. Fixed Size Division Approach

#### Intuition

- Divide the array into two equal halves
- Use the first half for stack1, growing from left to right
- Use the second half for stack2, growing from right to left

#### Implementation

```cpp
#include <iostream>
using namespace std;

class TwoStacks {
private:
    int* arr;
    int size;
    int top1, top2;
    
public:
    // Constructor
    TwoStacks(int n) {
        size = n;
        arr = new int[n];
        top1 = -1;
        top2 = size;
    }
    
    // Destructor
    ~TwoStacks() {
        delete[] arr;
    }
    
    // Push to stack 1
    void push1(int x) {
        // Check if there is space available
        if (top1 < top2 - 1) {
            top1++;
            arr[top1] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }
    
    // Push to stack 2
    void push2(int x) {
        // Check if there is space available
        if (top1 < top2 - 1) {
            top2--;
            arr[top2] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }
    
    // Pop from stack 1
    int pop1() {
        if (top1 >= 0) {
            int x = arr[top1];
            top1--;
            return x;
        } else {
            cout << "Stack Underflow\n";
            exit(1);
        }
    }
    
    // Pop from stack 2
    int pop2() {
        if (top2 < size) {
            int x = arr[top2];
            top2++;
            return x;
        } else {
            cout << "Stack Underflow\n";
            exit(1);
        }
    }
    
    // Return the top element of stack 1
    int peek1() {
        if (top1 >= 0) {
            return arr[top1];
        }
        cout << "Stack 1 is empty\n";
        return -1;
    }
    
    // Return the top element of stack 2
    int peek2() {
        if (top2 < size) {
            return arr[top2];
        }
        cout << "Stack 2 is empty\n";
        return -1;
    }
    
    // Check if stack 1 is empty
    bool isEmpty1() {
        return top1 == -1;
    }
    
    // Check if stack 2 is empty
    bool isEmpty2() {
        return top2 == size;
    }
};

int main() {
    TwoStacks ts(10);
    ts.push1(5);
    ts.push2(10);
    ts.push2(15);
    ts.push1(11);
    ts.push2(7);
    
    cout << "Popped element from stack1: " << ts.pop1() << endl;
    cout << "Popped element from stack2: " << ts.pop2() << endl;
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(1) for all operations (push, pop, peek, isEmpty)
- Space Complexity: O(n) for the array of size n

### 2. Dynamic Size Division Approach

#### Intuition

- Start both stacks at the ends of the array
- Stack1 grows from left to right (starting at index 0)
- Stack2 grows from right to left (starting at index n-1)
- Allow the stacks to grow dynamically until they meet

This approach is more space-efficient as it doesn't pre-allocate fixed space for each stack.

#### Implementation

```cpp
#include <iostream>
using namespace std;

class TwoStacks {
private:
    int* arr;
    int size;
    int top1, top2;
    
public:
    // Constructor
    TwoStacks(int n) {
        size = n;
        arr = new int[n];
        top1 = -1;
        top2 = size;
    }
    
    // Destructor
    ~TwoStacks() {
        delete[] arr;
    }
    
    // Push to stack 1
    void push1(int x) {
        // Check if there is space available
        if (top1 < top2 - 1) {
            top1++;
            arr[top1] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }
    
    // Push to stack 2
    void push2(int x) {
        // Check if there is space available
        if (top1 < top2 - 1) {
            top2--;
            arr[top2] = x;
        } else {
            cout << "Stack Overflow\n";
        }
    }
    
    // Pop from stack 1
    int pop1() {
        if (top1 >= 0) {
            int x = arr[top1];
            top1--;
            return x;
        } else {
            cout << "Stack Underflow\n";
            exit(1);
        }
    }
    
    // Pop from stack 2
    int pop2() {
        if (top2 < size) {
            int x = arr[top2];
            top2++;
            return x;
        } else {
            cout << "Stack Underflow\n";
            exit(1);
        }
    }
    
    // Return the top element of stack 1
    int peek1() {
        if (top1 >= 0) {
            return arr[top1];
        }
        cout << "Stack 1 is empty\n";
        return -1;
    }
    
    // Return the top element of stack 2
    int peek2() {
        if (top2 < size) {
            return arr[top2];
        }
        cout << "Stack 2 is empty\n";
        return -1;
    }
    
    // Check if stack 1 is empty
    bool isEmpty1() {
        return top1 == -1;
    }
    
    // Check if stack 2 is empty
    bool isEmpty2() {
        return top2 == size;
    }
};

int main() {
    TwoStacks ts(10);
    
    // Push elements to both stacks
    ts.push1(5);
    ts.push2(10);
    ts.push2(15);
    ts.push1(11);
    ts.push2(7);
    ts.push1(3);
    ts.push2(1);
    ts.push1(9);
    
    cout << "Stack 1 top: " << ts.peek1() << endl;
    cout << "Stack 2 top: " << ts.peek2() << endl;
    
    cout << "Popped element from stack1: " << ts.pop1() << endl;
    cout << "Popped element from stack2: " << ts.pop2() << endl;
    
    cout << "Stack 1 top after pop: " << ts.peek1() << endl;
    cout << "Stack 2 top after pop: " << ts.peek2() << endl;
    
    return 0;
}
```

### 3. Middle-Out Approach (Alternative)

#### Intuition

- Start both stacks from the middle of the array
- Stack1 grows leftward from the middle
- Stack2 grows rightward from the middle
- This approach can be useful in specific scenarios with known access patterns

## Related LeetCode Problems

1. [LeetCode 155: Min Stack](https://leetcode.com/problems/min-stack/) (Similar concept of designing a specialized stack)
2. [LeetCode 225: Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/) (Similar concept of implementing a data structure using another data structure)

## Applications

1. **Memory Management**: Operating systems use multiple stacks for managing function calls and interrupts
2. **Undo/Redo Functionality**: Applications can use two stacks to maintain the history of operations
3. **Expression Evaluation**: Parser implementations
4. **Browser Navigation**: Managing back and forward navigation

## Summary

| Approach | Space Efficiency | Performance | Best For |
| --- | --- | --- | --- |
| Fixed Division | Less efficient | Consistent | When stack sizes are predictable |
| Dynamic Division | More efficient | Consistent | When stack sizes are unpredictable |
| Middle-Out | Depends on usage pattern | Potentially better cache locality | Specific access patterns |
