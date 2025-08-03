#include <iostream>
#include <vector>
using namespace std;

class UnionFind{
private:
    vector<int> parent, rank;
public:

    UnionFind(int n) : parent(n), rank(n,0){

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x){
        if(parent[x] !=x ){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unit(int x,int y){
        int rootX = find(x);
        int rootY = find(y);
      
            if (rootX != rootY)
            {
                if (rank[rootX] > rank[rootY]){
                    parent[rootY] = rootX;
                }else if(rank[rootX] < rank[rootY]){
                    parent[rootX] = rootY;
                }else{
                    parent[rootY] = rootX;
                    rank[rootX]++ ;
                }
            }
            else
            cout <<"Is already Connected" << endl;
    }

    bool isConnected(int x,int y){
        return find(x) == find(y);
    }

    void print(){
        cout <<"Parent : ";
        for (auto &it : parent)
        {
            cout << it << " ";
        }
        cout << endl << "Rank   : ";
        for (auto &it : rank)
        {
            cout << it << " ";
        }
        cout <<endl;
    }

};

int main(){
    UnionFind un(5);

    un.unit(1,2); 
    un.unit(0,3);
    un.unit(2,0);
    un.unit(3,2);
    un.print();
    cout <<boolalpha << un.isConnected(1 , 0)<<endl;
    return 0;
}

