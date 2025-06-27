# Minimum Knight Moves - Optimized Matrix-Grid BFS
## LeetCode Problem 1197

**Difficulty:** Medium  
**Category:** Matrix-Grid BFS, Chess Algorithms  
**Pattern:** Infinite grid pathfinding with symmetry optimization

## Problem Description

In an **infinite** chessboard with coordinates from `-infinity` to `+infinity`, you have a **knight** at square `[0, 0]`.

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

Return the minimum number of steps needed to move the knight to the square `[x, y]`. It is guaranteed that the answer exists.

**Knight Movement Pattern:**
- (±2, ±1) and (±1, ±2) in all combinations
- Total of 8 possible moves from any position

**Key Challenges:**
- Infinite grid requires careful boundary management
- Large coordinates need optimization techniques
- Symmetry can be exploited to reduce search space

## Real-World Applications

1. **Game Development**: Pathfinding for chess-like games
2. **Robotics**: Movement planning with specific constraints
3. **Network Routing**: Multi-hop communication patterns
4. **Puzzle Solving**: Chess puzzle optimization
5. **AI Planning**: State space search with complex moves

## Core Algorithm Approaches

### Approach 1: Standard BFS with Coordinate Mapping

Direct BFS with careful coordinate handling:

```cpp
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
private:
    vector<pair<int, int>> moves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
public:
    int minKnightMoves(int x, int y) {
        // Handle origin case
        if (x == 0 && y == 0) return 0;
        
        queue<pair<int, int>> q;
        unordered_set<string> visited;
        
        q.push({0, 0});
        visited.insert("0,0");
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                auto [currX, currY] = q.front();
                q.pop();
                
                for (auto [dx, dy] : moves) {
                    int newX = currX + dx;
                    int newY = currY + dy;
                    
                    if (newX == x && newY == y) {
                        return steps;
                    }
                    
                    string key = to_string(newX) + "," + to_string(newY);
                    if (visited.find(key) == visited.end()) {
                        // Pruning: limit search to reasonable bounds
                        if (abs(newX) <= 300 && abs(newY) <= 300) {
                            visited.insert(key);
                            q.push({newX, newY});
                        }
                    }
                }
            }
        }
        
        return -1; // Should never reach here for valid inputs
    }
};
```

**Time Complexity:** O(max(|x|, |y|)²)  
**Space Complexity:** O(max(|x|, |y|)²)

### Approach 2: Symmetry Optimization

Exploit coordinate symmetry to reduce search space:

```cpp
class OptimizedSolution {
private:
    vector<pair<int, int>> moves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
public:
    int minKnightMoves(int x, int y) {
        // Use symmetry: work only in first quadrant
        x = abs(x);
        y = abs(y);
        
        // Handle special cases
        if (x == 0 && y == 0) return 0;
        if (x == 1 && y == 1) return 2;
        
        queue<pair<int, int>> q;
        unordered_set<string> visited;
        
        q.push({0, 0});
        visited.insert("0,0");
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                auto [currX, currY] = q.front();
                q.pop();
                
                for (auto [dx, dy] : moves) {
                    int newX = currX + dx;
                    int newY = currY + dy;
                    
                    if (newX == x && newY == y) {
                        return steps;
                    }
                    
                    string key = to_string(newX) + "," + to_string(newY);
                    if (visited.find(key) == visited.end()) {
                        // Smart pruning: only explore promising directions
                        if (newX >= -2 && newY >= -2 && 
                            newX <= x + 2 && newY <= y + 2) {
                            visited.insert(key);
                            q.push({newX, newY});
                        }
                    }
                }
            }
        }
        
        return -1;
    }
};
```

### Approach 3: Bidirectional BFS

Meet-in-the-middle search for large coordinates:

