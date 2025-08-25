# Future and Promise in C++

Futures and promises are synchronization primitives in C++ that enable asynchronous communication between threads. A promise represents a value that will be available in the future, while a future is an object that can retrieve that value when it becomes available.

## Key Concepts

1. **Promise**: A one-time object that can store a value or exception to be retrieved later
2. **Future**: An object that can retrieve a value set by an associated promise
3. **get()**: A method on a future that retrieves the value (blocking if not yet available)

## Use Cases

1. **Asynchronous computation**: One thread performs a computation and another retrieves the result when needed
2. **Producer-consumer pattern**: One thread produces data, another consumes it
3. **Task completion notification**: Notify when a background task completes without polling

## Key Operations

- **prom.set_value(val)**: Sets the value in the promise
- **prom.set_exception(ex)**: Sets an exception in the promise
- **fut.get()**: Gets the value (blocks until available)
- **fut.wait()**: Waits for the value to be available without retrieving it
- **fut.valid()**: Checks if the future can be used (has not been moved from)

## Benefits

1. Clear separation between producer and consumer threads
2. Automatic synchronization without explicit locks
3. Exception propagation between threads
4. One-time communication channel with clear ownership semantics

This pattern is especially useful when a thread needs to return a result, but the calling thread wants to continue execution without waiting.

## Example

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void computeValue(std::promise<int> prom) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate work
    int result = 42;  // some computed result
    prom.set_value(result); // send result to the future
}

int main() {
    std::promise<int> prom;               // Create a promise
    std::future<int> fut = prom.get_future();  // Get future from promise

    std::thread t(computeValue, std::move(prom));  // Launch thread and pass promise

    std::cout << "Waiting for result from worker thread...\n";

    int value = fut.get();  // Blocks until promise sets the value

    std::cout << "Result received: " << value << "\n";

    t.join();
    return 0;
}
```
