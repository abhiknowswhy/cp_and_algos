# Surrounded Regions

## Problem Description
Given an `m x n` matrix `board` containing `'X'` and `'O'`, capture all regions that are 4-directionally surrounded by `'X'`.

A region is captured by flipping all `'O'`s into `'X'`s in that surrounded region.

**Key insight**: An `'O'` is NOT captured if:
- It's on the border of the board, OR
- It's connected to an `'O'` that's on the border

## Approach
This problem can be solved using BFS/DFS by identifying which `'O'` cells are "safe" (connected to border). The strategy is to work backwards:

1. **Find all border `'O'` cells** and mark them as "safe"
2. **Use BFS/DFS** to mark all `'O'` cells connected to border cells as "safe"
3. **Flip remaining `'O'` cells** to `'X'` (these are surrounded)

## Algorithm Steps
1. **Iterate through border cells** and find all `'O'` cells
2. **For each border `'O'`**: Use BFS/DFS to mark all connected `'O'` cells as safe
3. **Iterate through entire board**: Convert non-safe `'O'` cells to `'X'`
4. **Restore safe cells**: Convert temporarily marked cells back to `'O'`

## Implementation

### Approach 1: BFS Solution
```cpp
#include <queue>
#include <vector>

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        
        int m = board.size(), n = board[0].size();
        
        // Mark all border-connected 'O's as safe using BFS
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Check border cells
                if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && 
                    board[i][j] == 'O') {
                    bfsMarkSafe(board, i, j);
                }
            }
        }
        
        // Convert all remaining 'O' to 'X' and restore safe cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';  // Surrounded region
                } else if (board[i][j] == 'S') {
                    board[i][j] = 'O';  // Restore safe cells
                }
            }
        }
    }
    
private:
    void bfsMarkSafe(vector<vector<char>>& board, int startRow, int startCol) {
        int m = board.size(), n = board[0].size();
        queue<pair<int, int>> q;
        
        q.push({startRow, startCol});
        board[startRow][startCol] = 'S';  // Mark as safe
        
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    board[newRow][newCol] == 'O') {
                    board[newRow][newCol] = 'S';
                    q.push({newRow, newCol});
                }
            }
        }
    }
};
```

### Approach 2: DFS Solution
```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        
        int m = board.size(), n = board[0].size();
        
        // Mark border-connected regions as safe
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == 0 || i == m - 1 || j == 0 || j == n - 1) && 
                    board[i][j] == 'O') {
                    dfsMarkSafe(board, i, j);
                }
            }
        }
        
        // Process the board
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'S') {
                    board[i][j] = 'O';
                }
            }
        }
    }
    
private:
    void dfsMarkSafe(vector<vector<char>>& board, int row, int col) {
        int m = board.size(), n = board[0].size();
        
        if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] != 'O') {
            return;
        }
        
        board[row][col] = 'S';  // Mark as safe
        
        // Explore all 4 directions
        dfsMarkSafe(board, row - 1, col);
        dfsMarkSafe(board, row + 1, col);
        dfsMarkSafe(board, row, col - 1);
        dfsMarkSafe(board, row, col + 1);
    }
};
```

### Approach 3: Union-Find Solution
```cpp
class UnionFind {
public:
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
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
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        
        int m = board.size(), n = board[0].size();
        UnionFind uf(m * n + 1);  // +1 for dummy border node
        int borderNode = m * n;
        
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    int currentIndex = i * n + j;
                    
                    // Connect border 'O's to border node
                    if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                        uf.unite(currentIndex, borderNode);
                    }
                    
                    // Connect to adjacent 'O's
                    for (auto [dr, dc] : directions) {
                        int newRow = i + dr, newCol = j + dc;
                        if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                            board[newRow][newCol] == 'O') {
                            int neighborIndex = newRow * n + newCol;
                            uf.unite(currentIndex, neighborIndex);
                        }
                    }
                }
            }
        }
        
        // Flip 'O's not connected to border
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    int currentIndex = i * n + j;
                    if (!uf.connected(currentIndex, borderNode)) {
                        board[i][j] = 'X';
                    }
                }
            }
        }
    }
};
```

### Time Complexity
- **BFS/DFS**: O(m × n) - each cell visited at most once
- **Union-Find**: O(m × n × α(m × n)) where α is inverse Ackermann function

### Space Complexity
- **BFS**: O(m × n) for queue in worst case
- **DFS**: O(m × n) for recursion stack in worst case
- **Union-Find**: O(m × n) for parent and rank arrays

## Examples

### Example 1
```
Input:
[['X','X','X','X'],
 ['X','O','O','X'],
 ['X','X','O','X'],
 ['X','O','X','X']]

Output:
[['X','X','X','X'],
 ['X','X','X','X'],
 ['X','X','X','X'],
 ['X','O','X','X']]

Explanation: The 'O' in bottom-left is connected to border, so it remains.
```

### Example 2
```
Input: [['X']]
Output: [['X']]
```

## Key Insights

### Queue Pattern Usage
- **Connected component identification**: BFS explores all connected 'O' cells
- **Border-first strategy**: Start BFS from border cells to identify safe regions
- **Level-order marking**: BFS naturally marks all connected cells

### Problem Strategy
1. **Reverse thinking**: Instead of finding surrounded regions, find non-surrounded ones
2. **Border analysis**: Only border-connected regions are safe
3. **Temporary marking**: Use different character to track safe cells

### Edge Cases
- **Single cell board**: Handle trivial cases
- **All 'X' or all 'O'**: No changes needed
- **Border-only 'O'**: All cells remain 'O'

## Related Problems
- Number of Islands
- Pacific Atlantic Water Flow
- Max Area of Island
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
