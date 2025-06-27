# Cut Off Trees for Golf Event - Advanced Matrix-Grid BFS
## LeetCode Problem 675

**Difficulty:** Hard  
**Category:** Matrix-Grid BFS, Pathfinding  
**Pattern:** Multi-destination BFS with sorted target processing

## Problem Description

You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an `m x n` matrix. In this matrix:

- `0` means the cell cannot be walked through.
- `1` means an empty cell that can be walked through.
- A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.

In one step, you can walk in any of the four directions: up, down, left, or right. If you are standing in a cell with a tree, you can decide whether to cut it off.

You must cut off the trees in order of their heights - always cut the shortest trees first. The height of the trees that you cut off will be added to your answer. You start from the point `(0, 0)` and return the minimum steps to cut off all the trees. If you cannot cut off all the trees, return `-1`.

**Key Constraints:**
- Must cut trees in ascending height order
- Can only move in 4 directions (up, down, left, right)
- Cannot walk through obstacles (0 cells)
- Must find minimum path between consecutive tree locations

## Real-World Applications

1. **Resource Harvesting**: Optimizing collection routes in mining/forestry
2. **Facility Maintenance**: Scheduled equipment servicing with travel optimization
3. **Delivery Planning**: Package delivery with priority constraints
4. **Emergency Response**: Multi-site response with priority ordering
5. **Game Development**: Resource gathering mechanics in strategy games

## Core Algorithm Approaches

### Approach 1: BFS + Sorted Tree Processing (Optimal)

Combine sorting with BFS for shortest path between targets:

```cpp
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest.empty() || forest[0].empty()) return -1;
        
        int m = forest.size(), n = forest[0].size();
        
        // Collect all trees and sort by height
        vector<array<int, 3>> trees; // {height, row, col}
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }
        
        sort(trees.begin(), trees.end());
        
        int totalSteps = 0;
        int startR = 0, startC = 0;
        
        // Visit each tree in height order
        for (auto& tree : trees) {
            int targetR = tree[1], targetC = tree[2];
            
            int steps = bfsShortestPath(forest, startR, startC, targetR, targetC);
            if (steps == -1) return -1;
            
            totalSteps += steps;
            startR = targetR;
            startC = targetC;
        }
        
        return totalSteps;
    }
    
private:
    int bfsShortestPath(vector<vector<int>>& forest, int startR, int startC, 
                       int targetR, int targetC) {
        if (startR == targetR && startC == targetC) return 0;
        
        int m = forest.size(), n = forest[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        
        q.push({startR, startC});
        visited[startR][startC] = true;
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                        !visited[nr][nc] && forest[nr][nc] != 0) {
                        
                        if (nr == targetR && nc == targetC) {
                            return steps;
                        }
                        
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        return -1; // Cannot reach target
    }
};
```

**Time Complexity:** O(k × m × n) where k is number of trees  
**Space Complexity:** O(m × n) for visited array

### Approach 2: A* Search Optimization

Enhanced pathfinding with heuristic guidance:

```cpp
#include <queue>
#include <unordered_set>

class AStarSolution {
private:
    struct Node {
        int r, c, f, g, h;
        
        Node(int row, int col, int cost, int heuristic) 
            : r(row), c(col), g(cost), h(heuristic), f(cost + heuristic) {}
        
        bool operator>(const Node& other) const {
            return f > other.f;
        }
    };
    
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest.empty() || forest[0].empty()) return -1;
        
        int m = forest.size(), n = forest[0].size();
        
        // Collect and sort trees
        vector<array<int, 3>> trees;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }
        
        sort(trees.begin(), trees.end());
        
        int totalSteps = 0;
        int startR = 0, startC = 0;
        
        for (auto& tree : trees) {
            int targetR = tree[1], targetC = tree[2];
            
            int steps = aStarSearch(forest, startR, startC, targetR, targetC);
            if (steps == -1) return -1;
            
            totalSteps += steps;
            startR = targetR;
            startC = targetC;
        }
        
        return totalSteps;
    }
    
private:
    int aStarSearch(vector<vector<int>>& forest, int startR, int startC,
                   int targetR, int targetC) {
        if (startR == targetR && startC == targetC) return 0;
        
        int m = forest.size(), n = forest[0].size();
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        unordered_set<string> visited;
        
        int h = manhattanDistance(startR, startC, targetR, targetC);
        pq.push(Node(startR, startC, 0, h));
        visited.insert(to_string(startR) + "," + to_string(startC));
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            if (current.r == targetR && current.c == targetC) {
                return current.g;
            }
            
            for (auto& dir : directions) {
                int nr = current.r + dir[0];
                int nc = current.c + dir[1];
                string key = to_string(nr) + "," + to_string(nc);
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                    forest[nr][nc] != 0 && visited.find(key) == visited.end()) {
                    
                    visited.insert(key);
                    int g = current.g + 1;
                    int h = manhattanDistance(nr, nc, targetR, targetC);
                    pq.push(Node(nr, nc, g, h));
                }
            }
        }
        
        return -1;
    }
    
    int manhattanDistance(int r1, int c1, int r2, int c2) {
        return abs(r1 - r2) + abs(c1 - c2);
    }
};
```

