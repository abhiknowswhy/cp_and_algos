# Building H2O Molecules - Advanced Producer-Consumer Synchronization
## LeetCode Problem 1117

**Difficulty:** Medium  
**Category:** Producer-Consumer, Multithreading  
**Pattern:** Resource coordination with ratio constraints

## Problem Description

There are two kinds of threads: **oxygen** and **hydrogen**. Your goal is to group these threads to form water molecules.

There is a barrier where each thread has to wait until a complete molecule can be formed. Hydrogen and oxygen threads will be given `releaseHydrogen` and `releaseOxygen` methods respectively, which will allow them to pass the barrier. These threads should pass the barrier in groups of three, and they must immediately bond to form an H2O molecule.

You must guarantee that all the threads from one molecule bond before any other threads from the next molecule do.

**Constraints:**
- 2 hydrogen threads + 1 oxygen thread = 1 H2O molecule
- Threads must be released in groups of 3 (H-H-O or H-O-H or O-H-H)
- No partial molecules allowed
- Thread-safe implementation required

## Real-World Applications

1. **Resource Pool Management**: Coordinating different types of resources
2. **Assembly Line Control**: Synchronizing components for manufacturing
3. **Distributed Computing**: Coordinating different worker types
4. **Chemical Process Simulation**: Modeling molecular reactions
5. **Game Development**: Synchronizing different player roles

## Core Algorithm Approaches

### Approach 1: Semaphore-Based Coordination

Classic producer-consumer with counting semaphores:

```cpp
#include <semaphore.h>
#include <functional>
#include <thread>
#include <mutex>

class H2O {
private:
    sem_t hydrogenSem;
    sem_t oxygenSem;
    std::mutex moleculeMutex;
    int hydrogenCount;
    
public:
    H2O() {
        sem_init(&hydrogenSem, 0, 2);  // Allow 2 hydrogen at a time
        sem_init(&oxygenSem, 0, 0);    // Block oxygen initially
        hydrogenCount = 0;
    }
    
    ~H2O() {
        sem_destroy(&hydrogenSem);
        sem_destroy(&oxygenSem);
    }

    void hydrogen(std::function<void()> releaseHydrogen) {
        sem_wait(&hydrogenSem);  // Acquire hydrogen slot
        
        releaseHydrogen();
        
        std::lock_guard<std::mutex> lock(moleculeMutex);
        hydrogenCount++;
        
        if (hydrogenCount == 2) {
            // Signal oxygen to complete molecule
            sem_post(&oxygenSem);
            hydrogenCount = 0;
        }
    }

    void oxygen(std::function<void()> releaseOxygen) {
        sem_wait(&oxygenSem);  // Wait for 2 hydrogen atoms
        
        releaseOxygen();
        
        // Release slots for next molecule
        sem_post(&hydrogenSem);
        sem_post(&hydrogenSem);
    }
};
```

**Time Complexity:** O(1) per thread operation  
**Space Complexity:** O(1) constant space

### Approach 2: Condition Variable Implementation

Modern C++ approach with condition variables:

```cpp
#include <condition_variable>
#include <mutex>
#include <functional>

class H2OCondVar {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int hydrogenCount = 0;
    int oxygenCount = 0;
    bool moleculeReady = false;
    
public:
    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Wait until we can add hydrogen to a forming molecule
        cv.wait(lock, [this] { 
            return hydrogenCount < 2 && !moleculeReady; 
        });
        
        hydrogenCount++;
        releaseHydrogen();
        
        // Check if molecule is complete
        if (hydrogenCount == 2 && oxygenCount == 1) {
            moleculeReady = true;
            cv.notify_all();
        } else {
            cv.notify_all();  // Allow more atoms to join
        }
        
        // Wait for molecule completion
        cv.wait(lock, [this] { return moleculeReady; });
        
        // Reset for next molecule
        if (--hydrogenCount == 0 && oxygenCount == 0) {
            moleculeReady = false;
            cv.notify_all();
        }
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Wait until we can add oxygen to a forming molecule
        cv.wait(lock, [this] { 
            return oxygenCount == 0 && !moleculeReady; 
        });
        
        oxygenCount++;
        releaseOxygen();
        
        // Check if molecule is complete
        if (hydrogenCount == 2 && oxygenCount == 1) {
            moleculeReady = true;
            cv.notify_all();
        } else {
            cv.notify_all();  // Allow more atoms to join
        }
        
        // Wait for molecule completion
        cv.wait(lock, [this] { return moleculeReady; });
        
        // Reset for next molecule
        if (hydrogenCount == 0 && --oxygenCount == 0) {
            moleculeReady = false;
            cv.notify_all();
        }
    }
};
```

