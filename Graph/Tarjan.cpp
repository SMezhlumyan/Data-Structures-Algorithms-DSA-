#include <iostream>

#include <list>
#include <queue>
#include <vector>
#include <unordered_set>
#include <stack>
using namespace std;

template <bool undirected = true>
class Graph
{
private:
    vector<std::list<int>> adjlist;

public:
    Graph(int v)
    {
        adjlist.resize(v);
    }

    void AddEdge(int u, int v)
    {
        if (u >= adjlist.size())
            adjlist.resize(u + 1);
        if (v >= adjlist.size())
            adjlist.resize(v + 1);

        adjlist[u].push_back(v);

        if (undirected)
        {
            adjlist[v].push_back(u); // undirectional
        }
    }
    void AddVertex()
    {
        adjlist.push_back({});
    }

    void printGraph()
    {
        for (int u = 0; u < adjlist.size(); u++)
        {
            cout << u << "-> ";
            for (auto &v : adjlist[u])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }
    void travers()
    {
        if (undirected)
        {
            cout << "This fucntion is used only for the directed graph" << endl;
            return;
        }
        vector<list<int>> travers(adjlist.size());

        for (int u = 0; u < adjlist.size(); u++)
        {

            for (int &v : adjlist[u])
            {
                travers[v].push_back(u);
            }
        }
        adjlist = travers;
    }

    void Tarjandfs(int u, vector<int>& ids,vector<int>& ll,vector<bool>& onStack,stack<int>& st,int& timer,vector<vector<int>>& res){
        
        ids[u] = ll[u] = timer++;
        onStack[u] = true;
        st.push(u);

        for(auto& v : adjlist[u]){
            if(ids[v] == -1){
                Tarjandfs(v,ids,ll,onStack,st,timer,res);
            }
            if(onStack[v]){
                ll[u] = min(ll[u],ll[v]);
            }
        }
        if(ids[u] == ll[u]){
            vector<int> scc;
            for(int pos = st.top(); ; pos = st.top()){
                st.pop();

                scc.push_back(pos);
                onStack[pos] = false;
                
                if(ids[pos] == ids[u]) break;
            }
            res.push_back(scc);
        }

    }

    vector<vector<int>> Tarjan(){
        stack<int> st;
        vector<int> ids(adjlist.size(),-1);
        vector<int> ll(adjlist.size(),-1);
        vector<bool> onStack(adjlist.size(),false);
        vector<vector<int>> res;
        int timer = 0;

        for(int u=0; u < adjlist.size();u++){
            if(ids[u] == -1){
                Tarjandfs(u,ids,ll,onStack,st,timer,res);
            }
        }

        return res;
    }



};

int main(){

    Graph<false> g(7);
    g.AddEdge(0,1);
    g.AddEdge(1,2);
    g.AddEdge(2,0);
    g.AddEdge(1,3);
    g.AddEdge(3,4);
    g.AddEdge(4,5);
    g.AddEdge(5,3);
    g.AddEdge(5,6);

    
    
    vector<vector<int>> res =g.Tarjan();

    for(auto& vec :res){
        cout << "{ ";
        for(auto& it : vec){
            cout << it << ", ";
        }
        cout << "} , ";
    }
    return 0;
}