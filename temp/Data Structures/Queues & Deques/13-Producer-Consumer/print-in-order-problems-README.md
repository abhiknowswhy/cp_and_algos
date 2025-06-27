# Print in Order Problems - Sequential Producer-Consumer Coordination
## LeetCode Problem 1114

**Difficulty:** Easy  
**Category:** Producer-Consumer, Thread Synchronization  
**Pattern:** Sequential execution coordination with multiple threads

## Problem Description

Suppose we have a class with three methods: `first()`, `second()`, and `third()`. Three different threads A, B, and C will call these methods. Design a mechanism to ensure that:

1. `first()` is called before `second()`
2. `second()` is called before `third()`
3. The methods execute in the correct order regardless of thread arrival order

**Constraints:**
- Multiple threads may call the methods in any order
- Must maintain strict sequential ordering: first → second → third
- Thread-safe implementation required
- Each method should execute exactly once

## Real-World Applications

1. **System Initialization**: Sequential startup procedures
2. **Database Migrations**: Ordered schema updates
3. **Manufacturing Assembly**: Sequential assembly steps
4. **Software Deployment**: Ordered deployment phases
5. **Protocol Handshakes**: Sequential communication steps

## Core Algorithm Approaches

### Approach 1: Semaphore-Based Coordination

Classic approach using counting semaphores:

```cpp
#include <semaphore.h>
#include <functional>

class Foo {
private:
    sem_t sem_first_done;
    sem_t sem_second_done;
    
public:
    Foo() {
        sem_init(&sem_first_done, 0, 0);   // Initially blocked
        sem_init(&sem_second_done, 0, 0);  // Initially blocked
    }
    
    ~Foo() {
        sem_destroy(&sem_first_done);
        sem_destroy(&sem_second_done);
    }

    void first(std::function<void()> printFirst) {
        printFirst();
        sem_post(&sem_first_done);  // Signal first is complete
    }

    void second(std::function<void()> printSecond) {
        sem_wait(&sem_first_done);  // Wait for first to complete
        printSecond();
        sem_post(&sem_second_done); // Signal second is complete
    }

    void third(std::function<void()> printThird) {
        sem_wait(&sem_second_done); // Wait for second to complete
        printThird();
    }
};
```

**Time Complexity:** O(1) per method call  
**Space Complexity:** O(1) constant space

### Approach 2: Condition Variable Implementation

Modern C++ approach with condition variables:

```cpp
#include <mutex>
#include <condition_variable>
#include <functional>

class FooCondVar {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int stage = 0;  // 0: waiting for first, 1: waiting for second, 2: waiting for third
    
public:
    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lock(mtx);
        
        printFirst();
        stage = 1;
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return stage >= 1; });
        
        printSecond();
        stage = 2;
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return stage >= 2; });
        
        printThird();
        stage = 3;
    }
};
```

### Approach 3: Atomic Flag Implementation

Lock-free approach using atomic operations:

```cpp
#include <atomic>
#include <functional>

class FooAtomic {
private:
    std::atomic<bool> first_done{false};
    std::atomic<bool> second_done{false};
    
public:
    void first(std::function<void()> printFirst) {
        printFirst();
        first_done.store(true, std::memory_order_release);
    }

    void second(std::function<void()> printSecond) {
        // Busy wait for first to complete
        while (!first_done.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        
        printSecond();
        second_done.store(true, std::memory_order_release);
    }

    void third(std::function<void()> printThird) {
        // Busy wait for second to complete
        while (!second_done.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        
        printThird();
    }
};
```

### Approach 4: Promise/Future Implementation

C++ futures for one-time signaling:

```cpp
#include <future>
#include <functional>

class FooFuture {
private:
    std::promise<void> first_promise;
    std::promise<void> second_promise;
    std::future<void> first_future;
    std::future<void> second_future;
    
public:
    FooFuture() : first_future(first_promise.get_future()),
                  second_future(second_promise.get_future()) {}

    void first(std::function<void()> printFirst) {
        printFirst();
        first_promise.set_value();
    }

    void second(std::function<void()> printSecond) {
        first_future.wait();
        printSecond();
        second_promise.set_value();
    }

    void third(std::function<void()> printThird) {
        second_future.wait();
        printThird();
    }
};
```

