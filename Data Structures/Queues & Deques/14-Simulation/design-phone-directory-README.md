# Design Phone Directory - Queue-Based Resource Management Simulation
## LeetCode Problem 379

**Difficulty:** Medium  
**Category:** Simulation, Resource Management  
**Pattern:** Queue-based available resource tracking with efficient allocation/deallocation

## Problem Description

Design a phone directory which supports the following operations:

1. `get()`: Provide a number which is not assigned to anyone.
2. `check(number)`: Check if a number is available or not.
3. `release(number)`: Recycle or release a number.

**Constraints:**
- Numbers range from 0 to maxNumbers-1
- get() should return the smallest available number
- Operations should be efficient
- Support multiple get/release cycles

## Real-World Applications

1. **Resource Pool Management**: Database connection pools, thread pools
2. **ID Generation Systems**: Unique identifier allocation in distributed systems
3. **Memory Management**: Free block tracking in memory allocators
4. **License Management**: Software license allocation and tracking
5. **Parking Systems**: Available parking spot management

## Core Algorithm Approaches

### Approach 1: Queue + Set Hybrid (Optimal)

Combine queue for O(1) allocation with set for O(1) availability checking:

```cpp
#include <queue>
#include <unordered_set>
using namespace std;

class PhoneDirectory {
private:
    queue<int> available;           // Queue of available numbers
    unordered_set<int> availableSet; // Set for O(1) lookup
    int maxNumbers;
    
public:
    PhoneDirectory(int maxNumbers) : maxNumbers(maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
            availableSet.insert(i);
        }
    }
    
    int get() {
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        availableSet.erase(number);
        return number;
    }
    
    bool check(int number) {
        return number >= 0 && number < maxNumbers && 
               availableSet.find(number) != availableSet.end();
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers && 
            availableSet.find(number) == availableSet.end()) {
            available.push(number);
            availableSet.insert(number);
        }
    }
};
```

**Time Complexity:** O(1) for all operations  
**Space Complexity:** O(n) where n is maxNumbers

### Approach 2: Boolean Array with Queue

Simple approach using boolean array for tracking:

```cpp
class PhoneDirectoryArray {
private:
    vector<bool> isAvailable;
    queue<int> available;
    int maxNumbers;
    
public:
    PhoneDirectoryArray(int maxNumbers) : maxNumbers(maxNumbers) {
        isAvailable.resize(maxNumbers, true);
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
        }
    }
    
    int get() {
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        isAvailable[number] = false;
        return number;
    }
    
    bool check(int number) {
        return number >= 0 && number < maxNumbers && isAvailable[number];
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers && !isAvailable[number]) {
            isAvailable[number] = true;
            available.push(number);
        }
    }
};
```

### Approach 3: Priority Queue for Smallest Number

Ensures get() returns smallest available number:

```cpp
#include <priority_queue>

class PhoneDirectoryPQ {
private:
    priority_queue<int, vector<int>, greater<int>> available; // Min heap
    vector<bool> isAvailable;
    int maxNumbers;
    
public:
    PhoneDirectoryPQ(int maxNumbers) : maxNumbers(maxNumbers) {
        isAvailable.resize(maxNumbers, true);
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
        }
    }
    
    int get() {
        // Clean up invalid entries from top
        while (!available.empty() && !isAvailable[available.top()]) {
            available.pop();
        }
        
        if (available.empty()) {
            return -1;
        }
        
        int number = available.top();
        available.pop();
        isAvailable[number] = false;
        return number;
    }
    
    bool check(int number) {
        return number >= 0 && number < maxNumbers && isAvailable[number];
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers && !isAvailable[number]) {
            isAvailable[number] = true;
            available.push(number);
        }
    }
};
```

### Approach 4: Advanced Resource Pool with Statistics

Enhanced implementation with monitoring and optimization:

```cpp
#include <chrono>
#include <unordered_map>

class AdvancedPhoneDirectory {
private:
    queue<int> available;
    unordered_set<int> availableSet;
    unordered_map<int, chrono::steady_clock::time_point> allocatedTime;
    int maxNumbers;
    
    // Statistics
    int totalAllocations = 0;
    int totalReleases = 0;
    int peakUsage = 0;
    chrono::steady_clock::time_point startTime;
    
public:
    AdvancedPhoneDirectory(int maxNumbers) : maxNumbers(maxNumbers) {
        startTime = chrono::steady_clock::now();
        
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
            availableSet.insert(i);
        }
    }
    
    int get() {
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        availableSet.erase(number);
        
        // Record allocation
        allocatedTime[number] = chrono::steady_clock::now();
        totalAllocations++;
        
        int currentUsage = maxNumbers - available.size();
        peakUsage = max(peakUsage, currentUsage);
        
        return number;
    }
    
    bool check(int number) {
        return number >= 0 && number < maxNumbers && 
               availableSet.find(number) != availableSet.end();
    }
    
    void release(int number) {
        if (number >= 0 && number < maxNumbers && 
            availableSet.find(number) == availableSet.end()) {
            
            available.push(number);
            availableSet.insert(number);
            allocatedTime.erase(number);
            totalReleases++;
        }
    }
    
    // Utility methods
    int getAvailableCount() const {
        return available.size();
    }
    
    int getAllocatedCount() const {
        return maxNumbers - available.size();
    }
    
    double getUtilizationRate() const {
        return static_cast<double>(getAllocatedCount()) / maxNumbers;
    }
    
    vector<int> getAvailableNumbers() const {
        queue<int> temp = available;
        vector<int> result;
        while (!temp.empty()) {
            result.push_back(temp.front());
            temp.pop();
        }
        return result;
    }
    
    unordered_map<string, int> getStatistics() const {
        return {
            {"totalAllocations", totalAllocations},
            {"totalReleases", totalReleases},
            {"currentAllocated", getAllocatedCount()},
            {"peakUsage", peakUsage},
            {"availableCount", getAvailableCount()}
        };
    }
};
```

