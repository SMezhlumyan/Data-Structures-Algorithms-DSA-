#include <iostream>
#include <vector>
int minimum(const std::vector<int> &vec){
    int lowest = vec[0];
    for (auto &it : vec)
    {
        if (it < lowest)
        {
            lowest = it;
        }
    }
    return lowest;
}
int maximum(const std::vector<int> &vec){
    int higest = vec[0];
    for (auto &it : vec)
    {
        if (it > higest)
        {
            higest = it;
        }
    }
    return higest;
}

void sort(std::vector<int> &vec)
{
    int min = minimum(vec);
    int max = maximum(vec);
    int range = max - min + 1;

    std::vector<int> store(range,0);
    for(auto& it:vec){
        store[it-min]++;
    }
    
    int j=0;
    for(int i=0;i<range;i++){
        while (store[i]--)
        {
            vec[j++]=i+min;
        }
    }
}

void secondsort(std::vector<int>& vec){
    int max=maximum(vec);
    int min=minimum(vec);
    int range=max-min+1;
    std::vector<int> count(range,0);
    std::vector<int> output(vec.size());

    for(auto& it :vec){
        count[it-min]++;
    }
    
    for (int  i = 1;i < count.size(); i++)
    {
        count[i]+=count[i-1];
    }


    for (int i = vec.size()-1; i>=0; --i)
    {
        count[vec[i]-min]--;
        output[count[vec[i]-min]]=vec[i];
       
    }
    std::cout <<std::endl;

    vec = output;
}

int main()
{
   std::vector <int> vec ={4,8,215,23,2,3,3,1};
    
    secondsort(vec);
    for (auto& it:vec)
    {
        std::cout<<it<<" ";
    }
}