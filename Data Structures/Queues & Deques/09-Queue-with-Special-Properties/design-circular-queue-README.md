# Design Circular Queue

## Problem Description
Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle and the last position is connected back to the first position to make a circle.

Implement the `MyCircularQueue` class:
- `MyCircularQueue(k)` Initializes the object with the size of the queue to be k
- `boolean enQueue(int value)` Inserts an element into the circular queue. Returns true if successful
- `boolean deQueue()` Deletes an element from the circular queue. Returns true if successful
- `int Front()` Gets the front item from the queue. If the queue is empty, return -1
- `int Rear()` Gets the last item from the queue. If the queue is empty, return -1
- `boolean isEmpty()` Checks whether the circular queue is empty or not
- `boolean isFull()` Checks whether the circular queue is full or not

## Approach
A circular queue can be efficiently implemented using a fixed-size array with two pointers:
- **Front pointer**: Points to the first element
- **Rear pointer**: Points to the last element

**Key insight**: Use modular arithmetic to wrap around when reaching array boundaries.

**Size tracking strategies**:
1. **Keep separate count**: Track number of elements explicitly
2. **Sacrifice one slot**: Keep one slot empty to distinguish full vs empty
3. **Use flag**: Boolean flag to track full/empty state

## Algorithm Steps
1. **Initialize array** with fixed size and pointers
2. **Enqueue**: Add element at rear position, advance rear pointer
3. **Dequeue**: Remove element from front position, advance front pointer
4. **Use modular arithmetic** for circular behavior
5. **Track size** to handle full/empty conditions

## Implementation

### Approach 1: Array with Count Tracking
```cpp
class MyCircularQueue {
private:
    vector<int> buffer;
    int head;
    int count;
    int capacity;
    
public:
    MyCircularQueue(int k) {
        buffer.resize(k);
        head = 0;
        count = 0;
        capacity = k;
    }
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        
        int tail = (head + count) % capacity;
        buffer[tail] = value;
        count++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        
        head = (head + 1) % capacity;
        count--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return buffer[head];
    }
    
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        
        int tail = (head + count - 1) % capacity;
        return buffer[tail];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};
```

### Approach 2: Array with Head and Tail Pointers
```cpp
class MyCircularQueue {
private:
    vector<int> buffer;
    int head;
    int tail;
    int size;
    int capacity;
    
public:
    MyCircularQueue(int k) {
        buffer.resize(k);
        head = 0;
        tail = -1;
        size = 0;
        capacity = k;
    }
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        
        tail = (tail + 1) % capacity;
        buffer[tail] = value;
        size++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        
        head = (head + 1) % capacity;
        size--;
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : buffer[head];
    }
    
    int Rear() {
        return isEmpty() ? -1 : buffer[tail];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};
```

### Approach 3: Sacrifice One Slot Method
```cpp
class MyCircularQueue {
private:
    vector<int> buffer;
    int head;
    int tail;
    int capacity;
    
public:
    MyCircularQueue(int k) {
        buffer.resize(k + 1);  // One extra slot
        head = 0;
        tail = 0;
        capacity = k + 1;
    }
    
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        
        head = (head + 1) % capacity;
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : buffer[head];
    }
    
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        
        int realTail = (tail - 1 + capacity) % capacity;
        return buffer[realTail];
    }
    
    bool isEmpty() {
        return head == tail;
    }
    
    bool isFull() {
        return (tail + 1) % capacity == head;
    }
};
```