```cpp
class BidirectionalSolution {
public:
    int minKnightMoves(int x, int y) {
        if (x == 0 && y == 0) return 0;
        
        // Use symmetry
        x = abs(x);
        y = abs(y);
        
        unordered_set<string> visitedFromStart, visitedFromEnd;
        queue<pair<int, int>> qStart, qEnd;
        
        qStart.push({0, 0});
        qEnd.push({x, y});
        visitedFromStart.insert("0,0");
        visitedFromEnd.insert(to_string(x) + "," + to_string(y));
        
        int steps = 0;
        vector<pair<int, int>> moves = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        while (!qStart.empty() && !qEnd.empty()) {
            steps++;
            
            // Expand from smaller frontier
            if (qStart.size() <= qEnd.size()) {
                if (expandLevel(qStart, visitedFromStart, visitedFromEnd, moves, x, y)) {
                    return steps;
                }
            } else {
                if (expandLevel(qEnd, visitedFromEnd, visitedFromStart, moves, x, y)) {
                    return steps;
                }
            }
        }
        
        return -1;
    }
    
private:
    bool expandLevel(queue<pair<int, int>>& q, unordered_set<string>& visited,
                    unordered_set<string>& otherVisited,
                    vector<pair<int, int>>& moves, int targetX, int targetY) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            auto [currX, currY] = q.front();
            q.pop();
            
            for (auto [dx, dy] : moves) {
                int newX = currX + dx;
                int newY = currY + dy;
                
                string key = to_string(newX) + "," + to_string(newY);
                
                if (otherVisited.find(key) != otherVisited.end()) {
                    return true; // Paths meet
                }
                
                if (visited.find(key) == visited.end()) {
                    // Reasonable bounds checking
                    if (newX >= -2 && newY >= -2 && 
                        newX <= targetX + 2 && newY <= targetY + 2) {
                        visited.insert(key);
                        q.push({newX, newY});
                    }
                }
            }
        }
        
        return false;
    }
};
```

### Approach 4: Mathematical Formula (Advanced)

Direct calculation using mathematical insights:

```cpp
class MathematicalSolution {
public:
    int minKnightMoves(int x, int y) {
        x = abs(x);
        y = abs(y);
        
        // Ensure x >= y for calculation
        if (x < y) swap(x, y);
        
        // Special cases
        if (x == 0 && y == 0) return 0;
        if (x == 1 && y == 1) return 2;
        if (x == 2 && y == 2) return 4;
        
        // For large coordinates, use mathematical approximation
        if (x >= 2 * y) {
            // Linear region: mostly horizontal moves
            int t = max(0, (x + 1) / 2 - 2);
            return t + (x - 2 * t + 1) / 2 * 2 + (y != 0 ? 1 : 0);
        } else {
            // Diagonal region: optimal path is roughly diagonal
            int delta = x + y;
            return (delta + 2) / 3 + (delta % 3 == 1 ? 1 : 0);
        }
    }
};
```

## Detailed Algorithm Analysis

### Problem Characteristics

1. **Infinite Grid**: No boundary constraints, but pruning is essential
2. **8-Direction Movement**: Complex movement pattern vs standard 4-direction
3. **Shortest Path**: BFS guarantees minimum steps
4. **Symmetry**: Problem has 8-fold rotational/reflection symmetry

### Optimization Strategies

- **Coordinate Transformation**: Use abs() to work in first quadrant only
- **Intelligent Pruning**: Limit search to reasonable coordinate bounds
- **Bidirectional Search**: Meet-in-the-middle for large distances
- **Mathematical Bounds**: Theoretical minimum/maximum step estimates

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|--------|
| Standard BFS | O(max(x,y)²) | O(max(x,y)²) | Simple but potentially slow |
| Symmetry Opt. | O(max(x,y)²) | O(max(x,y)²) | 8x faster due to symmetry |
| Bidirectional | O(max(x,y)) | O(max(x,y)) | Best for large coordinates |
| Mathematical | O(1) | O(1) | Fastest but complex |

## Test Cases and Examples

### Example 1: Basic Movement
```cpp
void testBasicMovement() {
    Solution sol;
    
    // Simple cases
    cout << "To (2,1): " << sol.minKnightMoves(2, 1) << endl;  // Expected: 1
    cout << "To (5,5): " << sol.minKnightMoves(5, 5) << endl;  // Expected: 4
    cout << "To (0,0): " << sol.minKnightMoves(0, 0) << endl;  // Expected: 0
}
```

### Example 2: Negative Coordinates
```cpp
void testNegativeCoordinates() {
    Solution sol;
    
    // Test symmetry handling
    cout << "To (-1,-1): " << sol.minKnightMoves(-1, -1) << endl;  // Expected: 2
    cout << "To (-5,5): " << sol.minKnightMoves(-5, 5) << endl;    // Expected: 4
    cout << "To (5,-5): " << sol.minKnightMoves(5, -5) << endl;    // Expected: 4
}
```

