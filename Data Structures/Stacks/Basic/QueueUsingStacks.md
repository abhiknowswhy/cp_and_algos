# Implement a Queue Using Two Stacks

## Problem Description

Implement a first-in-first-out (FIFO) queue using only two stacks. The implemented queue should support the standard queue operations:

- **push(x)**: Adds an element x to the back of the queue.
- **pop()**: Removes and returns the element at the front of the queue.
- **peek()**: Returns the element at the front of the queue without removing it.
- **empty()**: Returns whether the queue is empty.

## Approaches to Solve the Problem

### 1. Push-Efficient Approach

#### Intuition

- Use two stacks: `s1` for pushing elements and `s2` for popping elements
- When pushing, simply push onto `s1`
- When popping or peeking, if `s2` is empty, transfer all elements from `s1` to `s2` (this reverses the order)
- This approach makes push operations O(1) and pop/peek potentially O(n) but amortized O(1)

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> pushStack;    // For pushing elements
    stack<int> popStack;     // For popping elements
    
    // Transfer elements from pushStack to popStack if popStack is empty
    void transferIfNeeded() {
        if (popStack.empty()) {
            while (!pushStack.empty()) {
                popStack.push(pushStack.top());
                pushStack.pop();
            }
        }
    }
    
public:
    MyQueue() {
        // No initialization needed
    }
    
    void push(int x) {
        pushStack.push(x);
    }
    
    int pop() {
        transferIfNeeded();
        int frontElement = popStack.top();
        popStack.pop();
        return frontElement;
    }
    
    int peek() {
        transferIfNeeded();
        return popStack.top();
    }
    
    bool empty() {
        return pushStack.empty() && popStack.empty();
    }
};
```

#### Explanation

- We maintain two stacks: `pushStack` and `popStack`
- When pushing an element, we simply add it to `pushStack`
- For pop or peek operations:
  - If `popStack` is empty, we transfer all elements from `pushStack` to `popStack` (which reverses their order)
  - Then we perform the operation on `popStack`
- This ensures that elements are returned in FIFO order despite using LIFO stacks

### 2. Transfer-on-Demand Approach

#### Intuition

Similar to the push-efficient approach, but with a slight optimization:
- Only transfer elements when needed for a pop or peek operation
- This avoids unnecessary transfers if multiple push operations occur in sequence

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> inputStack;    // For pushing elements
    stack<int> outputStack;   // For popping elements
    
public:
    MyQueue() {
        // No initialization needed
    }
    
    void push(int x) {
        inputStack.push(x);
    }
    
    int pop() {
        // If output stack is empty, transfer all elements from input stack
        if (outputStack.empty()) {
            while (!inputStack.empty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        
        int frontElement = outputStack.top();
        outputStack.pop();
        return frontElement;
    }
    
    int peek() {
        // If output stack is empty, transfer all elements from input stack
        if (outputStack.empty()) {
            while (!inputStack.empty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
        
        return outputStack.top();
    }
    
    bool empty() {
        return inputStack.empty() && outputStack.empty();
    }
};
```

### 3. Push-and-Transfer Approach (Not Recommended)

#### Intuition

An alternative approach is to maintain the queue invariant with each push:
- Always keep elements in the correct order in one stack
- Use the second stack as temporary storage during push operations
- This makes push operations O(n) but pop/peek O(1)

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> mainStack;    // Holds elements in queue order
    stack<int> tempStack;    // Temporary stack for push operations
    