### Approach 3: Bidirectional BFS

Optimize pathfinding with bidirectional search:

```cpp
class BidirectionalBFSSolution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest.empty() || forest[0].empty()) return -1;
        
        int m = forest.size(), n = forest[0].size();
        
        // Collect and sort trees
        vector<array<int, 3>> trees;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }
        
        sort(trees.begin(), trees.end());
        
        int totalSteps = 0;
        int startR = 0, startC = 0;
        
        for (auto& tree : trees) {
            int targetR = tree[1], targetC = tree[2];
            
            int steps = bidirectionalBFS(forest, startR, startC, targetR, targetC);
            if (steps == -1) return -1;
            
            totalSteps += steps;
            startR = targetR;
            startC = targetC;
        }
        
        return totalSteps;
    }
    
private:
    int bidirectionalBFS(vector<vector<int>>& forest, int startR, int startC,
                        int targetR, int targetC) {
        if (startR == targetR && startC == targetC) return 0;
        
        int m = forest.size(), n = forest[0].size();
        vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        unordered_set<string> visitedFromStart, visitedFromTarget;
        queue<pair<int, int>> qStart, qTarget;
        
        qStart.push({startR, startC});
        qTarget.push({targetR, targetC});
        visitedFromStart.insert(to_string(startR) + "," + to_string(startC));
        visitedFromTarget.insert(to_string(targetR) + "," + to_string(targetC));
        
        int steps = 0;
        
        while (!qStart.empty() && !qTarget.empty()) {
            steps++;
            
            // Expand from the smaller frontier
            if (qStart.size() <= qTarget.size()) {
                if (expandLevel(forest, qStart, visitedFromStart, visitedFromTarget, directions)) {
                    return steps;
                }
            } else {
                if (expandLevel(forest, qTarget, visitedFromTarget, visitedFromStart, directions)) {
                    return steps;
                }
            }
        }
        
        return -1;
    }
    
    bool expandLevel(vector<vector<int>>& forest, queue<pair<int, int>>& q,
                    unordered_set<string>& visited, unordered_set<string>& otherVisited,
                    vector<vector<int>>& directions) {
        int size = q.size();
        int m = forest.size(), n = forest[0].size();
        
        for (int i = 0; i < size; i++) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto& dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                string key = to_string(nr) + "," + to_string(nc);
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                    forest[nr][nc] != 0 && visited.find(key) == visited.end()) {
                    
                    if (otherVisited.find(key) != otherVisited.end()) {
                        return true; // Paths meet
                    }
                    
                    visited.insert(key);
                    q.push({nr, nc});
                }
            }
        }
        
        return false;
    }
};
```

## Detailed Algorithm Analysis

### Problem Decomposition

1. **Tree Collection**: Gather all tree positions and heights
2. **Sorting**: Order trees by height for processing sequence
3. **Pathfinding**: Find shortest path between consecutive targets
4. **Accumulation**: Sum all path lengths for total steps

### Key Insights

