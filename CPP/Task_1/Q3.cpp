#include <iostream>
#include <stdio.h>
#include <cmath>


using namespace std;


int count_digits(int n)
{
    int count = 0;
    while(n != 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

int from_bin_to_dec(int n)
{
    int dec = 0;
    int temp = 1;
    int digit = 0;

    while(n != 0)
    {
        digit = n % 10;
        n /=10;
        dec += digit * temp;
        temp = temp * 2;
    }
    return dec;
}

int from_dec_to_bin(int n)
{
    int temp = n;
    int count = 0;
    while(temp != 0)
    {
        temp /= 2;
        count++;
    }
    int *arr = (int*)calloc(count, sizeof(int));
    for(int i = 0; i < count; i++)
    {
        arr[i] = n % 2;
        n /= 2;
    }

    int bin = 0;
    for(int i = count - 1; i >= 0; i--)
    {
        bin = (10 * bin) + arr[i];
    }

    free(arr);
    return bin;
}



int main()
{


    int num = 13;
    int bin = from_dec_to_bin(num);

    cout << bin << endl;

    int dec = from_bin_to_dec(bin);

    cout << dec;


}