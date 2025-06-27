# Implement queue with stack operations

## Problem Description
Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:
- `void push(int x)` Pushes element x to the back of the queue.
- `int pop()` Removes the element from the front of the queue and returns it.
- `int peek()` Returns the element at the front of the queue.
- `boolean empty()` Returns true if the queue is empty, false otherwise.

**LeetCode Problem:** [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)

## Approach
Use two stacks: input stack for push operations and output stack for pop/peek operations. Transfer elements from input to output stack when output is empty and pop/peek is called.

## Algorithm Steps
1. Use two stacks: inputStack and outputStack
2. For push: Always push to inputStack
3. For pop/peek: If outputStack is empty, transfer all from inputStack
4. Pop/peek from outputStack (which now has correct order)

## Implementation

### C++
```cpp
class MyQueue {
private:
    stack<int> inputStack;
    stack<int> outputStack;
    
    void transferIfNeeded() {
        if (outputStack.empty()) {
            while (!inputStack.empty()) {
                outputStack.push(inputStack.top());
                inputStack.pop();
            }
        }
    }
    
public:
    MyQueue() {}
    
    void push(int x) {
        inputStack.push(x);
    }
    
    int pop() {
        transferIfNeeded();
        if (outputStack.empty()) {
            throw runtime_error("Queue is empty");
        }
        int result = outputStack.top();
        outputStack.pop();
        return result;
    }
    
    int peek() {
        transferIfNeeded();
        if (outputStack.empty()) {
            throw runtime_error("Queue is empty");
        }
        return outputStack.top();
    }
    
    bool empty() {
        return inputStack.empty() && outputStack.empty();
    }
};
```

### Time Complexity
- Push: O(1)
- Pop: Amortized O(1), worst case O(n)
- Peek: Amortized O(1), worst case O(n)
- Empty: O(1)

### Space Complexity
O(n) where n is the number of elements in the queue

## Examples

### Example 1
```
Input: 
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]

Output: 
[null, null, null, 1, 1, false]

Explanation: 
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
```

### Example 2
```
Input: 
["MyQueue", "push", "push", "pop", "push", "pop", "pop"]
[[], [1], [2], [], [3], [], []]

Output: 
[null, null, null, 1, null, 2, 3]

Explanation: 
Shows how elements are transferred between stacks as needed
```

## Notes
- Amortized analysis: Each element is moved at most twice (input→output)
- Alternative: Make push expensive instead of pop (always keep output stack in correct order)
- This technique is useful when you need queue behavior but only have stack operations
- Important pattern for interview questions about data structure conversions

## Related Problems
- [LeetCode 225 - Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
- [LeetCode 622 - Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
- [LeetCode 641 - Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)
- [LeetCode 155 - Min Stack](https://leetcode.com/problems/min-stack/)

## Pattern: 01-Basic-Queue-Operations
This problem demonstrates how to achieve queue behavior using different underlying data structures. It's a fundamental transformation technique and teaches important concepts about amortized time complexity analysis.
