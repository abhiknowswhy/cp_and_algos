# 01 Matrix (Distance to Nearest 0)

## Problem Description
Given an `m x n` binary matrix `mat`, return the distance of the nearest `0` for each cell. The distance between two adjacent cells is 1.

**LeetCode Link:** [542. 01 Matrix](https://leetcode.com/problems/01-matrix/)

## Approach
This is a classic **Multi-Source BFS** problem where we need to find the shortest distance from multiple sources (all 0s) to every cell. Instead of running BFS from each cell, we start BFS from all 0s simultaneously.

**Key Insight:** Start from all 0s and expand outward level by level. This guarantees that when we reach a cell for the first time, we've found the shortest distance.

## Algorithm Steps
1. Initialize a result matrix with infinity for all 1s and 0 for all 0s
2. Add all 0 positions to the queue (multi-source initialization)
3. Perform BFS level by level
4. For each cell, update its neighbors if we find a shorter path
5. Continue until queue is empty

## Implementation

### C++
```cpp
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;
        
        // Initialize: add all 0s to queue and set their distance to 0
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        
        // Directions for 4-connected neighbors
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Multi-source BFS
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                // Check bounds
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
                    // If we found a shorter path
                    if (dist[newRow][newCol] > dist[row][col] + 1) {
                        dist[newRow][newCol] = dist[row][col] + 1;
                        q.push({newRow, newCol});
                    }
                }
            }
        }
        
        return dist;
    }
};
```

### Alternative Approach - DP Solution
```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX - 1));
        
        // Initialize 0s
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    dp[i][j] = 0;
                }
            }
        }
        
        // Top-left to bottom-right pass
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
                if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
            }
        }
        
        // Bottom-right to top-left pass
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i < m - 1) dp[i][j] = min(dp[i][j], dp[i+1][j] + 1);
                if (j < n - 1) dp[i][j] = min(dp[i][j], dp[i][j+1] + 1);
            }
        }
        
        return dp;
    }
};
```

### Time Complexity
- **BFS Approach:** O(m × n) - Each cell is processed at most once
- **DP Approach:** O(m × n) - Two passes through the matrix

### Space Complexity
- **BFS Approach:** O(m × n) - Queue can hold all cells in worst case
- **DP Approach:** O(1) - Only using the result matrix

## Examples

### Example 1
```
Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]
Explanation: The nearest 0 for each 1 is itself at distance 1.
```

### Example 2
```
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
Explanation: 
- (1,1) has nearest 0s at distance 1
- (2,0) has nearest 0 at distance 1  
- (2,1) has nearest 0 at distance 2
- (2,2) has nearest 0 at distance 1
```

## Notes
- **Multi-Source BFS** is more efficient than running BFS from each cell individually
- **DP approach** is space-efficient but requires two passes
- Both approaches guarantee shortest distance due to their systematic exploration
- Handle edge cases: all 0s, all 1s (impossible), single cell

## Related Problems
- [LeetCode 994: Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [LeetCode 286: Walls and Gates](https://leetcode.com/problems/walls-and-gates/)
- [LeetCode 1162: As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)

## Pattern: 04-Multi-Source-BFS
This problem exemplifies **Multi-Source BFS** where:
- **Multiple sources:** All cells containing 0 are starting points
- **Simultaneous expansion:** BFS explores from all sources simultaneously
- **Level-by-level processing:** Guarantees shortest distance when cell is first reached
- **Optimization:** Avoids redundant single-source BFS calls from each cell
