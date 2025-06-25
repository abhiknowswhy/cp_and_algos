# Rat in a Maze

## Problem Definition

The Rat in a Maze problem is a common backtracking problem:

1. Given a maze (typically a 2D grid) with obstacles
2. A rat starts from a source cell (usually the top-left corner)
3. The goal is to reach a destination cell (usually the bottom-right corner)
4. The rat can only move in two or four directions (usually right and down, or all four cardinal directions)
5. The task is to find all possible paths from source to destination

## Implementations

### 1. Basic Rat in a Maze (Two Directions: Right and Down)

```cpp
#include <iostream>
#include <vector>
#include <string>

class RatInMaze {
private:
    bool isSafe(std::vector<std::vector<int>>& maze, int x, int y, int n) {
        // Check if (x, y) is a valid and open cell
        return (x >= 0 && y >= 0 && x < n && y < n && maze[x][y] == 1);
    }
    
    void solveMazeUtil(std::vector<std::vector<int>>& maze, int x, int y, int n,
                      std::vector<std::vector<int>>& sol, std::vector<std::string>& paths, std::string path) {
        // If destination is reached
        if (x == n - 1 && y == n - 1) {
            paths.push_back(path);
            return;
        }
        
        // Mark the current cell as part of solution path
        sol[x][y] = 1;
        
        // Move down
        if (isSafe(maze, x + 1, y, n)) {
            solveMazeUtil(maze, x + 1, y, n, sol, paths, path + "D");
        }
        
        // Move right
        if (isSafe(maze, x, y + 1, n)) {
            solveMazeUtil(maze, x, y + 1, n, sol, paths, path + "R");
        }
        
        // Backtrack - unmark current cell
        sol[x][y] = 0;
    }

public:
    std::vector<std::string> findPath(std::vector<std::vector<int>>& maze, int n) {
        std::vector<std::string> paths;
        
        // If the starting cell is blocked, return empty
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
            return paths;
        }
        
        // Solution matrix to keep track of path
        std::vector<std::vector<int>> sol(n, std::vector<int>(n, 0));
        
        // Find paths starting from (0, 0)
        solveMazeUtil(maze, 0, 0, n, sol, paths, "");
        
        return paths;
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    
    RatInMaze ratMaze;
    std::vector<std::string> paths = ratMaze.findPath(maze, n);
    
    std::cout << "All possible paths (using only Right and Down):" << std::endl;
    if (paths.empty()) {
        std::cout << "No path exists." << std::endl;
    } else {
        for (const std::string& path : paths) {
            std::cout << path << std::endl;
        }
    }
    
    return 0;
}
```

**Time Complexity**: O(2^(N^2)), where N is the size of the maze. In worst case, every cell can be reached from 2 directions, leading to 2^(N^2) paths.
**Space Complexity**: O(N^2) for the recursion stack and the solution matrix.

### 2. Rat in a Maze with Four Directions

```cpp
#include <iostream>
#include <vector>
#include <string>

class RatInMazeFourDirections {
private:
    // Possible moves: Down, Left, Right, Up
    std::vector<std::pair<int, int>> moves = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    std::vector<char> moveChars = {'D', 'L', 'R', 'U'};
    
    bool isSafe(std::vector<std::vector<int>>& maze, std::vector<std::vector<bool>>& visited, 
               int x, int y, int n) {
        return (x >= 0 && y >= 0 && x < n && y < n && maze[x][y] == 1 && !visited[x][y]);
    }
    
    void solveMazeUtil(std::vector<std::vector<int>>& maze, int x, int y, int n,
                      std::vector<std::vector<bool>>& visited, std::vector<std::string>& paths, std::string path) {
        // If destination is reached
        if (x == n - 1 && y == n - 1) {
            paths.push_back(path);
            return;
        }
        
        // Mark the current cell as visited
        visited[x][y] = true;
        
        // Try all four directions
        for (int i = 0; i < 4; i++) {
            int newX = x + moves[i].first;
            int newY = y + moves[i].second;
            
            if (isSafe(maze, visited, newX, newY, n)) {
                solveMazeUtil(maze, newX, newY, n, visited, paths, path + moveChars[i]);
            }
        }
        
        // Backtrack - unmark current cell
        visited[x][y] = false;
    }

public:
    std::vector<std::string> findPath(std::vector<std::vector<int>>& maze, int n) {
        std::vector<std::string> paths;
        
        // If the starting cell is blocked, return empty
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
            return paths;
        }
        
        // Visited matrix to keep track of visited cells
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        
        // Find paths starting from (0, 0)
        solveMazeUtil(maze, 0, 0, n, visited, paths, "");
        
        return paths;
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    
    RatInMazeFourDirections ratMaze;
    std::vector<std::string> paths = ratMaze.findPath(maze, n);
    
    std::cout << "All possible paths (using all four directions):" << std::endl;
    if (paths.empty()) {
        std::cout << "No path exists." << std::endl;
    } else {
        for (const std::string& path : paths) {
            std::cout << path << std::endl;
        }
    }
    
    return 0;
}
```

