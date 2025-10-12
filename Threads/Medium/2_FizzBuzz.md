# FizzBuzz Multithreaded Solution

This is a solution to the classic FizzBuzz problem, but implemented with multiple threads. The challenge is to coordinate multiple threads to print numbers from 1 to n where:

- If the number is divisible by 3, print "Fizz"
- If the number is divisible by 5, print "Buzz"
- If the number is divisible by both 3 and 5, print "FizzBuzz"
- Otherwise, print the number itself

## Key Threading Concepts Illustrated

- Mutex for exclusive access to shared state
- Condition variables for thread coordination
- Predicate functions to determine when to wake threads
- Notification to wake waiting threads

This solution demonstrates how to coordinate multiple threads that need to work on a shared sequence of values in a specific order.

Source: [LeetCode - Fizz Buzz Multithreaded](https://leetcode.com/problems/fizz-buzz-multithreaded/)

## Implementation

The solution uses mutex and condition variables to synchronize four threads:

```cpp
class FizzBuzz {
private:
    int n;
    int i;
    mutex mtx;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->i=1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return (i%3==0 and i%5!=0) || i > n; });
            
            if (i>n) break;

            printFizz();
            i++;

            lock.unlock();
            cv.notify_all();
        }
        
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return i%5==0 and i%3!=0 || i > n; });
            
            if (i>n) break;

            printBuzz();
            i++;

            lock.unlock();
            cv.notify_all();
        }

    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return i%15==0 || i > n; });
            
            if (i>n) break;

            printFizzBuzz();
            i++;

            lock.unlock();
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return i%3!=0 and i%5!=0 || i > n; });
            
            if (i>n) break;

            printNumber(i);
            i++;

            lock.unlock();
            cv.notify_all();
        }
    }
};
```

## How It Works:

1. Four threads handle the different output types (Fizz, Buzz, FizzBuzz, and number)
2. Each thread waits for its turn based on the current value of `i`
3. When a thread's condition is met, it prints its output and increments the counter
4. All other threads are notified to check if their conditions are now met
5. The process continues until all numbers from 1 to n have been processed

