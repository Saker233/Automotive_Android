#include <iostream>
#include <stdio.h>


using namespace std;



int main()
{
    int var = 0;
    int res = 0;

    cout << "Please Enter a Number: ";

    do 
    {
        
        cin >> var;

        res += var;

         if (var != 0) 
        { 
            cout << "Please Enter Another Number: ";
        }
        
    }
    while (var != 0);

    cout << "The Accumlation is: "<< res;
    



    
}