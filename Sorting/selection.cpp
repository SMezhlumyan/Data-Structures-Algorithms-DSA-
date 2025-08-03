#include <iostream>
#include <vector>


void sort(std::vector<int>& vec){
    for (int i = 0; i < vec.size()-1; i++)
    {
        int min=i;
        for (int j = i+1; j < vec.size(); j++)
        {
            if (vec[j] < vec[min])
                min=j;   
        }

        if (min!=i)
        {
            int tmp=vec[min];
            vec[min]=vec[i];
            vec[i]=tmp;
        }  
    }
}

int main(){
    std::vector <int> vec={2,3,5,4,6,1};
    sort(vec);
    for (auto& it:vec)
    {
        std::cout<<it<<" ";
    }
    
    return 0;
}