- **Greedy Strategy**: Always cut shortest tree first (problem constraint)
- **Independent Subproblems**: Each path finding is independent
- **Graph Connectivity**: Must verify all trees are reachable
- **Optimization Opportunities**: Pathfinding algorithm choice matters

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|--------|
| BFS | O(k × m × n) | O(m × n) | Simple and reliable |
| A* Search | O(k × m × n × log(m×n)) | O(m × n) | Better average case |
| Bidirectional BFS | O(k × m × n) | O(m × n) | Faster for long paths |

## Test Cases and Examples

### Example 1: Basic Forest
```cpp
void testBasicForest() {
    Solution sol;
    vector<vector<int>> forest = {
        {1, 2, 3},
        {0, 0, 4},
        {7, 6, 5}
    };
    
    int result = sol.cutOffTree(forest);
    // Expected: 6
    // Path: (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (2,1) -> (2,0)
    cout << "Result: " << result << endl;
}
```

### Example 2: Impossible Case
```cpp
void testImpossibleCase() {
    Solution sol;
    vector<vector<int>> forest = {
        {1, 2, 3},
        {0, 0, 0},
        {7, 6, 5}
    };
    
    int result = sol.cutOffTree(forest);
    // Expected: -1 (cannot reach trees in bottom row)
    cout << "Result: " << result << endl;
}
```

### Example 3: Single Tree
```cpp
void testSingleTree() {
    Solution sol;
    vector<vector<int>> forest = {{2}};
    
    int result = sol.cutOffTree(forest);
    // Expected: 0 (already at tree location)
    cout << "Result: " << result << endl;
}
```

## Performance Optimization Techniques

### Preprocessing Optimization
```cpp
class OptimizedSolution {
private:
    vector<vector<int>> dist;
    vector<array<int, 3>> trees;
    
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest.empty() || forest[0].empty()) return -1;
        
        // Collect trees
        collectTrees(forest);
        
        // Precompute distances between important points
        if (!precomputeDistances(forest)) return -1;
        
        // Calculate minimum path
        return calculateMinimumPath();
    }
    
private:
    void collectTrees(vector<vector<int>>& forest) {
        trees.clear();
        trees.push_back({0, 0, 0}); // Starting position
        
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest[0].size(); j++) {
                if (forest[i][j] > 1) {
                    trees.push_back({forest[i][j], i, j});
                }
            }
        }
        
        sort(trees.begin() + 1, trees.end()); // Don't sort starting position
    }
    
    bool precomputeDistances(vector<vector<int>>& forest) {
        int n = trees.size();
        dist.assign(n, vector<int>(n, -1));
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int d = bfsDistance(forest, trees[i][1], trees[i][2], 
                                  trees[j][1], trees[j][2]);
                if (d == -1) return false;
                dist[i][j] = dist[j][i] = d;
            }
            dist[i][i] = 0;
        }
        
        return true;
    }
    
    int calculateMinimumPath() {
        int totalSteps = 0;
        
        for (int i = 1; i < trees.size(); i++) {
            totalSteps += dist[i-1][i];
        }
        
        return totalSteps;
    }
};
```

### Memory-Efficient BFS
```cpp
class MemoryOptimizedBFS {
public:
    int bfsShortestPath(vector<vector<int>>& forest, int startR, int startC,
                       int targetR, int targetC) {
        if (startR == targetR && startC == targetC) return 0;
        
        int m = forest.size(), n = forest[0].size();
        vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        
        // Use bitset for memory efficiency with large grids
        vector<bitset<1000>> visited(m); // Assuming max 1000 columns
        queue<pair<int, int>> q;
        
        q.push({startR, startC});
        visited[startR][startC] = 1;
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                auto [r, c] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                        !visited[nr][nc] && forest[nr][nc] != 0) {
                        
                        if (nr == targetR && nc == targetC) {
                            return steps;
                        }
                        
                        visited[nr][nc] = 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        return -1;
    }
};
```

## Advanced Features and Extensions

