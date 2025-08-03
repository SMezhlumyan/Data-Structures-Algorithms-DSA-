#include <iostream>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
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

    vector<int> Dijksa(int src){
        vector<int> dist(adjlist.size(),numeric_limits<int>::max());
        priority_queue<pair<int,int>,vector<pair<int,int> >, greater< pair<int,int> > > pq;

        dist[src] = 0;
        pq.push({dist[src], src});

        while (!pq.empty()){
            auto [d, u]= pq.top();
            pq.pop();

            if (dist[u] < d) continue;

            for(auto [v , w] : adjlist[u]){
                if (dist[u] + w  < dist[v])  
                {
                    dist[v] =dist[u] + w ;
                    pq.push({dist[v] , v });
                }
            }
        }
        return dist;
    }   

};

int main(){

    Graph<false> g(3);

    g.AddEdge(0,1,3);
    g.AddEdge(0,2,6);
    g.AddEdge(0,3,5);
    g.AddEdge(1,3,4);
    g.AddEdge(1,2,1);
    g.AddEdge(2,4,5);
    g.AddEdge(3,4,2);

    vector<int> res =g.Dijksa(1);
    g.PrintGraph();

    cout << "{ ";
    for(auto& it :res){
        
        cout << it << ", ";
    }
    cout << "}";
}   