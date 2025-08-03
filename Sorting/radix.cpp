#include <iostream>
#include <vector>

int maximum(const std::vector<int> &vec)
{
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
void Counting(std::vector<int> &vec, int pos)
{
    std::vector<int> count(10,0);
    std::vector<int> output(vec.size());
   
    for(auto& it : vec){
        count[(it/pos)%10]++;
    }
    
    for(int i=1;i<count.size();i++){
        count[i]+=count[i-1];
    }
    

    for(int i = vec.size()-1;i >=0 ; i--){
      
        output[--count[(vec[i]/pos)%10]] = vec[i]; 
    }

    // for(int i =0 ;i<vec.size(); i++){
    //     vec[i] = output[i];
    // }

    vec = std::move(output);
}

void sort(std::vector<int> &vec)
{
    int max = maximum(vec);
    for (int pos = 1; max / pos; pos *= 10)
    {
        
        Counting(vec, pos);
        for(auto& it : vec){
            std::cout <<  it << " ";
        }

        std::cout <<" reset \n";
    }
}

int main()
{
    std::vector<int> vec = {2, 3, 1, 45, 5};
    sort(vec);

    for(auto& it : vec){
       std::cout <<  it << " ";
    }
}