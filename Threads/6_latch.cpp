"""
In C++, a latch is a synchronization primitive introduced in C++20 (defined in <latch>). It is used to block one or more threads until a counter reaches zero, but unlike a barrier, it can only be used once — it doesn't reset.
"""


#include <iostream>
#include <thread>
#include <latch>
#include <vector>

const int num_threads = 3;
std::latch start_latch(num_threads);  // initialized with thread count

void worker(int id) {
    std::cout << "Thread " << id << " initializing\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * (id + 1)));

    std::cout << "Thread " << id << " finished initialization\n";
    start_latch.count_down();  // signal completion
}

int main() {
    std::vector<std::thread> threads;

    // Launch worker threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    // Wait (blocks main thread) until all threads to complete initialization
    start_latch.wait();
    std::cout << "All threads initialized. Main thread continues.\n";

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
