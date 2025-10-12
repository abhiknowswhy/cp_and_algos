# As Far From Land as Possible

## Problem Description

Given an n x n grid containing only values 0 and 1, where:
- 0 represents water
- 1 represents land

Find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

**LeetCode Problem:** [1162. As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)

## Approach

Use multi-source BFS starting from all land cells simultaneously. This efficiently computes the minimum distance from each water cell to the nearest land cell in a single pass.

## Algorithm Steps

1. **Initialize**: Add all land cells (value = 1) to the BFS queue
2. **BFS Expansion**: Process queue level by level, visiting water cells
3. **Distance Tracking**: Track the maximum distance encountered during BFS
4. **Return Result**: Return the maximum distance found

## Implementation

### Approach 1: Multi-Source BFS (Optimal)
```cpp
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

class Solution {
public:
    int maxDistance(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::queue<std::pair<int, int>> q;
        
        // Add all land cells to queue and mark water cells as unvisited (-1)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                } else {
                    grid[i][j] = -1;
                }
            }
        }
        
        // If no land or no water, return -1
        if (q.empty() || q.size() == n * n) {
            return -1;
        }
        
        int maxDist = -1;
        std::vector<std::vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
                    grid[newRow][newCol] == -1) {
                    
                    grid[newRow][newCol] = grid[row][col] + 1;
                    maxDist = std::max(maxDist, grid[newRow][newCol]);
                    q.push({newRow, newCol});
                }
            }
        }
        
        return maxDist;
    }
};
```

### Approach 2: BFS with Separate Distance Matrix
```cpp
#include <vector>
#include <queue>
#include <algorithm>

class SolutionSeparateMatrix {
public:
    int maxDistance(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::vector<std::vector<int>> distances(n, std::vector<int>(n, -1));
        std::queue<std::pair<int, int>> q;
        
        // Initialize distances for land cells and add to queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    distances[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        
        if (q.empty() || q.size() == n * n) {
            return -1;
        }
        
        int maxDist = 0;
        std::vector<std::vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
                    distances[newRow][newCol] == -1) {
                    
                    distances[newRow][newCol] = distances[row][col] + 1;
                    maxDist = std::max(maxDist, distances[newRow][newCol]);
                    q.push({newRow, newCol});
                }
            }
        }
        
        return maxDist;
    }
};
```

### Approach 3: Dynamic Programming
```cpp
#include <vector>
#include <algorithm>

class SolutionDP {
public:
    int maxDistance(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, INT_MAX));
        
        // Initialize land cells
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                }
            }
        }
        
        // Forward pass: top-left to bottom-right
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] != 0) {
                    if (i > 0 && dp[i-1][j] != INT_MAX) {
                        dp[i][j] = std::min(dp[i][j], dp[i-1][j] + 1);
                    }
                    if (j > 0 && dp[i][j-1] != INT_MAX) {
                        dp[i][j] = std::min(dp[i][j], dp[i][j-1] + 1);
                    }
                }
            }
        }
        
        // Backward pass: bottom-right to top-left
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (dp[i][j] != 0) {
                    if (i < n - 1 && dp[i+1][j] != INT_MAX) {
                        dp[i][j] = std::min(dp[i][j], dp[i+1][j] + 1);
                    }
                    if (j < n - 1 && dp[i][j+1] != INT_MAX) {
                        dp[i][j] = std::min(dp[i][j], dp[i][j+1] + 1);
                    }
                }
            }
        }
        
        int maxDist = 0;
        bool hasWater = false;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    hasWater = true;
                    maxDist = std::max(maxDist, dp[i][j]);
                }
            }
        }
        
        return hasWater && maxDist != INT_MAX ? maxDist : -1;
    }
};
```

### Approach 4: Optimized BFS with Early Termination
```cpp
#include <vector>
#include <queue>
#include <algorithm>

class SolutionOptimized {
public:
    int maxDistance(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::queue<std::pair<int, int>> q;
        int waterCells = 0;
        
        // Count water cells and add land cells to queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                } else {
                    waterCells++;
                }
            }
        }
        
        // Early return cases
        if (q.empty() || waterCells == 0) {
            return -1;
        }
        
        int distance = 0;
        std::vector<std::vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!q.empty() && waterCells > 0) {
            int size = q.size();
            distance++;
            
            for (int i = 0; i < size; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];
                    
                    if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
                        grid[newRow][newCol] == 0) {
                        
                        grid[newRow][newCol] = 1;
                        waterCells--;
                        q.push({newRow, newCol});
                    }
                }
            }
        }
        
        return distance - 1;
    }
};
```