**Time Complexity**: O(4^(N^2)), as now every cell can be reached from 4 directions in the worst case.
**Space Complexity**: O(N^2)

### 3. Finding the Shortest Path

If we want to find the shortest path through the maze, we can use a breadth-first search (BFS) approach instead:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

class ShortestPathInMaze {
private:
    // Possible moves: Down, Left, Right, Up
    std::vector<std::pair<int, int>> moves = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    std::vector<char> moveChars = {'D', 'L', 'R', 'U'};
    
    bool isSafe(std::vector<std::vector<int>>& maze, std::vector<std::vector<bool>>& visited, 
               int x, int y, int n) {
        return (x >= 0 && y >= 0 && x < n && y < n && maze[x][y] == 1 && !visited[x][y]);
    }

public:
    std::string shortestPath(std::vector<std::vector<int>>& maze, int n) {
        // If the starting cell is blocked, return empty
        if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
            return "";
        }
        
        // BFS queue to store cell coordinates and path so far
        // (x, y, path)
        std::queue<std::tuple<int, int, std::string>> q;
        q.push(std::make_tuple(0, 0, ""));
        
        // Visited matrix to avoid cycles
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        visited[0][0] = true;
        
        while (!q.empty()) {
            auto [x, y, path] = q.front();
            q.pop();
            
            // If destination is reached, return the path
            if (x == n - 1 && y == n - 1) {
                return path;
            }
            
            // Try all four directions
            for (int i = 0; i < 4; i++) {
                int newX = x + moves[i].first;
                int newY = y + moves[i].second;
                
                if (isSafe(maze, visited, newX, newY, n)) {
                    visited[newX][newY] = true;
                    q.push(std::make_tuple(newX, newY, path + moveChars[i]));
                }
            }
        }
        
        // If no path is found
        return "";
    }
};

int main() {
    int n = 4;
    std::vector<std::vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    
    ShortestPathInMaze shortestPath;
    std::string path = shortestPath.shortestPath(maze, n);
    
    std::cout << "Shortest path from (0,0) to (" << n-1 << "," << n-1 << "):" << std::endl;
    if (path.empty()) {
        std::cout << "No path exists." << std::endl;
    } else {
        std::cout << path << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(N^2), as each cell is visited at most once.
**Space Complexity**: O(N^2) for the visited array and the queue.

## Variations

### 1. Maze with Multiple Exits

Find all possible paths from a source to any of several exits:

```cpp
// Instead of checking for a specific destination, check if the current cell is an exit
if (isExit(x, y)) {
    paths.push_back(path);
    return;
}
```

### 2. Maze with Keys and Doors

In this variation, the maze contains keys and doors. The rat can only go through a door if it has collected the corresponding key:

```cpp
// Track collected keys in the state
void solveMazeWithKeys(maze, x, y, collectedKeys, path) {
    // If current cell has a key, collect it
    if (maze[x][y] is a key) {
        collectedKeys |= (1 << key_id);  // Set the bit for this key
    }
    
    // For each adjacent cell
    for each (newX, newY) adjacent to (x, y) {
        // If it's a door and we have the key, or if it's not a door
        if ((maze[newX][newY] is not a door) || 
            (maze[newX][newY] is a door && we have the key)) {
            // Move to this cell
            solveMazeWithKeys(maze, newX, newY, collectedKeys, path + direction);
        }
    }
}
```

## Common Pitfalls

1. **Infinite Loops**: Not properly tracking visited cells can lead to infinite loops.
2. **Off-by-One Errors**: Miscalculating grid boundaries or destination coordinates.
3. **Path Representation**: Make sure to represent the path in a clear format (e.g., "DDRR" for Down-Down-Right-Right).
4. **Backtracking**: Remember to properly backtrack by marking cells as unvisited when moving back up the recursion tree.

## Related LeetCode Problems

1. [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) - Find the shortest path from top-left to bottom-right in a binary matrix
2. [490. The Maze](https://leetcode.com/problems/the-maze/) - A ball moving in a maze with obstacles
3. [505. The Maze II](https://leetcode.com/problems/the-maze-ii/) - Find the shortest distance for a ball to stop
4. [79. Word Search](https://leetcode.com/problems/word-search/) - Find if a word exists in a board by traversing adjacent cells
5. [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) - Similar backtracking approach
