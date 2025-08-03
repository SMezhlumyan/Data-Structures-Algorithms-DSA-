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
};


//Weight Graph

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
    vector<std::list<pair<int,int>>> adjlist; // (n,w)

public:
    Graph(int v)
    {
        adjlist.resize(v);
    }

    void AddEdge(int u, int v,int w)
    {
        if (u >= adjlist.size())
            adjlist.resize(u + 1);
        if (v >= adjlist.size())
            adjlist.resize(v + 1);

        adjlist[u].push_back({v,w});

        if (undirected)
        {
            adjlist[v].push_back({u,w}); // undirectional
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
            for (auto [v,w] : adjlist[u])
            {
                cout << v << "- " << w << " ";
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

            for (auto [v,w] : adjlist[u])
            {
                travers[v].push_back({u,w});
            }
        }
        adjlist = travers;
    }
};


//Weight Graph ChatGPT
#include <iostream>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_set>

using namespace std;

template <bool undirected = true>
class Graph
{
private:
    vector<list<pair<int, int>>> adjlist; // (node, weight)

public:
    Graph(int v)
    {
        adjlist.resize(v);
    }

    void AddEdge(int u, int v, int w)
    {
        if (max(u, v) >= adjlist.size())
            adjlist.resize(max(u, v) + 1);

        adjlist[u].push_back({v, w});

        if (undirected)
            adjlist[v].push_back({u, w});
    }

    void AddVertex()
    {
        adjlist.push_back({});
    }

    void PrintGraph() const
    {
        for (int u = 0; u < adjlist.size(); u++)
        {
            cout << u << " -> ";
            for (auto [v, w] : adjlist[u])
            {
                cout << "(" << v << ", " << w << ") ";
            }
            cout << endl;
        }
    }

    void Transpose()
    {
        if (undirected)
        {
            cout << "This function is only for directed graphs." << endl;
            return;
        }

        vector<list<pair<int, int>>> transposed(adjlist.size());

        for (int u = 0; u < adjlist.size(); u++)
        {
            for (auto [v, w] : adjlist[u])
            {
                transposed[v].push_back({u, w});
            }
        }
        adjlist = move(transposed);
    }


    
};