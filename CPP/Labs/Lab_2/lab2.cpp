#include <iostream>



namespace DynamicAlloc
{
    int** create2DArray(int size)
    {
        int **ptr = new int *[size];

        for(int i = 0; i< size; i++)
        {
            ptr[i] = new int[5];
        }

        std::cout<<"Double Array Allocated" << std::endl;

        return ptr;
    }

    void delete2DArray(int **ptr, int size)
    {
        for(int i=0; i < size; i++)
        {
            delete[] ptr[i];
        }

        delete[] ptr;

        std::cout<<"Double Array Deleted" << std::endl;
    }
}

int main()
{
    int **ptr = DynamicAlloc::create2DArray(5);

    DynamicAlloc::delete2DArray(ptr, 5);
}