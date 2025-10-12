# Making a Large Island

## Problem Description
You are given an `n x n` binary matrix `grid`. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in `grid` after applying this operation.

An island is a 4-directionally connected group of 1s.

## Approach
The brute force approach (flip each 0 and calculate island size) would be O(n⁴). We can optimize this using a two-pass approach:

1. **First pass**: Use BFS/DFS to find all existing islands and assign unique IDs
2. **Second pass**: For each 0, check which islands it would connect and calculate total size

**Key optimization**: Precompute island sizes and IDs, then for each 0, sum up the sizes of adjacent unique islands.

## Algorithm Steps
1. **Find all islands**: Use BFS to identify and label each island with unique ID
2. **Store island sizes**: Map each island ID to its size
3. **For each 0 cell**: Check adjacent islands and calculate potential merged size
4. **Handle edge cases**: Grid with all 1s or all 0s
5. **Return maximum**: Consider both existing islands and potential new ones

## Implementation

### Approach 1: BFS with Island Labeling
```cpp
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int islandId = 2;  // Start from 2 (0 and 1 are used)
        unordered_map<int, int> islandSizes;
        
        // First pass: Label all islands and calculate their sizes
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int size = bfsLabelIsland(grid, i, j, islandId);
                    islandSizes[islandId] = size;
                    islandId++;
                }
            }
        }
        
        // Handle case where grid is all 1s
        if (islandSizes.empty()) {
            return 1;  // We can change one 0 to 1
        }
        
        int maxSize = 0;
        
        // Get current maximum island size
        for (auto& [id, size] : islandSizes) {
            maxSize = max(maxSize, size);
        }
        
        // Second pass: Try flipping each 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int newSize = calculateMergedSize(grid, i, j, islandSizes);
                    maxSize = max(maxSize, newSize);
                }
            }
        }
        
        return maxSize;
    }
    
private:
    int bfsLabelIsland(vector<vector<int>>& grid, int startRow, int startCol, int id) {
        int n = grid.size();
        queue<pair<int, int>> q;
        
        q.push({startRow, startCol});
        grid[startRow][startCol] = id;
        int size = 1;
        
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 1) {
                    grid[newRow][newCol] = id;
                    q.push({newRow, newCol});
                    size++;
                }
            }
        }
        
        return size;
    }
    
    int calculateMergedSize(vector<vector<int>>& grid, int row, int col,
                           unordered_map<int, int>& islandSizes) {
        int n = grid.size();
        unordered_set<int> adjacentIslands;
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Find all unique adjacent islands
        for (auto [dr, dc] : directions) {
            int newRow = row + dr;
            int newCol = col + dc;
            
            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&
                grid[newRow][newCol] > 1) {  // It's an island (ID > 1)
                adjacentIslands.insert(grid[newRow][newCol]);
            }
        }
        
        // Calculate total size if we flip this 0 to 1
        int totalSize = 1;  // The flipped cell itself
        for (int islandId : adjacentIslands) {
            totalSize += islandSizes[islandId];
        }
        
        return totalSize;
    }
};
```

### Approach 2: DFS with Island Labeling
```cpp
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int islandId = 2;
        unordered_map<int, int> islandSizes;
        
        // Label all islands using DFS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int size = dfsLabelIsland(grid, i, j, islandId);
                    islandSizes[islandId] = size;
                    islandId++;
                }
            }
        }
        
        if (islandSizes.empty()) {
            return 1;
        }
        
        int maxSize = 0;
        for (auto& [id, size] : islandSizes) {
            maxSize = max(maxSize, size);
        }
        
        // Try flipping each 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> neighbors;
                    getNeighborIslands(grid, i, j, neighbors);
                    
                    int newSize = 1;
                    for (int neighborId : neighbors) {
                        newSize += islandSizes[neighborId];
                    }
                    
                    maxSize = max(maxSize, newSize);
                }
            }
        }
        
        return maxSize;
    }
    
private:
    int dfsLabelIsland(vector<vector<int>>& grid, int row, int col, int id) {
        int n = grid.size();
        
        if (row < 0 || row >= n || col < 0 || col >= n || grid[row][col] != 1) {
            return 0;
        }
        
        grid[row][col] = id;
        
        return 1 + dfsLabelIsland(grid, row - 1, col, id) +
                   dfsLabelIsland(grid, row + 1, col, id) +
                   dfsLabelIsland(grid, row, col - 1, id) +
                   dfsLabelIsland(grid, row, col + 1, id);
    }
    
    void getNeighborIslands(vector<vector<int>>& grid, int row, int col,
                           unordered_set<int>& neighbors) {
        int n = grid.size();
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (auto [dr, dc] : directions) {
            int newRow = row + dr;
            int newCol = col + dc;
            
            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n &&
                grid[newRow][newCol] > 1) {
                neighbors.insert(grid[newRow][newCol]);
            }
        }
    }
};
```

### Approach 3: Union-Find Solution
```cpp
class UnionFind {
public:
    vector<int> parent, size;
    int maxSize;
    
    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        maxSize = 1;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        
        if (size[px] < size[py]) swap(px, py);
        parent[py] = px;
        size[px] += size[py];
        maxSize = max(maxSize, size[px]);
    }
    
    int getSize(int x) {
        return size[find(x)];
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        UnionFind uf(n * n);
        
        // Connect all existing islands
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    // Connect with right neighbor
                    if (j + 1 < n && grid[i][j + 1] == 1) {
                        uf.unite(i * n + j, i * n + (j + 1));
                    }
                    // Connect with bottom neighbor
                    if (i + 1 < n && grid[i + 1][j] == 1) {
                        uf.unite(i * n + j, (i + 1) * n + j);
                    }
                }
            }
        }
        
        int result = uf.maxSize;
        
        // Try flipping each 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> components;
                    int newSize = 1;  // The flipped cell
                    
                    // Check all 4 neighbors
                    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    for (auto [dr, dc] : directions) {
                        int nr = i + dr, nc = j + dc;
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                            int component = uf.find(nr * n + nc);
                            if (components.find(component) == components.end()) {
                                components.insert(component);
                                newSize += uf.getSize(nr * n + nc);
                            }
                        }
                    }
                    
                    result = max(result, newSize);
                }
            }
        }
        
        return result;
    }
};
```

### Time Complexity
- **BFS/DFS approaches**: O(n²) for labeling + O(n²) for checking = O(n²)
- **Union-Find approach**: O(n² × α(n²)) ≈ O(n²) where α is inverse Ackermann

### Space Complexity
- **All approaches**: O(n²) for auxiliary data structures

## Examples

### Example 1
```cpp
Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect the two 1s, then we get an island with area = 3.
```

### Example 2
```cpp
Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
```

### Example 3
```cpp
Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
```

## Key Insights

### Queue Pattern Usage
- **Island identification**: BFS efficiently explores connected components
- **Labeling strategy**: Assign unique IDs to distinguish different islands
- **Size precomputation**: Cache island sizes to avoid recalculation

### Problem Strategy
1. **Two-phase approach**: First identify islands, then try connections
2. **Unique labeling**: Use IDs > 1 to distinguish from original 0s and 1s
3. **Adjacent island tracking**: Use sets to avoid double-counting merged islands

### Optimization Techniques
- **Avoid brute force**: Don't recalculate island sizes for each flip
- **Set-based deduplication**: Ensure each adjacent island counted once
- **Early termination**: Track maximum as we go

## Related Problems
- Number of Islands
- Max Area of Island
- Number of Distinct Islands
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
