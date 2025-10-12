# Custom Semaphore Implementation in C++

This example demonstrates how to implement a semaphore in C++ without using the built-in semaphore class from C++20. This custom implementation is useful for environments where C++20 features are not available.

## Implementation Details

The semaphore is implemented using:

1. A mutex for thread safety
2. A condition variable for signaling between threads
3. A counter to track available "tokens"

## When to Use

- In environments without C++20 support
- When you need custom semaphore behavior
- When implementing resource pools or thread limits
- For educational purposes to understand how semaphores work

## Example

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    // Initialize with some value (e.g., number of allowed threads)
    Semaphore(int value = 1) : count(value) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return count > 0; });  // Wait until count > 0
        --count;  // Take one "token"
    }

    void release() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;  // Return one "token"
        cv.notify_one();  // Wake one waiting thread
    }
};


Semaphore sem(2);  // Allow 2 threads concurrently

void task(int id) {
    std::cout << "Thread " << id << " waiting...\n";
    sem.acquire();
    std::cout << "Thread " << id << " entered\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread " << id << " leaving\n";
    sem.release();
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);
    std::thread t4(task, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

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
Thread 4 waiting...
Thread 1 leaving
Thread 3 entered
Thread 2 leaving
Thread 4 entered
Thread 3 leaving
Thread 4 leaving
```
