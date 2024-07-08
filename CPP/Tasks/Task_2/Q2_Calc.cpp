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
        int res = 0;

        res = first + second;

        return res;
    }

    int SUB()
    {
        int res = 0;

        res = first - second;

        return res;
    }

    int MULT()
    {
        int res = 0;

        res = first * second;

        return res;
    }

    double DIV()
    {
        int res = 0;

        res = first / second;

        return res;
    }

    int POW()
    {
        int res = 0; 
        res = first ^ second;

        return res;
    }

    double SQRT()
    {
        int res = 0;

        res = sqrt(first);

        return res;
    }



};


int main()
{
    Calc c;


    int first_num=0;
    int second_num= 0;
    char operation = 0;
    std::cout<< "Please Enter The First Number";
    std::cin>>first_num;

    std::cout<< "Please Enter The operation";
    std::cin>>operation;

    std::cout<< "Please Enter The Second Number";
    std::cin>>second_num;

    c.set_first(first_num);

    c.set_second(second_num);

    c.set_op(operation);\

    int result = 0;

    switch (operation)
    {
    case '+':
        result = c.ADD(first_num, second_num);
        break;
    case '-':
        result = c.SUB(first_num, second_num);
        break;
    case '*':
        result = c.MULT(first_num, second_num);
        break;
    case '/':
        result = c.DIV(first_num, second_num);
        break;
    case 'p':
        result = c.POW(first_num, second_num);
        break;
    
    case 's':
        result = c.SQRT(first_num);
        break;
    default:
        break;
    }

    std::cout <<result << std::endl;
}