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
   
    void fillStack(int u, stack<int> &st, vector<bool> &visited)
    {
        visited[u] = true;

        for (auto &v : adjlist[u])
        {
            if (!visited[v])
            {
                fillStack(v, st, visited);
            }
        }
        st.push(u);
    }

    void  dfsKosarajou(int u,vector<bool>& visited, vector<int>& components,vector<list<int>>& rev){
        visited[u]= true;
        components.push_back(u);

        for (auto &v : rev[u])
        {
           if(!visited[v])
                dfsKosarajou(v,visited,components,rev); 
        }
        
    }

    vector<vector<int>> GetCSSKosarajou(){
        vector<vector<int>> res;
        stack<int> st;
        vector<bool> visited(adjlist.size());
        for (int u = 0; u < adjlist.size(); u++)
        {
            if (!visited[u])
            {
                fillStack(u, st, visited);
            }
        }

        vector<std::list<int>> rev(adjlist.size());
        for (int u = 0; u < adjlist.size(); u++)
        {
            for(auto& v : adjlist[u]){
                rev[v].push_back(u);
            }
        }

        fill(visited.begin(),visited.end(),false);

        while (!st.empty())
        {
            int u = st.top();
            st.pop();

            if (!visited[u])
            {
                vector<int> components;
                dfsKosarajou(u,visited,components,rev);
                res.push_back(components);
            }
            

        }
        
        return res;
    }
      
};

int main()
{

    Graph<false> g(7);
    g.AddEdge(0,1);
    g.AddEdge(1,0);
    g.AddEdge(0,2);
    g.AddEdge(1,3);
    g.AddEdge(3,2);
    g.AddEdge(2,4);
    g.AddEdge(4,3);
    g.AddEdge(4,5);
    g.AddEdge(2,6);
    g.AddEdge(6,5);
    g.AddEdge(5,6);
    
    
    vector<vector<int>> res =g.GetCSSKosarajou();

    for(auto& vec :res){
        cout << "{ ";
        for(auto& it : vec){
            cout << it << ", ";
        }
        cout << "} , ";
    }
    return 0;
}