#include <iostream>
#include <cstdlib>
#include <string>

class Vertex
{
    int x;
    int y;

public:
    void set_verteces()
    {
        x = rand() % 201 - 100;

        y = rand() % 201 - 100;
    }

    int get_first()
    {
        return x;
    }

    int get_second()
    {
        return y;
    }

    std::string get_representation()
    {
        std::string s = "The first component is : " + std::to_string(x) + " The second component is : " + std::to_string(y);

        return s;
    }
};

int main()
{
    Vertex v;

    v.set_verteces();

    std::cout << v.get_first() << std::endl;

    std::cout << v.get_second() << std::endl;

    std::cout << v.get_representation() << std::endl;
}