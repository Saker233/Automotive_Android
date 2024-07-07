#include <iostream>

using namespace std;

class Car
{
    string company;
    string model;
    int year;


    public:
    void set_comp(string c)
    {
        company = c;
    }
    void set_model(string m)
    {
        model = m;
    }
    void set_year(int y)
    {
        year = y;
    }

    string get_comp()
    {
        return company;
    }
    string get_model()
    {

        return model;
    }
    int get_year()
    {
        return year;
    }


};


int main()
{
    Car c1;

    c1.set_comp("Mercedes");
    c1.set_model("MyBach");
    c1.set_year(2024);

    cout << c1.get_comp() << endl;
    cout << c1.get_model() << endl;
    cout << c1.get_year() << endl;

}