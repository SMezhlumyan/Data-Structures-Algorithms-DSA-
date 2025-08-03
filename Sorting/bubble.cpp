#include <iostream>
#include <vector>
void sort(std::vector<int>& vec){
    int n= vec.size()-1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i; j++)
        {
            if (vec[j]>vec[j+1])
            {
                int tmp=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=tmp;
            }
            
        }
        
    }
    
}

int main(){

std::vector<int> vec={1,3,2,5,4};
sort(vec);

for (auto& it:vec)
{
std::cout<<it;
}


}