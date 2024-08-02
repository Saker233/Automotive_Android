#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> keepBeeping(true);

void beepEveryThreeSeconds(int delayInSeconds)
{
    while (keepBeeping)
    {
        std::this_thread::sleep_for(std::chrono::seconds(delayInSeconds));
        if (keepBeeping)
        {
            std::cout << "SOUND" << '\a' << std::endl; 
        }
    }
}

int main()
{
    std::thread beepThread(beepEveryThreeSeconds, 3);

    std::cout << "Press Enter to stop the beep...\n";
    std::cin.get(); 

    keepBeeping = false; 
    beepThread.join();   

    std::cout << "Beep stopped.\n";
    return 0;
}