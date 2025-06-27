# Graph BFS Traversal

## Problem Description

Implement Breadth-First Search (BFS) traversal for a graph. Given a graph represented as an adjacency list and a starting vertex, return the BFS traversal order.

BFS explores vertices level by level, visiting all neighbors of the current level before moving to the next level.

## Approach

Use a queue to maintain the order of vertex exploration. Start from the given vertex, mark it as visited, and add its unvisited neighbors to the queue. Process vertices in FIFO order.

## Algorithm Steps

1. Initialize a queue with the starting vertex
2. Mark the starting vertex as visited
3. While queue is not empty:
   - Dequeue a vertex from front
   - Add it to result
   - For each unvisited neighbor, mark as visited and enqueue
4. Return the traversal order

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> bfsTraversal(vector<vector<int>>& graph, int start) {
        vector<int> result;
        if (graph.empty() || start >= graph.size()) return result;
        
        vector<bool> visited(graph.size(), false);
        queue<int> q;
        
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            result.push_back(vertex);
            
            // Visit all unvisited neighbors
            for (int neighbor : graph[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return result;
    }
    
    // For disconnected graph - traverse all components
    vector<int> bfsTraversalComplete(vector<vector<int>>& graph) {
        vector<int> result;
        vector<bool> visited(graph.size(), false);
        
        for (int i = 0; i < graph.size(); i++) {
            if (!visited[i]) {
                vector<int> component = bfsFromVertex(graph, i, visited);
                result.insert(result.end(), component.begin(), component.end());
            }
        }
        
        return result;
    }
    
private:
    vector<int> bfsFromVertex(vector<vector<int>>& graph, int start, vector<bool>& visited) {
        vector<int> component;
        queue<int> q;
        
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            component.push_back(vertex);
            
            for (int neighbor : graph[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return component;
    }
};
```

### Time Complexity

- **O(V + E)** where V is number of vertices and E is number of edges
- Each vertex is visited once and each edge is explored once

### Space Complexity

- **O(V)** for visited array and BFS queue
- In worst case, queue can contain all vertices

## Examples

### Example 1

```
Input: graph = [[1,2],[0,3],[0,3],[1,2]], start = 0
Output: [0,1,2,3]
Explanation: Starting from 0, visit neighbors 1,2, then neighbor 3
```

### Example 2

```
Input: graph = [[1],[0,2,3],[1],[1]], start = 0  
Output: [0,1,2,3]
Explanation: BFS traversal from vertex 0
```

## Notes

- BFS guarantees shortest path in unweighted graphs
- Order of neighbors affects the exact traversal sequence
- For disconnected graphs, need to check all vertices
- Memory usage can be high for wide graphs (many neighbors per vertex)

## Related Problems

- [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) - LeetCode 102
- [Word Ladder](https://leetcode.com/problems/word-ladder/) - LeetCode 127
- [Clone Graph](https://leetcode.com/problems/clone-graph/) - LeetCode 133
- [Course Schedule](https://leetcode.com/problems/course-schedule/) - LeetCode 207

## LeetCode Links

- Practice BFS on various graph problems on LeetCode
- No specific "BFS Traversal" problem, but concept used in many problems

## Pattern: 02-Breadth-First-Search-BFS

This is the fundamental BFS pattern for graphs. The queue-based level-by-level exploration is the core technique used in many graph algorithms like shortest path, level order traversal, and connected components.
