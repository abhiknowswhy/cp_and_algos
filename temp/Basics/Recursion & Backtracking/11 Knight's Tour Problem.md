# Knight's Tour Problem

## Problem Definition

The Knight's Tour problem asks: Can a knight piece from chess visit every square on an N×N chessboard exactly once, starting from any square?

- In a **closed tour**, the knight must also be able to move back to its starting position in one move.
- In an **open tour**, this constraint doesn't apply.

## Background

This is a classic backtracking problem studied in mathematics and computer science. It's an instance of the more general Hamiltonian path problem in graph theory.

## Implementations

### 1. Backtracking Solution

The most straightforward approach is to use backtracking:

```cpp
#include <iostream>
#include <vector>
#include <iomanip>

class KnightsTour {
private:
    // Possible knight moves (8 possible moves)
    std::vector<std::pair<int, int>> moves = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };
    
    bool solveKnightTourUtil(std::vector<std::vector<int>>& board, int x, int y, 
                            int moveCount, int boardSize) {
        // If all squares are visited, we've found a solution
        if (moveCount == boardSize * boardSize) {
            return true;
        }
        
        // Try all possible moves from the current position
        for (const auto& move : moves) {
            int nextX = x + move.first;
            int nextY = y + move.second;
            
            // Check if the move is valid
            if (isValidMove(board, nextX, nextY, boardSize)) {
                // Make the move
                board[nextX][nextY] = moveCount;
                
                // Recursively try to solve from the new position
                if (solveKnightTourUtil(board, nextX, nextY, moveCount + 1, boardSize)) {
                    return true;
                }
                
                // Backtrack
                board[nextX][nextY] = -1;
            }
        }
        
        return false;
    }
    
    bool isValidMove(const std::vector<std::vector<int>>& board, int x, int y, int boardSize) {
        // Check if the move is within the board and the square hasn't been visited yet
        return (x >= 0 && y >= 0 && x < boardSize && y < boardSize && board[x][y] == -1);
    }

public:
    bool solveKnightTour(int boardSize, int startX, int startY) {
        // Initialize the board with -1 (unvisited)
        std::vector<std::vector<int>> board(boardSize, std::vector<int>(boardSize, -1));
        
        // Mark the starting position as visited
        board[startX][startY] = 0;
        
        // Try to solve the tour
        bool solved = solveKnightTourUtil(board, startX, startY, 1, boardSize);
        
        if (solved) {
            printSolution(board);
        } else {
            std::cout << "No solution exists for board size " << boardSize
                      << " starting from position (" << startX << ", " << startY << ")" << std::endl;
        }
        
        return solved;
    }
    
    void printSolution(const std::vector<std::vector<int>>& board) {
        int boardSize = board.size();
        
        std::cout << "Knight's Tour Solution:" << std::endl;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << std::setw(3) << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int boardSize = 8;  // Standard 8x8 chessboard
    int startX = 0;
    int startY = 0;
    
    KnightsTour tour;
    tour.solveKnightTour(boardSize, startX, startY);
    
    return 0;
}
```

**Time Complexity**: O(8^(N^2)), where N is the board size. This is because at each step, there are at most 8 possible moves, and there are N^2 steps in total.

**Space Complexity**: O(N^2) for the board and recursion stack.

### 2. Warnsdorff's Algorithm

A more efficient heuristic approach called Warnsdorff's rule:

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

class WarnsdorffKnightsTour {
private:
    // Possible knight moves
    std::vector<std::pair<int, int>> moves = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };
    
    bool isValidMove(const std::vector<std::vector<int>>& board, int x, int y, int boardSize) {
        return (x >= 0 && y >= 0 && x < boardSize && y < boardSize && board[x][y] == -1);
    }
    
    // Count the number of valid moves from a given position
    int countDegree(const std::vector<std::vector<int>>& board, int x, int y, int boardSize) {
        int count = 0;
        
        for (const auto& move : moves) {
            int nextX = x + move.first;
            int nextY = y + move.second;
            
            if (isValidMove(board, nextX, nextY, boardSize)) {
                count++;
            }
        }
        
        return count;
    }
    
    bool solveKnightTourUtil(std::vector<std::vector<int>>& board, int x, int y, 
                           int moveCount, int boardSize) {
        // If all squares are visited, we've found a solution
        if (moveCount == boardSize * boardSize) {
            return true;
        }
        
        // Find all possible next moves and sort them by accessibility (Warnsdorff's rule)
        std::vector<std::pair<int, std::pair<int, int>>> nextMoves;
        
        for (const auto& move : moves) {
            int nextX = x + move.first;
            int nextY = y + move.second;
            
            if (isValidMove(board, nextX, nextY, boardSize)) {
                // Count how many valid moves are available from the next position
                int degree = countDegree(board, nextX, nextY, boardSize);
                nextMoves.push_back({degree, {nextX, nextY}});
            }
        }
        
        // Sort by degree (number of available moves)
        std::sort(nextMoves.begin(), nextMoves.end());
        
        // Try moves in order of increasing degree (fewer available moves first)
        for (const auto& nextMove : nextMoves) {
            int nextX = nextMove.second.first;
            int nextY = nextMove.second.second;
            
            // Make the move
            board[nextX][nextY] = moveCount;
            
            if (solveKnightTourUtil(board, nextX, nextY, moveCount + 1, boardSize)) {
                return true;
            }
            
            // Backtrack
            board[nextX][nextY] = -1;
        }
        
        return false;
    }

