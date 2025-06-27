# Topological Sorting

## Problem Description
Given a Directed Acyclic Graph (DAG) with `V` vertices and `E` edges, find a topological ordering of the vertices. A topological ordering is a linear ordering of vertices such that for every directed edge `(u, v)`, vertex `u` comes before vertex `v` in the ordering.

**GeeksforGeeks Link:** [Topological Sort](https://practice.geeksforgeeks.org/problems/topological-sort/1)

**Note:** Topological sorting is only possible for Directed Acyclic Graphs (DAGs).

## Approach
There are two main approaches to solve topological sorting:

1. **Kahn's Algorithm (BFS with Queue):** Use in-degree and queue
2. **DFS-based approach:** Use DFS and stack (or recursion)

**Key Insight:** In a valid topological order, vertices with no incoming edges should come first.

## Algorithm Steps

### Kahn's Algorithm (BFS):
1. Calculate in-degree for all vertices
2. Add all vertices with in-degree 0 to queue
3. While queue is not empty:
   - Remove vertex from queue and add to result
   - Decrease in-degree of all neighbors
   - Add neighbors with in-degree 0 to queue
4. Check if all vertices are processed (cycle detection)

### DFS Approach:
1. Use DFS traversal with a stack
2. After visiting all neighbors, add current vertex to stack
3. Pop all vertices from stack to get topological order

## Implementation

### C++ - Kahn's Algorithm (BFS with Queue)
```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
        vector<int> indegree(V, 0);
        
        // Calculate in-degrees
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                indegree[v]++;
            }
        }
        
        // Add all vertices with in-degree 0 to queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> result;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);
            
            // Reduce in-degree of neighbors
            for (int v : adj[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Check for cycle (if result size != V, there's a cycle)
        if (result.size() != V) {
            return {}; // Cycle detected, no valid topological order
        }
        
        return result;
    }
};
```

### C++ - DFS Approach
```cpp
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        stack<int> st;
        
        // Perform DFS for all unvisited vertices
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, st);
            }
        }
        
        // Pop all vertices from stack to get topological order
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }
        
        return result;
    }
    
private:
    void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
        visited[u] = true;
        
        // Visit all neighbors first
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited, st);
            }
        }
        
        // Add current vertex to stack after visiting neighbors
        st.push(u);
    }
};
```

### C++ - DFS with Cycle Detection
```cpp
class Solution {
public:
    vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
        vector<int> color(V, 0); // 0: white, 1: gray, 2: black
        vector<int> result;
        bool hasCycle = false;
        
        for (int i = 0; i < V; i++) {
            if (color[i] == 0) {
                if (dfsWithCycleDetection(i, adj, color, result, hasCycle)) {
                    return {}; // Cycle detected
                }
            }
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
    
private:
    bool dfsWithCycleDetection(int u, vector<vector<int>>& adj, vector<int>& color, 
                               vector<int>& result, bool& hasCycle) {
        if (hasCycle) return true;
        
        color[u] = 1; // Mark as gray (visiting)
        
        for (int v : adj[u]) {
            if (color[v] == 1) {
                // Back edge found - cycle detected
                hasCycle = true;
                return true;
            }
            if (color[v] == 0 && dfsWithCycleDetection(v, adj, color, result, hasCycle)) {
                return true;
            }
        }
        
        color[u] = 2; // Mark as black (visited)
        result.push_back(u);
        return false;
    }
};
```

### Time Complexity
- **Kahn's Algorithm:** O(V + E) - Each vertex and edge processed once
- **DFS Approach:** O(V + E) - DFS traversal of graph

### Space Complexity
- **Kahn's Algorithm:** O(V) - Queue and in-degree array
- **DFS Approach:** O(V) - Recursion stack and visited array

## Examples

### Example 1
```
Input: V = 6, E = 6
Edges: (5,2), (5,0), (4,0), (4,1), (2,3), (3,1)
Adjacency List: 
0 -> []
1 -> []
2 -> [3]
3 -> [1]
4 -> [0, 1]
5 -> [2, 0]

Output: [4, 5, 2, 3, 1, 0] (One possible topological order)
Explanation: In this order, all directed edges go from left to right.
```

### Example 2
```
Input: V = 4, E = 3
Edges: (0,1), (1,2), (2,3)
Adjacency List:
0 -> [1]
1 -> [2]
2 -> [3]
3 -> []

Output: [0, 1, 2, 3]
Explanation: Linear chain, only one possible topological order.
```

### Example 3 (Cycle Detection)
```
Input: V = 3, E = 3
Edges: (0,1), (1,2), (2,0)
Output: [] (No valid topological order due to cycle)
```

## Notes
- **DAG requirement:** Topological sorting only works on Directed Acyclic Graphs
- **Multiple solutions:** A DAG can have multiple valid topological orderings
- **Cycle detection:** If not all vertices are processed, there's a cycle
- **Applications:** Task scheduling, dependency resolution, build systems

## Related Problems
- [LeetCode 207: Course Schedule](https://leetcode.com/problems/course-schedule/)
- [LeetCode 210: Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [LeetCode 269: Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)
- [LeetCode 310: Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)

## Pattern: 06-Task-Scheduling
Topological sorting is fundamental to **Task Scheduling** pattern where:
- **Dependency management:** Tasks have prerequisite relationships
- **Queue-based processing:** Process tasks with no dependencies first (Kahn's algorithm)
- **Order guarantee:** Ensures all dependencies are satisfied before processing a task
- **Cycle detection:** Identifies impossible scheduling scenarios (circular dependencies)
