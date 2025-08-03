#include <vector>
#include <iostream>
using namespace std;

int Knapsack(const vector<int>& values,const vector<int>& weight,int cap,int n){
    vector<vector<int>> dp(n+1,vector<int>(cap+1,0));
    
    for(int i = 1;i <= n; ++i){
        for(int w = 1; w <= cap; ++w){

            if(weight[i-1] <= w){
                dp[i][w] = max(dp[i-1][w],dp[i-1][w-weight[i-1]] + values[i-1]);
            }else{
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][cap]; 
}

int main(){
    vector<int> values = {60, 100, 120};
    vector<int> weight = {1, 2, 3};
    int capacity = 3;
    int n = values.size();

    cout << Knapsack(values,weight,capacity,n);

    return 0; 
}
