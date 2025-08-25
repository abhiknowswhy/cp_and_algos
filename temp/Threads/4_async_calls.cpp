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
