# Number of Distinct Islands

## Problem Description

Given an `m x n` binary grid where `1` represents land and `0` represents water, return the number of distinct islands.

Two islands are considered the same if one island can be translated (not rotated or reflected) to equal the other.

**Key insight**: Islands are distinct if they have different shapes when normalized to the same starting position.

## Approach

The key challenge is how to represent island shapes in a canonical form for comparison. We can use BFS/DFS to explore each island and record the relative positions of all land cells.

**Shape representation strategies:**

1. **Path encoding**: Record the sequence of moves during traversal
2. **Coordinate normalization**: Store relative coordinates from a reference point
3. **Hash-based comparison**: Use set operations for shape comparison

## Algorithm Steps

1. **Iterate through grid** to find unvisited land cells
2. **For each island**: Use BFS/DFS to explore and record its shape
3. **Normalize shape**: Convert coordinates to relative positions
4. **Store unique shapes**: Use set to count distinct shapes
5. **Return count** of unique island shapes

## Implementation

### Approach 1: BFS with Coordinate Normalization

```cpp
#include <queue>
#include <vector>
#include <set>
#include <string>

class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
      
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        set<vector<pair<int, int>>> uniqueShapes;
      
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    vector<pair<int, int>> shape = bfsGetShape(grid, visited, i, j);
                    uniqueShapes.insert(shape);
                }
            }
        }
      
        return uniqueShapes.size();
    }
  
private:
    vector<pair<int, int>> bfsGetShape(vector<vector<int>>& grid,
                                      vector<vector<bool>>& visited,
                                      int startRow, int startCol) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        vector<pair<int, int>> shape;
      
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;
      
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
      
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
          
            // Store relative coordinates (normalized to starting position)
            shape.push_back({row - startRow, col - startCol});
          
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
              
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
      
        // Sort to ensure consistent representation
        sort(shape.begin(), shape.end());
        return shape;
    }
};
```

### Approach 2: DFS with Path Encoding

```cpp
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
      
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        set<string> uniquePaths;
      
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    string path = "";
                    dfsGetPath(grid, visited, i, j, path, 'S'); // S for start
                    uniquePaths.insert(path);
                }
            }
        }
      
        return uniquePaths.size();
    }
  
private:
    void dfsGetPath(vector<vector<int>>& grid, vector<vector<bool>>& visited,
                   int row, int col, string& path, char direction) {
        int m = grid.size(), n = grid[0].size();
      
        if (row < 0 || row >= m || col < 0 || col >= n || 
            visited[row][col] || grid[row][col] == 0) {
            return;
        }
      
        visited[row][col] = true;
        path += direction;
      
        // Explore in consistent order: up, down, left, right
        dfsGetPath(grid, visited, row - 1, col, path, 'U');
        dfsGetPath(grid, visited, row + 1, col, path, 'D');
        dfsGetPath(grid, visited, row, col - 1, path, 'L');
        dfsGetPath(grid, visited, row, col + 1, path, 'R');
      
        // Add backtrack marker to distinguish different paths
        path += 'B';
    }
};
```

### Approach 3: BFS with String Hash Representation

```cpp
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
      
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        set<string> uniqueShapes;
      
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    string shapeHash = bfsGetShapeHash(grid, visited, i, j);
                    uniqueShapes.insert(shapeHash);
                }
            }
        }
      
        return uniqueShapes.size();
    }
  
private:
    string bfsGetShapeHash(vector<vector<int>>& grid,
                          vector<vector<bool>>& visited,
                          int startRow, int startCol) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        vector<pair<int, int>> coordinates;
      
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;
      
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
      
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
          
            coordinates.push_back({row, col});
          
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
              
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
      
        // Normalize coordinates and create hash
        return normalizeAndHash(coordinates);
    }
  
    string normalizeAndHash(vector<pair<int, int>>& coordinates) {
        if (coordinates.empty()) return "";
      
        // Find minimum row and column for normalization
        int minRow = coordinates[0].first;
        int minCol = coordinates[0].second;
      
        for (auto [row, col] : coordinates) {
            minRow = min(minRow, row);
            minCol = min(minCol, col);
        }
      
        // Normalize and sort
        vector<pair<int, int>> normalized;
        for (auto [row, col] : coordinates) {
            normalized.push_back({row - minRow, col - minCol});
        }
      
        sort(normalized.begin(), normalized.end());
      
        // Create string representation
        string hash = "";
        for (auto [row, col] : normalized) {
            hash += to_string(row) + "," + to_string(col) + ";";
        }
      
        return hash;
    }
};
```

### Time Complexity

- **All approaches**: O(m × n) where m and n are grid dimensions
- **Sorting overhead**: O(k log k) per island where k is island size
- **Overall**: O(m × n + total_cells × log(max_island_size))

### Space Complexity

- **BFS/DFS**: O(m × n) for visited array and queue/stack
- **Shape storage**: O(total_land_cells) for storing all island shapes
- **Set operations**: Depends on number and size of unique islands

## Examples

### Example 1

```
Input: grid = [[1,1,0,0,0],
               [1,1,0,0,0],
               [0,0,0,1,1],
               [0,0,0,1,1]]
Output: 1
Explanation: Both islands have the same shape (2×2 rectangle).
```

### Example 2

```
Input: grid = [[1,1,0,1,1],
               [1,0,0,0,1],
               [0,0,0,0,0],
               [1,1,0,1,1]]
Output: 3
Explanation: Three different island shapes.
```

### Example 3

```
Input: grid = [[1,1,1],
               [0,1,0],
               [0,1,0]]
Output: 1
Explanation: Only one island shape (T-shape).
```

## Key Insights

### Queue Pattern Usage

- **Connected component traversal**: BFS explores each island completely
- **Systematic exploration**: Level-order traversal ensures consistent shape recording
- **Coordinate collection**: Queue helps gather all island coordinates efficiently

### Shape Representation Challenges

1. **Translation invariance**: Islands at different positions should be considered same
2. **Consistent ordering**: Need deterministic way to represent same shapes
3. **Efficient comparison**: Use sets or hashes for quick shape matching

### Optimization Techniques

- **Early termination**: Skip already visited cells
- **Coordinate normalization**: Translate all shapes to origin
- **Path encoding**: Record traversal path instead of coordinates
- **Sorting**: Ensure consistent representation of same shapes

## Related Problems

- Number of Islands
- Max Area of Island
- Number of Distinct Islands II (with rotations/reflections)
  Output:
  Explanation:
