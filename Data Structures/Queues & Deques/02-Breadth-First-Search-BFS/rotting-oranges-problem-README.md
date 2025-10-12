# Rotting oranges problem

## Problem Description
You are given an m x n grid where each cell can have one of three values:
- 0 representing an empty cell,
- 1 representing a fresh orange, or
- 2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

**LeetCode Problem:** [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)

## Approach
Use multi-source BFS starting from all initially rotten oranges simultaneously. Track time and count of fresh oranges to determine when all are rotten.

## Algorithm Steps
1. Find all initially rotten oranges and count fresh oranges
2. Add all rotten oranges to queue with time 0
3. BFS: For each rotten orange, rot adjacent fresh oranges
4. Track maximum time taken and decrement fresh count
5. Return time if all fresh oranges are rotten, else -1

## Implementation

### C++
```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        queue<pair<int, int>> q; // {row, col}
        int freshCount = 0;
        
        // Find all initially rotten oranges and count fresh ones
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 2) {
                    q.push({r, c});
                } else if (grid[r][c] == 1) {
                    freshCount++;
                }
            }
        }
        
        // If no fresh oranges, return 0
        if (freshCount == 0) return 0;
        
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int minutes = 0;
        
        while (!q.empty()) {
            int size = q.size();
            bool rottenThisRound = false;
            
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && 
                        grid[nr][nc] == 1) {
                        grid[nr][nc] = 2;
                        q.push({nr, nc});
                        freshCount--;
                        rottenThisRound = true;
                    }
                }
            }
            
            if (rottenThisRound) minutes++;
        }
        
        return freshCount == 0 ? minutes : -1;
    }
};
```

### Time Complexity
O(m × n) where m and n are grid dimensions

### Space Complexity
O(m × n) for the queue in worst case

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

Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, 
because rotting only happens 4-directionally.
```

### Example 3
```
Input: grid = [[0,2]]
Output: 0

Explanation: Since there are already no fresh oranges at minute 0, the answer is 0.
```

## Notes
- Multi-source BFS: Start from multiple points simultaneously
- Track both time progression and completion status
- Grid modification in-place to mark rotten oranges
- 4-directional movement pattern is common in grid problems

## Related Problems
- [LeetCode 286 - Walls and Gates](https://leetcode.com/problems/walls-and-gates/)
- [LeetCode 542 - 01 Matrix](https://leetcode.com/problems/01-matrix/)
- [LeetCode 1162 - As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)
- [LeetCode 417 - Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)

## Pattern: 02-Breadth-First-Search-BFS
This problem demonstrates multi-source BFS where we start from multiple initial points. It's a common pattern for spreading/infection problems and shortest distance from multiple sources.
