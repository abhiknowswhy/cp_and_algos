/*
A minimum spanning tree (MST) or minimum weight spanning tree is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight.

Step 1: Determine an arbitrary vertex as the starting vertex of the MST. We pick 0 in the below diagram.
Step 2: Follow steps 3 to 5 till there are vertices that are not included in the MST (known as fringe vertex).
Step 3: Find edges connecting any tree vertex with the fringe vertices.
Step 4: Find the minimum among these edges.
Step 5: Add the chosen edge to the MST. Since we consider only the edges that connect fringe vertices with the rest, we never get a cycle.
Step 6: Return the MST and exit
*/


#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a structure for the graph
class Graph {
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list representation

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Since the graph is undirected
    }

    // Function to find the Minimum Spanning Tree (MST) using Prim's Algorithm
    void primMST() {
        vector<int> key(V, numeric_limits<int>::max()); // Stores the minimum weight edge to reach a node
        vector<int> parent(V, -1); // Stores the parent of each node in MST
        vector<bool> inMST(V, false); // Keeps track of nodes included in MST
        
        // Min-heap (priority queue) to get the node with the smallest key value
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        key[0] = 0; // Start from the first node
        pq.push({0, 0}); // Insert source node with key value 0

        while (!pq.empty()) {
            int u = pq.top().second; // Extract node with the smallest key value
            pq.pop();

            if (inMST[u]) continue; // Skip if node is already in MST
            inMST[u] = true; // Include the node in MST

            // Iterate over adjacent vertices
            for (auto& [v, weight] : adj[u]) {
                // If v is not in MST and the weight of (u, v) is less than key[v]
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight; // Update key value
                    pq.push({key[v], v}); // Push updated value into priority queue
                    parent[v] = u; // Update parent
                }
            }
        }

        // Output the edges of the MST
        cout << "Edge\tWeight" << endl;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << "\t" << key[i] << endl;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    cout << "Prim's Minimum Spanning Tree:\n";
    g.primMST();

    return 0;
}
