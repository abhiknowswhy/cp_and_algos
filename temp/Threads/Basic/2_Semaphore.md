# Semaphores in C++

A semaphore in C++ is a synchronization mechanism used to control access to a shared resource in concurrent programming. It helps avoid race conditions by allowing only a certain number of threads to access a critical section of code at the same time.

## Key Concepts

1. **Counting Semaphore**: Allows a specific number of threads to access a resource simultaneously
2. **Binary Semaphore**: Acts like a mutex, allowing only one thread at a time
3. **Acquire (Wait)**: Decrements the semaphore counter, blocking if counter is already 0
4. **Release (Signal)**: Increments the semaphore counter, potentially unblocking waiting threads

## When to Use

- When you need to limit concurrent access to a resource
- When you need to synchronize multiple threads based on resource availability
- When implementing producer-consumer patterns
- When implementing resource pools with limited capacity

## Example Using C++20 Semaphores

```cpp
#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<2> sem(2); // Maximum 2 threads can enter

void task(int id) {
    std::cout << "Thread " << id << " waiting...\n";
    sem.acquire();  // Try to enter
    std::cout << "Thread " << id << " entered\n";

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work

    std::cout << "Thread " << id << " leaving\n";
    sem.release();  // Exit
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
```

Sample output

```text
Thread 1 waiting...
Thread 1 entered
Thread 2 waiting...
Thread 2 entered
Thread 3 waiting...
Thread 1 leaving
Thread 3 entered
Thread 2 leaving
Thread 3 leaving
```
