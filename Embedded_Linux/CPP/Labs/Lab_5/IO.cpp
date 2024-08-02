#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <iomanip>

int main()
{

    std::ifstream in{"./input.txt"};

    if (!in)
    {
        std::cerr << "Error opening the file\n";

        return 1;
    }

    std::ofstream out{"./output.txt"};

    if (!out)
    {
        std::cerr << "Error opening the file\n";

        return 1;
    }

    std::string str;

    int sum = 0;
    double avg = 0;
    int min = 0;
    int max = 0;
    int index = 0;

    std::array<int, 9> arr;

    while (std::getline(in, str))
    {
        int num = stoi(str);

        arr[index] = num;

        index++;
    }

    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    for (int i = 0; i < arr.size(); i++)
    {
        avg = sum / arr.size();
    }

    std::sort(arr.begin(), arr.end());

    min = arr[0];

    max = arr[8];

    // std:: cout << sum << std::endl;

    // std:: cout << avg << std::endl;

    // std:: cout << min << std::endl;

    // std:: cout << max << std::endl;

    // out << num << std::endl;
    out << "-------------------------------------------------------------------------------------------------------------------\n";
    out << "| " << std::setw(20) << std::setfill(' ') << "SUM"
        << " | " << std::setw(24) << std::setfill(' ') << "AVG"
        << " | " << std::setw(24) << std::setfill(' ') << "MIN"
        << " | " << std::setw(24) << std::setfill(' ') << "MAX"
        << " |\n";
    out << "--------------------------------------------------------------------------------------------------------------------\n";
    out << "| " << std::setw(20) << std::setfill(' ') << sum
        << " | " << std::setw(24) << std::setfill(' ') << std::fixed << std::setprecision(2) << avg
        << " | " << std::setw(24) << std::setfill(' ') << min
        << " | " << std::setw(24) << std::setfill(' ') << max
        << " |\n";
    out << "--------------------------------------------------------------------------------------------------------------------\n";

    // std::cout<<  "|" <<std::right << std::setw(15) << "SUM"
    //           << std::setw(10) << "|" << std::setw(10)<<"AVG"
    //           << std::setw(15) << "MIN" << std::setw(10) << "MAX" <<std::endl;

    // std::cout<< "|"<< std::right << std::setw(15) << sum
    //           << std::setw(10) << avg
    //           << std::setw(15) << min << std::setw(15)<< max <<std::endl;

    in.close();
    out.close();
}