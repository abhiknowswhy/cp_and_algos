# Dijkstra's Algorithm for Shortest Path

Dijkstra's algorithm is a greedy algorithm that solves the single-source shortest path problem for a graph with non-negative edge weights, producing a shortest-path tree.

## How it works

1. Initialize distances of all vertices as infinite and distance of the source as 0
2. Create a priority queue and insert the source vertex with distance 0
3. While the priority queue is not empty:
   - Extract the vertex with minimum distance
   - For each adjacent vertex of the extracted vertex:
     - If the distance to the adjacent vertex through the current vertex is less than its current distance, update the distance and add it to the priority queue

## Time Complexity
- O((V + E) log V) where V is the number of vertices and E is the number of edges

## Space Complexity
- O(V) for storing the distances and the priority queue

## Implementation in C++

```cpp
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
```

## Example Explanation

In the example above:
- We create a graph with 5 vertices (0 to 4)
- The source vertex is 0
- The output shows the shortest distance from the source to each vertex
- The algorithm uses a min-priority queue to efficiently select the vertex with the minimum distance
- The structure `pair<int, int>` represents (distance, vertex)
