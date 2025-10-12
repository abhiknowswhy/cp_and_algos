# Shortest Bridge - Multi-Source BFS

**LeetCode 934: Shortest Bridge**

## Problem Description

You are given an `n x n` binary matrix `grid` where `1` represents land and `0` represents water.

An **island** is a 4-directionally connected group of `1`s. There are exactly two islands in the given grid.

You may change `0`s to `1`s to connect the two islands to form **one island**.

Return the smallest number of `0`s you must flip to connect the two islands.

## Multiple Approaches

### Approach 1: DFS + BFS (Two-Pass)

```cpp
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
private:
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
    void dfs(vector<vector<int>>& grid, int i, int j, queue<pair<int,int>>& q) {
        int n = grid.size();
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1) {
            return;
        }
        
        grid[i][j] = 2; // Mark as visited island 1
        q.push({i, j});
        
        for (auto& dir : directions) {
            dfs(grid, i + dir[0], j + dir[1], q);
        }
    }
    
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;
        
        // Step 1: Find first island using DFS and add to queue
        bool found = false;
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j, q);
                    found = true;
                }
            }
        }
        
        // Step 2: BFS to find shortest path to second island
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                    
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        if (grid[nx][ny] == 1) {
                            return steps; // Found second island
                        }
                        if (grid[nx][ny] == 0) {
                            grid[nx][ny] = 2; // Mark as visited
                            q.push({nx, ny});
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
```

### Approach 2: Union-Find + BFS

```cpp
class UnionFind {
public:
    vector<int> parent, rank;
    
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
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
        
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class SolutionUnionFind {
private:
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
    int getIndex(int i, int j, int n) {
        return i * n + j;
    }
    
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        UnionFind uf(n * n);
        
        // Step 1: Union all land cells to form islands
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    for (auto& dir : directions) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                            uf.unite(getIndex(i, j, n), getIndex(ni, nj, n));
                        }
                    }
                }
            }
        }
        
        // Step 2: Find representatives of two islands
        vector<int> islands;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int root = uf.find(getIndex(i, j, n));
                    if (find(islands.begin(), islands.end(), root) == islands.end()) {
                        islands.push_back(root);
                        if (islands.size() == 2) break;
                    }
                }
            }
            if (islands.size() == 2) break;
        }
        
        // Step 3: BFS from first island to find shortest path to second
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && uf.find(getIndex(i, j, n)) == islands[0]) {
                    q.push({i, j});
                    visited[i][j] = true;
                }
            }
        }
        
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                for (auto& dir : directions) {
                    int nx = x + dir[0], ny = y + dir[1];
                    
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                        if (grid[nx][ny] == 1 && uf.find(getIndex(nx, ny, n)) == islands[1]) {
                            return steps;
                        }
                        if (grid[nx][ny] == 0) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
```

### Approach 3: Bidirectional BFS

```cpp
class SolutionBidirectional {
private:
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
    void findIsland(vector<vector<int>>& grid, int startI, int startJ, 
                   queue<pair<int,int>>& q, int color) {
        int n = grid.size();
        queue<pair<int,int>> dfsQ;
        dfsQ.push({startI, startJ});
        grid[startI][startJ] = color;
        
        while (!dfsQ.empty()) {
            auto [i, j] = dfsQ.front();
            dfsQ.pop();
            q.push({i, j});
            
            for (auto& dir : directions) {
                int ni = i + dir[0], nj = j + dir[1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                    grid[ni][nj] = color;
                    dfsQ.push({ni, nj});
                }
            }
        }
    }
    
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        
        queue<pair<int,int>> q1, q2;
        
        // Find and mark both islands
        bool firstFound = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (!firstFound) {
                        findIsland(grid, i, j, q1, 2);
                        firstFound = true;
                    } else {
                        findIsland(grid, i, j, q2, 3);
                        goto bidirectional_search;
                    }
                }
            }
        }
        
        bidirectional_search:
        
        // Bidirectional BFS
        int steps = 0;
        while (!q1.empty() && !q2.empty()) {
            // Always expand smaller frontier
            if (q1.size() > q2.size()) {
                swap(q1, q2);
            }
            
            int size = q1.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q1.front();
                q1.pop();
                
                for (auto& dir : directions) {
                    int nx = x + dir[0], ny = y + dir[1];
                    
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        if (grid[nx][ny] == 3) { // Found other island
                            return steps;
                        }
                        if (grid[nx][ny] == 0) {
                            grid[nx][ny] = 2;
                            q1.push({nx, ny});
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
```

