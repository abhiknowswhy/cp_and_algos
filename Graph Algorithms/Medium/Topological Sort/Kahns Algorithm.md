# Topological Sort

Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u→v, vertex u comes before v in the ordering.

## Approaches

### 1. Topological Sorting using DFS

**Algorithm:**
1. Create a graph with n vertices and m-directed edges
2. Initialize a stack and a visited array of size n
3. For each unvisited vertex in the graph:
   - Call the DFS function with the vertex as parameter
   - Mark the vertex as visited in the DFS function
   - Recursively call DFS for all unvisited neighbors
   - Once all neighbors have been visited, push the vertex onto the stack
4. After all vertices have been visited, pop elements from the stack and append to the output list
5. The resulting list is the topologically sorted order of the graph

### 2. Topological Sorting using BFS (Kahn's algorithm)

**Algorithm:**
1. Calculate in-degree for each vertex
2. Add all nodes with in-degree 0 to a queue
3. While the queue is not empty:
   - Remove a node from the queue
   - For each outgoing edge from the removed node:
     - Decrement the in-degree of the destination node by 1
     - If the in-degree becomes 0, add the node to the queue
4. If the queue is empty and there are still nodes with non-zero in-degree, the graph contains a cycle
5. The order in which nodes were processed represents the topological ordering

## Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Kahn's Algorithm (BFS)
    void topologicalSortBFS() {
        vector<int> inDegree(V, 0);
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                inDegree[v]++;
            }
        }
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            for (int v : adj[u]) {
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        if (topoOrder.size() != V) {
            cout << "Graph has a cycle!" << endl;
            return;
        }
        for (int node : topoOrder) {
            cout << node << " ";
        }
        cout << endl;
    }

    // DFS-based Topological Sort
    void topologicalSortDFSUtil(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                topologicalSortDFSUtil(u, visited, Stack);
            }
        }
        Stack.push(v);
    }

    void topologicalSortDFS() {
        stack<int> Stack;
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                topologicalSortDFSUtil(i, visited, Stack);
            }
        }
        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
        cout << endl;
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Topological Sort (BFS): ";
    g.topologicalSortBFS();
    
    cout << "Topological Sort (DFS): ";
    g.topologicalSortDFS();
    
    return 0;
}
```

## Time and Space Complexity

- **Time Complexity:** O(V + E) where V is the number of vertices and E is the number of edges
- **Space Complexity:** O(V) for the queue/stack and visited array

## Applications

- Task scheduling
- Build dependency management
- Course prerequisite planning
- Symbol resolution in linkers
