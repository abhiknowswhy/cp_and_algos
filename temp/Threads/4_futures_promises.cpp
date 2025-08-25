"""
Promise is a type which will help you continue execution of a thread despite a concrete value not being returned yet iin the program.
Value is set in the promise asynchronously. Promise returns an object of type future.
When value is require, we synchronize by waiting till the future returns the exact value of the object.
"""

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
