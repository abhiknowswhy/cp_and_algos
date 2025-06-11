# Cycle Detection - DFS

While doing DFS traversal, track the visited nodes. If you encounter a visited node that is not the parent of the current node, then there is a cycle.

Use when adjacency list of a graph is provided.

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, int parent, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, node, graph, visited))
                return true;
        } else if (neighbor != parent) {
            return true;  // Found a cycle
        }
    }
    return false;
}

bool hasCycleDFS(int n, vector<vector<int>>& graph) {
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, -1, graph, visited))
                return true;
        }
    }
    return false;
}

int main() {
    int n = 4;  // Number of nodes
    vector<vector<int>> graph(n);

    // Add edges (undirected)
    graph[0].push_back(1);
    graph[1].push_back(0);

    graph[1].push_back(2);
    graph[2].push_back(1);

    graph[2].push_back(3);
    graph[3].push_back(2);

    graph[3].push_back(0);
    graph[0].push_back(3);

    if (hasCycleDFS(n, graph))
        cout << "Cycle detected using DFS\n";
    else
        cout << "No cycle detected using DFS\n";

    return 0;
}
```
