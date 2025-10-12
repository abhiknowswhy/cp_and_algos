# Shortest Path in Unweighted Graph

## Problem Description

Given an unweighted graph and two vertices (source and destination), find the shortest path between them. Return the minimum number of edges in the path, or -1 if no path exists.

In an unweighted graph, all edges have equal weight (cost = 1), so the shortest path is the one with minimum number of edges.

## Approach

Use BFS starting from the source vertex. BFS explores vertices level by level, guaranteeing that when we first reach the destination, we've found the shortest path.

## Algorithm Steps

1. If source equals destination, return 0
2. Initialize queue with source vertex and distance 0
3. Mark source as visited
4. While queue is not empty:
   - Dequeue vertex and its distance
   - For each unvisited neighbor:
     - If it's the destination, return distance + 1
     - Mark as visited and enqueue with distance + 1
5. If destination not found, return -1

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>>& graph, int source, int destination) {
        if (source == destination) return 0;
        
        int n = graph.size();
        if (source >= n || destination >= n) return -1;
        
        vector<bool> visited(n, false);
        queue<pair<int, int>> q; // {vertex, distance}
        
        q.push({source, 0});
        visited[source] = true;
        
        while (!q.empty()) {
            auto [vertex, dist] = q.front();
            q.pop();
            
            for (int neighbor : graph[vertex]) {
                if (neighbor == destination) {
                    return dist + 1;
                }
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, dist + 1});
                }
            }
        }
        
        return -1; // No path found
    }
    
    // Alternative: Return the actual path
    vector<int> shortestPathWithRoute(vector<vector<int>>& graph, int source, int destination) {
        if (source == destination) return {source};
        
        int n = graph.size();
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(source);
        visited[source] = true;
        
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            
            for (int neighbor : graph[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = vertex;
                    q.push(neighbor);
                    
                    if (neighbor == destination) {
                        return reconstructPath(parent, source, destination);
                    }
                }
            }
        }
        
        return {}; // No path found
    }
    
private:
    vector<int> reconstructPath(vector<int>& parent, int source, int destination) {
        vector<int> path;
        int current = destination;
        
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
};

// For edge list representation
class Solution2 {
public:
    int shortestPath(int n, vector<vector<int>>& edges, int source, int destination) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]); // Undirected
        }
        
        return shortestPathBFS(graph, source, destination);
    }
    
private:
    int shortestPathBFS(vector<vector<int>>& graph, int source, int destination) {
        if (source == destination) return 0;
        
        vector<bool> visited(graph.size(), false);
        queue<pair<int, int>> q;
        
        q.push({source, 0});
        visited[source] = true;
        
        while (!q.empty()) {
            auto [vertex, dist] = q.front();
            q.pop();
            
            for (int neighbor : graph[vertex]) {
                if (neighbor == destination) {
                    return dist + 1;
                }
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, dist + 1});
                }
            }
        }
        
        return -1;
    }
};
```

### Time Complexity

- **O(V + E)** where V is number of vertices and E is number of edges
- Each vertex and edge is visited at most once

### Space Complexity

- **O(V)** for visited array and BFS queue
- Queue can contain at most O(V) vertices

## Examples

### Example 1

```
Input: graph = [[1,2],[0,3],[0,3],[1,2]], source = 0, destination = 3
Output: 2
Explanation: Path 0 → 1 → 3 or 0 → 2 → 3 (both have length 2)
```

### Example 2

```
Input: graph = [[1],[0,2],[1]], source = 0, destination = 2
Output: 2  
Explanation: Path 0 → 1 → 2
```

### Example 3

```
Input: graph = [[1],[0],[]], source = 0, destination = 2
Output: -1
Explanation: No path exists from 0 to 2
```

## Notes

- BFS guarantees shortest path in unweighted graphs
- For weighted graphs, use Dijkstra's algorithm instead
- Can modify to return actual path by tracking parent pointers
- Bidirectional BFS can optimize for large graphs

## Related Problems

- [Word Ladder](https://leetcode.com/problems/word-ladder/) - LeetCode 127
- [Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/) - LeetCode 433
- [Open the Lock](https://leetcode.com/problems/open-the-lock/) - LeetCode 752
- [Snakes and Ladders](https://leetcode.com/problems/snakes-and-ladders/) - LeetCode 909

## LeetCode Links

- Practice on various shortest path problems using BFS
- [Word Ladder](https://leetcode.com/problems/word-ladder/) - LeetCode 127

## Pattern: 02-Breadth-First-Search-BFS

This is the classic application of BFS for finding shortest paths. The level-by-level exploration ensures that when we reach the target, we've found the minimum number of edges needed.
