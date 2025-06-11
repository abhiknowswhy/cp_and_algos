#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a structure for the graph
class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // For undirected graph
    }

    void dijkstra(int src) {
        vector<int> dist(V, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& [v, weight] : adj[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        cout << "Vertex\tDistance from Source" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << "\t" << dist[i] << endl;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 2, 6);
    g.addEdge(4, 2, 3);
    g.addEdge(4, 3, 2);
    
    cout << "Dijkstra's Shortest Path Algorithm from Source 0:\n";
    g.dijkstra(0);
    
    return 0;
}
