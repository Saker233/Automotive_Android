#include <iostream>
#include <string_view>





std::string func2(std::string_view h, std::string_view n, std::string_view r)
{
    std::string result{h};  
    int pos = 0;
    while((pos = result.find(n, pos)) != std::string::npos)
    {
        result.replace(pos, n.size(), r);
        pos += r.size();
    }
    return result;
}


int main()
{
    std::string haystack;
    std::string needle;
    std::string replacement;


    std::cout << "Please Enter a Haystack: ";
    std::cin >> haystack;


    std::cout << "Please Enter a Needle: ";
    std::cin >> needle;



    std::cout << "Please Enter a Replacemnt: ";
    std::cin >> replacement;

    // std::string_view str1{haystack};

    // std::string_view str2{needle};

    // std::string_view str3{replacement};

    std::string result = func2(str1, needle, replacement);

    std::cout << result << std::endl;




}