### Approach 5: Queue-Based Producer-Consumer

Traditional queue approach with blocking:

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>

class FooQueue {
private:
    std::queue<int> orderQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    int expectedNext = 1;
    
public:
    void first(std::function<void()> printFirst) {
        executeInOrder(1, printFirst);
    }

    void second(std::function<void()> printSecond) {
        executeInOrder(2, printSecond);
    }

    void third(std::function<void()> printThird) {
        executeInOrder(3, printThird);
    }
    
private:
    void executeInOrder(int order, std::function<void()> func) {
        std::unique_lock<std::mutex> lock(queueMutex);
        
        cv.wait(lock, [this, order] { return expectedNext == order; });
        
        func();
        expectedNext++;
        cv.notify_all();
    }
};
```

## Detailed Algorithm Analysis

### Synchronization Mechanisms

1. **Semaphores**: Traditional Unix-style signaling
2. **Condition Variables**: Modern C++ preferred approach
3. **Atomic Operations**: Lock-free high-performance option
4. **Futures/Promises**: One-time signaling mechanism
5. **Blocking Queues**: Producer-consumer style coordination

### Performance Characteristics

- **Semaphores**: OS kernel calls, moderate overhead
- **Condition Variables**: User-space when possible, good performance
- **Atomics**: Fastest but uses busy waiting (CPU intensive)
- **Futures**: Clean API but higher memory overhead
- **Queues**: Most flexible but highest overhead

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | CPU Usage |
|----------|----------------|------------------|-----------|
| Semaphore | O(1) | O(1) | Low |
| Condition Variable | O(1) | O(1) | Low |
| Atomic | O(1) | O(1) | High (busy wait) |
| Future/Promise | O(1) | O(1) | Low |
| Queue-Based | O(1) | O(1) | Low |

## Test Cases and Usage Examples

### Example 1: Basic Sequential Execution
```cpp
void testBasicExecution() {
    Foo foo;
    std::string output;
    std::mutex outputMutex;
    
    auto printFirst = [&]() {
        std::lock_guard<std::mutex> lock(outputMutex);
        output += "first";
    };
    
    auto printSecond = [&]() {
        std::lock_guard<std::mutex> lock(outputMutex);
        output += "second";
    };
    
    auto printThird = [&]() {
        std::lock_guard<std::mutex> lock(outputMutex);
        output += "third";
    };
    
    // Create threads in reverse order to test synchronization
    std::vector<std::thread> threads;
    threads.emplace_back([&]() { foo.third(printThird); });
    threads.emplace_back([&]() { foo.second(printSecond); });
    threads.emplace_back([&]() { foo.first(printFirst); });
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Output: " << output << std::endl;  // Should be "firstsecondthird"
}
```

### Example 2: Multiple Instances Stress Test
```cpp
void stressTestMultipleInstances() {
    const int NUM_INSTANCES = 1000;
    std::vector<std::unique_ptr<Foo>> instances;
    std::vector<std::thread> threads;
    std::atomic<int> correctOrder{0};
    
    // Create instances
    for (int i = 0; i < NUM_INSTANCES; i++) {
        instances.push_back(std::make_unique<Foo>());
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Create threads for each instance
    for (int i = 0; i < NUM_INSTANCES; i++) {
        std::shared_ptr<std::atomic<int>> counter = std::make_shared<std::atomic<int>>(0);
        
        auto printFirst = [counter, &correctOrder]() {
            int expected = 0;
            if (counter->compare_exchange_strong(expected, 1)) {
                // Successfully incremented from 0 to 1
            } else {
                std::cout << "Order violation in first!" << std::endl;
            }
        };
        
        auto printSecond = [counter]() {
            int expected = 1;
            if (!counter->compare_exchange_strong(expected, 2)) {
                std::cout << "Order violation in second!" << std::endl;
            }
        };
        
        auto printThird = [counter, &correctOrder]() {
            int expected = 2;
            if (counter->compare_exchange_strong(expected, 3)) {
                correctOrder.fetch_add(1);
            } else {
                std::cout << "Order violation in third!" << std::endl;
            }
        };
        
        // Random order threads
        threads.emplace_back([&, i]() { instances[i]->third(printThird); });
        threads.emplace_back([&, i]() { instances[i]->first(printFirst); });
        threads.emplace_back([&, i]() { instances[i]->second(printSecond); });
    }
    
    // Wait for completion
    for (auto& t : threads) {
        t.join();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Completed " << NUM_INSTANCES << " instances in " 
              << duration.count() << " ms" << std::endl;
    std::cout << "Correct order: " << correctOrder.load() << "/" << NUM_INSTANCES << std::endl;
}
```

### Example 3: Performance Comparison
```cpp
void comparePerformance() {
    const int ITERATIONS = 10000;
    
    std::cout << "Performance Comparison (" << ITERATIONS << " iterations):" << std::endl;
    
    // Test Semaphore approach
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < ITERATIONS; i++) {
            Foo foo;
            std::vector<std::thread> threads;
            
            threads.emplace_back([&]() { foo.first([](){}); });
            threads.emplace_back([&]() { foo.second([](){}); });
            threads.emplace_back([&]() { foo.third([](){}); });
            
            for (auto& t : threads) t.join();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Semaphore: " << duration.count() << " ms" << std::endl;
    }
    
    // Test Condition Variable approach
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < ITERATIONS; i++) {
            FooCondVar foo;
            std::vector<std::thread> threads;
            
            threads.emplace_back([&]() { foo.first([](){}); });
            threads.emplace_back([&]() { foo.second([](){}); });
            threads.emplace_back([&]() { foo.third([](){}); });
            
            for (auto& t : threads) t.join();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Condition Variable: " << duration.count() << " ms" << std::endl;
    }
}
```

## Advanced Features and Extensions

### Timeout Support
```cpp
class FooWithTimeout {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int stage = 0;
    
public:
    enum class Result { SUCCESS, TIMEOUT, ERROR };
    
