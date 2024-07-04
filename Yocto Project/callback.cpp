#include <iostream>
#include <stdio.h>

using namespace std;

typedef int(*Eventhandler)(int *row, int size);


typedef int*(eventhandler)(int** arr_2d, int arr_size, int *row_size, Eventhandler func);

int* Two_D_arr(int** arr_2d, int arr_size, int *row_size, Eventhandler func)
{
    int* res = (int*)malloc(arr_size * sizeof(int));

    for(int i =0; i < arr_size; i++)
    {
        res[i] = func(arr_2d[i], row_size[i]);
    }

    return res;
}

int accumlate(int *row_size, int arr_size)
{
    int sum = 0;
    for(int i = 0; i < arr_size; i++)
    {
        sum += row_size[i];
    }

    return sum;
}


int main()
{

    int row1[] = {50,2,3};
    int row2[] = {4,5};
    int row3[] = {6,7};

    int *arr[] = {row1, row2, row3};

    int row_size[] = {3, 2, 2};

    int row = 3;

    int* (*call_back)(int**, int, int*, Eventhandler) = Two_D_arr;


    int *res = call_back(arr, row, row_size, accumlate);


    for (int i = 0; i < row; i++)
    {
        cout <<  res[i] << endl;   
        
    }

    free(res);



}