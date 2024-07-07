#include <iostream>
#include <math.h>
#include <cctype>
#include <array>
#include <algorithm>

namespace MathFunction 
{
    void print(double x)
    {
        std::cout << sqrt(x) << std::endl; 
    }
}

namespace StringFunction 
{
    std::string print(const std::string& x)
    {
        std::string upper_x = x;
        std::transform(upper_x.begin(), upper_x.end(), upper_x.begin(), ::toupper);
        std::cout << upper_x << std::endl;
        return upper_x;
    }
}




namespace ArrayFunction 
{
    void print(const std::array<int, 8>& arr) {
        for(int i = arr.size(); i > 0; i--) {
            std::cout << arr[i - 1] << " ";
        }
    }
}

int main()
{
    MathFunction::print(9);

    StringFunction::print("mohamed");

    std::array<int, 8> arr = {1,2,3,4,5,6,7,8};

    ArrayFunction::print(arr);


}