public:
    bool solveKnightTour(int boardSize, int startX, int startY) {
        std::vector<std::vector<int>> board(boardSize, std::vector<int>(boardSize, -1));
        
        // Mark the starting position
        board[startX][startY] = 0;
        
        bool solved = solveKnightTourUtil(board, startX, startY, 1, boardSize);
        
        if (solved) {
            printSolution(board);
        } else {
            std::cout << "No solution exists for board size " << boardSize
                      << " starting from position (" << startX << ", " << startY << ")" << std::endl;
        }
        
        return solved;
    }
    
    void printSolution(const std::vector<std::vector<int>>& board) {
        int boardSize = board.size();
        
        std::cout << "Knight's Tour Solution (Warnsdorff's algorithm):" << std::endl;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << std::setw(3) << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int boardSize = 8;
    int startX = 0;
    int startY = 0;
    
    WarnsdorffKnightsTour tour;
    tour.solveKnightTour(boardSize, startX, startY);
    
    return 0;
}
```

**Time Complexity**: While the worst-case is still O(8^(N^2)), in practice Warnsdorff's algorithm performs much better, often close to O(N^2).

**Space Complexity**: O(N^2) for the board.

### 3. Divide and Conquer Solution (For Specific Board Sizes)

For certain board sizes (e.g., 8×8), the Knight's Tour problem can be solved using a divide-and-conquer approach:

```cpp
#include <iostream>
#include <vector>
#include <iomanip>

class DivideConquerKnightsTour {
private:
    // Pre-computed solution patterns for 8x8 board
    std::vector<std::vector<int>> solveFor8x8(int startX, int startY) {
        // This is a simplified implementation that works for specific start positions
        // In a real implementation, this would use multiple patterns based on symmetry
        
        // An 8x8 board can be divided into four 4x4 boards
        // We can solve each quadrant independently and then combine them
        
        std::vector<std::vector<int>> board(8, std::vector<int>(8, -1));
        
        // For simplicity, we're implementing a hardcoded solution for starting position (0,0)
        if (startX == 0 && startY == 0) {
            // This is an example of a valid knight's tour on 8x8 starting from (0,0)
            // In practice, this would be more flexible
            int solution[8][8] = {
                { 0,  59, 38, 33, 30, 17,  8, 63},
                {37, 34, 31, 60, 9,  62, 29, 16},
                {58, 1,  36, 39, 32, 27, 18,  7},
                {35, 48, 41, 26, 61, 10, 15, 28},
                {42, 57, 2,  49, 40, 23,  6, 19},
                {47, 50, 45, 54, 25, 20, 11, 14},
                {56, 43, 52, 3,  22, 13, 24,  5},
                {51, 46, 55, 44, 53,  4, 21, 12}
            };
            
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    board[i][j] = solution[i][j];
                }
            }
            return board;
        }
        
        // For other start positions, we'd need to adapt the solution or use a different approach
        // For simplicity, we just return an empty board for other start positions
        return board;
    }

public:
    bool solveKnightTour(int boardSize, int startX, int startY) {
        if (boardSize == 8) {
            std::vector<std::vector<int>> solution = solveFor8x8(startX, startY);
            
            // Check if a solution was found
            bool hasSolution = (solution[0][0] != -1);
            
            if (hasSolution) {
                printSolution(solution);
                return true;
            } else {
                std::cout << "No pre-computed solution for starting position (" << startX << ", " << startY << ")" << std::endl;
                return false;
            }
        } else {
            std::cout << "Divide and conquer approach is only implemented for 8x8 boards" << std::endl;
            return false;
        }
    }
    
    void printSolution(const std::vector<std::vector<int>>& board) {
        int boardSize = board.size();
        
        std::cout << "Knight's Tour Solution (Divide and Conquer):" << std::endl;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << std::setw(3) << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int boardSize = 8;
    int startX = 0;
    int startY = 0;
    
    DivideConquerKnightsTour tour;
    tour.solveKnightTour(boardSize, startX, startY);
    
    return 0;
}
```

**Time Complexity**: O(1) for pre-computed solutions.
**Space Complexity**: O(N^2) for the board.

## Mathematical Analysis

### Existence of Solutions

- A Knight's Tour exists for all N×N boards where N ≥ 5.
- For a 3×3 board, no Knight's Tour exists.
- For a 4×4 board, no closed tour exists, but open tours do exist.
- For even-sized boards, a closed Knight's Tour is always possible.

### Number of Solutions

The number of distinct Knight's Tours grows exponentially with the board size:
- 5×5: 1,728 closed tours
- 6×6: 6,637,920 closed tours
- 8×8: Approximately 1.3 × 10^13 closed tours (estimated)

## Common Pitfalls

1. **Inefficient Backtracking**: Naive backtracking can be extremely slow for larger boards.
2. **Not Using Heuristics**: Without heuristics like Warnsdorff's rule, the solution may not be found in reasonable time.
3. **Checking for Closed Tours**: Remember to check if the last position can reach the starting position if a closed tour is required.
4. **Small Boards**: For board sizes less than 5×5, be aware that solutions might not exist for all starting positions.

## Related Problems

1. [Hamiltonian Path](https://en.wikipedia.org/wiki/Hamiltonian_path) - Finding a path that visits every vertex exactly once
2. [Traveling Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) - Finding the shortest possible route that visits each city exactly once
3. [Euler's Path](https://en.wikipedia.org/wiki/Eulerian_path) - Finding a path that traverses every edge exactly once
4. [N-Queens Problem](https://leetcode.com/problems/n-queens/) - Another classic backtracking problem