### Visualization Support
```cpp
class ForestVisualizer {
public:
    void visualizeForest(vector<vector<int>>& forest, 
                        const vector<array<int, 3>>& trees) {
        cout << "Forest Layout:" << endl;
        
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest[0].size(); j++) {
                if (forest[i][j] == 0) {
                    cout << "  X  ";
                } else if (forest[i][j] == 1) {
                    cout << "  .  ";
                } else {
                    cout << setw(3) << forest[i][j] << "  ";
                }
            }
            cout << endl;
        }
        
        cout << "\nTree cutting order:" << endl;
        for (int i = 0; i < trees.size(); i++) {
            cout << "Tree " << (i+1) << ": Height " << trees[i][0] 
                 << " at (" << trees[i][1] << ", " << trees[i][2] << ")" << endl;
        }
    }
    
    void visualizePath(vector<vector<int>>& forest, 
                      vector<pair<int, int>>& path) {
        vector<vector<char>> display(forest.size(), 
                                   vector<char>(forest[0].size(), '.'));
        
        for (int i = 0; i < forest.size(); i++) {
            for (int j = 0; j < forest[0].size(); j++) {
                if (forest[i][j] == 0) display[i][j] = 'X';
                else if (forest[i][j] > 1) display[i][j] = 'T';
            }
        }
        
        for (int i = 0; i < path.size(); i++) {
            int r = path[i].first, c = path[i].second;
            if (i == 0) display[r][c] = 'S';
            else if (i == path.size() - 1) display[r][c] = 'E';
            else display[r][c] = '*';
        }
        
        for (auto& row : display) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **No Trees**: Empty forest or only obstacles
2. **Unreachable Trees**: Trees separated by obstacles
3. **Single Cell**: 1x1 grid with various contents
4. **Large Sparse Grid**: Efficiency with mostly empty spaces
5. **Tree at Start**: Starting position has a tree

### Implementation Considerations
- **Memory Usage**: Large grids require efficient visited tracking
- **Path Reconstruction**: Optional for debugging/visualization
- **Early Termination**: Stop if any tree is unreachable
- **Coordinate Validation**: Bounds checking in all directions

## Pattern Recognition: Matrix-Grid BFS

This problem demonstrates **Matrix-Grid BFS** through:

1. **Multi-Target BFS**: Sequentially finding paths to multiple destinations
2. **Constraint-Based Processing**: Tree height ordering requirement
3. **Connectivity Analysis**: Ensuring all targets are reachable
4. **Optimization Opportunities**: Algorithm choice affects performance

### Related Matrix-Grid BFS Problems
- **Shortest Bridge** (LeetCode 934): Find minimum bridge between islands
- **As Far from Land as Possible** (LeetCode 1162): Multi-source BFS
- **Escape a Large Maze** (LeetCode 1036): Large grid pathfinding

## Mathematical Properties

### Theoretical Bounds
- **Lower Bound**: Ω(k × (m + n)) where k is number of trees
- **Upper Bound**: O(k × m × n) for BFS approach
- **Optimal Substructure**: Each shortest path is independent

### Graph Theory Connections
- **Metric Space**: Triangle inequality holds for shortest paths
- **Reachability**: Connected component analysis
- **Path Optimization**: Various shortest path algorithms applicable

## Related LeetCode Problems

1. **[LeetCode 864] Shortest Path to Get All Keys** - Similar multi-target BFS
2. **[LeetCode 787] Cheapest Flights Within K Stops** - Constrained pathfinding
3. **[LeetCode 1293] Shortest Path in Grid with Obstacles Elimination** - Modified BFS
4. **[LeetCode 317] Shortest Distance from All Buildings** - Multi-source optimization

## Summary

The Cut Off Trees for Golf Event problem showcases advanced Matrix-Grid BFS concepts:

- **Multi-Stage Pathfinding**: Sequential shortest path computation
- **Constraint Integration**: Ordering requirements affect algorithm design
- **Performance Optimization**: Choice of pathfinding algorithm matters
- **Real-World Modeling**: Resource collection with scheduling constraints

Key takeaways for competitive programming:
- **Algorithm Selection**: Choose pathfinding method based on grid characteristics
- **Early Termination**: Detect impossible cases quickly
- **Memory Efficiency**: Important for large grids
- **Preprocessing**: Can improve performance for multiple queries

This problem pattern appears in logistics, game development, and resource management scenarios, making it valuable for both algorithmic competitions and practical applications.
