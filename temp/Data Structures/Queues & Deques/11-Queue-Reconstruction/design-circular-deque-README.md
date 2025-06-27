# Design Circular Deque - Advanced Queue Reconstruction
## LeetCode Problem 641

**Difficulty:** Medium  
**Category:** Queue Reconstruction, Data Structure Design  
**Pattern:** Circular buffer implementation with dual-ended operations

## Problem Description

Design a circular double-ended queue (deque) that supports adding and removing elements from both front and rear ends. Implement the MyCircularDeque class:

- `MyCircularDeque(k)` Initializes the deque with a maximum size of k.
- `insertFront(value)` Adds an item at the front of Deque. Return true if successful, false otherwise.
- `insertLast(value)` Adds an item at the rear of Deque. Return true if successful, false otherwise.
- `deleteFront()` Deletes an item from the front of Deque. Return true if successful, false otherwise.
- `deleteLast()` Deletes an item from the rear of Deque. Return true if successful, false otherwise.
- `getFront()` Gets the front item from the Deque. Return -1 if empty.
- `getRear()` Gets the rear item from the Deque. Return -1 if empty.
- `isEmpty()` Checks whether the circular deque is empty.
- `isFull()` Checks whether the circular deque is full.

**Key Requirements:**
- All operations must be O(1) time complexity
- Space-efficient circular buffer implementation
- Handle edge cases for empty and full states

## Real-World Applications

1. **Browser History**: Forward and backward navigation
2. **Text Editors**: Undo/redo operations with limited history
3. **Game Development**: Action queues for real-time strategy games
4. **Operating Systems**: Process scheduling with priority adjustments
5. **Audio/Video Streaming**: Buffer management for smooth playback

## Core Algorithm Approaches

### Approach 1: Array-Based Circular Buffer (Optimal)

Most space-efficient implementation using fixed-size array:

```cpp
#include <vector>
using namespace std;

class MyCircularDeque {
private:
    vector<int> buffer;
    int head, tail, size, capacity;
    
public:
    MyCircularDeque(int k) : capacity(k), size(0), head(0), tail(0) {
        buffer.resize(k);
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;
        
        head = (head - 1 + capacity) % capacity;
        buffer[head] = value;
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        size++;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        
        head = (head + 1) % capacity;
        size--;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        
        tail = (tail - 1 + capacity) % capacity;
        size--;
        return true;
    }
    
    int getFront() {
        return isEmpty() ? -1 : buffer[head];
    }
    
    int getRear() {
        return isEmpty() ? -1 : buffer[(tail - 1 + capacity) % capacity];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};
```

**Time Complexity:** O(1) for all operations  
**Space Complexity:** O(k) where k is the maximum capacity

### Approach 2: Doubly Linked List Implementation

More flexible but higher memory overhead:

```cpp
class MyCircularDequeLinked {
private:
    struct Node {
        int val;
        Node* prev;
        Node* next;
        Node(int x) : val(x), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
    int capacity;
    
public:
    MyCircularDequeLinked(int k) : capacity(k), size(0) {
        head = new Node(-1);
        tail = new Node(-1);
        head->next = tail;
        tail->prev = head;
    }
    
    ~MyCircularDequeLinked() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;
        
        Node* newNode = new Node(value);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        
        Node* newNode = new Node(value);
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev = newNode;
        size++;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        
        Node* toDelete = head->next;
        head->next = toDelete->next;
        toDelete->next->prev = head;
        delete toDelete;
        size--;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        
        Node* toDelete = tail->prev;
        tail->prev = toDelete->prev;
        toDelete->prev->next = tail;
        delete toDelete;
        size--;
        return true;
    }
    
    int getFront() {
        return isEmpty() ? -1 : head->next->val;
    }
    
    int getRear() {
        return isEmpty() ? -1 : tail->prev->val;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};
```

### Approach 3: Enhanced Circular Deque with Statistics

Advanced implementation with operation tracking:

