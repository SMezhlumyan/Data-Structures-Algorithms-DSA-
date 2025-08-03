#include <iostream>
#include <vector>
using namespace std;

int Partition(vector<int> &arr, int l, int r)
{
    int j = l - 1;
    for (int i = l; i < r; i++)
    {
        if (arr[i] <= arr[r])
        {
            swap(arr[++j], arr[i]);
        }
    }
    swap(arr[++j], arr[r]);
    return j;
}

int quick_select(vector<int> &arr, int l, int r, int k)
{
    if (l <= r)
    { // " < "->wrong [1,-2];
        int p = Partition(arr, l, r);

        if (p == k)
            return arr[p];
        if (p > k)
            return quick_select(arr, l, p - 1, k);
        else
            return quick_select(arr, p + 1, r, k);
    }
    return -1;
}

int min_quickselect(vector<int> &arr, int k){
    return quick_select(arr, 0, arr.size() - 1, k - 1); //  k - 1 important
}

int max_quickselect(vector<int> &arr, int k){
    return quick_select(arr, 0 , arr.size() - 1 ,arr.size() - k);
}

int main()
{

    vector<int> arr = {1, -2,3};
    int val = max_quickselect(arr, 4);

    cout << val << endl;
}