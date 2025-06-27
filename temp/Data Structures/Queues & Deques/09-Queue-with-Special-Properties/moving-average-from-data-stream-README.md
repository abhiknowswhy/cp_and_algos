# Moving Average from Data Stream

## Problem Description
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Implement the `MovingAverage` class:
- `MovingAverage(int size)` Initializes the object with the size of the window
- `double next(int val)` Returns the moving average of the last `size` values of the stream

## Approach
This problem requires maintaining a sliding window of the most recent values. A queue is perfect for this as it provides:
- **FIFO behavior**: Remove oldest values when window is full
- **Efficient insertion**: Add new values to the end
- **Sum tracking**: Maintain running sum for O(1) average calculation

## Algorithm Steps
1. **Initialize queue** with maximum size and running sum tracker
2. **For each new value**: Add to queue and update sum
3. **Check window size**: If queue exceeds size limit, remove oldest value
4. **Calculate average**: Return sum divided by current queue size
5. **Optimize**: Use circular buffer for O(1) space efficiency

## Implementation

### Approach 1: Queue-based Solution
```cpp
#include <queue>

class MovingAverage {
private:
    queue<int> window;
    int maxSize;
    double sum;
    
public:
    MovingAverage(int size) {
        maxSize = size;
        sum = 0.0;
    }
    
    double next(int val) {
        // Add new value
        window.push(val);
        sum += val;
        
        // Remove oldest value if window exceeds size
        if (window.size() > maxSize) {
            sum -= window.front();
            window.pop();
        }
        
        // Return average
        return sum / window.size();
    }
};
```

### Approach 2: Circular Buffer (Optimized)
```cpp
class MovingAverage {
private:
    vector<int> buffer;
    int maxSize;
    int currentSize;
    int head;  // Points to oldest element
    double sum;
    
public:
    MovingAverage(int size) {
        buffer.resize(size);
        maxSize = size;
        currentSize = 0;
        head = 0;
        sum = 0.0;
    }
    
    double next(int val) {
        if (currentSize < maxSize) {
            // Buffer not full yet
            buffer[currentSize] = val;
            sum += val;
            currentSize++;
        } else {
            // Buffer is full, replace oldest value
            sum = sum - buffer[head] + val;
            buffer[head] = val;
            head = (head + 1) % maxSize;
        }
        
        return sum / currentSize;
    }
};
```

### Approach 3: Deque-based Solution
```cpp
#include <deque>

class MovingAverage {
private:
    deque<int> window;
    int maxSize;
    double sum;
    
public:
    MovingAverage(int size) {
        maxSize = size;
        sum = 0.0;
    }
    
    double next(int val) {
        // Add new value to back
        window.push_back(val);
        sum += val;
        
        // Remove oldest value from front if needed
        if (window.size() > maxSize) {
            sum -= window.front();
            window.pop_front();
        }
        
        return sum / window.size();
    }
};
```

### Approach 4: Thread-Safe Version
```cpp
#include <queue>
#include <mutex>

class ThreadSafeMovingAverage {
private:
    queue<int> window;
    int maxSize;
    double sum;
    mutable std::mutex mtx;
    
public:
    ThreadSafeMovingAverage(int size) {
        maxSize = size;
        sum = 0.0;
    }
    
    double next(int val) {
        std::lock_guard<std::mutex> lock(mtx);
        
        window.push(val);
        sum += val;
        
        if (window.size() > maxSize) {
            sum -= window.front();
            window.pop();
        }
        
        return sum / window.size();
    }
    
    double getCurrentAverage() const {
        std::lock_guard<std::mutex> lock(mtx);
        return window.empty() ? 0.0 : sum / window.size();
    }
    
    int getWindowSize() const {
        std::lock_guard<std::mutex> lock(mtx);
        return window.size();
    }
};
```

### Time Complexity
- **Queue approach**: O(1) for each `next()` operation
- **Circular buffer**: O(1) for each `next()` operation  
- **Deque approach**: O(1) amortized for each `next()` operation

### Space Complexity
- **All approaches**: O(size) where size is the window size
- **Circular buffer**: Slightly more memory efficient due to no dynamic allocation

## Examples

### Example 1
```cpp
MovingAverage movingAverage(3);
cout << movingAverage.next(1) << endl;  // 1.0 = (1) / 1
cout << movingAverage.next(10) << endl; // 5.5 = (1 + 10) / 2
cout << movingAverage.next(3) << endl;  // 4.666... = (1 + 10 + 3) / 3
cout << movingAverage.next(5) << endl;  // 6.0 = (10 + 3 + 5) / 3
```

### Example 2
```cpp
MovingAverage movingAverage(1);
cout << movingAverage.next(1) << endl;  // 1.0
cout << movingAverage.next(2) << endl;  // 2.0
cout << movingAverage.next(3) << endl;  // 3.0
```

## Key Insights

### Queue Pattern Usage
- **Sliding window maintenance**: Queue naturally maintains FIFO order
- **Efficient updates**: O(1) insertion and deletion operations
- **Memory management**: Automatic cleanup of old values

### Design Considerations
1. **Sum tracking**: Maintain running sum instead of recalculating each time
2. **Overflow handling**: Use double for sum to avoid integer overflow
3. **Empty window**: Handle edge case when no values have been added
4. **Thread safety**: Consider concurrent access in multi-threaded environments

### Optimization Techniques
- **Circular buffer**: More memory efficient than queue
- **Avoid division**: Store sum and count separately if only integer results needed
- **Batch operations**: Could extend to handle multiple values at once

### Edge Cases
- Window size of 1
- Very large numbers causing overflow
- Empty stream (no values added yet)
- Floating point precision issues

## Variations

### Extended Moving Average
```cpp
class ExtendedMovingAverage {
private:
    deque<int> window;
    int maxSize;
    double sum;
    
public:
    ExtendedMovingAverage(int size) : maxSize(size), sum(0.0) {}
    
    double next(int val) {
        window.push_back(val);
        sum += val;
        
        if (window.size() > maxSize) {
            sum -= window.front();
            window.pop_front();
        }
        
        return sum / window.size();
    }
    
    // Additional methods
    double getVariance() {
        if (window.empty()) return 0.0;
        
        double mean = sum / window.size();
        double variance = 0.0;
        
        for (int val : window) {
            variance += (val - mean) * (val - mean);
        }
        
        return variance / window.size();
    }
    
    int getMin() {
        return window.empty() ? 0 : *min_element(window.begin(), window.end());
    }
    
    int getMax() {
        return window.empty() ? 0 : *max_element(window.begin(), window.end());
    }
};
```

## Related Problems
- Design Hit Counter
- Sliding Window Maximum
- LRU Cache
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
