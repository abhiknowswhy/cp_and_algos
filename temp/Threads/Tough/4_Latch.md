# Latches in C++

A latch is a synchronization primitive introduced in C++20 that blocks one or more threads until a specified counter reaches zero. Unlike a barrier, a latch is a single-use mechanism - it doesn't reset after the counter reaches zero.

## Key Concepts

1. **One-time synchronization**: Once released, a latch stays released
2. **Count-down mechanism**: Threads reduce the counter until it reaches zero
3. **Waiting mechanism**: Threads can wait for the counter to reach zero

## Key Methods

1. **count_down()**: Decrements the counter by one
2. **wait()**: Blocks until the counter reaches zero
3. **arrive_and_wait()**: Combines count_down() and wait() in one call
4. **try_wait()**: Non-blocking check if counter is zero

## Use Cases

- Initialization synchronization
- Thread starting gun (have all threads start simultaneously after initialization)
- One-time coordination between parent and child threads
- Waiting for all prerequisites to complete before proceeding

## Differences from Barrier

- Latches are single-use; barriers can be used repeatedly
- Latches don't reset; barriers automatically reset for reuse
- Latches can be counted down by threads that don't wait on them

## Example

```cpp
#include <iostream>
#include <thread>
#include <latch>
#include <vector>

const int num_threads = 3;
std::latch start_latch(num_threads);  // initialized with thread count

void worker(int id) {
    std::cout << "Thread " << id << " initializing\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * (id + 1)));

    std::cout << "Thread " << id << " finished initialization\n";
    start_latch.count_down();  // signal completion
}

int main() {
    std::vector<std::thread> threads;

    // Launch worker threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    // Wait (blocks main thread) until all threads to complete initialization
    start_latch.wait();
    std::cout << "All threads initialized. Main thread continues.\n";

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

Sample output:

```text
Thread 0 initializing
Thread 1 initializing
Thread 2 initializing
Thread 0 finished initialization
Thread 1 finished initialization
Thread 2 finished initialization
All threads initialized. Main thread continues.
```
