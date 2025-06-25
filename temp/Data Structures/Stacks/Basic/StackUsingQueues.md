# Implement a Stack Using Queues

## Problem Description

Implement a last-in-first-out (LIFO) stack using only queues. The implemented stack should support the standard stack operations:

- **push(x)**: Pushes element x to the top of the stack.
- **pop()**: Removes and returns the element on top of the stack.
- **top()**: Returns the element on the top of the stack without removing it.
- **empty()**: Returns whether the stack is empty.

## Approaches to Solve the Problem

### 1. Two Queues - Push Efficient

#### Intuition

- Use two queues: `q1` as the main queue and `q2` as an auxiliary queue
- Keep the most recently added element accessible for top and pop operations
- For push operations, simply add to `q1`
- For pop/top operations, move all elements except the last one from `q1` to `q2`, then access the last element
- After a pop operation, swap `q1` and `q2`

#### Implementation

```cpp
#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
    queue<int> q1; // Main queue
    queue<int> q2; // Auxiliary queue
    int topElement; // Tracks the top element for top() operation
    
public:
    MyStack() {
        // No initialization needed
    }
    
    void push(int x) {
        q1.push(x);
        topElement = x; // Update top element
    }
    
    int pop() {
        // Move all elements except the last one to q2
        while (q1.size() > 1) {
            topElement = q1.front(); // Update top element to be the new top after popping
            q2.push(q1.front());
            q1.pop();
        }
        
        // Get the last element (to be popped)
        int popped = q1.front();
        q1.pop();
        
        // Swap q1 and q2
        swap(q1, q2);
        
        return popped;
    }
    
    int top() {
        return topElement;
    }
    
    bool empty() {
        return q1.empty();
    }
};
```

#### Explanation

- When pushing an element, we simply add it to `q1` and update `topElement` to track the most recently added element
- When popping an element:
  - We move all elements except the last one from `q1` to `q2`
  - We remember the last element before removing it from `q1`
  - We swap `q1` and `q2` so that `q1` contains all remaining elements
- The `top()` operation simply returns `topElement`, which always tracks the most recently added element
- This approach makes `push` and `top` operations O(1), but `pop` operation O(n)

### 2. Two Queues - Pop Efficient

#### Intuition

- Use two queues: `q1` as the main queue and `q2` as an auxiliary queue
- Keep elements in a specific order so that the top element is always at the front of `q1`
- For push operations, rearrange the elements to maintain this order
- For pop/top operations, simply access the front of `q1`

#### Implementation

```cpp
#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
    queue<int> q1; // Main queue
    queue<int> q2; // Auxiliary queue
    
public:
    MyStack() {
        // No initialization needed
    }
    
    void push(int x) {
        // Push new element to empty q2
        q2.push(x);
        
        // Move all elements from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        
        // Swap q1 and q2, so q1 has all elements with newest at front
        swap(q1, q2);
    }
    
    int pop() {
        int popped = q1.front();
        q1.pop();
        return popped;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return q1.empty();
    }
};
```

#### Explanation

- When pushing an element:
  - We add the new element to the empty `q2`
  - We move all elements from `q1` to `q2` (which puts the new element at the front)
  - We swap `q1` and `q2` so that `q1` contains all elements with the newest at the front
- For `pop()` and `top()`, we simply access the front of `q1`
- This approach makes `pop` and `top` operations O(1), but `push` operation O(n)

### 3. Single Queue Approach

#### Intuition

- Use a single queue to implement the stack
- After pushing a new element, rotate the queue so that the new element is at the front
- This maintains the stack order with only one queue

#### Implementation

```cpp
#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
    queue<int> q;
    
public:
    MyStack() {
        // No initialization needed
    }
    
    void push(int x) {
        // Add the new element
        q.push(x);
        
        // Rotate the queue to put the new element at the front
        int size = q.size();
        for (int i = 0; i < size - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int popped = q.front();
        q.pop();
        return popped;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};
```

#### Explanation

- When pushing an element:
  - We add the new element to the back of the queue
  - We rotate the queue by removing each element from the front and adding it to the back, until the new element is at the front
  - After this rotation, the most recently added element is at the front of the queue, followed by previously added elements in reverse order of their addition
- The `pop()` and `top()` operations simply access the front of the queue
- This approach uses less memory (only one queue) but still has O(n) push operations

## Complexity Analysis