public:
    MyQueue() {
        // No initialization needed
    }
    
    void push(int x) {
        // Transfer all elements from mainStack to tempStack
        while (!mainStack.empty()) {
            tempStack.push(mainStack.top());
            mainStack.pop();
        }
        
        // Push the new element onto mainStack
        mainStack.push(x);
        
        // Transfer all elements back from tempStack to mainStack
        while (!tempStack.empty()) {
            mainStack.push(tempStack.top());
            tempStack.pop();
        }
    }
    
    int pop() {
        int frontElement = mainStack.top();
        mainStack.pop();
        return frontElement;
    }
    
    int peek() {
        return mainStack.top();
    }
    
    bool empty() {
        return mainStack.empty();
    }
};
```

#### Explanation

- In this approach, we always maintain the queue order in `mainStack`
- When pushing a new element:
  1. We transfer all elements from `mainStack` to `tempStack` (reversing their order)
  2. We push the new element onto `mainStack` (it will be at the bottom)
  3. We transfer all elements back from `tempStack` to `mainStack` (restoring their order)
- This makes pop and peek operations simple (just access the top of `mainStack`), but push operations become expensive

## Complexity Analysis

### Push-Efficient / Transfer-on-Demand Approach
- **push()**: O(1) time
- **pop()**: Amortized O(1) time. In the worst case, it's O(n) when we need to transfer all elements, but each element is transferred at most once.
- **peek()**: Amortized O(1) time, same reasoning as pop().
- **empty()**: O(1) time
- **Space Complexity**: O(n), where n is the number of elements in the queue.

### Push-and-Transfer Approach
- **push()**: O(n) time, as we need to transfer all n elements twice for each push.
- **pop()**: O(1) time
- **peek()**: O(1) time
- **empty()**: O(1) time
- **Space Complexity**: O(n), where n is the number of elements in the queue.

## Step-by-Step Execution

Let's trace through the Push-Efficient approach with an example:

Operations: push(1), push(2), peek(), pop(), push(3), peek(), pop(), pop()

1. push(1):
   - pushStack: [1] 
   - popStack: []

2. push(2):
   - pushStack: [1, 2] 
   - popStack: []

3. peek():
   - popStack is empty, so transfer elements:
     - popStack: [2, 1]
   - Return top of popStack: 1

4. pop():
   - popStack: [2]
   - Return: 1

5. push(3):
   - pushStack: [3]
   - popStack: [2]

6. peek():
   - popStack is not empty, so no transfer needed
   - Return top of popStack: 2

7. pop():
   - popStack: []
   - Return: 2

8. pop():
   - popStack is empty, so transfer elements:
     - popStack: [3]
   - Return: 3

Final state:
- pushStack: []
- popStack: []

## Related LeetCode Problems

- [LeetCode 232: Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [LeetCode 225: Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
- [LeetCode 155: Min Stack](https://leetcode.com/problems/min-stack/)
- [LeetCode 716: Max Stack](https://leetcode.com/problems/max-stack/)
- [LeetCode 622: Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)

## Applications

- **Function Call Management**: Implementing function call patterns that require both LIFO and FIFO behaviors
- **Task Scheduling**: Implementing task schedulers that need to prioritize certain operations
- **Web Browser Navigation**: Implementing back/forward functionality with additional queue-like features
- **Print Spooling**: Managing print jobs in order while allowing for efficient data structure operations
- **Undo/Redo Functionality**: Implementing complex undo/redo patterns that require both stack and queue behavior

## Summary

| Approach | Push Complexity | Pop Complexity | Peek Complexity | Space Complexity | Pros | Cons |
|----------|-----------------|----------------|-----------------|------------------|------|------|
| Push-Efficient | O(1) | Amortized O(1) | Amortized O(1) | O(n) | Fast push operations, good amortized performance | Occasional O(n) pop/peek operations |
| Transfer-on-Demand | O(1) | Amortized O(1) | Amortized O(1) | O(n) | Similar to push-efficient, with clearer implementation | Same as push-efficient |
| Push-and-Transfer | O(n) | O(1) | O(1) | O(n) | Consistent O(1) pop/peek operations | Expensive push operations |

The Push-Efficient and Transfer-on-Demand approaches are generally preferred because:

1. They provide better amortized performance for typical queue usage patterns.
2. Push operations are common in many applications and should be efficient.
3. The occasional O(n) cost for pop/peek operations is amortized over multiple operations.

In practice, the choice between these approaches depends on the specific usage pattern:
- If push operations are more frequent, use the Push-Efficient approach.
- If pop/peek operations are more frequent and predictable, the Push-and-Transfer approach might be worth considering, but it's usually not preferred due to its consistently high cost for push operations.
