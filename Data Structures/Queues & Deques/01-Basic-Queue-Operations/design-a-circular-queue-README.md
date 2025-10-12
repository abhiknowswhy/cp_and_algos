# Design a circular queue

## Problem Description
Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle and the last position is connected back to the first position to make a circle.

Implement the MyCircularQueue class:
- `MyCircularQueue(k)` Initializes the object with the size of the queue to be k.
- `boolean enQueue(int value)` Inserts an element into the circular queue. Return true if successful.
- `boolean deQueue()` Deletes an element from the circular queue. Return true if successful.
- `int Front()` Gets the front item from the queue. Return -1 if empty.
- `int Rear()` Gets the last item from the queue. Return -1 if empty.
- `boolean isEmpty()` Checks whether the circular queue is empty.
- `boolean isFull()` Checks whether the circular queue is full.

**LeetCode Problem:** [622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)

## Approach
Use a fixed-size array with front and rear pointers. Key insight: leave one slot empty to distinguish between full and empty states. Use modular arithmetic for circular behavior.

## Algorithm Steps
1. Initialize array of size k+1, front=0, rear=0
2. For enQueue: Check if full, add at rear, increment rear with modulo
3. For deQueue: Check if empty, increment front with modulo
4. Use (rear + 1) % size == front to check if full

## Implementation

### C++
```cpp
class MyCircularQueue {
private:
    vector<int> data;
    int front;
    int rear;
    int size;
    
public:
    MyCircularQueue(int k) : size(k + 1), front(0), rear(0) {
        data.resize(size);
    }
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        data[rear] = value;
        rear = (rear + 1) % size;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        front = (front + 1) % size;
        return true;
    }
    
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[front];
    }
    
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[(rear - 1 + size) % size];
    }
    
    bool isEmpty() {
        return front == rear;
    }
    
    bool isFull() {
        return (rear + 1) % size == front;
    }
};
```

### Time Complexity
- All operations: O(1)

### Space Complexity
O(k) where k is the given size

## Examples

### Example 1
```
Input: 
["MyCircularQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]

Output: 
[null, true, true, true, false, 3, true, true, true, 4]

Explanation: 
MyCircularQueue circularQueue = new MyCircularQueue(3);
circularQueue.enQueue(1); // return True
circularQueue.enQueue(2); // return True
circularQueue.enQueue(3); // return True
circularQueue.enQueue(4); // return False (queue is full)
circularQueue.Rear();     // return 3
circularQueue.isFull();   // return True
circularQueue.deQueue();  // return True
circularQueue.enQueue(4); // return True
circularQueue.Rear();     // return 4
```

### Example 2
```
Input: 
["MyCircularQueue", "enQueue", "deQueue", "Front"]
[[1], [1], [], []]

Output: 
[null, true, true, -1]

Explanation: 
Single element queue, after dequeue it becomes empty
```

## Notes
- Key insight: Use k+1 size array to distinguish full from empty
- Alternative: Use a counter variable instead of extra space
- Modular arithmetic handles wrap-around automatically
- Rear calculation needs careful handling: (rear - 1 + size) % size

## Related Problems
- [LeetCode 641 - Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)
- [LeetCode 232 - Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [LeetCode 225 - Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

## Pattern: 01-Basic-Queue-Operations
Circular queue optimizes space usage by reusing array positions. It's fundamental for implementing efficient queues in systems with memory constraints and forms the basis for ring buffers in operating systems.