### Approach 4: A* Algorithm with Manhattan Distance

```cpp
class SolutionAStar {
private:
    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
    struct Node {
        int x, y, g, f;
        Node(int x, int y, int g, int h) : x(x), y(y), g(g), f(g + h) {}
        
        bool operator>(const Node& other) const {
            return f > other.f;
        }
    };
    
    int manhattanDistance(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }
    
    void findIsland(vector<vector<int>>& grid, queue<pair<int,int>>& q) {
        int n = grid.size();
        bool found = false;
        
        for (int i = 0; i < n && !found; i++) {
            for (int j = 0; j < n && !found; j++) {
                if (grid[i][j] == 1) {
                    queue<pair<int,int>> dfs;
                    dfs.push({i, j});
                    grid[i][j] = 2;
                    
                    while (!dfs.empty()) {
                        auto [x, y] = dfs.front();
                        dfs.pop();
                        q.push({x, y});
                        
                        for (auto& dir : directions) {
                            int nx = x + dir[0], ny = y + dir[1];
                            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                                grid[nx][ny] = 2;
                                dfs.push({nx, ny});
                            }
                        }
                    }
                    found = true;
                }
            }
        }
    }
    
    pair<int, int> findClosestTarget(const vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }
    
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        
        queue<pair<int,int>> sources;
        findIsland(grid, sources);
        
        auto [targetX, targetY] = findClosestTarget(grid);
        if (targetX == -1) return -1;
        
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        vector<vector<int>> visited(n, vector<int>(n, -1));
        
        // Initialize A* with all source points
        while (!sources.empty()) {
            auto [x, y] = sources.front();
            sources.pop();
            
            int h = manhattanDistance(x, y, targetX, targetY);
            pq.push(Node(x, y, 0, h));
            visited[x][y] = 0;
        }
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            if (grid[current.x][current.y] == 1) {
                return current.g;
            }
            
            for (auto& dir : directions) {
                int nx = current.x + dir[0];
                int ny = current.y + dir[1];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    int newG = current.g + (grid[nx][ny] == 0 ? 1 : 0);
                    
                    if (visited[nx][ny] == -1 || newG < visited[nx][ny]) {
                        visited[nx][ny] = newG;
                        int h = manhattanDistance(nx, ny, targetX, targetY);
                        pq.push(Node(nx, ny, newG, h));
                    }
                }
            }
        }
        return -1;
    }
};
```

## Complexity Analysis

**Time Complexity:**
- **DFS + BFS**: O(N²) where N is the grid dimension
- **Union-Find + BFS**: O(N² × α(N²)) where α is inverse Ackermann
- **Bidirectional BFS**: O(N²) but typically faster in practice
- **A\* Algorithm**: O(N² log N) due to priority queue operations

**Space Complexity:**
- **DFS + BFS**: O(N²) for queue and grid modification
- **Union-Find + BFS**: O(N²) for union-find structure
- **Bidirectional BFS**: O(N²) for two queues
- **A\* Algorithm**: O(N²) for priority queue and visited array

## Example Walkthrough

### Example 1

```plaintext
Input: grid = [[0,1],[1,0]]
Output: 1
Explanation: We can connect the two islands by changing one 0 to 1

Grid visualization:
0 1     ->    1 1
1 0           1 0
```

### Example 2

```plaintext
Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Explanation: We need to flip 2 zeros to connect the islands

Grid visualization:
0 1 0     ->    0 1 0
0 0 0           0 1 0  
0 0 1           0 1 1
```

### Example 3

```plaintext
Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
Explanation: Islands are already adjacent, need only 1 flip
```

## Key Optimization Techniques

### 1. Island Identification

```cpp
// Efficiently mark first island and add boundary to queue
void markIslandAndAddBoundary(vector<vector<int>>& grid, int i, int j, queue<pair<int,int>>& q) {
    stack<pair<int,int>> dfs;
    dfs.push({i, j});
    grid[i][j] = 2;
    
    while (!dfs.empty()) {
        auto [x, y] = dfs.top();
        dfs.pop();
        
        bool isBoundary = false;
        for (auto& dir : directions) {
            int nx = x + dir[0], ny = y + dir[1];
            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid.size()) {
                if (grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    dfs.push({nx, ny});
                } else if (grid[nx][ny] == 0) {
                    isBoundary = true;
                }
            }
        }
        
        if (isBoundary) {
            q.push({x, y});
        }
    }
}
```

