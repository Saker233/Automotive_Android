#include <iostream>
#include <stdio.h>



using namespace std;


int main()
{
    int pop = 162100;

    int res = pop;

    int count = 0;

    while(res <= 1000000)
    {
        res *= 1.065;
        count++;
        cout << res << endl;
    }

    cout << "The number of years to reach million population is : " << count << endl;
}