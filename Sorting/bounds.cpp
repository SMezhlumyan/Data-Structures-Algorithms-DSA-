#include <iostream>
#include <vector>

int lower_bound(const std::vector<int>& vec, int target){
    int l=0;
    int r=vec.size()-1;

    while (l<r)
    {
        int mid=(r-l)/2 + l;
        if (vec[mid]<target)
        {
            l=mid+1;
        }else{
            r =mid;
        }
    }
    return l;  
}

int uperr_bound(const std::vector<int>& vec, int target){
    int l=0;
    int r=vec.size()-1;

    while (l<r)
    {
        int mid=(r-l)/2 + l;
        if (vec[mid]<=target)
        {
            l=mid+1;
        }else{
            r =mid;
        }
    }
    return l;  
}

int main() {
    std::vector<int> vec = {1,3,5,6};
    int target = 7;
    std::cout << 7 << " " <<lower_bound(vec,target) << std::endl;
    
    return 0;
}
