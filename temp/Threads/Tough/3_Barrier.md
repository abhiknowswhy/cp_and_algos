# Barriers in C++

A barrier is a synchronization mechanism introduced in C++20 that ensures multiple threads wait until all have reached a certain point in their execution before any of them proceed. This is particularly useful for coordinating threads that work in phases.

## Key Concepts

1. **Synchronization point**: A place where all threads must arrive before any can continue
2. **Arrival**: The act of a thread reaching the barrier
3. **Completion phase function**: Optional function that runs exactly once when all threads arrive

## Key Methods

1. **arrive_and_wait()**: Signals arrival and waits for all threads
2. **arrive_and_drop()**: Signals arrival and reduces the expected count for future synchronizations
3. **arrive()**: Signals arrival without waiting, returns a completion token

## Use Cases

- Parallel algorithms with multiple phases
- Scientific computing that requires step-by-step synchronization
- Graphics rendering pipelines
- Simulation systems where all actors need to finish a time step before proceeding

## Benefits

- Automatic synchronization of multiple threads
- Ability to reuse the same barrier for multiple synchronization points
- More expressive than manual synchronization with condition variables

## Example

```cpp
#include <iostream>
#include <thread>
#include <barrier>
#include <vector>

const int num_threads = 4;

// Barrier object
std::barrier sync_point(num_threads);

void worker(int id) {
    std::cout << "Thread " << id << " doing phase 1 work\n";
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));

    std::cout << "Thread " << id << " waiting at barrier\n";
    sync_point.arrive_and_wait(); // Wait for others

    std::cout << "Thread " << id << " doing phase 2 work\n";
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

Sample output:

```text
Thread 0 doing phase 1 work
Thread 1 doing phase 1 work
Thread 2 doing phase 1 work
Thread 3 doing phase 1 work
Thread 0 waiting at barrier
Thread 1 waiting at barrier
Thread 2 waiting at barrier
Thread 3 waiting at barrier
Thread 0 doing phase 2 work
Thread 1 doing phase 2 work
Thread 2 doing phase 2 work
Thread 3 doing phase 2 work
```
