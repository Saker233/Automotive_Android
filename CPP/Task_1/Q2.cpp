#include <iostream>
#include <stdio.h>


using namespace std;



int main()
{
    int hours = 0;
    int mins = 0;
    int seconds = 0;

    int x = 0;

    cout << "Please Enter Any Intger: ";

    cin >> x;

    // Get number of hours by dividing by 3600 it wil give us an integer and some fraction which will be neglected
    hours = x / (60 * 60);

    //remember the neglected fractions? here it comes, these fractions represent the minutes and seconds and we gonna store them in temp
    int temp_rem = x % (60 * 60);


    // we get the number of mintues by dividing this number by 60 it will give us an integer which is the minutes and some fractions also gonna be neglected
    mins = temp_rem / 60;

    // the remainder of this number is actually the number of seconds
    seconds = temp_rem % 60;

    cout << "H:M:S  -  "<<hours<<":"<<mins<<":"<<seconds;

}