    Result first(std::function<void()> printFirst, 
                std::chrono::milliseconds timeout = std::chrono::milliseconds(1000)) {
        std::unique_lock<std::mutex> lock(mtx);
        
        printFirst();
        stage = 1;
        cv.notify_all();
        return Result::SUCCESS;
    }

    Result second(std::function<void()> printSecond, 
                 std::chrono::milliseconds timeout = std::chrono::milliseconds(1000)) {
        std::unique_lock<std::mutex> lock(mtx);
        
        if (!cv.wait_for(lock, timeout, [this] { return stage >= 1; })) {
            return Result::TIMEOUT;
        }
        
        printSecond();
        stage = 2;
        cv.notify_all();
        return Result::SUCCESS;
    }

    Result third(std::function<void()> printThird, 
                std::chrono::milliseconds timeout = std::chrono::milliseconds(1000)) {
        std::unique_lock<std::mutex> lock(mtx);
        
        if (!cv.wait_for(lock, timeout, [this] { return stage >= 2; })) {
            return Result::TIMEOUT;
        }
        
        printThird();
        stage = 3;
        return Result::SUCCESS;
    }
};
```

### Exception Safety
```cpp
class FooExceptionSafe {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int stage = 0;
    std::exception_ptr exception = nullptr;
    
public:
    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lock(mtx);
        
        try {
            printFirst();
            stage = 1;
        } catch (...) {
            exception = std::current_exception();
            stage = -1;  // Error state
        }
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return stage >= 1 || stage == -1; });
        
        if (stage == -1) {
            std::rethrow_exception(exception);
        }
        
        try {
            printSecond();
            stage = 2;
        } catch (...) {
            exception = std::current_exception();
            stage = -1;
        }
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return stage >= 2 || stage == -1; });
        
        if (stage == -1) {
            std::rethrow_exception(exception);
        }
        
        printThird();
        stage = 3;
    }
};
```

### Monitoring and Debugging
```cpp
class FooDebug {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int stage = 0;
    std::vector<std::string> executionLog;
    std::chrono::steady_clock::time_point startTime;
    
public:
    FooDebug() : startTime(std::chrono::steady_clock::now()) {}
    
    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lock(mtx);
        logEvent("first() called");
        
