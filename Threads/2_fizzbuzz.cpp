"""
Solution to the leet code question - https://leetcode.com/problems/fizz-buzz-multithreaded/
"""

class FizzBuzz {
private:
    int n;
    int i;
    mutex mtx;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->i=1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return (i%3==0 and i%5!=0) || i > n; });
            
            if (i>n) break;

            printFizz();
            i++;

            lock.unlock();
            cv.notify_all();
        }
        
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return i%5==0 and i%3!=0 || i > n; });
            
            if (i>n) break;

            printBuzz();
            i++;

            lock.unlock();
            cv.notify_all();
        }

    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return i%15==0 || i > n; });
            
            if (i>n) break;

            printFizzBuzz();
            i++;

            lock.unlock();
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {

        while(i<=n){
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [=]() { return i%3!=0 and i%5!=0 || i > n; });
            
            if (i>n) break;

            printNumber(i);
            i++;

            lock.unlock();
            cv.notify_all();
        }
    }
};