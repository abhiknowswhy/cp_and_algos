# Pacific Atlantic Water Flow

## Problem Description
Given an `m x n` rectangular island that borders both the **Pacific Ocean** and **Atlantic Ocean**. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an `m x n` integer matrix `heights` where `heights[r][c]` represents the height above sea level of the cell at coordinate `(r, c)`.

The island receives a lot of rain, and the rain water can flow to neighboring cells directly if the neighboring cell's height is **less than or equal to** the current cell's height. Water can flow from any cell adjacent to an ocean into that ocean.

Return a **2D list** of grid coordinates `result` where `result[i] = [ri, ci]` denotes that rain water can flow from cell `(ri, ci)` to **both** the Pacific and Atlantic oceans.

**LeetCode Link:** [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)

## Approach
This is a **Multi-Source BFS/DFS** problem. Instead of checking each cell individually, we work backwards:

1. Start from all ocean border cells
2. Use BFS/DFS to find all cells that can reach each ocean
3. Find intersection of cells that can reach both oceans

**Key Insight:** Work backwards from oceans - if water can flow from cell A to cell B, then A's height ≥ B's height.

## Algorithm Steps
1. Create two boolean matrices to track reachability to Pacific and Atlantic
2. Initialize queues with all border cells (Pacific: top & left, Atlantic: bottom & right)
3. Run BFS from each ocean simultaneously
4. For each ocean, mark all reachable cells
5. Find cells that can reach both oceans

## Implementation

### C++ - BFS Approach
```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};
        
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));
        
        queue<pair<int, int>> pacificQueue, atlanticQueue;
        
        // Initialize border cells
        for (int i = 0; i < m; i++) {
            // Pacific: left border
            pacific[i][0] = true;
            pacificQueue.push({i, 0});
            
            // Atlantic: right border
            atlantic[i][n-1] = true;
            atlanticQueue.push({i, n-1});
        }
        
        for (int j = 0; j < n; j++) {
            // Pacific: top border
            pacific[0][j] = true;
            pacificQueue.push({0, j});
            
            // Atlantic: bottom border
            atlantic[m-1][j] = true;
            atlanticQueue.push({m-1, j});
        }
        
        // BFS for both oceans
        bfs(heights, pacific, pacificQueue);
        bfs(heights, atlantic, atlanticQueue);
        
        // Find intersection
        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        
        return result;
    }
    
private:
    void bfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, 
             queue<pair<int, int>>& q) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    !visited[newRow][newCol] && 
                    heights[newRow][newCol] >= heights[row][col]) {
                    
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
    }
};
```

### C++ - DFS Approach
```cpp
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};
        
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));
        
        // DFS from Pacific borders
        for (int i = 0; i < m; i++) {
            dfs(heights, pacific, i, 0, 0);           // Left border
            dfs(heights, atlantic, i, n-1, 0);       // Right border
        }
        
        for (int j = 0; j < n; j++) {
            dfs(heights, pacific, 0, j, 0);          // Top border
            dfs(heights, atlantic, m-1, j, 0);       // Bottom border
        }
        
        // Find intersection
        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        
        return result;
    }
    
private:
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, 
             int row, int col, int prevHeight) {
        int m = heights.size(), n = heights[0].size();
        
        if (row < 0 || row >= m || col < 0 || col >= n || 
            visited[row][col] || heights[row][col] < prevHeight) {
            return;
        }
        
        visited[row][col] = true;
        
        // Explore all 4 directions
        dfs(heights, visited, row-1, col, heights[row][col]);
        dfs(heights, visited, row+1, col, heights[row][col]);
        dfs(heights, visited, row, col-1, heights[row][col]);
        dfs(heights, visited, row, col+1, heights[row][col]);
    }
};
```

### Time Complexity
- **Both BFS & DFS:** O(m × n) - Each cell is visited at most once for each ocean

### Space Complexity
- **BFS:** O(m × n) - Queue space + visited arrays
- **DFS:** O(m × n) - Recursion stack + visited arrays

## Examples

### Example 1
```
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: 
Rain water can flow to both oceans from these coordinates.
```

### Example 2
```
Input: heights = [[1]]
Output: [[0,0]]
Explanation: 
The single cell can reach both oceans as it's on the border.
```

## Notes
- **Reverse thinking:** Instead of "can this cell reach ocean?", ask "can ocean reach this cell?"
- **Water flow rule:** Water flows from higher to lower or equal height
- **Border initialization:** All border cells can reach their adjacent ocean
- **Multi-source:** We start BFS/DFS from all border cells simultaneously

## Related Problems
- [LeetCode 200: Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [LeetCode 994: Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [LeetCode 542: 01 Matrix](https://leetcode.com/problems/01-matrix/)
- [LeetCode 130: Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)

## Pattern: 04-Multi-Source-BFS
This problem demonstrates **Multi-Source BFS** where:
- **Multiple sources:** All border cells of each ocean are starting points
- **Reverse exploration:** Work backwards from destination to find all reachable sources
- **Simultaneous processing:** Process all border cells of each ocean together
- **Intersection finding:** Combine results from both multi-source searches
