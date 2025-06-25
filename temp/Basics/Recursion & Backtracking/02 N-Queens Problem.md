# N-Queens Problem

## What is the N-Queens Problem?

The N-Queens problem is a classic combinatorial problem that asks to place N chess queens on an N×N chessboard so that no two queens threaten each other. This means no two queens can share the same row, column, or diagonal.

## Problem Constraints

1. Place exactly N queens on an N×N board
2. No two queens can attack each other:
   - No two queens on the same row
   - No two queens on the same column
   - No two queens on the same diagonal (both main and anti-diagonals)

## Implementations

### 1. Backtracking Solution

Backtracking is particularly suitable for this problem, as we can place queens one by one, and backtrack when we detect conflicts:

```cpp
#include <iostream>
#include <vector>
#include <string>

class NQueensSolver {
private:
    int n;
    std::vector<std::vector<std::string>> solutions;

    bool isSafe(const std::vector<int>& queensPos, int row, int col) {
        // Check for conflicts with previously placed queens
        for (int i = 0; i < row; i++) {
            // Same column check
            if (queensPos[i] == col)
                return false;
            
            // Diagonal check (check if queens are on same diagonal)
            if (abs(queensPos[i] - col) == abs(i - row))
                return false;
        }
        return true;
    }

    void solve(std::vector<int>& queensPos, int row) {
        // If we placed all N queens successfully
        if (row == n) {
            // Convert the queen positions to board representation
            std::vector<std::string> board(n, std::string(n, '.'));
            for (int i = 0; i < n; i++) {
                board[i][queensPos[i]] = 'Q';
            }
            solutions.push_back(board);
            return;
        }

        // Try placing a queen in each column of the current row
        for (int col = 0; col < n; col++) {
            if (isSafe(queensPos, row, col)) {
                // Place the queen
                queensPos[row] = col;
                
                // Recur for the next row
                solve(queensPos, row + 1);
                
                // Backtrack (this is implicit as we'll try the next column)
            }
        }
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        this->n = n;
        solutions.clear();
        
        // queensPos[i] represents the column where a queen is placed in row i
        std::vector<int> queensPos(n, -1);
        
        // Start solving from the first row
        solve(queensPos, 0);
        
        return solutions;
    }
};

void printSolution(const std::vector<std::string>& board) {
    for (const std::string& row : board) {
        std::cout << row << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    int n = 4; // Size of the board (4x4)
    NQueensSolver solver;
    
    std::vector<std::vector<std::string>> solutions = solver.solveNQueens(n);
    
    std::cout << "Number of solutions for " << n << "-Queens: " << solutions.size() << std::endl;
    std::cout << "Solutions:" << std::endl;
    
    for (int i = 0; i < solutions.size(); i++) {
        std::cout << "Solution " << (i + 1) << ":" << std::endl;
        printSolution(solutions[i]);
    }
    
    return 0;
}
```

**Time Complexity**: O(N!), where N is the board size. This is approximate as we're pruning many branches.
**Space Complexity**: O(N) for the recursion stack and to store intermediate states.

### 2. Optimized Backtracking with Bit Manipulation

We can optimize the solution using bit manipulation to track occupied columns, diagonals, and anti-diagonals:

```cpp
#include <iostream>
#include <vector>
#include <string>

class OptimizedNQueensSolver {
private:
    int n;
    std::vector<std::vector<std::string>> solutions;

    void solve(int row, int colMask, int diagMask, int antiDiagMask, std::vector<int>& queensPos) {
        if (row == n) {
            // Convert the queen positions to board representation
            std::vector<std::string> board(n, std::string(n, '.'));
            for (int i = 0; i < n; i++) {
                board[i][queensPos[i]] = 'Q';
            }
            solutions.push_back(board);
            return;
        }

        // Calculate available positions for current row
        // ~(colMask | diagMask | antiDiagMask) gives positions where we CAN place queens
        // & ((1 << n) - 1) limits to the board size
        int availablePositions = ~(colMask | diagMask | antiDiagMask) & ((1 << n) - 1);

        while (availablePositions > 0) {
            // Extract the rightmost set bit (a valid position to place queen)
            int pos = availablePositions & -availablePositions;
            
            // Convert bit position to column index
            int col = __builtin_ctz(pos); // Count trailing zeros
            
            // Place queen
            queensPos[row] = col;
            
            // Remove this position from available positions
            availablePositions &= ~pos;
            
            // Recur for next row with updated masks
            solve(
                row + 1,
                colMask | pos,                 // Update column mask
                (diagMask | pos) << 1,         // Update diagonal mask
                (antiDiagMask | pos) >> 1,     // Update anti-diagonal mask
                queensPos
            );
            // Backtracking happens implicitly as we try the next position
        }
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        this->n = n;
        solutions.clear();
        std::vector<int> queensPos(n, -1);
        
        solve(0, 0, 0, 0, queensPos);
        
        return solutions;
    }
};

// Same main function as before
void printSolution(const std::vector<std::string>& board) {
    for (const std::string& row : board) {
        std::cout << row << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    int n = 4; // Size of the board (4x4)
    OptimizedNQueensSolver solver;
    
    std::vector<std::vector<std::string>> solutions = solver.solveNQueens(n);
    
    std::cout << "Number of solutions for " << n << "-Queens: " << solutions.size() << std::endl;
    std::cout << "Solutions:" << std::endl;
    
    for (int i = 0; i < solutions.size(); i++) {
        std::cout << "Solution " << (i + 1) << ":" << std::endl;
        printSolution(solutions[i]);
    }
    
    return 0;
}
```

**Time Complexity**: Still O(N!), but with much better constant factors due to efficient checking
**Space Complexity**: O(N)

## Common Pitfalls

1. **Incorrect Diagonal Checking**: Remember to check both main diagonals and anti-diagonals.
2. **Inefficient Conflict Checking**: Re-examining the entire board can be very slow. Instead, store queen positions in a way that makes checking for conflicts efficient.
3. **Large N Values**: The problem becomes computationally expensive for large N (N > 15) due to its factorial time complexity.

## Mathematical Properties

- For N=1, there is 1 solution
- For N=2 and N=3, there are no solutions
- For N=4, there are 2 solutions
- For N=8 (standard chess board), there are 92 solutions
- For large N, the number of solutions grows rapidly

## Related LeetCode Problems

1. [51. N-Queens](https://leetcode.com/problems/n-queens/) - Return all distinct solutions to the N-Queens puzzle
2. [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/) - Return the number of distinct solutions to the N-Queens puzzle
3. [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) - Uses similar backtracking techniques
