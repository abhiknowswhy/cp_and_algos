#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list
    vector<vector<int>> adjT; // Transposed adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
        adjT.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);  // Original graph
        adjT[v].push_back(u); // Transposed graph (reversed edges)
    }

    // First DFS to store finish times
    void dfs(int node, vector<bool> &visited, stack<int> &st) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor])
                dfs(neighbor, visited, st);
        }
        st.push(node); // Push to stack after all neighbors are processed
    }

    // Second DFS to explore SCCs
    void dfsTranspose(int node, vector<bool> &visited) {
        cout << node << " "; // Print SCC component
        visited[node] = true;
        for (int neighbor : adjT[node]) {
            if (!visited[neighbor])
                dfsTranspose(neighbor, visited);
        }
    }

    // Function to find and print all SCCs
    void findSCCs() {
        stack<int> st;
        vector<bool> visited(V, false);

        // Step 1: DFS to get finish order
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                dfs(i, visited, st);
        }

        // Step 2: Reset visited array for the second pass
        fill(visited.begin(), visited.end(), false);

        // Step 3: Process nodes in decreasing order of finish time
        cout << "Strongly Connected Components:\n";
        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                dfsTranspose(node, visited);
                cout << endl;
            }
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    g.findSCCs();

    return 0;
}
