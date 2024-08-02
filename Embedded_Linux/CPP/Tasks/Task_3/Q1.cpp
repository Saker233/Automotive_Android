#include <iostream>
#include <array>
#include <cstdlib>

int main()
{
    std::pair<int, int> ver{5, 10};

    std::array<std::pair<int, int>, 5> arr;

    arr[0] = std::make_pair((rand() % 201 - 100), (rand() % 201 - 100));

    arr[1] = std::make_pair((rand() % 201 - 100), (rand() % 201 - 100));

    arr[2] = std::make_pair((rand() % 201 - 100), (rand() % 201 - 100));

    arr[3] = std::make_pair((rand() % 201 - 100), (rand() % 201 - 100));

    arr[4] = std::make_pair((rand() % 201 - 100), (rand() % 201 - 100));

    for(auto i : arr)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}