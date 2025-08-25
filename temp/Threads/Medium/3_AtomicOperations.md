# Atomic Operations in C++

Atomic operations in C++ provide a way to perform thread-safe operations on variables without using mutexes or other synchronization primitives. The `<atomic>` header provides atomic types and operations that are guaranteed to be atomic by the hardware.

## Key Concepts:

1. **Atomic Types**: Special types that ensure operations are indivisible
2. **Atomic Operations**: Read, write, and read-modify-write operations that appear to execute instantaneously
3. **Memory Ordering**: Rules that govern how memory accesses are ordered

## What Makes This Thread-Safe?

Unlike the non-atomic version which could have race conditions, the atomic counter guarantees that:

1. The increment operation is atomic - no other thread can interrupt it
2. Memory is synchronized correctly between threads
3. No data races occur when accessing the counter
4. The final result will always be correct (200)

## Common Atomic Operations

- `load()`: Read the value atomically
- `store()`: Write the value atomically
- `exchange()`: Replace with new value and return old value
- `fetch_add()`: Add value and return old value
- `fetch_sub()`: Subtract value and return old value
- `compare_exchange_weak()`, `compare_exchange_strong()`: Compare and swap if equal

## When to Use

- Simple shared counters between threads
- Flag variables for synchronization
- When performance is critical (atomic operations are generally faster than mutex locks)
- Lock-free and wait-free algorithms


## Example: Thread-Safe Counter

This example demonstrates how to use atomic operations to implement a thread-safe counter:

```cpp
#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

atomic<int> counter(0); // Atomic integer

void increment_counter(int id)
{
    for (int i = 0; i < 100; ++i) {
        // Increment counter atomically
        counter.fetch_add(1);
    }
}

int main()
{
    thread t1(increment_counter, 1);
    thread t2(increment_counter, 2);
    
    t1.join();
    t2.join();
    
    cout << "Counter: " << counter.load() << std::endl; // Should always be 200

    return 0;
}
```
