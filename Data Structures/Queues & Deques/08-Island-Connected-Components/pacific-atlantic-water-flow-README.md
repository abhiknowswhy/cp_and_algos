# Pacific Atlantic Water Flow

## Problem Description
There is an `m x n` rectangular island that borders both the Pacific and Atlantic oceans. The Pacific ocean touches the island's left and top edges, and the Atlantic ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an `m x n` integer matrix `heights` where `heights[r][c]` represents the height above sea level of the cell at coordinate `(r, c)`.

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into that ocean.

Return a 2D list of grid coordinates where the rain water can flow to both the Pacific and Atlantic oceans.

## Approach
This problem can be solved using BFS (or DFS) by working backwards from the ocean boundaries. Instead of checking if water can reach oceans from each cell, we check which cells can be reached from each ocean.

**Key insight:** If water can flow from cell A to ocean X, then we can trace backwards from ocean X to reach cell A.

**Strategy:**
1. Start BFS from all Pacific border cells (top row, left column)
2. Start BFS from all Atlantic border cells (bottom row, right column)  
3. Find intersection of cells reachable from both oceans

## Algorithm Steps
1. **Initialize two sets** to track cells reachable from Pacific and Atlantic
2. **BFS from Pacific borders**: Mark all cells that can reach Pacific ocean
3. **BFS from Atlantic borders**: Mark all cells that can reach Atlantic ocean
4. **Find intersection**: Return cells that can reach both oceans
5. **Water flow rule**: Water flows from higher/equal height to lower/equal height

## Implementation

### Approach 1: BFS Solution
```cpp
#include <queue>
#include <vector>
#include <set>

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};
        
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));
        
        // BFS from Pacific borders (top row and left column)
        queue<pair<int, int>> pacificQueue;
        for (int i = 0; i < m; i++) {
            pacificQueue.push({i, 0});  // Left column
            pacific[i][0] = true;
        }
        for (int j = 1; j < n; j++) {
            pacificQueue.push({0, j});  // Top row
            pacific[0][j] = true;
        }
        
        // BFS from Atlantic borders (bottom row and right column)
        queue<pair<int, int>> atlanticQueue;
        for (int i = 0; i < m; i++) {
            atlanticQueue.push({i, n - 1});  // Right column
            atlantic[i][n - 1] = true;
        }
        for (int j = 0; j < n - 1; j++) {
            atlanticQueue.push({m - 1, j});  // Bottom row
            atlantic[m - 1][j] = true;
        }
        
        // BFS for Pacific reachable cells
        bfs(heights, pacificQueue, pacific);
        
        // BFS for Atlantic reachable cells
        bfs(heights, atlanticQueue, atlantic);
        
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
    void bfs(vector<vector<int>>& heights, queue<pair<int, int>>& q, 
             vector<vector<bool>>& visited) {
        int m = heights.size(), n = heights[0].size();
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
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

### Approach 2: DFS Solution
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
            dfs(heights, pacific, i, 0, 0);  // Left column
        }
        for (int j = 0; j < n; j++) {
            dfs(heights, pacific, 0, j, 0);  // Top row
        }
        
        // DFS from Atlantic borders
        for (int i = 0; i < m; i++) {
            dfs(heights, atlantic, i, n - 1, 0);  // Right column
        }
        for (int j = 0; j < n; j++) {
            dfs(heights, atlantic, m - 1, j, 0);  // Bottom row
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
        dfs(heights, visited, row - 1, col, heights[row][col]);
        dfs(heights, visited, row + 1, col, heights[row][col]);
        dfs(heights, visited, row, col - 1, heights[row][col]);
        dfs(heights, visited, row, col + 1, heights[row][col]);
    }
};
```

### Approach 3: Optimized BFS with Single Pass
```cpp
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};
        
        int m = heights.size(), n = heights[0].size();
        
        // 0: not visited, 1: Pacific reachable, 2: Atlantic reachable, 3: both
        vector<vector<int>> reachability(m, vector<int>(n, 0));
        
        queue<pair<int, int>> q;
        
        // Mark Pacific borders and add to queue
        for (int i = 0; i < m; i++) {
            reachability[i][0] |= 1;  // Left column - Pacific
            q.push({i, 0});
        }
        for (int j = 1; j < n; j++) {
            reachability[0][j] |= 1;  // Top row - Pacific
            q.push({0, j});
        }
        
        // BFS for Pacific
        bfsWithMask(heights, q, reachability, 1);
        
        // Mark Atlantic borders and add to queue
        for (int i = 0; i < m; i++) {
            reachability[i][n - 1] |= 2;  // Right column - Atlantic
            q.push({i, n - 1});
        }
        for (int j = 0; j < n - 1; j++) {
            reachability[m - 1][j] |= 2;  // Bottom row - Atlantic
            q.push({m - 1, j});
        }
        
        // BFS for Atlantic
        bfsWithMask(heights, q, reachability, 2);
        
        // Collect cells reachable from both oceans
        vector<vector<int>> result;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (reachability[i][j] == 3) {  // Both Pacific (1) and Atlantic (2)
                    result.push_back({i, j});
                }
            }
        }
        
        return result;
    }
    
private:
    void bfsWithMask(vector<vector<int>>& heights, queue<pair<int, int>>& q,
                     vector<vector<int>>& reachability, int mask) {
        int m = heights.size(), n = heights[0].size();
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    !(reachability[newRow][newCol] & mask) &&  // Not yet reached by this ocean
                    heights[newRow][newCol] >= heights[row][col]) {
                    
                    reachability[newRow][newCol] |= mask;
                    q.push({newRow, newCol});
                }
            }
        }
    }
};
```

### Time Complexity
- **BFS/DFS**: O(m × n) where m and n are matrix dimensions
- Each cell is visited at most twice (once for each ocean)

### Space Complexity
- **BFS**: O(m × n) for visited arrays and queue
- **DFS**: O(m × n) for visited arrays and recursion stack

## Examples

### Example 1
```cpp
Input: heights = [[1,2,2,3,5],
                  [3,2,3,4,4],
                  [2,4,5,3,1],
                  [6,7,1,4,5],
                  [5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

Explanation: The cells marked can reach both Pacific and Atlantic oceans.
```

### Example 2
```cpp
Input: heights = [[1]]
Output: [[0,0]]
Explanation: Single cell can reach both oceans (it's on the border).
```

## Key Insights

### Queue Pattern Usage
- **Multi-source BFS**: Start from all border cells simultaneously
- **Reverse thinking**: Instead of "can reach ocean", ask "can be reached from ocean"
- **Intersection finding**: Use two separate BFS traversals and find common cells

### Problem Strategy
1. **Border analysis**: Ocean borders are starting points for BFS
2. **Flow direction**: Water flows from equal/higher to equal/lower heights
3. **Reverse BFS**: Much more efficient than checking each cell individually

### Optimization Techniques
- **Bit masking**: Use single array with bits for different oceans
- **Early termination**: Stop BFS when no new cells can be reached
- **Memory optimization**: Reuse queue for both BFS runs

## Related Problems
- Surrounded Regions
- Number of Islands
- Walls and Gates
Output: 
Explanation: 
```

### Example 2
```
Input: 
Output: 
Explanation: 
```

## Notes
<!-- Add any additional notes, edge cases, or variations -->

## Related Problems
<!-- List related problems -->

## Pattern: 08-Island-Connected-Components
<!-- Explain how this problem fits the pattern -->
