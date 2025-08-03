#include <iostream>
#include <vector>

void sort(std::vector<int>& vec){
    for (int i = 1; i < vec.size(); i++)
    {
        int j=i-1;
        int tmp=vec[i];
        while (j>=0 && vec[j]>tmp)
        {
            vec[j+1]=vec[j];
            j--;
        }
        vec[j+1]=tmp;   
    }
    
}

int main(){
    std::vector <int> vec ={2,3,1,4,9,5,1};
    
    sort(vec);
    for (auto& it:vec)
    {
        std::cout<<it<<" ";
    }
    return 0;
}