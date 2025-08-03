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
      
};

int main(){
    Graph<false> g(3);
    g.AddEdge(1 , 0);
    g.AddEdge(1 , 2);
    g.AddEdge(2 , 0);

    vector<int> vec = g.TopologicalSortDFS();

    for(auto& it : vec){
        cout << it << " ";
    }
    cout <<endl;
    
    vec = g.TopologicalSortDFS();

    for(auto& it : vec){
        cout << it << " ";
    }
    cout <<endl;
}