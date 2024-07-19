#include <iostream>



class Time
{
    int hours;
    int minutes;
    int seconds;
    public:
    Time() = default;

    Time(int h, int m, int s)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }

    void Display_12()
    {
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }

    friend Time operator+(Time const& obj1, Time const& obj2)
    {
        Time res;
        res.hours = obj1.hours + obj2.hours;
        res.minutes = obj1.minutes + obj2.minutes;
        res.seconds = obj1.seconds + obj2.seconds;
        return res;
    }
    
};



int main()
{
    Time o1(1, 45, 30);
    Time o2(2, 10, 20);

    Time o3;

    o3 = o1 + o2;

    o3.Display_12();
}