The **Floyd-Warshall algorithm** is a classical dynamic programming algorithm to compute the **All-Pairs Shortest Paths (APSP)** in a  **weighted, directed graph** . It works even with  **negative weights** , as long as there are  **no negative cycles** .

---

### ✅ **Key Concepts**

* We maintain a matrix `dist[i][j]` representing the shortest distance from node `i` to `j`.
* We also maintain a matrix `next[i][j]` for path reconstruction: it stores the next node to go to from `i` in order to reach `j` along the shortest path.
* The algorithm iterates over each node `k` as an **intermediate node** and updates the shortest paths using:

```cpp
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
```

---

### 🚀 C++ Implementation: `APSP` Class

```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <stdexcept>
#include <unordered_set>

using namespace std;

class APSP {
private:
    const int INF = 1e9;
    int n;
    vector<vector<int>> dist;
    vector<vector<int>> next;
    vector<bool> hasNegCycle;

public:
    APSP(int vertices) : n(vertices) {
        dist.assign(n, vector<int>(n, INF));
        next.assign(n, vector<int>(n, -1));
        hasNegCycle.assign(n, false);
        for (int i = 0; i < n; ++i)
            dist[i][i] = 0;
    }

    void addEdge(int u, int v, int weight) {
        dist[u][v] = weight;
        next[u][v] = v;
    }

    void floydWarshall() {
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (dist[i][k] < INF && dist[k][j] < INF &&
                        dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }

        // Mark nodes part of or reachable from negative cycles
        for (int k = 0; k < n; ++k)
            if (dist[k][k] < 0)
                for (int i = 0; i < n; ++i)
                    for (int j = 0; j < n; ++j)
                        if (dist[i][k] < INF && dist[k][j] < INF)
                            hasNegCycle[i] = hasNegCycle[j] = true;
    }

    bool hasNegativeCycleOnPath(int u, int v) {
        return hasNegCycle[u] && hasNegCycle[v];
    }

    vector<int> getPath(int u, int v) {
        if (next[u][v] == -1)
            return {};
        if (hasNegativeCycleOnPath(u, v))
            throw runtime_error("Path from " + to_string(u) + " to " + to_string(v) + " involves a negative cycle.");

        vector<int> path = {u};
        while (u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        return path;
    }

    int getDistance(int u, int v) {
        if (dist[u][v] >= INF)
            return -1;
        if (hasNegativeCycleOnPath(u, v))
            throw runtime_error("Distance from " + to_string(u) + " to " + to_string(v) + " involves a negative cycle.");
        return dist[u][v];
    }

    void printDistanceMatrix() {
        cout << "Distance Matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] >= INF)
                    cout << "INF ";
                else
                    cout << setw(4) << dist[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void printPath(int u, int v) {
        try {
            vector<int> path = getPath(u, v);
            if (path.empty() and u!=v) {
                cout << "No path from " << u << " to " << v << "\n";
                return;
            } 
            cout << "Path from " << u << " to " << v << ": ";
            for (int node : path)
                cout << node << " ";
            cout << "\n";
        } catch (const exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
};

int main() {
    int V = 4;
    APSP apsp(V);

    // Add directed edges: (from, to, weight)
    apsp.addEdge(0, 1, 3);
    apsp.addEdge(0, 2, 10);
    apsp.addEdge(1, 2, -2);
    apsp.addEdge(2, 3, 2);
    apsp.addEdge(3, 1, 1);

    apsp.floydWarshall();

    apsp.printDistanceMatrix();

    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            apsp.printPath(u, v);
            try {
                int d = apsp.getDistance(u, v);
                cout << "Distance: " << d << "\n\n";
            } catch (const exception &e) {
                cout << "Error: " << e.what() << "\n\n";
            }
        }
    }

    return 0;
}
```
