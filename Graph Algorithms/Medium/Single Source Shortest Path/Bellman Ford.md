# Bellman-Ford Algorithm

## Introduction

The Bellman-Ford algorithm is a single-source shortest path algorithm that can handle graphs with negative edge weights. Unlike Dijkstra's algorithm, it can also detect negative cycles (cycles whose total edge weight is negative) in a graph.

## How It Works

The algorithm works by repeatedly relaxing all edges in the graph, where "relaxing" means updating the shortest known distance to each vertex. In a graph with V vertices, if there are no negative cycles, the shortest path can contain at most V-1 edges. Therefore, the algorithm performs V-1 iterations of relaxation on all edges.

## Key Features

- Can handle negative edge weights
- Detects negative cycles
- Slower than Dijkstra's algorithm (O(V*E) vs O(E + V log V))
- Works on both directed and undirected graphs

## Algorithm Steps

1. Initialize distances from source to all vertices as infinite and distance to the source as 0
2. Relax all edges V-1 times (where V is the number of vertices)
   - For each edge (u, v) with weight w:
     - If dist[u] + w < dist[v], then update dist[v] = dist[u] + w
3. Check for negative cycles by relaxing all edges one more time
   - If any distance changes, then there is a negative cycle

## Time and Space Complexity

- Time Complexity: O(V*E) where V is the number of vertices and E is the number of edges
- Space Complexity: O(V) for the distance array

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int u, v;
    int weight;
};

class BellmanFord {
    int V, E;
    vector<Edge> edges;
    vector<int> distance;
    vector<int> parent;

public:
    BellmanFord(int vertices, int edgeCount) : V(vertices), E(edgeCount) {
        edges.reserve(E);
        distance.resize(V, INF);
        parent.resize(V, -1);
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    void run(int source) {
        distance[source] = 0;

        // Relax all edges V-1 times
        for (int i = 1; i <= V - 1; ++i) {
            for (const Edge& e : edges) {
                if (distance[e.u] != INF && distance[e.u] + e.weight < distance[e.v]) {
                    distance[e.v] = distance[e.u] + e.weight;
                    parent[e.v] = e.u;
                }
            }
        }

        // Check for negative weight cycles
        for (const Edge& e : edges) {
            if (distance[e.u] != INF && distance[e.u] + e.weight < distance[e.v]) {
                throw runtime_error("Graph contains a negative weight cycle");
            }
        }
    }

    void printDistances(int source) const {
        cout << "Vertex\tDistance from Source " << source << "\n";
        for (int i = 0; i < V; ++i) {
            cout << i << "\t";
            if (distance[i] == INF)
                cout << "INF\n";
            else
                cout << distance[i] << "\n";
        }
    }

    vector<int> getPath(int dest) const {
        if (distance[dest] == INF) return {}; // No path

        vector<int> path;
        for (int v = dest; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int V = 5; // Number of vertices
    int E = 8; // Number of edges

    BellmanFord bf(V, E);

    // Example graph
    bf.addEdge(0, 1, -1);
    bf.addEdge(0, 2, 4);
    bf.addEdge(1, 2, 3);
    bf.addEdge(1, 3, 2);
    bf.addEdge(1, 4, 2);
    bf.addEdge(3, 2, 5);
    bf.addEdge(3, 1, 1);
    bf.addEdge(4, 3, -3);

    try {
        bf.run(0);
        bf.printDistances(0);

        cout << "\nPath from 0 to 3: ";
        vector<int> path = bf.getPath(3);
        for (int v : path)
            cout << v << " ";
        cout << "\n";
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }

    return 0;
}

```

## Applications

- Finding shortest paths in routing algorithms
- Network routing protocols (like RIP - Routing Information Protocol)
- Arbitrage detection in currency exchange
- Circuit delay calculation in electronic design automation

## Advantages and Disadvantages

### Advantages

- Can handle negative edge weights
- Can detect negative weight cycles
- Simple implementation

### Disadvantages

- Slower than Dijkstra's algorithm for graphs without negative edge weights
- Doesn't work when negative cycles are present (but can detect them)

## Alternative Approach - SPFA (Shortest Path Faster Algorithm)

A queue-based optimization of Bellman-Ford, with average-case time complexity often better than O(V*E).