### Example 3: Large Coordinates
```cpp
void testLargeCoordinates() {
    BidirectionalSolution sol;
    
    // Performance test
    auto start = chrono::high_resolution_clock::now();
    int result = sol.minKnightMoves(100, 100);
    auto end = chrono::high_resolution_clock::now();
    
    cout << "To (100,100): " << result << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << " ms" << endl;
}
```

## Advanced Optimizations and Features

### Memoization for Multiple Queries
```cpp
class MemoizedSolution {
private:
    unordered_map<string, int> memo;
    vector<pair<int, int>> moves = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    
public:
    int minKnightMoves(int x, int y) {
        x = abs(x);
        y = abs(y);
        
        string key = to_string(x) + "," + to_string(y);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int result = bfsWithMemo(x, y);
        memo[key] = result;
        return result;
    }
    
private:
    int bfsWithMemo(int targetX, int targetY) {
        if (targetX == 0 && targetY == 0) return 0;
        
        queue<pair<int, int>> q;
        unordered_set<string> visited;
        
        q.push({0, 0});
        visited.insert("0,0");
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                for (auto [dx, dy] : moves) {
                    int newX = x + dx;
                    int newY = y + dy;
                    
                    if (newX == targetX && newY == targetY) {
                        return steps;
                    }
                    
                    string key = to_string(newX) + "," + to_string(newY);
                    if (visited.find(key) == visited.end() &&
                        newX >= -2 && newY >= -2 && 
                        newX <= targetX + 2 && newY <= targetY + 2) {
                        
                        visited.insert(key);
                        q.push({newX, newY});
                    }
                }
            }
        }
        
        return -1;
    }
};
```

### Path Reconstruction
```cpp
class PathTrackingSolution {
public:
    pair<int, vector<pair<int, int>>> minKnightMovesWithPath(int x, int y) {
        x = abs(x);
        y = abs(y);
        
        if (x == 0 && y == 0) return {0, {{0, 0}}};
        
        queue<pair<int, int>> q;
        unordered_map<string, pair<int, int>> parent;
        unordered_set<string> visited;
        
        q.push({0, 0});
        visited.insert("0,0");
        parent["0,0"] = {-1, -1}; // No parent for starting position
        
        vector<pair<int, int>> moves = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            steps++;
            
            for (int i = 0; i < size; i++) {
                auto [currX, currY] = q.front();
                q.pop();
                
                for (auto [dx, dy] : moves) {
                    int newX = currX + dx;
                    int newY = currY + dy;
                    
                    if (newX == x && newY == y) {
                        // Reconstruct path
                        vector<pair<int, int>> path;
                        path.push_back({x, y});
                        
                        string key = to_string(currX) + "," + to_string(currY);
                        while (parent[key].first != -1) {
                            path.push_back({currX, currY});
                            auto [px, py] = parent[key];
                            currX = px;
                            currY = py;
                            key = to_string(currX) + "," + to_string(currY);
                        }
                        path.push_back({0, 0});
                        
                        reverse(path.begin(), path.end());
                        return {steps, path};
                    }
                    
                    string newKey = to_string(newX) + "," + to_string(newY);
                    if (visited.find(newKey) == visited.end() &&
                        newX >= -2 && newY >= -2 && 
                        newX <= x + 2 && newY <= y + 2) {
                        
                        visited.insert(newKey);
                        parent[newKey] = {currX, currY};
                        q.push({newX, newY});
                    }
                }
            }
        }
        
        return {-1, {}};
    }
};
```

### Visualization Tools
```cpp
class KnightMoveVisualizer {
public:
    void visualizeKnightMoves(int x, int y) {
        PathTrackingSolution sol;
        auto [steps, path] = sol.minKnightMovesWithPath(x, y);
        
        cout << "Knight moves from (0,0) to (" << x << "," << y << ")" << endl;
        cout << "Minimum steps: " << steps << endl << endl;
        
        for (int i = 0; i < path.size(); i++) {
            cout << "Step " << i << ": (" << path[i].first << ", " << path[i].second << ")";
            if (i < path.size() - 1) {
                int dx = path[i+1].first - path[i].first;
                int dy = path[i+1].second - path[i].second;
                cout << " -> Move (" << dx << ", " << dy << ")";
            }
            cout << endl;
        }
    }
    
    void visualizeBoard(const vector<pair<int, int>>& path, int x, int y) {
        // Create a board showing the path
        int minX = min(0, x) - 1;
        int maxX = max(0, x) + 1;
        int minY = min(0, y) - 1;
        int maxY = max(0, y) + 1;
        
        cout << "\nBoard visualization:" << endl;
        
        for (int row = maxY; row >= minY; row--) {
            for (int col = minX; col <= maxX; col++) {
                bool isPath = false;
                int stepNum = -1;
                
                for (int i = 0; i < path.size(); i++) {
                    if (path[i].first == col && path[i].second == row) {
                        isPath = true;
                        stepNum = i;
                        break;
                    }
                }
                
                if (col == 0 && row == 0) {
                    cout << " S ";
                } else if (col == x && row == y) {
                    cout << " E ";
                } else if (isPath) {
                    cout << setw(2) << stepNum << " ";
                } else {
                    cout << " . ";
                }
            }
            cout << endl;
        }
    }
};
```