### Approach 4: Thread-Safe Circular Queue
```cpp
#include <mutex>
#include <condition_variable>

class ThreadSafeCircularQueue {
private:
    vector<int> buffer;
    int head;
    int tail;
    int count;
    int capacity;
    mutable mutex mtx;
    condition_variable notFull;
    condition_variable notEmpty;
    
public:
    ThreadSafeCircularQueue(int k) : buffer(k), head(0), tail(0), count(0), capacity(k) {}
    
    bool enQueue(int value) {
        unique_lock<mutex> lock(mtx);
        
        if (count == capacity) {
            return false;  // Non-blocking version
        }
        
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        count++;
        
        notEmpty.notify_one();
        return true;
    }
    
    bool enQueueBlocking(int value) {
        unique_lock<mutex> lock(mtx);
        
        notFull.wait(lock, [this] { return count < capacity; });
        
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        count++;
        
        notEmpty.notify_one();
        return true;
    }
    
    bool deQueue() {
        unique_lock<mutex> lock(mtx);
        
        if (count == 0) {
            return false;
        }
        
        head = (head + 1) % capacity;
        count--;
        
        notFull.notify_one();
        return true;
    }
    
    int Front() {
        lock_guard<mutex> lock(mtx);
        return count == 0 ? -1 : buffer[head];
    }
    
    int Rear() {
        lock_guard<mutex> lock(mtx);
        if (count == 0) return -1;
        
        int realTail = (tail - 1 + capacity) % capacity;
        return buffer[realTail];
    }
    
    bool isEmpty() {
        lock_guard<mutex> lock(mtx);
        return count == 0;
    }
    
    bool isFull() {
        lock_guard<mutex> lock(mtx);
        return count == capacity;
    }
};
```

### Time Complexity
- **All operations**: O(1) - constant time for all operations

### Space Complexity
- **Storage**: O(k) where k is the queue capacity

## Examples

### Example 1
```cpp
MyCircularQueue myCircularQueue(3);
myCircularQueue.enQueue(1);  // return True
myCircularQueue.enQueue(2);  // return True
myCircularQueue.enQueue(3);  // return True
myCircularQueue.enQueue(4);  // return False (queue is full)
myCircularQueue.Rear();      // return 3
myCircularQueue.isFull();    // return True
myCircularQueue.deQueue();   // return True
myCircularQueue.enQueue(4);  // return True
myCircularQueue.Rear();      // return 4
```

### Example 2
```cpp
MyCircularQueue myCircularQueue(1);
myCircularQueue.enQueue(1);  // return True
myCircularQueue.deQueue();   // return True
myCircularQueue.Front();     // return -1 (queue is empty)
myCircularQueue.Rear();      // return -1 (queue is empty)
```

## Key Insights

### Queue Pattern Usage
- **Fixed-size buffer**: Circular queue uses fixed memory efficiently
- **Wrap-around behavior**: Modular arithmetic enables circular property
- **State management**: Careful tracking of full/empty conditions

### Design Considerations
1. **Full vs Empty detection**: Different strategies have trade-offs
2. **Pointer management**: Consistent advancement with modular arithmetic
3. **Edge cases**: Handle empty queue operations gracefully
4. **Thread safety**: Add synchronization for concurrent access

### Implementation Variants
- **Count tracking**: Simple and intuitive
- **Sacrifice slot**: Elegant but wastes one slot
- **Flag-based**: Additional state for precise tracking
- **Thread-safe**: Blocking and non-blocking operations

### Common Pitfalls
- **Integer overflow**: Use modular arithmetic correctly
- **Empty vs Full confusion**: Clear distinction needed
- **Off-by-one errors**: Careful index calculations
- **Race conditions**: Proper synchronization in multi-threaded environments

## Applications
- **Producer-Consumer**: Buffering between fast producer and slow consumer
- **Streaming**: Real-time data processing with fixed buffer
- **Resource pooling**: Connection pools, thread pools
- **Game development**: Event queues, command buffers

## Related Problems
- Design Circular Deque
- Moving Average from Data Stream
- Design Hit Counter
Output: 
Explanation: 
```

### Example 2
```
Input: 
Output: 
Explanation: 
```

## Notes
<!-- Add any additional notes, edge cases, or variations -->

## Related Problems
<!-- List related problems -->

## Pattern: 09-Queue-with-Special-Properties
<!-- Explain how this problem fits the pattern -->
