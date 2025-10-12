# Minimum Height Trees

## Problem Description
A tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.

Given a tree of `n` nodes labelled from `0` to `n - 1`, and an array of `n - 1` edges where `edges[i] = [ai, bi]` indicates that there is an undirected edge between the two nodes `ai` and `bi` in the tree, you can choose any node of the tree as the root. When you pick a node `x` as the root, the height of the tree is the number of edges on the longest downward path between `x` and a leaf.

Return a list of all nodes that when used as the root will produce a tree with minimum height.

**LeetCode Link:** [310. Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)

## Approach
This problem can be solved using **topological sorting with BFS**. The key insight is that the minimum height tree roots are always in the "center" of the tree.

**Key Insight:** Start from leaf nodes (degree 1) and keep removing them layer by layer until we reach the center nodes. The remaining 1-2 nodes will be the roots that minimize tree height.

## Algorithm Steps
1. Handle edge cases (n ≤ 2)
2. Build adjacency list and calculate degrees
3. Add all leaf nodes (degree 1) to queue
4. Use BFS to remove leaves layer by layer
5. Continue until 1-2 nodes remain
6. Return remaining nodes as minimum height tree roots

## Implementation

### C++ - BFS (Topological Sort)
```cpp
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n <= 2) {
            vector<int> result;
            for (int i = 0; i < n; i++) {
                result.push_back(i);
            }
            return result;
        }
        
        // Build adjacency list
        vector<unordered_set<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].insert(edge[1]);
            adj[edge[1]].insert(edge[0]);
        }
        
        // Find initial leaves (nodes with degree 1)
        queue<int> leaves;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() == 1) {
                leaves.push(i);
            }
        }
        
        int remaining = n;
        
        // Remove leaves layer by layer
        while (remaining > 2) {
            int leavesCount = leaves.size();
            remaining -= leavesCount;
            
            for (int i = 0; i < leavesCount; i++) {
                int leaf = leaves.front();
                leaves.pop();
                
                // Remove this leaf from its neighbor
                int neighbor = *adj[leaf].begin();
                adj[neighbor].erase(leaf);
                
                // If neighbor becomes a leaf, add it to queue
                if (adj[neighbor].size() == 1) {
                    leaves.push(neighbor);
                }
            }
        }
        
        // Collect remaining nodes
        vector<int> result;
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }
        
        return result;
    }
};
```

### C++ - Alternative Implementation with Degree Array
```cpp
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n <= 2) {
            vector<int> result;
            for (int i = 0; i < n; i++) {
                result.push_back(i);
            }
            return result;
        }
        
        // Build adjacency list and degree array
        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);
        
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }
        
        // Find initial leaves
        queue<int> leaves;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                leaves.push(i);
            }
        }
        
        int remaining = n;
        
        // Remove leaves layer by layer
        while (remaining > 2) {
            int leavesCount = leaves.size();
            remaining -= leavesCount;
            
            for (int i = 0; i < leavesCount; i++) {
                int leaf = leaves.front();
                leaves.pop();
                
                // Reduce degree of all neighbors
                for (int neighbor : adj[leaf]) {
                    degree[neighbor]--;
                    if (degree[neighbor] == 1) {
                        leaves.push(neighbor);
                    }
                }
            }
        }
        
        // Collect remaining nodes
        vector<int> result;
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }
        
        return result;
    }
};
```

### C++ - DFS Approach (Less Efficient)
```cpp
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n <= 2) {
            vector<int> result;
            for (int i = 0; i < n; i++) {
                result.push_back(i);
            }
            return result;
        }
        
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        int minHeight = INT_MAX;
        vector<int> result;
        
        // Try each node as root and calculate height
        for (int root = 0; root < n; root++) {
            int height = getHeight(root, -1, adj);
            if (height < minHeight) {
                minHeight = height;
                result.clear();
                result.push_back(root);
            } else if (height == minHeight) {
                result.push_back(root);
            }
        }
        
        return result;
    }
    
private:
    int getHeight(int node, int parent, vector<vector<int>>& adj) {
        int maxHeight = 0;
        for (int neighbor : adj[node]) {
            if (neighbor != parent) {
                maxHeight = max(maxHeight, 1 + getHeight(neighbor, node, adj));
            }
        }
        return maxHeight;
    }
};
```

### Time Complexity
- **BFS (Optimal):** O(n) - Each node is processed once
- **DFS (Brute Force):** O(n²) - Calculate height for each root

### Space Complexity
- **BFS:** O(n) - Adjacency list and queue
- **DFS:** O(n) - Adjacency list and recursion stack

## Examples

### Example 1
```
Input: n = 4, edges = [[1,0],[1,2],[1,3]]
Output: [1]
Explanation: 
Tree structure:
    0
    |
    1
   / \
  2   3
Node 1 as root gives minimum height of 1.
```

### Example 2
```
Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
Output: [3,4]
Explanation:
Tree structure:
  0   1   2
   \ | /
    3-4-5
Both nodes 3 and 4 as roots give minimum height of 2.
```

### Example 3
```
Input: n = 1, edges = []
Output: [0]
Explanation: Single node tree.
```

## Notes
- **Center property:** MHT roots are always the center nodes of the tree
- **Maximum roots:** At most 2 nodes can be MHT roots
- **Leaf removal:** BFS approach simulates peeling off leaves until center is reached
- **Edge cases:** Handle n ≤ 2 separately

## Related Problems
- [LeetCode 207: Course Schedule](https://leetcode.com/problems/course-schedule/)
- [LeetCode 210: Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [LeetCode 269: Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)
- [LeetCode 1245: Tree Diameter](https://leetcode.com/problems/tree-diameter/)

## Pattern: 06-Task-Scheduling
This problem fits **Task Scheduling** pattern where:
- **Layer-by-layer processing:** Remove nodes in layers like scheduling tasks by priority levels
- **Queue-based BFS:** Use queue to process nodes in order of their "readiness" (becoming leaves)
- **Dependency management:** Nodes depend on their neighbors; remove dependencies gradually
- **Optimal scheduling:** Find optimal configuration (minimum height roots) through systematic processing