## Edge Cases and Special Considerations

### Critical Edge Cases
1. **Origin**: (0,0) → 0 steps
2. **Adjacent Diagonal**: (1,1) → 2 steps (cannot reach in 1 step)
3. **Large Coordinates**: (300,300) → performance testing
4. **Negative Coordinates**: (-5,-5) → symmetry verification
5. **One Coordinate Zero**: (5,0) → edge movement patterns

### Mathematical Properties
- **Minimum Steps Formula**: For large coordinates, approximately `(x+y+2)/3`
- **Parity Constraints**: Some positions require specific parity of steps
- **Boundary Effects**: Small coordinates have special cases

## Pattern Recognition: Matrix-Grid BFS

This problem demonstrates **Matrix-Grid BFS** with unique characteristics:

1. **Infinite Grid**: No physical boundaries, requires algorithmic boundaries
2. **Complex Movement**: 8-direction knight moves vs standard 4-direction
3. **Symmetry Exploitation**: Mathematical properties reduce search space
4. **Distance Optimization**: Multiple algorithms depending on coordinate size

### Related Chess Problems
- **N-Queens**: Constraint satisfaction on chessboard
- **Knight's Tour**: Visit all squares exactly once
- **Bishop/Rook Paths**: Different movement patterns

## Performance Benchmarking

```cpp
class PerformanceBenchmark {
public:
    void compareApproaches() {
        vector<pair<int, int>> testCases = {
            {1, 1}, {5, 5}, {10, 10}, {50, 50}, {100, 100}
        };
        
        cout << "Performance Comparison:" << endl;
        cout << "Target\t\tBFS\t\tBidirectional\tMath" << endl;
        
        for (auto [x, y] : testCases) {
            cout << "(" << x << "," << y << ")\t\t";
            
            // BFS timing
            auto start = chrono::high_resolution_clock::now();
            OptimizedSolution sol1;
            int result1 = sol1.minKnightMoves(x, y);
            auto end = chrono::high_resolution_clock::now();
            auto time1 = chrono::duration_cast<chrono::microseconds>(end - start);
            
            // Bidirectional timing
            start = chrono::high_resolution_clock::now();
            BidirectionalSolution sol2;
            int result2 = sol2.minKnightMoves(x, y);
            end = chrono::high_resolution_clock::now();
            auto time2 = chrono::duration_cast<chrono::microseconds>(end - start);
            
            cout << time1.count() << "µs\t\t" << time2.count() << "µs" << endl;
        }
    }
};
```

## Related LeetCode Problems

1. **[LeetCode 1336] Number of Days Between Two Dates** - Mathematical calculation
2. **[LeetCode 752] Open the Lock** - BFS with constraints
3. **[LeetCode 773] Sliding Puzzle** - State space search
4. **[LeetCode 934] Shortest Bridge** - Matrix BFS with pathfinding

## Summary

The Minimum Knight Moves problem showcases sophisticated Matrix-Grid BFS techniques:

- **Infinite Grid Handling**: Algorithmic boundary management
- **Symmetry Optimization**: Mathematical properties reduce complexity
- **Multiple Algorithms**: Different approaches for different input sizes
- **Chess Movement**: Complex 8-direction pathfinding

Key algorithmic insights:
- **Coordinate Transformation**: Symmetry reduces problem size by factor of 8
- **Intelligent Pruning**: Essential for infinite grid problems
- **Algorithm Selection**: Choose method based on coordinate magnitude
- **Mathematical Optimization**: Direct formulas beat search for large inputs

This problem pattern appears in game development, robotics, and mathematical optimization, making it valuable for both competitive programming and practical applications involving constrained movement planning.