## Detailed Algorithm Analysis

### Design Decisions

1. **Data Structure Choice**: Queue provides FIFO ordering, set provides fast lookup
2. **Memory vs Speed Trade-off**: Hybrid approach balances both requirements
3. **Edge Case Handling**: Validate input ranges and double-release protection
4. **Resource Tracking**: Maintain both allocated and available state

### Key Implementation Considerations

- **Duplicate Release Prevention**: Check if number already available
- **Range Validation**: Ensure number is within valid range
- **Empty Pool Handling**: Return -1 when no numbers available
- **Smallest Number Guarantee**: Use appropriate data structure

## Complexity Analysis

| Approach | get() | check() | release() | Space |
|----------|-------|---------|-----------|-------|
| Queue + Set | O(1) | O(1) | O(1) | O(n) |
| Boolean Array | O(1) | O(1) | O(1) | O(n) |
| Priority Queue | O(log n) | O(1) | O(log n) | O(n) |
| Advanced | O(1) | O(1) | O(1) | O(n) |

## Test Cases and Usage Examples

### Example 1: Basic Operations
```cpp
void testBasicOperations() {
    PhoneDirectory directory(3);
    
    cout << "Initial state:" << endl;
    cout << "get(): " << directory.get() << endl;     // 0
    cout << "get(): " << directory.get() << endl;     // 1
    cout << "check(0): " << directory.check(0) << endl;  // false
    cout << "get(): " << directory.get() << endl;     // 2
    cout << "check(2): " << directory.check(2) << endl;  // false
    cout << "release(2)" << endl;
    directory.release(2);
    cout << "check(2): " << directory.check(2) << endl;  // true
    cout << "get(): " << directory.get() << endl;     // 2
}
```

### Example 2: Edge Cases
```cpp
void testEdgeCases() {
    PhoneDirectory directory(2);
    
    // Exhaust all numbers
    int num1 = directory.get();  // 0
    int num2 = directory.get();  // 1
    int num3 = directory.get();  // -1 (no more available)
    
    cout << "Numbers: " << num1 << ", " << num2 << ", " << num3 << endl;
    
    // Invalid operations
    directory.release(-1);       // Invalid number
    directory.release(5);        // Out of range
    directory.release(0);        // Valid release
    directory.release(0);        // Duplicate release (should be ignored)
    
    cout << "After releases, get(): " << directory.get() << endl; // 0
}
```

### Example 3: Performance Testing
```cpp
void performanceTest() {
    const int MAX_NUMBERS = 100000;
    const int OPERATIONS = 1000000;
    
    AdvancedPhoneDirectory directory(MAX_NUMBERS);
    
    auto start = chrono::high_resolution_clock::now();
    
    // Mixed operations
    vector<int> allocated;
    for (int i = 0; i < OPERATIONS; i++) {
        if (i % 3 == 0 && !allocated.empty()) {
            // Release a random number
            int idx = rand() % allocated.size();
            directory.release(allocated[idx]);
            allocated.erase(allocated.begin() + idx);
        } else {
            // Get a number
            int num = directory.get();
            if (num != -1) {
                allocated.push_back(num);
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Performance Test Results:" << endl;
    cout << "Operations: " << OPERATIONS << endl;
    cout << "Time: " << duration.count() << " ms" << endl;
    cout << "Ops/second: " << (OPERATIONS * 1000.0 / duration.count()) << endl;
    
    auto stats = directory.getStatistics();
    for (const auto& [key, value] : stats) {
        cout << key << ": " << value << endl;
    }
}
```

## Advanced Features and Extensions

### Thread-Safe Version
```cpp
#include <mutex>

class ThreadSafePhoneDirectory {
private:
    queue<int> available;
    unordered_set<int> availableSet;
    mutable mutex mtx;
    int maxNumbers;
    
public:
    ThreadSafePhoneDirectory(int maxNumbers) : maxNumbers(maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
            availableSet.insert(i);
        }
    }
    
    int get() {
        lock_guard<mutex> lock(mtx);
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        availableSet.erase(number);
        return number;
    }
    
    bool check(int number) const {
        lock_guard<mutex> lock(mtx);
        return number >= 0 && number < maxNumbers && 
               availableSet.find(number) != availableSet.end();
    }
    
    void release(int number) {
        lock_guard<mutex> lock(mtx);
        if (number >= 0 && number < maxNumbers && 
            availableSet.find(number) == availableSet.end()) {
            available.push(number);
            availableSet.insert(number);
        }
    }
};
```

