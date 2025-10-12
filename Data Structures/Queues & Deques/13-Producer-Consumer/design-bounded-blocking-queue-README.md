# Design Bounded Blocking Queue

## Problem Description
Design a **bounded blocking queue** which has the following methods:

- `BoundedBlockingQueue(int capacity)`: The constructor initializes the queue with a maximum capacity
- `void enqueue(int element)`: Adds an element to the front of the queue. If the queue is full, the calling thread is blocked until the queue is no longer full
- `int dequeue()`: Returns and removes an element from the rear of the queue. If the queue is empty, the calling thread is blocked until the queue is no longer empty
- `int size()`: Returns the number of elements currently in the queue

Your implementation will be tested using multiple threads at the same time. Each thread will either be a producer thread that only makes calls to the `enqueue` method or a consumer thread that only makes calls to the `dequeue` method. The `size` method will be called from time to time.

**Note**: You are NOT allowed to use any built-in bounded blocking queue implementations (such as `BlockingQueue` in Java).

## Approach
The bounded blocking queue can be implemented using various synchronization primitives and data structures. Here, we will discuss multiple approaches:

1. **Mutex + Condition Variables**: Using mutex locks and condition variables to block and wake up threads.
2. **Semaphore-based Implementation**: Using semaphores to manage the count of empty and filled slots.
3. **Circular Buffer Implementation**: Using a circular buffer with atomic variables for head, tail, and count.
4. **Lock-Free Implementation**: An advanced approach that uses atomic operations to achieve lock-free behavior.
5. **Python Implementation**: A straightforward implementation in Python using threading primitives.

## Algorithm Steps
1. **Initialization**: Set up the internal data structures (e.g., queue, mutex, condition variables, semaphores).
2. **Enqueue**:
   - Check if the queue is full.
   - If full, block the thread (wait on a condition variable or semaphore).
   - If not full, add the element to the queue and notify a waiting consumer.
3. **Dequeue**:
   - Check if the queue is empty.
   - If empty, block the thread (wait on a condition variable or semaphore).
   - If not empty, remove an element from the queue and notify a waiting producer.
4. **Size**: Return the current number of elements in the queue (ensure thread safety).

## Implementation

### Python
```python
import threading
from collections import deque

class BoundedBlockingQueue:
    
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.queue = deque()
        self.mutex = threading.Lock()
        self.not_full = threading.Condition(self.mutex)
        self.not_empty = threading.Condition(self.mutex)
    
    def enqueue(self, element: int) -> None:
        with self.not_full:
            while len(self.queue) >= self.capacity:
                self.not_full.wait()
            
            self.queue.append(element)
            self.not_empty.notify()
    
    def dequeue(self) -> int:
        with self.not_empty:
            while len(self.queue) == 0:
                self.not_empty.wait()
            
            element = self.queue.popleft()
            self.not_full.notify()
            return element
    
    def size(self) -> int:
        with self.mutex:
            return len(self.queue)
```

### Time Complexity
- `enqueue`: O(1) on average, but can be O(n) in the worst case if resizing is needed (not applicable for circular buffer and lock-free implementations).
- `dequeue`: O(1).
- `size`: O(1).

### Space Complexity
- O(n), where n is the capacity of the queue. This is the space required for the internal data structures to hold the elements.

## Examples

### Example 1
```
Input: 
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
- Consider using lock-free programming techniques for high-performance scenarios.
- Always prefer using higher-level abstractions (like `std::queue`) unless low-level control is necessary.

## Related Problems
- **LeetCode 1188 - Design Bounded Blocking Queue**: Exact problem
- **LeetCode 1116 - Print Zero Even Odd**: Thread synchronization
- **LeetCode 1114 - Print in Order**: Basic thread coordination
- **LeetCode 1115 - Print FooBar Alternately**: Alternating execution
- **LeetCode 1242 - Web Crawler Multithreaded**: Producer-consumer pattern

## Pattern: 13-Producer-Consumer
This problem is a classic example of the producer-consumer pattern, where the bounded blocking queue acts as a buffer between producers (which add data) and consumers (which remove data). Proper synchronization is required to ensure that producers do not add data when the buffer is full, and consumers do not remove data when the buffer is empty.
