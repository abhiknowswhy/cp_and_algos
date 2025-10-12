# Cycle Detection - DSU

Use DSU to keep track of connected components. If you find two vertices that are already in the same component (i.e., have the same root), then a cycle exists.

Use when list of edges in the graph is provided.

```cpp
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return true;  // Cycle detected

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return false;
    }
};

bool hasCycleUnionFind(int n, vector<pair<int,int>>& edges) {
    UnionFind uf(n);
    for (auto& edge : edges) {
        if (uf.unite(edge.first, edge.second))
            return true;
    }
    return false;
}

int main() {
    int n = 4;
    vector<pair<int,int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0}
    };

    if (hasCycleUnionFind(n, edges))
        cout << "Cycle detected using Union-Find\n";
    else
        cout << "No cycle detected using Union-Find\n";

    return 0;
}
```
