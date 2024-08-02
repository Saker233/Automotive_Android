#include <iostream>
#include <vector>




std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>> &v) 
{
    std::vector<std::vector<int>> transposed(v[0].size(), std::vector<int>(v.size()));
    
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            transposed[j][i] = v[i][j];
        }
    }
    
    return transposed;
}




void print(std::vector<std::vector<int>> &v)
{
    for (const auto& row : v) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}



int main()
{
    std::vector<std::vector<int>> v1 = 
    {
        {1,2,3,4,5},
        {6,7,8,9,10},
        {11,12,13,14,15},
        {16,17,18,19,20}
    }   ;               //{{1,2,3}, {4,5,6}, {7,8,9}};

    
    std::vector<std::vector<int>> v2 = transpose(v1);

    print(v2);


    // std::cout << v1.size() << std::endl;


  


    


   

}