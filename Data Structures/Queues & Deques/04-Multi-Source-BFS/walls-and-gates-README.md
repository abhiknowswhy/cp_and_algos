# Walls and Gates

## Problem Description

You are given an `m x n` grid `rooms` initialized with these three possible values:
- `-1` A wall or an obstacle
- `0` A gate
- `INF` Infinity means an empty room

Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with `INF`.

## Approach

Use multi-source BFS starting from all gates simultaneously. This ensures that each empty room gets filled with the minimum distance to any gate.

## Algorithm Steps

1. Add all gates (cells with value 0) to the queue
2. Use BFS to explore all reachable empty rooms
3. For each room, update distance if current path is shorter
4. Continue until all reachable rooms are processed
5. Unreachable rooms remain as INF

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        
        int rows = rooms.size();
        int cols = rooms[0].size();
        queue<pair<int, int>> q;
        
        // Add all gates to queue
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (rooms[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                // Check bounds and if it's an empty room with larger distance
                if (newRow >= 0 && newRow < rows && 
                    newCol >= 0 && newCol < cols && 
                    rooms[newRow][newCol] > rooms[row][col] + 1) {
                    
                    rooms[newRow][newCol] = rooms[row][col] + 1;
                    q.push({newRow, newCol});
                }
            }
        }
    }
    
    // Alternative approach with explicit distance tracking
    void wallsAndGatesAlternative(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        
        int rows = rooms.size();
        int cols = rooms[0].size();
        const int INF = 2147483647;
        
        queue<pair<pair<int, int>, int>> q; // {{row, col}, distance}
        
        // Add all gates with distance 0
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (rooms[i][j] == 0) {
                    q.push({{i, j}, 0});
                }
            }
        }
        
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            
            int row = current.first.first;
            int col = current.first.second;
            int dist = current.second;
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < rows && 
                    newCol >= 0 && newCol < cols && 
                    rooms[newRow][newCol] == INF) {
                    
                    rooms[newRow][newCol] = dist + 1;
                    q.push({{newRow, newCol}, dist + 1});
                }
            }
        }
    }
    
    // DFS approach (less efficient)
    void wallsAndGatesDFS(vector<vector<int>>& rooms) {
        if (rooms.empty() || rooms[0].empty()) return;
        
        for (int i = 0; i < rooms.size(); i++) {
            for (int j = 0; j < rooms[0].size(); j++) {
                if (rooms[i][j] == 0) {
                    dfs(rooms, i, j, 0);
                }
            }
        }
    }
    
private:
    void dfs(vector<vector<int>>& rooms, int row, int col, int dist) {
        if (row < 0 || row >= rooms.size() || 
            col < 0 || col >= rooms[0].size() || 
            rooms[row][col] < dist) {
            return;
        }
        
        rooms[row][col] = dist;
        
        dfs(rooms, row + 1, col, dist + 1);
        dfs(rooms, row - 1, col, dist + 1);
        dfs(rooms, row, col + 1, dist + 1);
        dfs(rooms, row, col - 1, dist + 1);
    }
};
```

### Time Complexity

- **O(m × n)** where m is number of rows and n is number of columns
- Each cell is visited at most once

### Space Complexity

- **O(m × n)** for the BFS queue in worst case
- When all cells are gates initially

## Examples

### Example 1

```
Input: rooms = [
  [INF,-1,0,INF],
  [INF,INF,INF,-1],
  [INF,-1,INF,-1],
  [0,-1,INF,INF]
]

Output: [
  [3,-1,0,1],
  [2,2,1,-1],
  [1,-1,2,-1],
  [0,-1,3,4]
]
```

### Example 2

```
Input: rooms = [[-1]]
Output: [[-1]]
```

## Notes

- Multi-source BFS ensures optimal distances from any gate
- BFS guarantees shortest path in unweighted grid
- Handle walls (-1) by skipping them
- Only update distances when a shorter path is found
- INF typically represented as 2147483647

## Related Problems

- [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) - LeetCode 994
- [01 Matrix](https://leetcode.com/problems/01-matrix/) - LeetCode 542
- [As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/) - LeetCode 1162

## LeetCode Links

- [Walls and Gates](https://leetcode.com/problems/walls-and-gates/) - LeetCode 286 (Premium)

## Pattern: 04-Multi-Source-BFS

This is a classic multi-source BFS problem where we start from multiple sources (all gates) simultaneously to find minimum distances. This pattern is optimal when we need shortest distances from multiple starting points.
