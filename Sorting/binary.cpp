#include <iostream>
#include <vector>
int search(std::vector<int> vec,int target){
    int l=0;
    int r=vec.size()-1;
    while (l <= r)
    {
        int mid=(r-l)/2+l;
        if (vec[mid] == target)
        {
            return mid;
        }
        if(vec[mid] < target){
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return -1;
    
}

int  searchRec(std::vector <int> vec,int target,int l,int r ){
    if (l>r)
    {
        return -1;
    }

    int mid=(r-l)/2+l;
    
    if (vec[mid]==target)
    {
        return mid;
    }
    if(vec[mid]<target){
       return searchRec(vec,target,mid+1,r);
    }
    else{
       return searchRec(vec,target,l,mid-1);
    }   
}



int main(){
    std::vector<int> vec={1,2,3,3,3,6,7};
    std::cout<<search(vec,6);
}