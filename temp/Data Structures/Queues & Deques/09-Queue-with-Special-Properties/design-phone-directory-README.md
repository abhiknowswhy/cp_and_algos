# Design Phone Directory

## Problem Description
Design a Phone Directory which supports the following operations:
1. `get()`: Provide a number which is not assigned to anyone.
2. `check(int number)`: Check if a number is available or not.
3. `release(int number)`: Recycle or release a number.

**LeetCode Problem:** [379. Design Phone Directory](https://leetcode.com/problems/design-phone-directory/)

## Approach
Use a queue-based approach to efficiently manage available phone numbers. The key insight is to maintain a pool of available numbers using a queue data structure, along with a boolean array to track which numbers are currently in use.

## Algorithm Steps
1. **Initialization**: Create a queue with all available numbers (0 to maxNumbers-1)
2. **Get Operation**: Dequeue a number from available pool, mark as used
3. **Check Operation**: Query the boolean array to check availability
4. **Release Operation**: Add number back to queue if it was previously assigned

## Implementation

### Approach 1: Queue + Boolean Array (Optimal)
```cpp
#include <queue>
#include <vector>
#include <iostream>
#include <cassert>

class PhoneDirectory {
private:
    std::queue<int> available;
    std::vector<bool> used;
    int maxNumbers;
    
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) : maxNumbers(maxNumbers), used(maxNumbers, false) {
        // Initialize queue with all available numbers
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
        }
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        used[number] = true;
        return number;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        if (number < 0 || number >= maxNumbers) {
            return false;
        }
        return !used[number];
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if (number >= 0 && number < maxNumbers && used[number]) {
            used[number] = false;
            available.push(number);
        }
    }
};
```

### Approach 2: Set-Based Implementation
```cpp
#include <unordered_set>
#include <vector>

class PhoneDirectorySet {
private:
    std::unordered_set<int> available;
    int maxNumbers;
    
public:
    PhoneDirectorySet(int maxNumbers) : maxNumbers(maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            available.insert(i);
        }
    }
    
    int get() {
        if (available.empty()) {
            return -1;
        }
        
        int number = *available.begin();
        available.erase(number);
        return number;
    }
    
    bool check(int number) {
        return available.find(number) != available.end();
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers) {
            available.insert(number);
        }
    }
};
```

### Approach 3: Linked List Implementation
```cpp
#include <vector>

class PhoneDirectoryLinkedList {
private:
    struct Node {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };
    
    Node* head;
    std::vector<bool> used;
    int maxNumbers;
    
public:
    PhoneDirectoryLinkedList(int maxNumbers) : maxNumbers(maxNumbers), used(maxNumbers, false) {
        head = nullptr;
        // Build linked list in reverse order
        for (int i = maxNumbers - 1; i >= 0; i--) {
            Node* newNode = new Node(i);
            newNode->next = head;
            head = newNode;
        }
    }
    
    ~PhoneDirectoryLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    int get() {
        if (!head) {
            return -1;
        }
        
        int number = head->value;
        Node* temp = head;
        head = head->next;
        delete temp;
        
        used[number] = true;
        return number;
    }
    
    bool check(int number) {
        if (number < 0 || number >= maxNumbers) {
            return false;
        }
        return !used[number];
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers && used[number]) {
            used[number] = false;
            Node* newNode = new Node(number);
            newNode->next = head;
            head = newNode;
        }
    }
};
```

### Approach 4: Priority Queue Implementation
```cpp
#include <priority_queue>
#include <vector>

class PhoneDirectoryPQ {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    std::vector<bool> used;
    int maxNumbers;
    
public:
    PhoneDirectoryPQ(int maxNumbers) : maxNumbers(maxNumbers), used(maxNumbers, false) {
        for (int i = 0; i < maxNumbers; i++) {
            minHeap.push(i);
        }
    }
    
    int get() {
        if (minHeap.empty()) {
            return -1;
        }
        
        int number = minHeap.top();
        minHeap.pop();
        used[number] = true;
        return number;
    }
    
    bool check(int number) {
        if (number < 0 || number >= maxNumbers) {
            return false;
        }
        return !used[number];
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers && used[number]) {
            used[number] = false;
            minHeap.push(number);
        }
    }
};
```

### Time Complexity
- **Get**: O(1) average case for queue/linked list, O(log n) for priority queue
- **Check**: O(1) for all approaches
- **Release**: O(1) average case for queue/set, O(log n) for priority queue

### Space Complexity
- **Queue Approach**: O(n) where n is maxNumbers
- **Set Approach**: O(n) where n is maxNumbers
- **All approaches**: O(n) for tracking used numbers

## Examples

### Example 1: Basic Operations
```cpp
void testBasicOperations() {
    PhoneDirectory phoneDirectory(3);
    
    // Initially all numbers 0,1,2 are available
    assert(phoneDirectory.check(0) == true);
    assert(phoneDirectory.check(1) == true);
    assert(phoneDirectory.check(2) == true);
    
    // Get a number
    int num1 = phoneDirectory.get();
    assert(num1 >= 0 && num1 <= 2);
    assert(phoneDirectory.check(num1) == false);
    
    // Get another number
    int num2 = phoneDirectory.get();
    assert(num2 >= 0 && num2 <= 2 && num2 != num1);
    
    // Release a number
    phoneDirectory.release(num1);
    assert(phoneDirectory.check(num1) == true);
    
    std::cout << "Basic operations test passed!" << std::endl;
}
```

### Example 2: Edge Cases
```cpp
void testEdgeCases() {
    PhoneDirectory phoneDirectory(1);
    
    // Get the only available number
    int num = phoneDirectory.get();
    assert(num == 0);
    
    // Try to get another number (should return -1)
    assert(phoneDirectory.get() == -1);
    
    // Check invalid numbers
    assert(phoneDirectory.check(-1) == false);
    assert(phoneDirectory.check(1) == false);
    
    // Release and check again
    phoneDirectory.release(0);
    assert(phoneDirectory.check(0) == true);
    
    // Double release should be safe
    phoneDirectory.release(0);
    assert(phoneDirectory.check(0) == true);
    
    std::cout << "Edge cases test passed!" << std::endl;
}
```

## Advanced Features

### Thread-Safe Implementation
```cpp
#include <mutex>
#include <queue>
#include <vector>

class ThreadSafePhoneDirectory {
private:
    std::queue<int> available;
    std::vector<bool> used;
    int maxNumbers;
    mutable std::mutex mtx;
    
public:
    ThreadSafePhoneDirectory(int maxNumbers) : maxNumbers(maxNumbers), used(maxNumbers, false) {
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
        }
    }
    
    int get() {
        std::lock_guard<std::mutex> lock(mtx);
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        used[number] = true;
        return number;
    }
    
    bool check(int number) const {
        std::lock_guard<std::mutex> lock(mtx);
        if (number < 0 || number >= maxNumbers) {
            return false;
        }
        return !used[number];
    }
    
    void release(int number) {
        std::lock_guard<std::mutex> lock(mtx);
        if (number >= 0 && number < maxNumbers && used[number]) {
            used[number] = false;
            available.push(number);
        }
    }
};
```

### Performance Benchmarking
```cpp
#include <chrono>
#include <random>

void benchmarkPhoneDirectory() {
    const int maxNumbers = 100000;
    const int operations = 1000000;
    
    PhoneDirectory dir(maxNumbers);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxNumbers - 1);
    
    std::vector<int> allocated;
    
    for (int i = 0; i < operations; i++) {
        int op = i % 3;
        if (op == 0) {
            // Get operation
            int num = dir.get();
            if (num != -1) {
                allocated.push_back(num);
            }
        } else if (op == 1 && !allocated.empty()) {
            // Release operation
            int idx = dis(gen) % allocated.size();
            dir.release(allocated[idx]);
            allocated.erase(allocated.begin() + idx);
        } else {
            // Check operation
            int num = dis(gen);
            dir.check(num);
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Benchmark completed: " << operations << " operations in " 
              << duration.count() << " microseconds" << std::endl;
}
```

## Real-World Applications

### 1. Phone Number Management System
```cpp
class TelcoPhoneDirectory {
private:
    PhoneDirectory directory;
    std::unordered_map<int, std::string> numberToCustomer;
    std::unordered_map<std::string, int> customerToNumber;
    
public:
    TelcoPhoneDirectory(int maxNumbers) : directory(maxNumbers) {}
    
    int assignNumber(const std::string& customer) {
        int number = directory.get();
        if (number != -1) {
            numberToCustomer[number] = customer;
            customerToNumber[customer] = number;
        }
        return number;
    }
    
    bool releaseNumber(const std::string& customer) {
        if (customerToNumber.find(customer) != customerToNumber.end()) {
            int number = customerToNumber[customer];
            directory.release(number);
            numberToCustomer.erase(number);
            customerToNumber.erase(customer);
            return true;
        }
        return false;
    }
    
    bool isNumberAvailable(int number) {
        return directory.check(number);
    }
    
    std::string getCustomer(int number) {
        auto it = numberToCustomer.find(number);
        return (it != numberToCustomer.end()) ? it->second : "";
    }
};
```

### 2. Resource Pool Management
```cpp
template<typename ResourceType>
class ResourcePool {
private:
    PhoneDirectory directory;
    std::vector<ResourceType> resources;
    
public:
    ResourcePool(const std::vector<ResourceType>& resourceList) 
        : directory(resourceList.size()), resources(resourceList) {}
    
    std::pair<int, ResourceType*> acquireResource() {
        int id = directory.get();
        if (id == -1) {
            return {-1, nullptr};
        }
        return {id, &resources[id]};
    }
    
    void releaseResource(int id) {
        directory.release(id);
    }
    
    bool isResourceAvailable(int id) {
        return directory.check(id);
    }
};
```

## Notes
- **Memory Efficiency**: Queue approach uses less memory than set for sparse usage
- **Performance**: Queue provides O(1) operations vs O(log n) for priority queue
- **Thread Safety**: Consider using locks for concurrent access
- **Edge Cases**: Handle invalid number ranges and double releases gracefully
- **Real-world Usage**: Common in telecom systems and resource management

## Related Problems
- [LeetCode 379. Design Phone Directory](https://leetcode.com/problems/design-phone-directory/)
- [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/)
- [LeetCode 380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)
- [LeetCode 432. All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/)
- [LeetCode 355. Design Twitter](https://leetcode.com/problems/design-twitter/)

## Pattern: 09-Queue-with-Special-Properties
This problem demonstrates the Queue with Special Properties pattern by:
1. **Queue-based Resource Management**: Using queue to maintain available resources efficiently
2. **State Tracking**: Combining queue with auxiliary data structures for state management
3. **Dynamic Resource Allocation**: Supporting get/release operations with queue semantics
4. **Memory Pool Pattern**: Similar to memory allocators that maintain free block lists

The queue serves as a FIFO container for available phone numbers, making allocation and deallocation operations efficient while maintaining the order of availability.
