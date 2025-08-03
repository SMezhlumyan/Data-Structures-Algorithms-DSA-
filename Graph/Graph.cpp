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

    int GetShortPath(int src, int dst)
    {
        int level = 0;
        vector<bool> visited(adjlist.size());
        queue<int> q;
        q.push(src);

        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                int u = q.front();
                q.pop();

                if (u == dst)
                {
                    return level;
                }

                for (auto &v : adjlist[u])
                {
                    if (!visited[v])
                    {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            ++level;
        }

        return -1;
    }
    int getNumberOfNodeLevel(int src, int trglevel)
    {
        vector<int> visited(adjlist.size(), false);
        queue<int> q;

        q.push(src);
        visited[src] = true;

        while (!q.empty())
        {

            int size = q.size();

            if (trglevel-- <= 0)
                return size;

            while (size--)
            {
                int u = q.front();
                q.pop();

                for (auto &v : adjlist[u])
                {
                    if (!visited[v])
                    {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }

        return -1;
    }

    void dfs(int u, vector<bool> &visited)
    {
        visited[u] = true;
        for (auto &v : adjlist[u])
        {
            if (!visited[v])
            {
                dfs(v, visited);
            }
        }
    }

    int getNumberOfComponents()
    {
        int components = 0;

        vector<bool> visited(adjlist.size());
        for (int u = 0; u < adjlist.size(); u++)
        {
            if (!visited[u])
            {
                dfs(u, visited);
                components++;
            }
        }
        return components;
    }

    int CountOfPaths(int src, int des)
    {
        vector<bool> visited(adjlist.size());
        return dfsCount(src, des, visited);
    }

    int dfsCount(int u, int des, vector<bool> &visited)
    {

        if (u == des)
        {
            return 1;
        }
        int count = 0;
        visited[u] = true;

        for (auto &v : adjlist[u])
        {
            if (!visited[v])
            {
                count += dfsCount(v, des, visited);
            }
        }
        visited[u] = false;
        return count;
    }
    // bool cycledfs(int u, vector<bool>& visited){

    //     if(visited[u]){
    //         return true;
    //     }
    //     visited[u] = true;

    //     for (auto& nb : adjlist[u])
    //     {
    //         if (cycledfs(nb,visited))
    //         {
    //             return true;
    //         }
    //     }

    //     visited[u] =false;
    //     return false;
    // }

    // bool IsCycle(){
    //     vector<bool> visited(adjlist.size());

    //     for (int u = 0; u < adjlist.size(); u++)
    //     {
    //         visited[u] =true;
    //         for ( auto&  nb : adjlist[u])
    //         {
    //             if (cycledfs(nb , visited))
    //             {
    //                 return true;
    //             }

    //         }
    //         visited[u] =false;

    //     }

    //     return false;
    // }

    bool hasCycle(int u, vector<bool> &visited)
    {

        visited[u] = true;

        for (auto &nb : adjlist[u])
        {
            if (visited[nb])
                return true;

            if (hasCycle(nb, visited))
                return true;
        }
        visited[u] = false;
        return false;
    }

    bool IsCycleDir()
    {
        vector<bool> visited(adjlist.size(), false);

        for (int u = 0; u < adjlist.size(); u++)
        {
            if (hasCycle(u, visited))
                return true;
        }

        return false;
    }

    bool hasCycleUnDir(int u, int par, vector<bool> &visited)
    {
        visited[u] = true;
        for (auto &v : adjlist[u])
        {
            if (v != par && visited[v])
                return true;
            if (v != par)
                if (hasCycleUnDir(v, u, visited))
                    return true;
        }
        return false;
    }

    bool IsCycleUnDir(int src)
    {
        vector<bool> visited(adjlist.size(), false);

        return hasCycleUnDir(src, -1, visited);
    }

    void topologicalHelper(int u, vector<bool> &visited, stack<int> &st)
    {

        visited[u] = true;

        for (auto &nb : adjlist[u])
        {
            if (!visited[nb])
                topologicalHelper(nb, visited, st);
        }

        st.push(u);
    }

    vector<int> TopologicalSortDFS()
    {
        vector<bool> visited(adjlist.size(), false);
        stack<int> st;
        for (int u = 0; u < adjlist.size(); u++)
        {
            if (!visited[u])
            {
                topologicalHelper(u, visited, st);
            }
        }

        vector<int> res;
        while (!st.empty())
        {
            res.push_back(st.top());
            st.pop();
        }

        return res;
    }

    vector<int> KhansTopSort()
    {
        vector<int> inDegree(adjlist.size());

        for (int u = 0; u < adjlist.size(); u++)
        {
            for (auto &nb : adjlist[u])
            {
                ++inDegree[nb];
            }
        }

        queue<int> q;
        for (int u = 0; u < adjlist.size(); u++)
        {
            if (inDegree[u] == 0)
                q.push(u);
        }

        vector<int> ans;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            ans.push_back(u);

            for (auto &nb : adjlist[u])
            {
                --inDegree[nb];

                if (inDegree[nb] == 0)
                {
                    q.push(nb);
                }
            }
        }
        if (ans.size() != adjlist.size())
        {
            cout << "Is Cycle";
            return {};
        }

        return ans;
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

    // Graph<false> g(5);

    // g.AddEdge(0,1);
    // g.AddEdge(1,2);
    // g.AddEdge(2,3);
    // g.AddEdge(3,0);

    // cout << g.IsCycleDir();

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