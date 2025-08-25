"""
Question:
Using 3 threads print numbers from 1 to 100 (comma separated), such that 
- thread 1 prints all even numbers
- thread 2 prints all odd numbers
- thread 1 prints all commas
"""


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::string turn = "odd"; // start with even
int current = 1;
int last_val = 100;

void print_even() {
    while (current <= last_val) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return turn == "even" || current > last_val; });
        
        if (current > last_val) break;
        
        if (current % 2 == 0) {
            std::cout << current ;
            current++;
        }
        
        turn = "comma";
        lock.unlock();
        cv.notify_all();
    }
}

void print_odd() {
    while (current <= last_val) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return turn == "odd" || current > last_val; });
        
        if (current > last_val) break;
        
        if (current % 2 == 1) {
            std::cout << current ;
            current++;
        }
        
        turn = "comma";
        lock.unlock();
        cv.notify_all();
    }
}

void print_comma() {
    while (current <= last_val) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return turn == "comma" || current > last_val; });
        
        if (current > last_val) break;

        std::cout << ",";

        if(current%2==0){
            turn = "even";
        } else {
            turn = "odd";
        }

        lock.unlock();
        cv.notify_all();
    }
}


int main() {
    std::thread t1(print_odd);
    std::thread t2(print_even);
    std::thread t3(print_comma);
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}