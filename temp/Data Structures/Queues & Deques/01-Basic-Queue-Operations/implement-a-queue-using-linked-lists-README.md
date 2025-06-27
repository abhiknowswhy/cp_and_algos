# Implement a queue using linked lists

## Problem Description
Implement a queue using a singly linked list. The queue should support:
- `enqueue(x)`: Add element x to the rear of the queue
- `dequeue()`: Remove and return the front element
- `front()`: Get the front element without removing it
- `isEmpty()`: Check if the queue is empty
- `size()`: Get the number of elements in the queue

## Approach
Use a singly linked list with head and tail pointers. Head points to the front (for dequeue) and tail points to the rear (for enqueue). This allows O(1) operations at both ends.

## Algorithm Steps
1. Create a ListNode structure with data and next pointer
2. Maintain head and tail pointers and size counter
3. For enqueue: Create new node, link from tail, update tail
4. For dequeue: Remove head node, update head, return data

## Implementation

### C++
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class QueueLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;
    
public:
    QueueLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~QueueLinkedList() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(int x) {
        ListNode* newNode = new ListNode(x);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    int dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        
        int result = head->val;
        ListNode* temp = head;
        head = head->next;
        
        if (head == nullptr) { // Queue becomes empty
            tail = nullptr;
        }
        
        delete temp;
        size--;
        return result;
    }
    
    int front() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return head->val;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    int getSize() {
        return size;
    }
    
    void display() {
        ListNode* current = head;
        cout << "Queue: ";
        while (current) {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }
};
```

### Time Complexity
- Enqueue: O(1)
- Dequeue: O(1)
- Front: O(1)
- isEmpty: O(1)
- Size: O(1)

### Space Complexity
O(n) where n is the number of elements in the queue

## Examples

### Example 1
```
Input: 
enqueue(1), enqueue(2), enqueue(3), dequeue(), front(), dequeue()

Output: 
Queue after enqueues: 1 2 3
Dequeue returns: 1
Front returns: 2  
Dequeue returns: 2
Final queue: 3

Explanation: 
Elements are added to rear and removed from front (FIFO)
```

### Example 2
```
Input: 
enqueue(5), dequeue(), isEmpty(), enqueue(10), size()

Output: 
Dequeue returns: 5
isEmpty returns: true
Size returns: 1

Explanation: 
Queue becomes empty after dequeue, then new element added
```

## Notes
- Dynamic memory allocation allows unlimited queue size (memory permitting)
- Need to handle memory cleanup to avoid memory leaks
- Tail pointer optimization allows O(1) enqueue vs O(n) without it
- Special case when queue becomes empty (both head and tail become null)

## Related Problems
- [LeetCode 232 - Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
- [LeetCode 225 - Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
- [LeetCode 622 - Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
- [LeetCode 641 - Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)

## Pattern: 01-Basic-Queue-Operations
This implements the fundamental queue operations using dynamic memory allocation. Unlike array implementation, it doesn't have size limitations but requires careful memory management. Essential for understanding queue behavior before moving to advanced patterns.
