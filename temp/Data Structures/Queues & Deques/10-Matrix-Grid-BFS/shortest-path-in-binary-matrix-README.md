# Shortest Path in Binary Matrix

## Problem Description
Given an `n x n` binary matrix `grid`, return the length of the shortest clear path from top-left to bottom-right. If such a path does not exist, return -1.

A clear path is a path where:
- All visited cells are 0 (clear)
- You can move in 8 directions (horizontally, vertically, and diagonally)
- The path length is the number of cells in the path

## Approach
This is a classic shortest path problem in an unweighted grid. BFS is optimal because:
- **Unweighted edges**: Each move has the same cost (1)
- **Shortest guarantee**: BFS explores paths in order of increasing length
- **8-directional movement**: More complex than standard 4-directional grid problems

## Algorithm Steps
1. **Check edge cases**: Start or end cell blocked, empty grid
2. **Initialize BFS**: Queue with starting position and distance 1
3. **For each position**: Explore all 8 possible directions
4. **Track visited**: Mark cells to avoid revisiting
5. **Return distance** when destination is reached

## Implementation

### Approach 1: Standard BFS
```cpp
#include <queue>
#include <vector>

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Edge cases
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }
        
        if (n == 1) {
            return 1;  // Single cell case
        }
        
        // 8 directions: horizontal, vertical, and diagonal
        vector<pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        q.push({0, 0});
        visited[0][0] = true;
        int pathLength = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                // Check if reached destination
                if (row == n - 1 && col == n - 1) {
                    return pathLength;
                }
                
                // Explore all 8 directions
                for (auto [dr, dc] : directions) {
                    int newRow = row + dr;
                    int newCol = col + dc;
                    
                    if (isValid(newRow, newCol, n) && 
                        grid[newRow][newCol] == 0 && 
                        !visited[newRow][newCol]) {
                        
                        visited[newRow][newCol] = true;
                        q.push({newRow, newCol});
                    }
                }
            }
            
            pathLength++;
        }
        
        return -1;  // No path found
    }
    
private:
    bool isValid(int row, int col, int n) {
        return row >= 0 && row < n && col >= 0 && col < n;
    }
};
```

### Approach 2: BFS with Distance Tracking
```cpp
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }
        
        vector<pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        queue<tuple<int, int, int>> q;  // row, col, distance
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        q.push({0, 0, 1});
        visited[0][0] = true;
        
        while (!q.empty()) {
            auto [row, col, dist] = q.front();
            q.pop();
            
            if (row == n - 1 && col == n - 1) {
                return dist;
            }
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
                    
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol, dist + 1});
                }
            }
        }
        
        return -1;
    }
};
```

### Approach 3: A* Search (Optimized)
```cpp
#include <queue>
#include <cmath>

class Solution {
private:
    struct Node {
        int row, col, distance, heuristic;
        
        bool operator>(const Node& other) const {
            return distance + heuristic > other.distance + other.heuristic;
        }
    };
    
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }
        
        if (n == 1) return 1;
        
        vector<pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        pq.push({0, 0, 1, manhattanDistance(0, 0, n-1, n-1)});
        visited[0][0] = true;
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            if (current.row == n - 1 && current.col == n - 1) {
                return current.distance;
            }
            
            for (auto [dr, dc] : directions) {
                int newRow = current.row + dr;
                int newCol = current.col + dc;
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
                    
                    visited[newRow][newCol] = true;
                    int heuristic = manhattanDistance(newRow, newCol, n-1, n-1);
                    pq.push({newRow, newCol, current.distance + 1, heuristic});
                }
            }
        }
        
        return -1;
    }
    
private:
    int manhattanDistance(int r1, int c1, int r2, int c2) {
        return max(abs(r1 - r2), abs(c1 - c2));  // Chebyshev distance for 8-directional
    }
};
```

### Approach 4: Bidirectional BFS
```cpp
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0) {
            return -1;
        }
        
        if (n == 1) return 1;
        
        vector<pair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        set<pair<int, int>> startSet, endSet;
        vector<vector<int>> visited(n, vector<int>(n, 0));  // 0: unvisited, 1: from start, 2: from end
        
        startSet.insert({0, 0});
        endSet.insert({n-1, n-1});
        visited[0][0] = 1;
        visited[n-1][n-1] = 2;
        
        int level = 1;
        
        while (!startSet.empty() && !endSet.empty()) {
            // Always expand the smaller set
            if (startSet.size() > endSet.size()) {
                swap(startSet, endSet);
            }
            
            set<pair<int, int>> nextSet;
            
            for (auto [row, col] : startSet) {
                for (auto [dr, dc] : directions) {
                    int newRow = row + dr;
                    int newCol = col + dc;
                    
                    if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&
                        grid[newRow][newCol] == 0) {
                        
                        if (visited[newRow][newCol] == 0) {
                            visited[newRow][newCol] = visited[row][col];
                            nextSet.insert({newRow, newCol});
                        } else if (visited[newRow][newCol] != visited[row][col]) {
                            return level + 1;  // Path found
                        }
                    }
                }
            }
            
            startSet = nextSet;
            level++;
        }
        
        return -1;
    }
};
```

### Time Complexity
- **Standard BFS**: O(n²) - each cell visited at most once
- **A* Search**: O(n² log n) - priority queue operations
- **Bidirectional BFS**: O(n²) but often faster in practice

### Space Complexity
- **All approaches**: O(n²) for visited array and queue/priority queue

## Examples

### Example 1
```
Input: grid = [[0,0,0],
               [1,1,0],
               [1,1,0]]
Output: 4
Path: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)
```

### Example 2
```
Input: grid = [[0,1],
               [1,0]]
Output: -1
Explanation: No clear path exists.
```

### Example 3
```
Input: grid = [[1,0,0],
               [1,1,0],
               [1,1,0]]
Output: -1
Explanation: Starting cell is blocked.
```

## Key Insights

### Queue Pattern Usage
- **Level-order exploration**: BFS guarantees shortest path in unweighted grid
- **8-directional movement**: More neighbors to explore than standard grid problems
- **Distance tracking**: Either by level processing or storing distance with each node

### Optimization Strategies
1. **Early termination**: Stop as soon as destination is reached
2. **A* heuristic**: Use Manhattan/Chebyshev distance to guide search
3. **Bidirectional search**: Search from both ends to reduce search space
4. **Visited optimization**: Use in-place marking if grid modification is allowed

### Edge Cases
- Single cell grid (n=1)
- Start or end cell blocked
- No path exists
- Grid with all zeros vs. mixed obstacles

## Related Problems
- Word Ladder
- Shortest Bridge
- Minimum Knight Moves
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

## Pattern: 10-Matrix-Grid-BFS
<!-- Explain how this problem fits the pattern -->
