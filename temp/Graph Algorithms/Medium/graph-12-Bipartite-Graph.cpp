/*

A bipartite graph is a graph whose vertices can be divided into two disjoint sets such that no two vertices within the same set are adjacent (i.e., there are no edges connecting vertices of the same set).

Other means of defining this property is
- 2 colorable
- No odd-length cycles

Algorithm to Check if a Graph is Bipartite
- Use BFS or DFS to traverse the graph.
- Color a node with one color (e.g., 0) and its neighbors with the opposite color (e.g., 1).
- If at any step, a node has the same color as its adjacent node, the graph is not bipartite.
- If all nodes are colored without conflicts, the graph is bipartite.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isBipartite(vector<vector<int>> &graph, int n)
{
    vector<int> color(n, -1); // -1 means uncolored

    for (int start = 0; start < n; start++)
    { // Handle disconnected graphs
        if (color[start] == -1)
        {
            queue<int> q;
            q.push(start);
            color[start] = 0; // Start coloring with 0

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int neighbor : graph[node])
                {
                    if (color[neighbor] == -1)
                    { // If uncolored, color with opposite color
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    }
                    else if (color[neighbor] == color[node])
                    { // If adjacent nodes have same color
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    vector<vector<int>> graph = {
        {1, 3},
        {0, 2},
        {1, 3},
        {0, 2}};

    int n = graph.size();
    cout << (isBipartite(graph, n) ? "Bipartite" : "Not Bipartite") << endl;

    return 0;
}
