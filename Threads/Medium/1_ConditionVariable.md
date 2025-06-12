# Condition Variables in C++

A condition variable is a synchronization primitive used with a mutex to allow threads to wait until a specific condition occurs. It provides a way for threads to communicate with each other about the state of a shared resource.

## Key Concepts

1. **Wait**: Puts the thread to sleep until the condition is met
2. **Notify**: Wakes up one or more waiting threads when a condition changes
3. **Predicate Function**: A condition that must be satisfied to wake up

## When to Use

- When threads need to wait for a specific condition to occur
- For producer-consumer scenarios
- For implementing thread-safe queues
- When coordinating multiple threads that work in stages

## Example: Alternate Thread Printing

This example demonstrates how three threads can coordinate to print numbers from 1 to 100, alternating between even numbers, odd numbers, and commas:

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::string turn = "odd"; // start with even
int current = 1;
int last_val = 100;

void print_even() {
    while (current <= last_val) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return turn == "even" || current > last_val; });
        
        if (current > last_val) break;
        
        if (current % 2 == 0) {
            std::cout << current ;
            current++;
        }
        
        turn = "comma";
        lock.unlock();
        cv.notify_all();
    }
}

void print_odd() {
    while (current <= last_val) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return turn == "odd" || current > last_val; });
        
        if (current > last_val) break;
        
        if (current % 2 == 1) {
            std::cout << current ;
            current++;
        }
        
        turn = "comma";
        lock.unlock();
        cv.notify_all();
    }
}

void print_comma() {
    while (current <= last_val) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return turn == "comma" || current > last_val; });
        
        if (current > last_val) break;

        std::cout << ",";

        if(current%2==0){
            turn = "even";
        } else {
            turn = "odd";
        }

        lock.unlock();
        cv.notify_all();
    }
}


int main() {
    std::thread t1(print_odd);
    std::thread t2(print_even);
    std::thread t3(print_comma);
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}
```

Output:

```text
1,2,3,4,5,...,99,100
```