### Two Queues - Push Efficient
- **push()**: O(1) time
- **pop()**: O(n) time, where n is the number of elements in the stack
- **top()**: O(1) time
- **empty()**: O(1) time
- **Space Complexity**: O(n), where n is the number of elements in the stack

### Two Queues - Pop Efficient
- **push()**: O(n) time, where n is the number of elements in the stack
- **pop()**: O(1) time
- **top()**: O(1) time
- **empty()**: O(1) time
- **Space Complexity**: O(n), where n is the number of elements in the stack

### Single Queue Approach
- **push()**: O(n) time, where n is the number of elements in the stack
- **pop()**: O(1) time
- **top()**: O(1) time
- **empty()**: O(1) time
- **Space Complexity**: O(n), where n is the number of elements in the stack

## Step-by-Step Execution

Let's trace through the Single Queue approach with an example:

Operations: push(1), push(2), top(), pop(), push(3), top(), pop(), empty()

1. push(1):
   - q: [1]

2. push(2):
   - q after adding 2: [1, 2]
   - Rotate: Remove 1 and add to back
   - q after rotation: [2, 1]

3. top():
   - Return front of q: 2

4. pop():
   - Remove and return front of q: 2
   - q: [1]

5. push(3):
   - q after adding 3: [1, 3]
   - Rotate: Remove 1 and add to back
   - q after rotation: [3, 1]

6. top():
   - Return front of q: 3

7. pop():
   - Remove and return front of q: 3
   - q: [1]

8. empty():
   - q is not empty, return false

Let's also trace through the Two Queues - Pop Efficient approach:

Operations: push(1), push(2), top(), pop(), push(3), top(), pop(), empty()

1. push(1):
   - q2: [1]
   - Swap q1 and q2
   - q1: [1], q2: []

2. push(2):
   - q2: [2]
   - Move elements from q1 to q2: q2: [2, 1]
   - Swap q1 and q2
   - q1: [2, 1], q2: []

3. top():
   - Return front of q1: 2

4. pop():
   - Remove and return front of q1: 2
   - q1: [1], q2: []

5. push(3):
   - q2: [3]
   - Move elements from q1 to q2: q2: [3, 1]
   - Swap q1 and q2
   - q1: [3, 1], q2: []

6. top():
   - Return front of q1: 3

7. pop():
   - Remove and return front of q1: 3
   - q1: [1], q2: []

8. empty():
   - q1 is not empty, return false

## Related LeetCode Problems

- [LeetCode 225: Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
- [LeetCode 232: Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [LeetCode 155: Min Stack](https://leetcode.com/problems/min-stack/)
- [LeetCode 716: Max Stack](https://leetcode.com/problems/max-stack/)
- [LeetCode 622: Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
- [LeetCode 641: Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)

## Applications

- **Data Structure Implementation**: Understanding and implementing abstract data types using different underlying structures
- **Compiler Design**: Implementing parsing and syntax analysis tools
- **Browser History**: Managing navigation history with both stack and queue behaviors
- **Task Scheduling**: Implementing priority systems that need both FIFO and LIFO behaviors
- **Function Call Management**: Simulating recursive function calls in languages without native stack support

## Summary

| Approach | Push Complexity | Pop Complexity | Top Complexity | Space Complexity | Pros | Cons |
|----------|-----------------|----------------|----------------|------------------|------|------|
| Two Queues - Push Efficient | O(1) | O(n) | O(1) | O(n) | Fast push and top operations | Slow pop operations |
| Two Queues - Pop Efficient | O(n) | O(1) | O(1) | O(n) | Fast pop and top operations | Slow push operations |
| Single Queue | O(n) | O(1) | O(1) | O(n) | Uses less memory (only one queue) | Slow push operations |

The choice between these approaches depends on the specific use case:

1. If push operations are more frequent than pop operations, the "Two Queues - Push Efficient" approach is preferable.
2. If pop operations are more frequent than push operations, the "Two Queues - Pop Efficient" or "Single Queue" approach is preferable.
3. If memory usage is a primary concern, the "Single Queue" approach is preferable as it uses only one queue.

Note that implementing a stack using queues is generally less efficient than using a native stack implementation. This exercise is primarily educational, demonstrating how data structures can be built from different underlying primitives.

In practice, the two-queue approaches might be slightly faster for their optimized operations, but the single-queue approach is often preferred for its simplicity and lower memory footprint.
