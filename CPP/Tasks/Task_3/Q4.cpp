#include <iostream>

/*

258. Add Digits

Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.



Example 1:

Input: num = 38
Output: 2
Explanation: The process is
38 --> 3 + 8 --> 11
11 --> 1 + 1 --> 2
Since 2 has only one digit, return it.
Example 2:

Input: num = 0
Output: 0

*/

class Solution
{

public:
    int addDigits(int num)
    {
        int qut = 10;
        int rem = 0;
        int new_num = 0;

        while (qut != 0)
        {
            qut = num / 10; // 38 / 10 = 3
            rem = num % 10; // rem = 8

            new_num = qut + rem; // 8 + 3 = 11

            num = new_num;
        }

        return num;
    }
};

int main()
{
    Solution n;

    // int num = n.addDigits(38);

    std::cout << n.addDigits(543) << std::endl;
}