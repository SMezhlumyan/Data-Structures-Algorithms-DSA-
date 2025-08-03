#include <vector>
using namespace std;

void insertion_sort(vector<float>& arr){

    for (int i = 1; i < arr.size(); i++)
    {
        int j = i-1;
        float key = arr[i];

        while (j>=0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }

}

void bucketSort(vector<float>& arr){
    int n = arr.size();

    std::vector<std::vector<float>> buckets(n);

    for (int i = 0; i < n; i++)
    {
        int index = arr[i] * n;
        buckets[index].push_back(arr[i]);
    }
    
    for (auto& bucket : buckets)
    {
        insertion_sort(bucket);
    } 
    
    int index = 0;
    for (auto& bucket: buckets)
    {
        for (auto& it : bucket)
        {
            arr[index++]=it;
        }
    }
}