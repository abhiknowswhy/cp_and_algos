# Shortest Distance from All Buildings

## Problem Description
You are given an `m x n` grid where each cell is one of the following:
- `0` representing an empty land which you can pass by freely
- `1` representing a building which you cannot pass through
- `2` representing an obstacle which you cannot pass through

You want to build a house on an empty land that reaches all buildings in the **shortest total travel distance**. You can only move up, down, left, and right.

Return the **shortest travel distance** for such a house. If it is not possible to build such a house that reaches all buildings, return `-1`.

**LeetCode Link:** [317. Shortest Distance from All Buildings](https://leetcode.com/problems/shortest-distance-from-all-buildings/)

## Approach
This is a **Multi-Source BFS** problem where we need to find the optimal location that minimizes total distance to all buildings. We have two main approaches:

1. **BFS from each building:** For each building, run BFS to calculate distances to all empty lands
2. **Multi-source BFS:** Run BFS from all buildings simultaneously (more complex but can be optimized)

**Key Insight:** A cell is a valid candidate only if it can reach ALL buildings.

## Algorithm Steps
1. Count total number of buildings in the grid
2. For each building, run BFS to calculate distances to all reachable empty lands
3. Track which empty lands can reach this building
4. Only consider empty lands that can reach ALL buildings
5. Return the minimum total distance among valid candidates

## Implementation

### C++ - BFS from Each Building
```cpp
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return -1;
        
        int m = grid.size(), n = grid[0].size();
        int buildings = 0;
        
        // Count buildings
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) buildings++;
            }
        }
        
        vector<vector<int>> totalDist(m, vector<int>(n, 0));
        vector<vector<int>> reachable(m, vector<int>(n, 0));
        
        // Run BFS from each building
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (!bfs(grid, i, j, totalDist, reachable)) {
                        return -1;  // Some building can't reach any empty land
                    }
                }
            }
        }
        
        // Find minimum total distance
        int minDist = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0 && reachable[i][j] == buildings) {
                    minDist = min(minDist, totalDist[i][j]);
                }
            }
        }
        
        return minDist == INT_MAX ? -1 : minDist;
    }
    
private:
    bool bfs(vector<vector<int>>& grid, int startRow, int startCol, 
             vector<vector<int>>& totalDist, vector<vector<int>>& reachable) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;
        int distance = 0;
        bool foundEmptyLand = false;
        
        while (!q.empty()) {
            int size = q.size();
            distance++;
            
            for (int i = 0; i < size; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];
                    
                    if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                        !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                        
                        visited[newRow][newCol] = true;
                        totalDist[newRow][newCol] += distance;
                        reachable[newRow][newCol]++;
                        q.push({newRow, newCol});
                        foundEmptyLand = true;
                    }
                }
            }
        }
        
        return foundEmptyLand;
    }
};
```

### C++ - Optimized Approach with Grid Modification
```cpp
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return -1;
        
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> totalDist(m, vector<int>(n, 0));
        int buildings = 0;
        int emptyLand = 0;  // Track what value represents reachable empty land
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int reachableBuildings = bfsOptimized(grid, i, j, totalDist, emptyLand);
                    if (reachableBuildings < buildings) {
                        return -1;  // This building can't reach some previously reachable areas
                    }
                    buildings++;
                    emptyLand--;  // Decrease value for next iteration
                }
            }
        }
        
        int minDist = INT_MAX;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == emptyLand) {  // Reachable by all buildings
                    minDist = min(minDist, totalDist[i][j]);
                }
            }
        }
        
        return minDist == INT_MAX ? -1 : minDist;
    }
    
private:
    int bfsOptimized(vector<vector<int>>& grid, int startRow, int startCol, 
                     vector<vector<int>>& totalDist, int targetValue) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        q.push({startRow, startCol});
        int distance = 0;
        int reachableEmptyLands = 0;
        
        while (!q.empty()) {
            int size = q.size();
            distance++;
            
            for (int i = 0; i < size; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];
                    
                    if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                        grid[newRow][newCol] == targetValue) {
                        
                        grid[newRow][newCol]--;  // Mark as visited for this building
                        totalDist[newRow][newCol] += distance;
                        q.push({newRow, newCol});
                        reachableEmptyLands++;
                    }
                }
            }
        }
        
        return reachableEmptyLands;
    }
};
```

### Time Complexity
- **Basic Approach:** O(k × m × n) where k is number of buildings
- **Optimized Approach:** O(k × m × n) but with better pruning

### Space Complexity
- **Both approaches:** O(m × n) for distance matrix and queue space

## Examples

### Example 1
```
Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 7
Explanation: 
Given three buildings at (0,0), (0,4), and (2,2), and an obstacle at (0,2).
The point (1,2) is an ideal empty land to build a house, as the total travel distance 
of 3+3+1=7 is minimal. So return 7.
```

### Example 2
```
Input: grid = [[1,0],[0,0]]
Output: 1
Explanation: The optimal location is (0,1) or (1,0) or (1,1) with distance 1.
```

### Example 3
```
Input: grid = [[1]]
Output: -1
Explanation: There are no empty lands to build a house.
```

## Notes
- **Reachability constraint:** Only consider empty lands that can reach ALL buildings
- **Optimization:** Use grid modification to avoid re-visiting unreachable areas
- **Early termination:** If any building can't reach some previously reachable areas, return -1
- **Edge cases:** No empty lands, isolated buildings, all obstacles

## Related Problems
- [LeetCode 542: 01 Matrix](https://leetcode.com/problems/01-matrix/)
- [LeetCode 994: Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [LeetCode 286: Walls and Gates](https://leetcode.com/problems/walls-and-gates/)
- [LeetCode 1162: As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)

## Pattern: 04-Multi-Source-BFS
This problem uses **Multi-Source BFS** concepts where:
- **Multiple individual BFS:** Run BFS from each building separately
- **Distance accumulation:** Sum distances from all buildings to each empty land
- **Reachability tracking:** Ensure empty land can reach all buildings
- **Optimization potential:** Could use true multi-source BFS for advanced solutions