### Range-Based Directory
```cpp
class RangePhoneDirectory {
private:
    queue<int> available;
    unordered_set<int> availableSet;
    int minNumber, maxNumber;
    
public:
    RangePhoneDirectory(int minNum, int maxNum) 
        : minNumber(minNum), maxNumber(maxNum) {
        for (int i = minNumber; i <= maxNumber; i++) {
            available.push(i);
            availableSet.insert(i);
        }
    }
    
    int get() {
        if (available.empty()) {
            return -1;
        }
        
        int number = available.front();
        available.pop();
        availableSet.erase(number);
        return number;
    }
    
    bool check(int number) {
        return number >= minNumber && number <= maxNumber && 
               availableSet.find(number) != availableSet.end();
    }
    
    void release(int number) {
        if (number >= minNumber && number <= maxNumber && 
            availableSet.find(number) == availableSet.end()) {
            available.push(number);
            availableSet.insert(number);
        }
    }
    
    pair<int, int> getRange() const {
        return {minNumber, maxNumber};
    }
};
```

### Batch Operations Support
```cpp
class BatchPhoneDirectory {
private:
    queue<int> available;
    unordered_set<int> availableSet;
    int maxNumbers;
    
public:
    BatchPhoneDirectory(int maxNumbers) : maxNumbers(maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
            availableSet.insert(i);
        }
    }
    
    vector<int> getBatch(int count) {
        vector<int> result;
        for (int i = 0; i < count && !available.empty(); i++) {
            int number = available.front();
            available.pop();
            availableSet.erase(number);
            result.push_back(number);
        }
        return result;
    }
    
    void releaseBatch(const vector<int>& numbers) {
        for (int number : numbers) {
            if (number >= 0 && number < maxNumbers && 
                availableSet.find(number) == availableSet.end()) {
                available.push(number);
                availableSet.insert(number);
            }
        }
    }
    
    bool checkBatch(const vector<int>& numbers) {
        for (int number : numbers) {
            if (!check(number)) {
                return false;
            }
        }
        return true;
    }
    
    bool check(int number) {
        return number >= 0 && number < maxNumbers && 
               availableSet.find(number) != availableSet.end();
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **Empty Directory**: All numbers allocated, get() returns -1
2. **Invalid Numbers**: Negative numbers or out-of-range values
3. **Duplicate Releases**: Releasing already available numbers
4. **Boundary Values**: Numbers at 0 and maxNumbers-1
5. **Single Number**: Directory with only one number

### Implementation Gotchas
- **Memory Leaks**: Proper cleanup of data structures
- **Integer Overflow**: Large maxNumbers values
- **Thread Safety**: Concurrent access in multi-threaded environments
- **Performance Degradation**: Efficiency with large number pools

## Pattern Recognition: Simulation

This problem demonstrates **Simulation** through:

1. **Resource State Modeling**: Tracking available vs allocated resources
2. **Real-Time Operations**: Dynamic allocation and deallocation
3. **System Behavior Simulation**: Mimicking real-world resource management
4. **State Transitions**: Resources move between available and allocated states

### Related Resource Management Problems
- **Memory Allocators**: Free block management
- **Database Connection Pools**: Connection lifecycle management
- **Thread Pools**: Worker thread allocation

## Optimization Techniques

### Memory Optimization
- **Bit Vectors**: Use bits instead of booleans for large ranges
- **Sparse Representation**: Only track allocated numbers for sparse usage
- **Memory Pools**: Pre-allocate memory for frequent operations

### Performance Optimization
- **Lazy Cleanup**: Defer expensive operations when possible
- **Batch Processing**: Group operations for better cache locality
- **Load Balancing**: Distribute numbers across multiple pools

## Related LeetCode Problems

1. **[LeetCode 1206] Design Skiplist** - Advanced data structure design
2. **[LeetCode 380] Insert Delete GetRandom O(1)** - Efficient random access
3. **[LeetCode 1603] Design Parking System** - Resource allocation simulation
4. **[LeetCode 146] LRU Cache** - Resource management with eviction

## Summary

The Design Phone Directory problem showcases essential Simulation concepts:

- **Resource Pool Management**: Efficient tracking of available resources
- **State Synchronization**: Maintaining consistency between data structures
- **Performance Optimization**: Balancing time and space complexity
- **Real-World Modeling**: Simulating practical resource allocation systems

Key takeaways for system design:
- **Data Structure Selection**: Choose structures that optimize for common operations
- **State Management**: Maintain multiple views of state for different access patterns
- **Scalability Considerations**: Design for growth in resource pool size
- **Monitoring Integration**: Build in observability from the start

This pattern is fundamental for understanding resource management in operating systems, database systems, and distributed computing platforms where efficient allocation and tracking of limited resources is crucial.