### Approach 3: Lock-Free Atomic Implementation

High-performance atomic operations approach:

```cpp
#include <atomic>
#include <functional>

class H2OAtomic {
private:
    std::atomic<int> hydrogenCount{0};
    std::atomic<bool> barrier{false};
    
public:
    void hydrogen(std::function<void()> releaseHydrogen) {
        // Atomic increment and check
        int currentH = hydrogenCount.fetch_add(1);
        
        if (currentH == 1) {
            // Second hydrogen triggers oxygen
            barrier.store(true);
        }
        
        releaseHydrogen();
        
        // Wait for molecule completion
        while (barrier.load()) {
            std::this_thread::yield();
        }
    }

    void oxygen(std::function<void()> releaseOxygen) {
        // Wait for barrier (2 hydrogens ready)
        while (!barrier.load()) {
            std::this_thread::yield();
        }
        
        releaseOxygen();
        
        // Reset for next molecule
        hydrogenCount.store(0);
        barrier.store(false);
    }
};
```

### Approach 4: Queue-Based Producer-Consumer

Traditional queue approach with synchronization:

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class H2OQueue {
private:
    std::queue<std::function<void()>> hydrogenQueue;
    std::queue<std::function<void()>> oxygenQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    
    void tryFormMolecule() {
        std::lock_guard<std::mutex> lock(queueMutex);
        
        if (hydrogenQueue.size() >= 2 && !oxygenQueue.empty()) {
            // Release one complete molecule
            auto h1 = hydrogenQueue.front(); hydrogenQueue.pop();
            auto h2 = hydrogenQueue.front(); hydrogenQueue.pop();
            auto o = oxygenQueue.front(); oxygenQueue.pop();
            
            // Execute in order
            h1();
            h2();
            o();
            
            cv.notify_all();
        }
    }
    
public:
    void hydrogen(std::function<void()> releaseHydrogen) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            hydrogenQueue.push(releaseHydrogen);
        }
        
        tryFormMolecule();
        
        // Wait if not yet processed
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [this, &releaseHydrogen] {
            // Check if our function was executed by seeing if queue size changed
            return true; // Simplified for example
        });
    }

    void oxygen(std::function<void()> releaseOxygen) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            oxygenQueue.push(releaseOxygen);
        }
        
        tryFormMolecule();
        
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [this] { return true; }); // Simplified
    }
};
```

## Detailed Algorithm Analysis

### Synchronization Patterns

1. **Barrier Synchronization**: Threads wait until group is complete
2. **Resource Counting**: Track available hydrogen/oxygen slots
3. **Atomic Operations**: Lock-free coordination when possible
4. **Condition Waiting**: Block threads until resources available

### Key Design Decisions

- **Resource Ratios**: 2:1 hydrogen to oxygen ratio enforcement
- **Deadlock Prevention**: Careful ordering of lock acquisition
- **Fairness**: Ensure all threads eventually proceed
- **Performance**: Balance between correctness and speed

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Concurrency |
|----------|----------------|------------------|-------------|
| Semaphore | O(1) | O(1) | High |
| Condition Variable | O(1) | O(1) | Medium |
| Atomic | O(1) | O(1) | Very High |
| Queue-Based | O(1) amortized | O(n) | Medium |

## Test Cases and Usage Examples

### Example 1: Basic Molecule Formation
```cpp
void testBasicMoleculeFormation() {
    H2O water;
    std::vector<std::string> output;
    std::mutex outputMutex;
    
    auto hydrogenRelease = [&]() {
        std::lock_guard<std::mutex> lock(outputMutex);
        output.push_back("H");
    };
    
    auto oxygenRelease = [&]() {
        std::lock_guard<std::mutex> lock(outputMutex);
        output.push_back("O");
    };
    
    // Create threads
    std::vector<std::thread> threads;
    
    // Add 4 hydrogen and 2 oxygen (should form 2 molecules)
    for (int i = 0; i < 4; i++) {
        threads.emplace_back([&]() { water.hydrogen(hydrogenRelease); });
    }
    for (int i = 0; i < 2; i++) {
        threads.emplace_back([&]() { water.oxygen(oxygenRelease); });
    }
    
    // Wait for completion
    for (auto& t : threads) {
        t.join();
    }
    
    // Verify output (should have 4 H's and 2 O's in groups of 3)
    std::cout << "Output: ";
    for (const auto& atom : output) {
        std::cout << atom << " ";
    }
    std::cout << std::endl;
}
```

### Example 2: Stress Testing
```cpp
void stressTest() {
    H2O water;
    std::atomic<int> hydrogenCount{0};
    std::atomic<int> oxygenCount{0};
    
    const int NUM_MOLECULES = 1000;
    const int NUM_HYDROGEN = NUM_MOLECULES * 2;
    const int NUM_OXYGEN = NUM_MOLECULES;
    
    auto hydrogenRelease = [&]() {
        hydrogenCount.fetch_add(1);
    };
    
    auto oxygenRelease = [&]() {
        oxygenCount.fetch_add(1);
    };
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;
    
    // Create hydrogen threads
    for (int i = 0; i < NUM_HYDROGEN; i++) {
        threads.emplace_back([&]() { water.hydrogen(hydrogenRelease); });
    }
    
    // Create oxygen threads
    for (int i = 0; i < NUM_OXYGEN; i++) {
        threads.emplace_back([&]() { water.oxygen(oxygenRelease); });
    }
    
    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Formed " << NUM_MOLECULES << " molecules in " 
              << duration.count() << " ms" << std::endl;
    std::cout << "H: " << hydrogenCount.load() << ", O: " << oxygenCount.load() << std::endl;
}
```

### Example 3: Deadlock Detection
```cpp
class DeadlockDetector {
private:
    std::atomic<bool> deadlockDetected{false};
    std::chrono::steady_clock::time_point lastProgress;
    std::mutex progressMutex;
    
public:
    void markProgress() {
        std::lock_guard<std::mutex> lock(progressMutex);
        lastProgress = std::chrono::steady_clock::now();
    }
    
