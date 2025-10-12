"""
A semaphore in C++ is a synchronization mechanism used to control access to a shared resource in concurrent programming (e.g., multithreading). It helps avoid race conditions by allowing only a certain number of threads to access a critical section of code at the same time.
"""

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    // Initialize with some value (e.g., number of allowed threads)
    Semaphore(int value = 1) : count(value) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return count > 0; });  // Wait until count > 0
        --count;  // Take one "token"
    }

    void release() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;  // Return one "token"
        cv.notify_one();  // Wake one waiting thread
    }
};


Semaphore sem(2);  // Allow 2 threads concurrently

void task(int id) {
    std::cout << "Thread " << id << " waiting...\n";
    sem.acquire();
    std::cout << "Thread " << id << " entered\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread " << id << " leaving\n";
    sem.release();
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);
    std::thread t3(task, 3);
    std::thread t4(task, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
