#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

std::vector<int> fibo_results(18, -1); // Array to store Fibonacci results (0 to 17)
std::mutex mtx;
std::condition_variable cv;
bool results_ready = false;

int fibonacci(int n)
{
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

void calculate_fibo(int n, std::function<void(int, int)> callback)
{
    int result = fibonacci(n);
    callback(n, result);
}

void print_results(const std::vector<int> &indices)
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []
            { return results_ready; });

    int sum = 0;
    for (int idx : indices)
    {
        std::cout << "Fibonacci(" << idx << ") = " << fibo_results[idx] << std::endl;
        sum += fibo_results[idx];
    }
    std::cout << "Sum of requested Fibonacci numbers: " << sum << std::endl;
}

int main()
{
    std::vector<int> indices = {4, 9, 14, 17}; // Indices to calculate

    std::vector<std::thread> threads;
    for (int idx : indices)
    {
        threads.emplace_back([idx]
                             { calculate_fibo(idx, [](int index, int result)
                                              {
                std::lock_guard<std::mutex> lock(mtx);
                fibo_results[index] = result;
                cv.notify_all(); }); });
    }

    std::thread printer_thread([&indices]
                               { print_results(indices); });

    for (auto &th : threads)
    {
        th.join();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        results_ready = true;
    }
    cv.notify_all();
    printer_thread.join();

    return 0;
}