### 2. Early Termination

```cpp
// Stop as soon as we reach the second island
for (auto& dir : directions) {
    int nx = x + dir[0], ny = y + dir[1];
    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
        if (grid[nx][ny] == 1) {
            return steps; // Found second island immediately
        }
    }
}
```

### 3. Boundary-Only BFS

```cpp
// Only add boundary cells to initial queue for efficient expansion
bool isBoundaryCell(const vector<vector<int>>& grid, int x, int y) {
    for (auto& dir : directions) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid.size() && grid[nx][ny] == 0) {
            return true;
        }
    }
    return false;
}
```

## Real-World Applications

### 1. Network Bridge Design

```cpp
class NetworkBridgeDesigner {
private:
    struct Network {
        vector<vector<int>> topology;
        vector<pair<int,int>> nodes;
    };
    
public:
    int minimumCablesToConnect(const Network& net1, const Network& net2) {
        // Find shortest distance between two network clusters
        queue<pair<int,int>> q;
        
        // Add all boundary nodes of first network
        for (auto [x, y] : net1.nodes) {
            q.push({x, y});
        }
        
        vector<vector<bool>> visited(1000, vector<bool>(1000, false));
        int cables = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                // Check if we reached second network
                for (auto [nx, ny] : net2.nodes) {
                    if (abs(x - nx) + abs(y - ny) <= 1) {
                        return cables;
                    }
                }
                
                // Expand search
                for (auto& dir : directions) {
                    int nx = x + dir[0], ny = y + dir[1];
                    if (nx >= 0 && nx < 1000 && ny >= 0 && ny < 1000 && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            cables++;
        }
        return -1;
    }
};
```

### 2. Game Map Connection

```cpp
class GameMapConnector {
private:
    struct Island {
        vector<pair<int,int>> cells;
        pair<int,int> center;
    };
    
public:
    int minimumBridgeTiles(vector<vector<int>>& gameMap) {
        vector<Island> islands = findAllIslands(gameMap);
        if (islands.size() < 2) return 0;
        
        // Find shortest bridge between any two islands
        int minBridge = INT_MAX;
        
        for (int i = 0; i < islands.size(); i++) {
            for (int j = i + 1; j < islands.size(); j++) {
                int bridgeLength = findShortestBridge(gameMap, islands[i], islands[j]);
                minBridge = min(minBridge, bridgeLength);
            }
        }
        
        return minBridge;
    }
    
private:
    vector<Island> findAllIslands(const vector<vector<int>>& grid) {
        // Implementation to find all islands
        vector<Island> islands;
        // ... island detection logic
        return islands;
    }
    
    int findShortestBridge(vector<vector<int>>& grid, const Island& island1, const Island& island2) {
        // BFS from island1 to island2
        queue<pair<int,int>> q;
        for (auto cell : island1.cells) {
            q.push(cell);
        }
        
        // ... BFS implementation
        return 0;
    }
};
```

### 3. Circuit Board Design

```cpp
class CircuitBoardRouter {
private:
    struct Component {
        vector<pair<int,int>> pins;
        string type;
    };
    
public:
    int minimumWireLength(vector<vector<int>>& board, const Component& comp1, const Component& comp2) {
        // Find shortest wire path between two components
        queue<pair<int,int>> q;
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
        
        // Start from all pins of first component
        for (auto [x, y] : comp1.pins) {
            if (board[x][y] == 0) { // Available routing space
                q.push({x, y});
                visited[x][y] = true;
            }
        }
        
        int wireLength = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                
                // Check if we reached second component
                for (auto [tx, ty] : comp2.pins) {
                    if (abs(x - tx) + abs(y - ty) <= 1) {
                        return wireLength;
                    }
                }
                
                // Expand to adjacent routing spaces
                for (auto& dir : directions) {
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                    
                    if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() 
                        && !visited[nx][ny] && board[nx][ny] == 0) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            wireLength++;
        }
        return -1; // No path found
    }
};
```

## Advanced Features

### 1. Multiple Islands Support

```cpp
class MultiIslandBridge {
public:
    int connectAllIslands(vector<vector<int>>& grid) {
        vector<vector<pair<int,int>>> islands = findAllIslands(grid);