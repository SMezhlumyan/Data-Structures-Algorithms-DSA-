#include <iostream>
#include <vector>

int getleftch(int i) {return 2*i+1;}
int getrightch(int i) {return 2*i+2;}

template <typename T, typename Compare = std::less<T>>
void heapifyDown(std::vector<T>& arr, int i, int size) {
    Compare cmp = Compare();
    int left = getleftch(i);
    int right = getrightch(i);
    int swapindex = i;


    if (left < size && cmp(arr[left], arr[swapindex])) {
        swapindex = left;
    }
    if (right < size && cmp(arr[right], arr[swapindex])) {
        swapindex = right;
    }                                                                     

    if (i != swapindex) {
        std::swap(arr[swapindex], arr[i]);
        heapifyDown<T, Compare>(arr, swapindex, size);
    }
}

template <typename T, typename Compare = std::less<T>>
void heapSort(std::vector<T>& arr) {
    int n = arr.size();

    for (int i = (n / 2) - 1; i >= 0; --i) {
        heapifyDown<T, Compare>(arr, i, n);
    }

    
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapifyDown<T, Compare>(arr, 0, i);
    }
}

int main(){
    std::vector vec = {10,3,34,28,13,33};

    heapSort<int,std::greater<int>>(vec);
    for (auto &it : vec)
    {   
        std::cout << it<<" ";
    }
    std::cout <<std::endl;
    
    return 0;
}