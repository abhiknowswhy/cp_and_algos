"""
A semaphore in C++ is a synchronization mechanism used to control access to a shared resource in concurrent programming (e.g., multithreading). It helps avoid race conditions by allowing only a certain number of threads to access a critical section of code at the same time.
"""

#include <iostream>
#include <thread>
#include <semaphore>

std::counting_semaphore<2> sem(2); // Maximum 2 threads can enter

void task(int id) {
    std::cout << "Thread " << id << " waiting...\n";
    sem.acquire();  // Try to enter
    std::cout << "Thread " << id << " entered\n";

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work

    std::cout << "Thread " << id << " leaving\n";
    sem.release();  // Exit
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
