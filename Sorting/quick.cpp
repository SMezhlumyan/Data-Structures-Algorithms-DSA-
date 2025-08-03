#include <iostream>
#include <vector>
#include <random>
int random(int l,int r){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(l, r);
    return dis(gen);
}

int Partitian1(std::vector<int>& vec, int l,int r){
   
    int pivot = vec[r];
    int i= l ;
    int j= r-1;
    while (i<=j)
    {
        while (vec[j] >= pivot) j--;
        while (vec[i] < pivot) i++;

        if (i<j)
        {
            std::swap(vec[i],vec[j]);
        }
    }

    std::swap(vec[i],vec[r]);
    return i;

}

int Partitian2(std::vector<int>& vec , int l , int r){
    int pi = vec[r];
    int i=l;

    for (int j = l; j < r; j++)
    {
        if(vec[j] <= pi){
            std::swap(vec[j],vec[i]);
            i++;
        }
    }

    std::swap(vec[i],vec[r]);
    return i;
}
int Partitian3(std::vector<int>& vec ,int l , int r){
    int mid = l + (r-l)/2;
    
    if ((vec[l] > vec[mid] && vec[r] < vec[mid]) || (vec[l] < vec[mid] && vec[r] > vec[mid])){
        std::swap(vec[mid],vec[r]); 
    }
    else if ((vec[mid] > vec[l] && vec[r] < vec[l]) || (vec[mid] < vec[l] && vec[r] > vec[l])){
        std::swap(vec[l],vec[r]); 
    }

    int pivot = vec[r];
    int i=l;
    int j=r-1;
    while (i<=j)
    {
        while (vec[j]>=pivot) j--;
        while (vec[i] < pivot) i++; 

        if(i<j) {std::swap(vec[i],vec[j]);}
    }
    
    std::swap(vec[r],vec[i]);
    return i;
    
}
int Partitian4(std::vector<int>& vec,int l, int r){
    int rand = random(l,r);
    std::swap(vec[rand], vec[r]); 

    int pivot = vec[r];
    int i = l;

    for (int j = l; j < r; j++)
    {
        if (vec[j] < pivot)
        {
            std::swap(vec[j],vec[i]);
            i++;
        }
    }
    std::swap(vec[i],vec[r]);
    return i;

}


void QuickSort(std::vector<int>& vec , int l, int r){
    if(l<r){
        int PI = Partitian4(vec ,l ,r);
        QuickSort(vec ,l ,PI-1);
        QuickSort(vec ,PI+1 ,r); 
    }

}

int main(){
    std::vector <int> vec= {1,2,2,4,2,3,2};
    QuickSort(vec,0,vec.size()-1);

    for (auto &it : vec)
    {
        
    std::cout << it<<" ";
    }
        

}