### Time Complexity
- **Multi-Source BFS**: O(n²) where n is the side length of the grid
- **DP Approach**: O(n²) with two passes over the grid
- **Space**: O(n²) for the queue and grid modifications

### Space Complexity
- **BFS**: O(n²) in worst case for queue storage
- **DP**: O(n²) for distance matrix
- **In-place**: O(1) additional space if modifying input grid is allowed

## Examples

### Example 1: Standard Case
```cpp
void testStandardCase() {
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {1, 0, 1},
        {0, 0, 0},
        {1, 0, 1}
    };
    
    int result = sol.maxDistance(grid);
    assert(result == 2);
    
    std::cout << "Standard case result: " << result << std::endl;
    // The center cell (1,1) has distance 2 from nearest land
}
```

### Example 2: All Land or All Water
```cpp
void testEdgeCases() {
    Solution sol;
    
    // All land
    std::vector<std::vector<int>> allLand = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    assert(sol.maxDistance(allLand) == -1);
    
    // All water
    std::vector<std::vector<int>> allWater = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    assert(sol.maxDistance(allWater) == -1);
    
    std::cout << "Edge cases test passed!" << std::endl;
}
```

## Advanced Features

### Visualization and Animation
```cpp
#include <iostream>
#include <iomanip>

class VisualizationSolution {
private:
    void printGrid(const std::vector<std::vector<int>>& grid, const std::string& title) {
        std::cout << "\n" << title << ":\n";
        for (const auto& row : grid) {
            for (int cell : row) {
                if (cell == -1) {
                    std::cout << std::setw(3) << "~";
                } else {
                    std::cout << std::setw(3) << cell;
                }
            }
            std::cout << "\n";
        }
    }
    
public:
    int maxDistanceWithVisualization(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::queue<std::pair<int, int>> q;
        
        printGrid(grid, "Initial Grid (1=Land, 0=Water)");
        
        // Mark water as unvisited and add land to queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                } else {
                    grid[i][j] = -1;
                }
            }
        }
        
        if (q.empty() || q.size() == n * n) {
            return -1;
        }
        
        int maxDist = -1;
        int level = 0;
        std::vector<std::vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        while (!q.empty()) {
            int size = q.size();
            level++;
            
            for (int i = 0; i < size; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];
                    
                    if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
                        grid[newRow][newCol] == -1) {
                        
                        grid[newRow][newCol] = grid[row][col] + 1;
                        maxDist = std::max(maxDist, grid[newRow][newCol]);
                        q.push({newRow, newCol});
                    }
                }
            }
            
            if (level <= 5) { // Show first few levels
                printGrid(grid, "After BFS Level " + std::to_string(level));
            }
        }
        
        printGrid(grid, "Final Distance Grid");
        return maxDist;
    }
};
```

### Performance Benchmarking
```cpp
#include <chrono>
#include <random>

void benchmarkMaxDistance() {
    const std::vector<int> sizes = {10, 50, 100, 200};
    
    for (int size : sizes) {
        std::vector<std::vector<int>> grid(size, std::vector<int>(size));
        
        // Generate random grid
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                grid[i][j] = dis(gen) < 0.3 ? 1 : 0; // 30% land
            }
        }
        
        Solution sol;
        auto start = std::chrono::high_resolution_clock::now();
        
        int result = sol.maxDistance(grid);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Grid " << size << "x" << size 
                  << ": " << duration.count() << " microseconds"
                  << ", Max Distance: " << result << std::endl;
    }
}
```

### Alternative Distance Metrics
```cpp
class AlternativeMetrics {
public:
    // Chebyshev distance (max of horizontal and vertical distance)
    int maxDistanceChebyshev(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::queue<std::pair<int, int>> q;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                } else {
                    grid[i][j] = -1;
                }
            }
        }
        
        if (q.empty() || q.size() == n * n) {
            return -1;
        }
        
        int maxDist = -1;
        // 8-directional movement for Chebyshev distance
        std::vector<std::vector<int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        };
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
                    grid[newRow][newCol] == -1) {
                    
                    grid[newRow][newCol] = grid[row][col] + 1;
                    maxDist = std::max(maxDist, grid[newRow][newCol]);
                    q.push({newRow, newCol});
                }
            }
        }
        
        return maxDist;
    }
    
    // Euclidean distance approximation
    int maxDistanceEuclidean(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        std::vector<std::vector<double>> distances(n, std::vector<double>(n, DBL_MAX));
        
        // Initialize land cells
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    distances[i][j] = 0.0;
                }
            }
        }
        
        // Compute minimum Euclidean distance for each water cell
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    for (int x = 0; x < n; x++) {
                        for (int y = 0; y < n; y++) {
                            if (grid[x][y] == 1) {
                                double dist = sqrt((i-x)*(i-x) + (j-y)*(j-y));
                                distances[i][j] = std::min(distances[i][j], dist);
                            }
                        }
                    }
                }
            }
        }
        
        double maxDist = 0.0;
        bool hasWater = false;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    hasWater = true;
                    maxDist = std::max(maxDist, distances[i][j]);
                }
            }
        }
        
        return hasWater ? (int)maxDist : -1;
    }
};
```

