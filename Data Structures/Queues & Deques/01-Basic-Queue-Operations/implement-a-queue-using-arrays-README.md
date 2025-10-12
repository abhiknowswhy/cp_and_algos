# Implement a queue using arrays

## Problem Description
Design your implementation of the queue. The queue should support the following operations:
- `MyQueue()` Initializes the object.
- `void push(int x)` Pushes element x to the back of the queue.
- `int pop()` Removes the element from the front of the queue and returns it.
- `int peek()` Returns the element at the front of the queue.
- `boolean empty()` Returns true if the queue is empty, false otherwise.

## Approach
Use a fixed-size array with two pointers (front and rear) to track the queue boundaries. Use a size counter to track the number of elements.

## Algorithm Steps
1. Initialize array with fixed capacity, front=0, rear=0, size=0
2. For enqueue: Add element at rear position, increment rear and size
3. For dequeue: Remove element from front position, increment front and size--
4. Use modular arithmetic for circular array behavior

## Implementation

### C++
```cpp
class MyQueue {
private:
    vector<int> data;
    int front;
    int rear;
    int size;
    int capacity;
    
public:
    MyQueue(int cap = 1000) : capacity(cap), front(0), rear(0), size(0) {
        data.resize(capacity);
    }
    
    void push(int x) {
        if (size == capacity) {
            throw runtime_error("Queue is full");
        }
        data[rear] = x;
        rear = (rear + 1) % capacity;
        size++;
    }
    
    int pop() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        int result = data[front];
        front = (front + 1) % capacity;
        size--;
        return result;
    }
    
    int peek() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        return data[front];
    }
    
    bool empty() {
        return size == 0;
    }
    
    int getSize() {
        return size;
    }
};
```

### Time Complexity
- Push: O(1)
- Pop: O(1)
- Peek: O(1)
- Empty: O(1)

### Space Complexity
O(n) where n is the capacity of the queue

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
["MyQueue", "push", "pop", "empty"]
[[], [1], [], []]

Output: 
[null, null, 1, true]

Explanation: 
MyQueue myQueue = new MyQueue();
myQueue.push(1);
myQueue.pop(); // returns 1
myQueue.empty(); // returns true
```

## Notes
- Use circular array to avoid shifting elements
- Always check for overflow and underflow conditions
- Front and rear pointers wrap around using modulo operation
- Alternative: Use dynamic resizing when queue becomes full

## Related Problems
- [LeetCode 232 - Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [LeetCode 622 - Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
- [LeetCode 225 - Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

## Pattern: 01-Basic-Queue-Operations
This problem demonstrates the fundamental FIFO (First In First Out) behavior of queues using array implementation. It's the foundation for understanding more complex queue patterns and is essential for BFS algorithms.
