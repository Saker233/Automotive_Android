#include <iostream>
#include <stdio.h>



using namespace std;




struct Name
{
    char* first_name;
    char* middle_name;
    char* last_name;
};

struct Date_of_Birth
{
    int day;
    int month;
    int year;
};

struct Address
{
    char* street;
    char* city;
    char* country;
};

struct Contact
{
    double telephone_number;
    double mobile_number;
    char* email;
};

struct Salary
{
    int basic;
    int additional;
    int reduction;
    int taxes;
};

struct Employees
{
    struct Name name;
    struct Date_of_Birth Date;
    struct Address ad;
    struct Contact con;
    char* Job;
    struct Salary sal;
};

int main()
{
    struct Employees emp;

    

}