        printFirst();
        stage = 1;
        logEvent("first() completed");
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(mtx);
        logEvent("second() called, waiting for first()");
        
        cv.wait(lock, [this] { return stage >= 1; });
        logEvent("second() proceeding");
        
        printSecond();
        stage = 2;
        logEvent("second() completed");
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(mtx);
        logEvent("third() called, waiting for second()");
        
        cv.wait(lock, [this] { return stage >= 2; });
        logEvent("third() proceeding");
        
        printThird();
        stage = 3;
        logEvent("third() completed");
    }
    
    void printExecutionLog() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Execution Log:" << std::endl;
        for (const auto& entry : executionLog) {
            std::cout << entry << std::endl;
        }
    }
    
private:
    void logEvent(const std::string& event) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            now - startTime).count();
        executionLog.push_back("[" + std::to_string(elapsed) + "µs] " + event);
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **Single Thread**: All methods called by same thread
2. **Exception in Method**: Cleanup and state consistency
3. **Timeout Scenarios**: Methods waiting too long
4. **Multiple Instances**: Each instance maintains separate state
5. **Resource Cleanup**: Proper destructor behavior

### Implementation Gotchas
- **Spurious Wakeups**: Always use predicate with condition variables
- **Memory Ordering**: Atomic operations need proper memory barriers
- **Exception Safety**: Ensure state consistency during exceptions
- **Deadlock Prevention**: Avoid nested locks

## Pattern Recognition: Producer-Consumer

This problem demonstrates **Producer-Consumer** coordination through:

1. **Sequential Dependencies**: Each step depends on previous completion
2. **Thread Coordination**: Multiple threads accessing shared state
3. **Signaling Mechanisms**: Threads signal completion to waiting threads
4. **State Management**: Tracking execution progress across threads

### Related Sequential Problems
- **Pipeline Processing**: Multi-stage data processing
- **Workflow Engines**: Sequential task execution
- **State Machines**: Ordered state transitions

## Related LeetCode Problems

1. **[LeetCode 1115] Print FooBar Alternately** - Alternating thread coordination
2. **[LeetCode 1116] Print Zero Even Odd** - Complex multi-thread sequencing
3. **[LeetCode 1117] Building H2O** - Resource ratio coordination
4. **[LeetCode 1195] Fizz Buzz Multithreaded** - Complex sequential logic

## Performance Optimization Tips

### Best Practices
1. **Choose Right Primitive**: Condition variables for complex logic, atomics for simple flags
2. **Avoid Busy Waiting**: Use blocking primitives when possible
3. **Memory Barriers**: Ensure proper ordering with atomics
4. **Exception Safety**: Always maintain consistent state

### Common Pitfalls
- **Race Conditions**: Ensure atomic read-modify-write operations
- **Priority Inversion**: Higher priority threads blocked by lower priority
- **Resource Leaks**: Proper cleanup in destructors
- **Performance Degradation**: Excessive synchronization overhead

## Summary

The Print in Order problem demonstrates fundamental Producer-Consumer synchronization:

- **Sequential Coordination**: Ensuring ordered execution across threads
- **Synchronization Primitives**: Multiple approaches with different trade-offs
- **State Management**: Tracking progress and dependencies
- **Error Handling**: Maintaining consistency during failures

Key insights for concurrent programming:
- **Primitive Selection**: Choose synchronization mechanism based on requirements
- **Performance vs Complexity**: Balance simplicity with performance needs
- **Exception Safety**: Always consider failure scenarios
- **Testing**: Stress test with multiple threads and instances

This pattern is fundamental to understanding concurrent programming and appears in many real-world scenarios involving sequential processing, workflow management, and system initialization procedures.
