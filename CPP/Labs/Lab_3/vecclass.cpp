/*
Implement a class for a dynamic array (Vector)
    * Containing the following functions
        * resize() - resize the array to double the size
        * pushback(value) - add the value to the end of the array
        * popback() - remove the last element from the array
        * removeAt(index) - remove the element at the given index
        * insertAt(index, value) - insert the value at the given index and shift the elements to the right
        * insertMiddle(value) - insert the value in the middle of the array
        * removeMiddle() - remove the middle element from the array
        * size() - return the size of the array
        * print() - print the array

    * The following overload constructors:
        * DynamicArray() - default constructor with capacity of 1
        * DynamicArray(size) - constructor with given capacity
        * DynamicArray(size, value) - constructor with given capacity and initial value for all elements --> DynamicArray arr(5, 10);
        * DynamicArray(size, values) - constructor with given capacity and initial values --> DynamicArray arr(5, new int[5]{1, 2, 3, 4, 5});
        * DynamicArray(arr) - copy constructor

    * Appropriate destructor

    - Private members:
        * array - pointer to the array
        * capacity - capacity of the array
        * currentSize - current size of the array

*/

#include <iostream>
#include <initializer_list>
#include <cstring>

class DynamicArray
{
    int *arr;
    int capacity;
    int current_size;

public:
    DynamicArray()
    {
        arr = new int[1];
        capacity = 1;
        current_size = 0;
    }

    DynamicArray(int size)
    {
        arr = new int[size];
        capacity = size;
        current_size = 0;
    }

    DynamicArray(int size, int value)
    {
        arr = new int[size];
        capacity = size;
        current_size = size;

        for (int i = 0; i < size; i++)
        {
            arr[i] = value;
        }
    }

    DynamicArray(int size, std::initializer_list<int> list)
    {
        arr = new int[size];
        capacity = list.size();
        current_size = 0;

        int i = 0;

        for (auto j : list)
        {
            arr[i++] = j;
        }
        current_size = i;
    }

    DynamicArray(const DynamicArray &ob)
    {
        arr = new int[ob.capacity];
        capacity = ob.capacity;
        current_size = ob.current_size;
        for (int i = 0; i < current_size; i++)
        {
            arr[i] = ob.arr[i];
        }
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    void resize()
    {

        int *new_arr = new int[capacity * 2];

        std::memcpy(new_arr, arr, capacity * sizeof(int));

        delete[] arr;

        arr = new_arr;
        capacity *= 2;
    }

    void push_back(int value)
    {
        if (capacity == current_size)
        {
            resize();
        }

        arr[current_size] = value;
        current_size++;
    }

    void pop_back()
    {

        current_size--;
    }

    void removeAt(int index)
    {
        // shift left
        for (int i = index; i < capacity - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        current_size--;
    }

    void insertAt(int index, int value)
    {
        if (index >= current_size)
        {
            push_back(value);
        }
        else
        {
            if (capacity == current_size)
            {
                resize();
            }
            // shift right
            for (int i = index; i < current_size; i++)
            {
                arr[i + 1] = arr[i];
            }
            arr[index] = value;
            current_size++;
        }
    }

    int size()
    {
        return current_size;
    }

    void print()
    {
        for (int i = 0; i < current_size; i++)
        {
            std::cout << arr[i] << " ";
        }
    }

    insertMid()
    {
        int mid = current_size / 2;

        insertAt(mid);
    }

    removeMid()
    {
        int mid = current_size / 2;

        removeAt(mid);
    }
};

int main()
{
    DynamicArray vec;

    DynamicArray vec1(5, 10);

    DynamicArray vec2(vec1);

    DynamicArray vec5(5, {1, 2, 3, 4, 5});

    vec2.insertAt(3, 55);

    // vec.push_back(1);
    // vec.push_back(2);
    // vec.push_back(3);
    // vec.push_back(4);
    // vec.push_back(5);
    // vec.push_back(6);

    std::cout << vec2.size() << std::endl;
    vec2.print();

    std::cout << std::endl;

    vec5.print();
}