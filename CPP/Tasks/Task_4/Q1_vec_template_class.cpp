#include <iostream>
#include <initializer_list>
#include <cstring>

template <typename T>
class DynamicArray
{
    T *arr;
    int capacity;
    int current_size;

public:
    DynamicArray()
    {
        arr = new T[1];
        capacity = 1;
        current_size = 0;
    }

    DynamicArray(int size)
    {
        arr = new T[size];
        capacity = size;
        current_size = 0;
    }

    DynamicArray(int size, T value)
    {
        arr = new T[size];
        capacity = size;
        current_size = size;

        for (int i = 0; i < size; i++)
        {
            arr[i] = value;
        }
    }

    DynamicArray(int size, std::initializer_list<T> list)
    {
        arr = new T[size];
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
        arr = new T[ob.capacity];
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
        T *new_arr = new T[capacity * 2];

        std::memcpy(new_arr, arr, capacity * sizeof(T));

        delete[] arr;

        arr = new_arr;
        capacity *= 2;
    }

    void push_back(T value)
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
        if (current_size > 0)
        {
            current_size--;
        }
    }

    void removeAt(int index)
    {
        if (index < 0 || index >= current_size)
        {
            std::cerr << "Index out of bounds." << std::endl;
            return;
        }
        for (int i = index; i < current_size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        current_size--;
    }

    void insertAt(int index, T value)
    {
        if (index < 0 || index > current_size)
        {
            std::cerr << "Index out of bounds." << std::endl;
            return;
        }
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
            for (int i = current_size; i > index; i--)
            {
                arr[i] = arr[i - 1];
            }
            arr[index] = value;
            current_size++;
        }
    }

    int size() const
    {
        return current_size;
    }

    void print() const
    {
        for (int i = 0; i < current_size; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void insertMid(T value)
    {
        int mid = current_size / 2;
        insertAt(mid, value);
    }

    void removeMid()
    {
        int mid = current_size / 2;
        removeAt(mid);
    }
};


int main()
{
    DynamicArray<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    arr1.print(); 

    DynamicArray<std::string> arr2;
    arr2.push_back("Hello");
    arr2.push_back("World");
    arr2.print(); 

    DynamicArray<double> arr3(5, 2.5);
    arr3.print(); 

    return 0;
}