    void checkForDeadlock() {
        auto now = std::chrono::steady_clock::now();
        auto timeSinceProgress = std::chrono::duration_cast<std::chrono::seconds>(
            now - lastProgress).count();
        
        if (timeSinceProgress > 5) { // 5 second timeout
            deadlockDetected.store(true);
            std::cout << "Potential deadlock detected!" << std::endl;
        }
    }
    
    bool isDeadlocked() const {
        return deadlockDetected.load();
    }
};
```

## Advanced Features and Extensions

### Molecule Order Tracking
```cpp
class H2OWithOrdering {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int hydrogenCount = 0;
    int moleculeId = 0;
    std::vector<std::string> moleculeSequence;
    
public:
    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [this] { return hydrogenCount < 2; });
        
        int currentMolecule = moleculeId;
        hydrogenCount++;
        
        releaseHydrogen();
        moleculeSequence.push_back("H" + std::to_string(currentMolecule));
        
        if (hydrogenCount == 2) {
            cv.notify_all();
        }
        
        // Wait for molecule completion
        cv.wait(lock, [this, currentMolecule] { 
            return moleculeId > currentMolecule; 
        });
    }
    
    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [this] { return hydrogenCount == 2; });
        
        releaseOxygen();
        moleculeSequence.push_back("O" + std::to_string(moleculeId));
        
        // Complete molecule
        hydrogenCount = 0;
        moleculeId++;
        cv.notify_all();
    }
    
    std::vector<std::string> getMoleculeSequence() const {
        return moleculeSequence;
    }
};
```

### Performance Monitoring
```cpp
class H2OProfiler {
private:
    H2O water;
    std::atomic<long long> totalWaitTime{0};
    std::atomic<int> moleculesFormed{0};
    
public:
    void hydrogen(std::function<void()> releaseHydrogen) {
        auto start = std::chrono::high_resolution_clock::now();
        
        water.hydrogen([&, start]() {
            auto end = std::chrono::high_resolution_clock::now();
            auto waitTime = std::chrono::duration_cast<std::chrono::microseconds>(
                end - start).count();
            totalWaitTime.fetch_add(waitTime);
            
            releaseHydrogen();
        });
    }
    
