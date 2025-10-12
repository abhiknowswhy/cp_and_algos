"""
In C++, a barrier is a synchronization mechanism that ensures that multiple threads wait until all have reached a certain point in their execution before any of them proceed. Barriers are especially useful in parallel computing where threads perform work in phases and need to synchronize between phases.
"""


#include <iostream>
#include <thread>
#include <barrier>
#include <vector>

const int num_threads = 4;

// Barrier object
std::barrier sync_point(num_threads);

void worker(int id) {
    std::cout << "Thread " << id << " doing phase 1 work\n";
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));

    std::cout << "Thread " << id << " waiting at barrier\n";
    sync_point.arrive_and_wait(); // Wait for others

    std::cout << "Thread " << id << " doing phase 2 work\n";
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
