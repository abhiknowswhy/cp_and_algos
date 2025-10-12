#include <bits/stdc++.h>
using namespace std;

// Structure to represent an edge
struct Edge
{
    int src, dest, weight;
};

// Compare function to sort edges by weight
bool compareEdges(Edge a, Edge b)
{
    return a.weight < b.weight;
}

// Disjoint Set Union (DSU) class with path compression and union by rank
class DSU
{
    vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with path compression
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank
    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Function to find MST using Kruskal's Algorithm
void kruskalMST(vector<Edge> &edges, int V)
{
    sort(edges.begin(), edges.end(), compareEdges); // Sort edges by weight

    DSU dsu(V);
    vector<Edge> mst; // Store the MST edges
    int mstWeight = 0;

    for (Edge &e : edges)
    {
        if (dsu.find(e.src) != dsu.find(e.dest))
        { // If adding this edge doesn't form a cycle
            dsu.unite(e.src, e.dest);
            mst.push_back(e);
            mstWeight += e.weight;
        }
        if (mst.size() == V - 1)
            break; // Stop when MST has (V-1) edges
    }

    // Print the MST edges and weight
    cout << "Minimum Spanning Tree Edges:\n";
    for (Edge &e : mst)
        cout << e.src << " -- " << e.dest << " (Weight: " << e.weight << ")\n";

    cout << "Total Weight of MST: " << mstWeight << endl;
}

int main()
{
    int V = 5; // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

    kruskalMST(edges, V);
    return 0;
}
