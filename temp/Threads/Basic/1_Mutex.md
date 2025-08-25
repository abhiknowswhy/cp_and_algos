# Mutex in C++

A mutex (mutual exclusion) is a synchronization primitive that prevents multiple threads from accessing shared resources simultaneously. It helps avoid race conditions by allowing only one thread to access a critical section of code at a time.

## Key Concepts

1. **Lock**: When a thread acquires a mutex lock, it gains exclusive access to the protected resource.
2. **Unlock**: When a thread is done with the resource, it releases the mutex, allowing other threads to acquire it.
3. **Race Condition Prevention**: By properly using mutexes, you prevent multiple threads from simultaneously modifying shared data.

## When to Use

- When multiple threads need to access shared resources
- When you need to protect critical sections of code
- When you need to ensure data consistency in multi-threaded environments

## Example

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment(const std::string& name) {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        ++counter;
        std::cout << name << " incremented counter to " << counter << "\n";
        mtx.unlock();
    }
}

int main() {
    std::thread t1(increment, "Thread 1");
    std::thread t2(increment, "Thread 2");

    t1.join();
    t2.join();

    return 0;
}
```

Sample output:

```text
Thread 1 incremented counter to 1
Thread 1 incremented counter to 2
Thread 1 incremented counter to 3
Thread 1 incremented counter to 4
Thread 1 incremented counter to 5
Thread 2 incremented counter to 6
Thread 2 incremented counter to 7
Thread 2 incremented counter to 8
Thread 2 incremented counter to 9
Thread 2 incremented counter to 10
```
