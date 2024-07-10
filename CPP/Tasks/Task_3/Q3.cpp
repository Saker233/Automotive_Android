#include <iostream>


/*

    Design Parking System -> Leetcode


    Design a parking system for a parking lot. The parking lot has three kinds of parking spaces: big, medium, and small, 
    with a fixed number of slots for each size.

Implement the ParkingSystem class:

ParkingSystem(int big, int medium, int small) Initializes object of the ParkingSystem class. 
The number of slots for each parking space are given as part of the constructor.


bool addCar(int carType) Checks whether there is a parking space of carType for the car that wants to get into the parking lot. 
carType can be of three kinds: big, medium, or small, which are represented by 1, 2, and 3 respectively. 
A car can only park in a parking space of its carType. If there is no space available, 
return false, else park the car in that size space and return true.

*/


class ParkingSystem {
    int big_car;
    int med_car;
    int small_car;
public:
    ParkingSystem(int big, int medium, int small) 
    {
        big_car = big;
        med_car = medium;
        small_car = small;
    }
    
    bool addCar(int carType) 
    {
        if(carType == 1)
        {
            if(big_car >= 1)
            {
                big_car--;
                return true;
            }
            else
            {
                return false;
            }
        }

        if(carType == 2)
        {
            if(med_car >= 1)
            {
                med_car--;
                return true;
            }
            else
            {
                return false;
            }
        }
        if(carType == 3)
        {
            if(small_car >= 1)
            {
                small_car--;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
};


int main()
{
    ParkingSystem park(1,1,1);

    std::cout << park.addCar(1) << std::endl;

    std::cout << park.addCar(2) << std::endl;

    std::cout << park.addCar(3) << std::endl;

    std::cout << park.addCar(1) << std::endl;

    std::cout << park.addCar(2) << std::endl;

    std::cout << park.addCar(3) << std::endl;

    

}