```cpp
#include <vector>
#include <unordered_map>

class EnhancedCircularDeque {
private:
    vector<int> buffer;
    int head, tail, size, capacity;
    mutable unordered_map<string, int> operationCount;
    
public:
    EnhancedCircularDeque(int k) : capacity(k), size(0), head(0), tail(0) {
        buffer.resize(k);
    }
    
    bool insertFront(int value) {
        operationCount["insertFront"]++;
        if (isFull()) return false;
        
        head = (head - 1 + capacity) % capacity;
        buffer[head] = value;
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        operationCount["insertLast"]++;
        if (isFull()) return false;
        
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        size++;
        return true;
    }
    
    bool deleteFront() {
        operationCount["deleteFront"]++;
        if (isEmpty()) return false;
        
        head = (head + 1) % capacity;
        size--;
        return true;
    }
    
    bool deleteLast() {
        operationCount["deleteLast"]++;
        if (isEmpty()) return false;
        
        tail = (tail - 1 + capacity) % capacity;
        size--;
        return true;
    }
    
    int getFront() {
        operationCount["getFront"]++;
        return isEmpty() ? -1 : buffer[head];
    }
    
    int getRear() {
        operationCount["getRear"]++;
        return isEmpty() ? -1 : buffer[(tail - 1 + capacity) % capacity];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
    
    // Additional utility methods
    vector<int> toVector() const {
        vector<int> result;
        if (isEmpty()) return result;
        
        int idx = head;
        for (int i = 0; i < size; i++) {
            result.push_back(buffer[idx]);
            idx = (idx + 1) % capacity;
        }
        return result;
    }
    
    unordered_map<string, int> getStatistics() const {
        return operationCount;
    }
    
    double getUtilization() const {
        return static_cast<double>(size) / capacity;
    }
};
```

## Detailed Algorithm Analysis

### Key Design Decisions

1. **Circular Buffer Logic**:
   - Use modular arithmetic for wraparound
   - Maintain separate head and tail pointers
   - Track size explicitly to distinguish empty/full states

2. **Index Management**:
   - Head moves backward on front insertion
   - Tail moves forward on rear insertion
   - Proper handling of negative indices with modular arithmetic

3. **Edge Case Handling**:
   - Empty deque: head == tail && size == 0
   - Full deque: size == capacity
   - Single element: special case for rear pointer calculation

### Mathematical Foundation

For a circular buffer of size `k`:
- Next position: `(index + 1) % k`
- Previous position: `(index - 1 + k) % k`
- Distance between positions: `(end - start + k) % k`

## Complexity Analysis

| Operation | Array-Based | Linked List | Enhanced |
|-----------|-------------|-------------|----------|
| Insert Front | O(1) | O(1) | O(1) |
| Insert Last | O(1) | O(1) | O(1) |
| Delete Front | O(1) | O(1) | O(1) |
| Delete Last | O(1) | O(1) | O(1) |
| Get Front | O(1) | O(1) | O(1) |
| Get Rear | O(1) | O(1) | O(1) |
| Space | O(k) | O(k) | O(k) |

## Test Cases and Usage Examples

### Example 1: Basic Operations
```cpp
void testBasicOperations() {
    MyCircularDeque deque(3);
    
    // Test insertions
    cout << deque.insertLast(1) << endl;    // true
    cout << deque.insertLast(2) << endl;    // true
    cout << deque.insertFront(3) << endl;   // true
    cout << deque.insertFront(4) << endl;   // false (full)
    
    // Test access
    cout << deque.getRear() << endl;        // 2
    cout << deque.getFront() << endl;       // 3
    
    // Test deletions
    cout << deque.deleteLast() << endl;     // true
    cout << deque.insertFront(4) << endl;   // true
    cout << deque.getFront() << endl;       // 4
}
```

### Example 2: Edge Cases
```cpp
void testEdgeCases() {
    MyCircularDeque deque(1);
    
    // Empty deque
    cout << deque.getFront() << endl;       // -1
    cout << deque.getRear() << endl;        // -1
    cout << deque.deleteFront() << endl;    // false
    cout << deque.deleteLast() << endl;     // false
    
    // Single element
    cout << deque.insertFront(1) << endl;   // true
    cout << deque.insertLast(2) << endl;    // false (full)
    cout << deque.getFront() << endl;       // 1
    cout << deque.getRear() << endl;        // 1
}
```

