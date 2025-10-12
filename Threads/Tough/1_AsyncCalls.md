# Asynchronous Programming in C++

Asynchronous programming in C++ allows you to execute tasks concurrently without manually managing threads. The `<future>` header provides facilities for asynchronous operations, returning results and handling exceptions.

## Key Components

1. **std::async**: A function template that runs a function asynchronously
2. **std::future**: An object that can retrieve values from asynchronous operations
3. **Launch policies**: Control whether to run asynchronously or lazily

## Launch Policies

- **launch::async**: Run the function in a new thread
- **launch::deferred**: Run the function lazily when `get()` or `wait()` is called
- **launch::async | launch::deferred** (default): Implementation decides which policy to use

## Benefits of async

1. **Simplicity**: No need to manually manage threads
2. **Exception propagation**: Exceptions in the async task are propagated to the calling thread
3. **Automatic cleanup**: Resources are properly cleaned up

## When to Use

- For tasks that can run independently
- When you need to retrieve a result from a background task
- For simple parallelism without explicit thread management
- When you need to handle exceptions from background tasks

## Example: Async Factorial Calculation

```cpp
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

// A simple function to compute factorial
int factorial(int n) {
    cout << "Computing factorial of " << n << " in thread " << this_thread::get_id() << "\n";
    this_thread::sleep_for(chrono::seconds(2)); // Simulate delay
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

int main() {
    cout << "Main thread ID: " << this_thread::get_id() << "\n";

    // Launch async task to compute factorial
    future<int> fut = async(launch::async, factorial, 5);

    cout << "Doing other work in main while factorial is being computed...\n";

    // Get the result (blocks until the task completes)
    int result = fut.get();

    cout << "Factorial result: " << result << "\n";

    return 0;
}
```
