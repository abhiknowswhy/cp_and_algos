# Connected Components in Graph

## Problem Description

Given an undirected graph represented as an adjacency list, find the number of connected components.

A connected component is a maximal set of vertices such that there is a path between every pair of vertices.

## Approach

Use BFS to traverse each unvisited vertex and mark all vertices in its connected component as visited. Count the number of BFS calls needed.

## Algorithm Steps

1. Initialize a visited array to track processed vertices
2. For each unvisited vertex, start a new BFS traversal
3. In BFS, mark current vertex as visited and add all unvisited neighbors to queue
4. Continue until queue is empty (one connected component processed)
5. Increment component count and repeat for remaining unvisited vertices

## Implementation

### C++
```cpp
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        int components = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                bfs(graph, i, visited);
                components++;
            }
        }
        
        return components;
    }
    
private:
    void bfs(vector<vector<int>>& graph, int start, vector<bool>& visited) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};
```

### Time Complexity
- **O(V + E)** where V is number of vertices and E is number of edges
- Each vertex and edge is visited once

### Space Complexity
- **O(V + E)** for adjacency list representation
- **O(V)** for visited array and BFS queue

## Examples

### Example 1
```
Input: n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2
Explanation: There are 2 connected components: {0,1,2} and {3,4}
```

### Example 2
```
Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1
Explanation: All vertices are connected in one component
```

## Notes

- Can also be solved using Union-Find (Disjoint Set Union) data structure
- DFS can be used instead of BFS with same time complexity
- Empty graph with n vertices has n connected components
- Complete graph has 1 connected component

## Related Problems

- [Number of Islands](https://leetcode.com/problems/number-of-islands/) - LeetCode 200
- [Friend Circles](https://leetcode.com/problems/friend-circles/) - LeetCode 547
- [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) - LeetCode 261

## LeetCode Links

- [Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) - LeetCode 323 (Premium)

## Pattern: 02-Breadth-First-Search-BFS

This problem demonstrates the BFS pattern for graph traversal. We use BFS to explore each connected component systematically, ensuring all reachable vertices are visited before moving to the next component.
