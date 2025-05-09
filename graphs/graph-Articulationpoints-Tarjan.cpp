#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list representation
    vector<int> disc, low, parent;
    vector<bool> articulationPoint;
    int time;

    void dfs(int u) {
        int children = 0;
        disc[u] = low[u] = ++time; // Initialize discovery and low values

        for (int v : adj[u]) {
            if (disc[v] == -1) { // If v is not visited
                children++;
                parent[v] = u;
                dfs(v);

                // Update low value of u for parent function calls
                low[u] = min(low[u], low[v]);

                // Check if u is an articulation point
                if (parent[u] == -1 && children > 1) // Case 1: Root node
                    articulationPoint[u] = true;
                if (parent[u] != -1 && low[v] >= disc[u]) // Case 2: Non-root node
                    articulationPoint[u] = true;
            } else if (v != parent[u]) { // Update low[u] for back edges
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        disc.assign(V, -1);
        low.assign(V, -1);
        parent.assign(V, -1);
        articulationPoint.assign(V, false);
        time = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void findArticulationPoints() {
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                dfs(i);
            }
        }

        cout << "Articulation points in the graph: ";
        for (int i = 0; i < V; i++) {
            if (articulationPoint[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    
    cout << "Finding articulation points using Tarjan's Algorithm:\n";
    g.findArticulationPoints();
    
    return 0;
}
