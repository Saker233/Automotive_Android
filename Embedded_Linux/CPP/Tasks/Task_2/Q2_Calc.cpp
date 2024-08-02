#include <iostream>
#include <cmath>
#include <cctype>

class Calc
{
    int first;
    int second;
    char op;

public:
    void set_first(int x)
    {
        first = x;
    }
    void set_second(int y)
    {
        second = y;
    }
    void set_op(char z)
    {
        op = z;
    }

    int ADD()
    {
        return first + second;
    }

    int SUB()
    {
        return first - second;
    }

    int MULT()
    {
        return first * second;
    }

    double DIV()
    {
        return static_cast<double>(first) / second;
    }

    int POW()
    {
        return pow(first, second);
    }

    double SQRT()
    {
        return sqrt(first);
    }
};

int main()
{
    Calc c;

    int first_num = 0;
    int second_num = 0;
    char operation = 0;
    std::cout << "Please Enter The First Number : ";
    std::cin >> first_num;

    std::cout << "Please Enter The operation : ";
    std::cin >> operation;

    if (operation != 's')
    {
        std::cout << "Please Enter The Second Number : ";
        std::cin >> second_num;
        c.set_second(second_num);
    }

    c.set_first(first_num);

    c.set_op(operation);

    double result = 0;

    switch (operation)
    {
    case '+':
        result = c.ADD();
        break;
    case '-':
        result = c.SUB();
        break;
    case '*':
        result = c.MULT();
        break;
    case '/':
        result = c.DIV();
        break;
    case 'p':
        result = c.POW();
        break;

    case 's':
        result = c.SQRT();
        break;
    default:
        std::cout << "Invalid Operation" << std::endl;
        break;
    }

    std::cout << result << std::endl;
}