## Real-World Applications

### 1. Emergency Services Planning
```cpp
class EmergencyServicesPlanner {
private:
    std::vector<std::vector<int>> cityGrid;
    std::vector<std::pair<int, int>> emergencyStations;
    
public:
    EmergencyServicesPlanner(std::vector<std::vector<int>>& grid) : cityGrid(grid) {
        // Find existing emergency stations
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 1) {
                    emergencyStations.push_back({i, j});
                }
            }
        }
    }
    
    std::pair<int, int> findOptimalNewStationLocation() {
        Solution sol;
        auto gridCopy = cityGrid;
        int maxDist = sol.maxDistance(gridCopy);
        
        // Find the cell with maximum distance to nearest station
        for (int i = 0; i < gridCopy.size(); i++) {
            for (int j = 0; j < gridCopy[i].size(); j++) {
                if (gridCopy[i][j] == maxDist) {
                    return {i, j};
                }
            }
        }
        
        return {-1, -1};
    }
    
    int calculateCoverageImprovement(int newRow, int newCol) {
        auto beforeGrid = cityGrid;
        auto afterGrid = cityGrid;
        afterGrid[newRow][newCol] = 1;
        
        Solution sol;
        int beforeMax = sol.maxDistance(beforeGrid);
        int afterMax = sol.maxDistance(afterGrid);
        
        return beforeMax - afterMax;
    }
};
```

### 2. Network Tower Optimization
```cpp
class NetworkTowerOptimizer {
private:
    std::vector<std::vector<int>> coverageMap;
    
public:
    NetworkTowerOptimizer(int rows, int cols) : coverageMap(rows, std::vector<int>(cols, 0)) {}
    
    void addTower(int row, int col) {
        coverageMap[row][col] = 1;
    }
    
    int findWorstCoverageDistance() {
        Solution sol;
        auto gridCopy = coverageMap;
        return sol.maxDistance(gridCopy);
    }
    
    std::vector<std::pair<int, int>> identifyDeadZones(int threshold) {
        std::vector<std::pair<int, int>> deadZones;
        auto gridCopy = coverageMap;
        
        Solution sol;
        sol.maxDistance(gridCopy); // This modifies gridCopy with distances
        
        for (int i = 0; i < gridCopy.size(); i++) {
            for (int j = 0; j < gridCopy[i].size(); j++) {
                if (coverageMap[i][j] == 0 && gridCopy[i][j] > threshold) {
                    deadZones.push_back({i, j});
                }
            }
        }
        
        return deadZones;
    }
};
```

## Notes

- **Multi-Source BFS**: Key insight for efficient solution - start from all sources simultaneously
- **Grid Modification**: Can use input grid to store distances to save space
- **Early Termination**: Can stop BFS when all water cells are visited
- **Manhattan Distance**: Most common distance metric for grid problems
- **Edge Cases**: Handle all-land and all-water scenarios

## Related Problems

- [LeetCode 1162. As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)
- [LeetCode 542. 01 Matrix](https://leetcode.com/problems/01-matrix/)
- [LeetCode 994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [LeetCode 1765. Map of Highest Peak](https://leetcode.com/problems/map-of-highest-peak/)
- [LeetCode 286. Walls and Gates](https://leetcode.com/problems/walls-and-gates/)

## Pattern: 10-Matrix-Grid-BFS

This problem exemplifies the Matrix Grid BFS pattern through:

1. **Multi-Source BFS**: Starting BFS simultaneously from multiple source points (all land cells)
2. **Level-by-Level Processing**: BFS naturally processes cells at distance d before distance d+1
3. **Distance Propagation**: Each BFS level represents cells at the same distance from nearest source
4. **Grid State Management**: Using the grid itself or additional matrix to track visited states and distances

The queue manages the BFS frontier, ensuring that all cells at distance k are processed before any cell at distance k+1, which is essential for finding the maximum distance efficiently.
