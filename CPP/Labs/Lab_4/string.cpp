#include <iostream>





int main()
{
    std::string text = "The cycle of life is a cycle of cycles";

    std::cout << text.size() << std::endl;
    

    int pos = 0;
    while((pos = text.find("cycle", pos)) != std::string::npos) 
    {
        


        text.replace(pos, 5, "circle");


        pos += 6; 
    }

    // text.replace(text.find("cycle"), 5, "circle");
    

    // text.replace(text.find("cycle", 9), 5, "circle");



    // text.replace(text.find("cycle", 28), 5, "circle");



    text.insert(4, "great ");

    

    text.insert(text.find("circle", 28), "never-edning ");

    std::cout << text << std::endl;


    std::cout << text.size() << std::endl;


}