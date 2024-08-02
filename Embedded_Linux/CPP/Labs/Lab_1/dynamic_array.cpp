#include <iostream>
#include <stdio.h>


using namespace std;

struct ARR
{
    int *arr;
    int total_size;
    int current_size;
};

int* INIT(ARR &vec, int size)
{
    vec.arr = (int*)malloc(size * sizeof(int));

    vec.total_size = size;

    vec.current_size = 0;
    
    return vec.arr;
}

void push_back(ARR &vec, int data)
{   
    if(vec.total_size == vec.current_size)
    {
        vec.arr = (int*)realloc(vec.arr, (vec.total_size * 2));

        vec.total_size *= 2;
    }

    vec.arr[vec.current_size] = data;
    vec.current_size++;
  
}

void print(ARR &vec)
{
    for(int i =0; i < vec.current_size; i++)
    {
        cout << vec.arr[i] << " ";
    }
}

void INSERT(ARR &vec, int pos, int data)
{
    if(pos >= vec.current_size)
    {
        push_back(vec, data);
    }
    else 
    {
        for (int i = pos; i < vec.current_size; i++)
        {
            vec.arr[i + 1] = vec.arr[i];
        }
        vec.arr[pos] = data;
        vec.current_size++;
    }
}



int main()
{

    ARR vec1;

    vec1.arr = INIT(vec1, 5);

    push_back(vec1, 1);
    push_back(vec1, 2);
    push_back(vec1, 3);


    print(vec1);

    cout << endl;

    INSERT(vec1, 2, 77);

    print(vec1);

    free(vec1.arr);

}