### Example 3: Performance Testing
```cpp
#include <chrono>

void performanceTest() {
    const int capacity = 10000;
    const int operations = 1000000;
    
    MyCircularDeque deque(capacity);
    
    auto start = chrono::high_resolution_clock::now();
    
    // Mixed operations
    for (int i = 0; i < operations; i++) {
        switch (i % 6) {
            case 0: deque.insertFront(i); break;
            case 1: deque.insertLast(i); break;
            case 2: deque.deleteFront(); break;
            case 3: deque.deleteLast(); break;
            case 4: deque.getFront(); break;
            case 5: deque.getRear(); break;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Time for " << operations << " operations: " 
         << duration.count() << " microseconds" << endl;
    cout << "Average time per operation: " 
         << static_cast<double>(duration.count()) / operations << " µs" << endl;
}
```

## Advanced Implementation Features

### Thread-Safe Circular Deque
```cpp
#include <mutex>

class ThreadSafeCircularDeque {
private:
    MyCircularDeque deque;
    mutable mutex mtx;
    
public:
    ThreadSafeCircularDeque(int k) : deque(k) {}
    
    bool insertFront(int value) {
        lock_guard<mutex> lock(mtx);
        return deque.insertFront(value);
    }
    
    bool insertLast(int value) {
        lock_guard<mutex> lock(mtx);
        return deque.insertLast(value);
    }
    
    // Similar implementations for other methods...
};
```

### Iterator Support
```cpp
class IterableCircularDeque : public MyCircularDeque {
public:
    class iterator {
    private:
        const IterableCircularDeque* deque;
        int index;
        int count;
        
    public:
        iterator(const IterableCircularDeque* d, int idx, int c) 
            : deque(d), index(idx), count(c) {}
        
        int operator*() const {
            return deque->buffer[index];
        }
        
        iterator& operator++() {
            index = (index + 1) % deque->capacity;
            count++;
            return *this;
        }
        
        bool operator!=(const iterator& other) const {
            return count != other.count;
        }
    };
    
    iterator begin() const {
        return iterator(this, head, 0);
    }
    
    iterator end() const {
        return iterator(this, head, size);
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **Empty Deque Operations**: All get/delete operations should return false/-1
2. **Full Deque Insertions**: Should return false without modifying state
3. **Single Element**: Front and rear should return same value
4. **Capacity 1**: Special handling for head/tail collision
5. **Wraparound**: Proper modular arithmetic for circular behavior

### Implementation Gotchas
- Negative index handling in previous position calculation
- Distinguishing empty vs full when head == tail
- Proper cleanup in destructor for linked list approach
- Thread safety in concurrent environments

## Pattern Recognition: Queue Reconstruction

This problem demonstrates **Queue Reconstruction** through:

1. **Dynamic Structure**: Ability to modify both ends of the queue
2. **State Management**: Maintaining consistent internal state during operations
3. **Circular Logic**: Reconstructing linear queue behavior in circular space
4. **Capacity Management**: Handling fixed-size constraints efficiently

### Related Pattern Applications
- **LRU Cache**: Deque for maintaining access order
- **Sliding Window**: Deque for maintaining window elements
- **Task Scheduling**: Priority adjustments at both ends

## Variations and Extensions

### Resizable Circular Deque
```cpp
class ResizableCircularDeque {
public:
    void resize(int newCapacity) {
        if (newCapacity < size) return; // Cannot shrink below current size
        
        vector<int> newBuffer(newCapacity);
        int newIndex = 0;
        
        // Copy existing elements
        for (int i = 0; i < size; i++) {
            newBuffer[newIndex++] = buffer[(head + i) % capacity];
        }
        
        buffer = move(newBuffer);
        head = 0;
        tail = size;
        capacity = newCapacity;
    }
};
```

## Related LeetCode Problems

1. **[LeetCode 622] Design Circular Queue** - Single-ended version
2. **[LeetCode 146] LRU Cache** - Uses deque for ordering
3. **[LeetCode 239] Sliding Window Maximum** - Monotonic deque
4. **[LeetCode 862] Shortest Subarray with Sum at Least K** - Deque optimization

## Summary

The Circular Deque design problem showcases advanced queue reconstruction concepts:

- **Efficient Space Usage**: Circular buffer eliminates wasted space
- **Dual-Ended Operations**: Support for both FIFO and LIFO semantics
- **Constant Time**: All operations maintain O(1) time complexity
- **Memory Management**: Careful pointer arithmetic and state tracking

This data structure serves as a foundation for many advanced algorithms and is essential for understanding queue-based optimizations in competitive programming and system design.
