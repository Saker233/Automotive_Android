#include <iostream>
#include <atomic>
#include <thread>

class Spinlock {
private:
    std::atomic_flag lock_flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (lock_flag.test_and_set(std::memory_order_acquire)) {}
    }

    void unlock() {
        lock_flag.clear(std::memory_order_release);
    }
};

void multiply(Spinlock& spinlock, int& shared_var) {
    for (int i = 0; i < 10; ++i) {
        spinlock.lock();
        shared_var *= 2;
        std::cout << "Multiplied by 2: " << shared_var << std::endl;
        spinlock.unlock();
        std::this_thread::yield(); 
    }
}

void divide(Spinlock& spinlock, int& shared_var) {
    for (int i = 0; i < 10; ++i) {
        spinlock.lock();
        shared_var /= 2;
        std::cout << "Divided by 2: " << shared_var << std::endl;
        spinlock.unlock();
        std::this_thread::yield(); 
    }
}

int main() {
    Spinlock spinlock;
    int shared_var = 10;

    std::thread t1(multiply, std::ref(spinlock), std::ref(shared_var));
    std::thread t2(divide, std::ref(spinlock), std::ref(shared_var));

    t1.join();
    t2.join();

    std::cout << "Final shared variable value: " << shared_var << std::endl;

    return 0;
}