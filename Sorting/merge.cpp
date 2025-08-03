#include <iostream>
#include <vector>

void merge(std::vector<int>& vec,int l,int mid,int r){
    int l1=l,l2=mid,r1=mid+1, r2=r;
    int index=0;
    std::vector<int> temp(r-l+1,0);
    while (l1<=l2 && r1<=r2)
    {
        if (vec[l1] < vec[r1])
        {
            temp[index]=vec[l1++];
        }else{
            temp[index]=vec[r1++];
        }
        index++;
    }

    while (l1<=l2)
    {
        temp[index]=vec[l1++];
        index++;
    }
    while (r1<=r2)
    {
        temp[index]=vec[r1++];
        index++;
    }   
    for (int i = l; i <= r; ++i) {
        vec[i] = temp[i-l];
    }
}
void mergesort(std::vector<int>& vec,int l,int r){
    if (l>=r)
    {
        return;
    }
    int mid=(r+l)/2;
        mergesort(vec,l,mid);
        mergesort(vec,mid+1,r);
        merge(vec,l,mid,r);
}



int main()
{
std::vector <int> vec ={2,4,-1,2,5};
    
    mergesort(vec,0,vec.size()-1);
    for (auto& it:vec)
    {
        std::cout<<it<<" ";
    }
}