    void oxygen(std::function<void()> releaseOxygen) {
        auto start = std::chrono::high_resolution_clock::now();
        
        water.oxygen([&, start]() {
            auto end = std::chrono::high_resolution_clock::now();
            auto waitTime = std::chrono::duration_cast<std::chrono::microseconds>(
                end - start).count();
            totalWaitTime.fetch_add(waitTime);
            moleculesFormed.fetch_add(1);
            
            releaseOxygen();
        });
    }
    
    void printStats() {
        std::cout << "Molecules formed: " << moleculesFormed.load() << std::endl;
        std::cout << "Average wait time: " 
                  << (totalWaitTime.load() / 3.0 / moleculesFormed.load()) 
                  << " µs per atom" << std::endl;
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **Unbalanced Input**: More hydrogen than oxygen or vice versa
2. **Single Thread**: Only one type of atom provided
3. **High Contention**: Many threads competing for resources
4. **Resource Starvation**: One type of thread never gets to proceed
5. **Exception Safety**: Cleanup when threads throw exceptions

### Implementation Gotchas
- **Race Conditions**: Careful ordering of operations
- **Memory Barriers**: Ensuring visibility of shared state
- **Thread Cleanup**: Proper resource cleanup on early exit
- **Spurious Wakeups**: Handling condition variable edge cases

## Pattern Recognition: Producer-Consumer

This problem exemplifies **Producer-Consumer** pattern through:

1. **Resource Coordination**: Multiple producer types creating shared output
2. **Ratio Constraints**: Specific ratios required for consumption
3. **Synchronization Barriers**: Groups must form completely before proceeding
4. **Thread Safety**: Multiple concurrent threads accessing shared state

### Related Producer-Consumer Problems
- **Bounded Buffer**: Classic single producer-consumer
- **Reader-Writer**: Multiple readers, single writer coordination
- **Dining Philosophers**: Resource contention and deadlock avoidance

## Mathematical Properties

### Theoretical Analysis
- **Minimum Wait Time**: O(1) when resources perfectly balanced
- **Maximum Throughput**: Limited by slowest thread type
- **Scalability**: Performance degrades with thread contention
- **Resource Utilization**: 100% when input ratios match 2:1

### Queuing Theory Applications
- **Little's Law**: Relationship between arrival rate and queue length
- **Utilization Analysis**: Efficiency of resource usage
- **Bottleneck Identification**: Finding limiting factors

## Related LeetCode Problems

1. **[LeetCode 1188] Design Bounded Blocking Queue** - Basic producer-consumer
2. **[LeetCode 1115] Print FooBar Alternately** - Thread coordination
3. **[LeetCode 1116] Print Zero Even Odd** - Multi-thread synchronization
4. **[LeetCode 1195] Fizz Buzz Multithreaded** - Complex thread coordination

## Summary

The Building H2O Molecules problem demonstrates advanced Producer-Consumer synchronization:

- **Resource Ratios**: Coordinating different types of producers
- **Barrier Synchronization**: Ensuring complete groups before proceeding
- **Thread Safety**: Multiple concurrent access patterns
- **Performance Optimization**: Balancing correctness with speed

Key insights for multithreaded programming:
- **Synchronization Primitives**: Choose appropriate tools (semaphores, condition variables, atomics)
- **Deadlock Prevention**: Careful ordering and timeout mechanisms
- **Performance Monitoring**: Track wait times and throughput
- **Resource Management**: Handle unbalanced inputs gracefully

This pattern appears in manufacturing systems, resource pools, and distributed computing scenarios, making it essential for understanding complex synchronization challenges in concurrent programming.
