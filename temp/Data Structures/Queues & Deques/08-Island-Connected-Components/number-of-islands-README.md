# Number of Islands

## Problem Description

Given an `m x n` 2D binary grid which represents a map of `'1'`s (land) and `'0'`s (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are surrounded by water.

## Approach

Use BFS to find connected components of land cells. Each time we encounter an unvisited land cell, start a new BFS to mark all connected land cells as visited, representing one island.

## Algorithm Steps

1. Initialize count to 0 and visited set
2. Iterate through each cell in the grid
3. If cell is land ('1') and not visited:
   - Increment island count
   - Start BFS from this cell to mark entire island as visited
4. In BFS, explore all 4-directionally connected land cells
5. Return total island count

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int rows = grid.size();
        int cols = grid[0].size();
        int islands = 0;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    bfs(grid, i, j, visited);
                    islands++;
                }
            }
        }
        
        return islands;
    }
    
private:
    void bfs(vector<vector<char>>& grid, int startRow, int startCol, 
             vector<vector<bool>>& visited) {
        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int,int>> q;
        
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;
        
        vector<pair<int,int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < rows && 
                    newCol >= 0 && newCol < cols && 
                    grid[newRow][newCol] == '1' && 
                    !visited[newRow][newCol]) {
                    
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
    }
    
    // Alternative: Modify grid in-place (destructive)
    int numIslandsInPlace(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int islands = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    bfsMarkVisited(grid, i, j);
                    islands++;
                }
            }
        }
        
        return islands;
    }
    
    void bfsMarkVisited(vector<vector<char>>& grid, int startRow, int startCol) {
        queue<pair<int,int>> q;
        q.push({startRow, startCol});
        grid[startRow][startCol] = '0'; // Mark as visited
        
        vector<pair<int,int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < grid.size() && 
                    newCol >= 0 && newCol < grid[0].size() && 
                    grid[newRow][newCol] == '1') {
                    
                    grid[newRow][newCol] = '0'; // Mark as visited
                    q.push({newRow, newCol});
                }
            }
        }
    }
    
    // DFS solution for comparison
    int numIslandsDFS(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        
        int islands = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    dfs(grid, i, j);
                    islands++;
                }
            }
        }
        
        return islands;
    }
    
    void dfs(vector<vector<char>>& grid, int row, int col) {
        if (row < 0 || row >= grid.size() || 
            col < 0 || col >= grid[0].size() || 
            grid[row][col] != '1') {
            return;
        }
        
        grid[row][col] = '0'; // Mark as visited
        
        // Explore all 4 directions
        dfs(grid, row + 1, col);
        dfs(grid, row - 1, col);
        dfs(grid, row, col + 1);
        dfs(grid, row, col - 1);
    }
};
```

### Time Complexity

- **O(m × n)** where m is number of rows and n is number of columns
- Each cell is visited at most once

### Space Complexity

- **O(min(m, n))** for BFS queue (worst case when grid is filled with lands)
- **O(m × n)** if using separate visited array

## Examples

### Example 1

```
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
```

### Example 2

```
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

## Notes

- Can solve with either BFS or DFS (similar time complexity)
- BFS uses queue, DFS uses recursion stack
- Can modify grid in-place to save space (mark visited cells as '0')
- Each connected component of '1's represents one island

## Related Problems

- [Max Area of Island](https://leetcode.com/problems/max-area-of-island/) - LeetCode 695
- [Number of Distinct Islands](https://leetcode.com/problems/number-of-distinct-islands/) - LeetCode 694
- [Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) - LeetCode 130

## LeetCode Links

- [Number of Islands](https://leetcode.com/problems/number-of-islands/) - LeetCode 200

## Pattern: 08-Island-Connected-Components

This is the classic island/connected components pattern using BFS. We find all connected regions of land cells, where each connected region represents one island. The BFS explores all reachable land cells from a starting point.
