# Max Area of Island

## Problem Description
You are given an `m x n` binary matrix `grid`. An island is a group of `1`'s (representing land) connected **4-directionally** (horizontal or vertical). You may assume all four edges of the grid are surrounded by water.

The **area** of an island is the number of cells with a value `1` in the island.

Return the **maximum area** of an island in `grid`. If there is no island, return `0`.

**LeetCode Link:** [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)

## Approach
This problem can be solved using either **BFS with Queue** or **DFS**. We need to find all connected components (islands) and track the maximum area.

**Key Insight:** For each unvisited land cell, explore the entire connected component and calculate its area.

## Algorithm Steps
1. Iterate through all cells in the grid
2. For each unvisited land cell ('1'), start BFS/DFS to explore the island
3. Mark visited cells and count the area
4. Track the maximum area found
5. Return the maximum area

## Implementation

### C++ - BFS with Queue
```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size(), n = grid[0].size();
        int maxArea = 0;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int area = bfs(grid, i, j, directions);
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
    
private:
    int bfs(vector<vector<int>>& grid, int startRow, int startCol, 
            vector<vector<int>>& directions) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        
        q.push({startRow, startCol});
        grid[startRow][startCol] = 0; // Mark as visited
        int area = 1;
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 1) {
                    
                    grid[newRow][newCol] = 0; // Mark as visited
                    q.push({newRow, newCol});
                    area++;
                }
            }
        }
        
        return area;
    }
};
```

### C++ - DFS Recursive
```cpp
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size(), n = grid[0].size();
        int maxArea = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int area = dfs(grid, i, j);
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
    
private:
    int dfs(vector<vector<int>>& grid, int row, int col) {
        int m = grid.size(), n = grid[0].size();
        
        if (row < 0 || row >= m || col < 0 || col >= n || grid[row][col] == 0) {
            return 0;
        }
        
        grid[row][col] = 0; // Mark as visited
        int area = 1;
        
        // Explore all 4 directions
        area += dfs(grid, row - 1, col);
        area += dfs(grid, row + 1, col);
        area += dfs(grid, row, col - 1);
        area += dfs(grid, row, col + 1);
        
        return area;
    }
};
```

### C++ - Union-Find Approach
```cpp
class UnionFind {
public:
    vector<int> parent, rank, size;
    int maxSize;
    
    UnionFind(int n) : parent(n), rank(n, 0), size(n, 1), maxSize(1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
                maxSize = max(maxSize, size[rootY]);
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
                maxSize = max(maxSize, size[rootX]);
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
                rank[rootX]++;
                maxSize = max(maxSize, size[rootX]);
            }
        }
    }
};

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(m * n);
        
        int maxArea = 0;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    maxArea = max(maxArea, 1);
                    
                    for (auto& dir : directions) {
                        int newRow = i + dir[0];
                        int newCol = j + dir[1];
                        
                        if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                            grid[newRow][newCol] == 1) {
                            uf.unite(i * n + j, newRow * n + newCol);
                            maxArea = max(maxArea, uf.maxSize);
                        }
                    }
                }
            }
        }
        
        return maxArea;
    }
};
```

### Time Complexity
- **BFS/DFS:** O(m × n) - Visit each cell at most once
- **Union-Find:** O(m × n × α(m × n)) where α is inverse Ackermann function

### Space Complexity
- **BFS:** O(min(m, n)) - Queue space for BFS
- **DFS:** O(m × n) - Recursion stack in worst case
- **Union-Find:** O(m × n) - Union-Find data structure

## Examples

### Example 1
```
Input: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
Output: 4
Explanation: The island in the bottom-right has area 4.
```

### Example 2
```
Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The largest island has area 6.
```

### Example 3
```
Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0
Explanation: No islands exist.
```

## Notes
- **Connected components:** Islands are 4-directionally connected components
- **Area calculation:** Count all cells in each connected component
- **Marking visited:** Modify grid in-place or use separate visited array
- **Edge cases:** Empty grid, no islands, single cell

## Related Problems
- [LeetCode 200: Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [LeetCode 463: Island Perimeter](https://leetcode.com/problems/island-perimeter/)
- [LeetCode 694: Number of Distinct Islands](https://leetcode.com/problems/number-of-distinct-islands/)
- [LeetCode 827: Making A Large Island](https://leetcode.com/problems/making-a-large-island/)

## Pattern: 08-Island-Connected-Components
This problem exemplifies **Island/Connected Components** pattern where:
- **Component discovery:** Use BFS/DFS to find all connected land cells
- **Area tracking:** Count cells in each connected component
- **Grid traversal:** Systematically explore 2D grid using queue or recursion
- **Optimization:** Track maximum area while exploring components
