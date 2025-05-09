/*
Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u-v, vertex u comes before v in the ordering.


Topological Sorting using DFS:
- Create a graph with n vertices and m-directed edges.
- Initialize a stack and a visited array of size n.
- For each unvisited vertex in the graph, do the following:
- Call the DFS function with the vertex as the parameter.
- In the DFS function, mark the vertex as visited and recursively call the DFS function for all unvisited neighbors of the vertex.
- Once all the neighbors have been visited, push the vertex onto the stack.
- After all, vertices have been visited, pop elements from the stack and append them to the output list until the stack is empty.
- The resulting list is the topologically sorted order of the graph.


Topological Sorting using BFS (Kahn's algorithm):
- Add all nodes with in-degree 0 to a queue.
- While the queue is not empty:
    - Remove a node from the queue.
    - For each outgoing edge from the removed node, decrement the in-degree of the destination node by 1.
    - If the in-degree of a destination node becomes 0, add it to the queue.
- If the queue is empty and there are still nodes in the graph, the graph contains a cycle and cannot be topologically sorted.
- The nodes in the queue represent the topological ordering of the graph.

*/


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
