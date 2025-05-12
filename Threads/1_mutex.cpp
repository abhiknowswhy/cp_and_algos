"""
Use two threads to increment a counter 100 times, such that the counter value will 10 at the end
Each increment should by increasing counter value by 1

Syntax for mutex, lock and unlock
"""


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
