# Rotting Oranges

## Problem Description

You are given an `m x n` grid where each cell can have one of three values:
- `0` representing an empty cell
- `1` representing a fresh orange  
- `2` representing a rotten orange

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return `-1`.

## Approach

Use multi-source BFS starting from all initially rotten oranges simultaneously. This ensures all oranges rot in the minimum time possible.

## Algorithm Steps

1. Count fresh oranges and add all rotten oranges to queue with time 0
2. If no fresh oranges initially, return 0
3. While queue is not empty:
   - Dequeue rotten orange with its time
   - Check all 4 adjacent cells
   - If cell has fresh orange, make it rotten and enqueue with time+1
   - Decrement fresh orange count
4. Return maximum time if all oranges rotten, else -1

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int freshCount = 0;
        queue<pair<pair<int,int>, int>> q; // {{row, col}, time}
        
        // Find all rotten oranges and count fresh ones
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }
        
        // If no fresh oranges, return 0
        if (freshCount == 0) return 0;
        
        vector<pair<int,int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        int maxTime = 0;
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            
            int row = current.first.first;
            int col = current.first.second;
            int time = current.second;
            
            maxTime = max(maxTime, time);
            
            // Check all 4 directions
            for (auto& dir : directions) {
                int newRow = row + dir.first;
                int newCol = col + dir.second;
                
                // Check bounds and if cell has fresh orange
                if (newRow >= 0 && newRow < rows && 
                    newCol >= 0 && newCol < cols && 
                    grid[newRow][newCol] == 1) {
                    
                    grid[newRow][newCol] = 2; // Make it rotten
                    freshCount--;
                    q.push({{newRow, newCol}, time + 1});
                }
            }
        }
        
        return freshCount == 0 ? maxTime : -1;
    }
    
    // Alternative cleaner implementation
    int orangesRottingV2(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        int fresh = 0, time = 0;
        queue<pair<int,int>> q;
        
        // Initialize queue with all rotten oranges
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }
        
        vector<pair<int,int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        while (!q.empty() && fresh > 0) {
            int queueSize = q.size();
            
            // Process all oranges that rot at current time
            for (int i = 0; i < queueSize; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                for (auto [dr, dc] : dirs) {
                    int newRow = row + dr;
                    int newCol = col + dc;
                    
                    if (newRow >= 0 && newRow < rows && 
                        newCol >= 0 && newCol < cols && 
                        grid[newRow][newCol] == 1) {
                        
                        grid[newRow][newCol] = 2;
                        fresh--;
                        q.push({newRow, newCol});
                    }
                }
            }
            
            time++;
        }
        
        return fresh == 0 ? time : -1;
    }
};
```

### Time Complexity

- **O(m × n)** where m is number of rows and n is number of columns
- Each cell is visited at most once

### Space Complexity

- **O(m × n)** for the BFS queue in worst case
- When all cells are initially rotten

## Examples

### Example 1

```
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Explanation:
Minute 0: [[2,1,1],[1,1,0],[0,1,1]]
Minute 1: [[2,2,1],[2,1,0],[0,1,1]]
Minute 2: [[2,2,2],[2,2,0],[0,1,1]]
Minute 3: [[2,2,2],[2,2,0],[0,2,1]]
Minute 4: [[2,2,2],[2,2,0],[0,2,2]]
```

### Example 2

```
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner will never rot
```

## Notes

- Multi-source BFS ensures simultaneous spreading from all rotten oranges
- Track fresh orange count to detect if all can be rotten
- Process level by level to correctly calculate time
- 4-directional movement only (not diagonal)

## Related Problems

- [Walls and Gates](https://leetcode.com/problems/walls-and-gates/) - LeetCode 286
- [01 Matrix](https://leetcode.com/problems/01-matrix/) - LeetCode 542
- [As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/) - LeetCode 1162

## LeetCode Links

- [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) - LeetCode 994

## Pattern: 04-Multi-Source-BFS

This is a classic multi-source BFS problem where we start BFS from multiple sources (all initially rotten oranges) simultaneously. This pattern is used when we need to find minimum time/distance from multiple starting points.
