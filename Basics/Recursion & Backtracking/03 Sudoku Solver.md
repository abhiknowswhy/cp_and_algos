# Sudoku Solver

## What is Sudoku?

Sudoku is a 9×9 grid-based number puzzle where the goal is to fill the grid so that each row, each column, and each of the nine 3×3 sub-grids contains all digits from 1 to 9 without repetition.

## Problem Definition

Given a partially filled 9×9 Sudoku board, complete all the empty cells so that:
1. Each row contains all digits from 1 to 9 without repetition
2. Each column contains all digits from 1 to 9 without repetition
3. Each of the nine 3×3 sub-boxes contains all digits from 1 to 9 without repetition

The empty cells are typically represented by a dot '.' or zero '0'.

## Implementations

### 1. Backtracking Solution

Backtracking is the standard approach for solving Sudoku puzzles programmatically:

```cpp
#include <iostream>
#include <vector>

class SudokuSolver {
private:
    // Check if it's valid to place 'num' at position (row, col)
    bool isValid(std::vector<std::vector<char>>& board, int row, int col, char num) {
        // Check row
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num) return false;
        }
        
        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num) return false;
        }
        
        // Check 3x3 box
        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[boxRowStart + i][boxColStart + j] == num) return false;
            }
        }
        
        // If we've passed all checks, the move is valid
        return true;
    }
    
    bool solve(std::vector<std::vector<char>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                // Find an empty cell
                if (board[row][col] == '.') {
                    // Try placing digits 1-9
                    for (char num = '1'; num <= '9'; num++) {
                        // If it's valid to place 'num' at (row, col)
                        if (isValid(board, row, col, num)) {
                            // Place the digit
                            board[row][col] = num;
                            
                            // Recursively solve the rest of the board
                            if (solve(board)) return true;
                            
                            // If placing 'num' didn't lead to a solution, backtrack
                            board[row][col] = '.';
                        }
                    }
                    // If we've tried all digits 1-9 and none worked, this board can't be solved
                    return false;
                }
            }
        }
        // If we've filled the entire board, we've found a solution
        return true;
    }

public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        solve(board);
    }
};

// Helper function to print the Sudoku board
void printBoard(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "- - - - - - - - - - - -" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    
    std::cout << "Sudoku Puzzle:" << std::endl;
    printBoard(board);
    
    SudokuSolver solver;
    solver.solveSudoku(board);
    
    std::cout << "\nSolution:" << std::endl;
    printBoard(board);
    
    return 0;
}
```

**Time Complexity**: O(9^(N*N)), where N is the board size (N=9 for standard Sudoku). This is because for each empty cell, we might have to try up to 9 numbers, and there could be up to N*N empty cells. However, due to constraints, the actual complexity is much lower.
**Space Complexity**: O(N*N) for the board and recursion stack.

### 2. Optimized Backtracking with Constraint Propagation

We can optimize the solution by keeping track of which numbers are already used in each row, column, and box:

```cpp
#include <iostream>
#include <vector>
#include <array>

class OptimizedSudokuSolver {
private:
    // Arrays to keep track of which numbers are used in each row, column, and box
    std::array<std::array<bool, 9>, 9> rowUsed;
    std::array<std::array<bool, 9>, 9> colUsed;
    std::array<std::array<bool, 9>, 9> boxUsed;
    
    // Get the box index (0-8) for a given cell (row, col)
    int getBoxIndex(int row, int col) {
        return (row / 3) * 3 + (col / 3);
    }
    
    bool solve(std::vector<std::vector<char>>& board) {
        // Find the empty cell with the fewest possibilities
        int minRow = -1, minCol = -1, minPossibilities = 10;
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    // Count how many possible numbers can go in this cell
                    int count = 0;
                    for (int num = 0; num < 9; num++) {
                        if (!rowUsed[i][num] && !colUsed[j][num] && !boxUsed[getBoxIndex(i, j)][num]) {
                            count++;
                        }
                    }
                    
                    if (count < minPossibilities) {
                        minPossibilities = count;
                        minRow = i;
                        minCol = j;
                    }
                    
                    // If we find a cell with only one possibility, choose it immediately
                    if (count == 1) {
                        break;
                    }
                }
            }
        }
        
        // If no empty cell was found, the board is filled
        if (minRow == -1) {
            return true;
        }
        
        // Try each possible number in the chosen cell
        for (int num = 0; num < 9; num++) {
            if (!rowUsed[minRow][num] && !colUsed[minCol][num] && !boxUsed[getBoxIndex(minRow, minCol)][num]) {
                // Mark this number as used
                rowUsed[minRow][num] = true;
                colUsed[minCol][num] = true;
                boxUsed[getBoxIndex(minRow, minCol)][num] = true;
                
                // Place the number in the board
                board[minRow][minCol] = '1' + num;
                
                // Recursively solve the rest
                if (solve(board)) {
                    return true;
                }
                
                // Backtrack
                board[minRow][minCol] = '.';
                rowUsed[minRow][num] = false;
                colUsed[minCol][num] = false;
                boxUsed[getBoxIndex(minRow, minCol)][num] = false;
            }
        }
        
        return false;
    }

public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        // Initialize the constraint arrays
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                rowUsed[i][j] = false;
                colUsed[i][j] = false;
                boxUsed[i][j] = false;
            }
        }
        
        // Mark the initially filled numbers as used
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '1';
                    rowUsed[i][num] = true;
                    colUsed[j][num] = true;
                    boxUsed[getBoxIndex(i, j)][num] = true;
                }
            }
        }
        
        // Solve the Sudoku
        solve(board);
    }
};

// Same printBoard function and a similar main function as before
void printBoard(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "- - - - - - - - - - - -" << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    
    std::cout << "Sudoku Puzzle:" << std::endl;
    printBoard(board);
    
    OptimizedSudokuSolver solver;
    solver.solveSudoku(board);
    
    std::cout << "\nSolution:" << std::endl;
    printBoard(board);
    
    return 0;
}
```

**Time Complexity**: Still theoretically O(9^(N*N)), but with much better performance due to smart cell selection and constraint propagation.
**Space Complexity**: O(N*N)

## Common Pitfalls

1. **Inefficient Validity Checking**: Checking the entire row, column, and box for each number placement can be slow. Using pre-calculated sets or arrays is much faster.
2. **Poor Empty Cell Selection**: Selecting cells in a fixed order isn't optimal. Choosing cells with fewer possibilities (MRV - Minimum Remaining Values heuristic) can significantly reduce the search space.
3. **Not Handling Multiple Solutions**: Some Sudoku puzzles may have multiple valid solutions. Make sure your code correctly handles this case if needed.

## Related LeetCode Problems

1. [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) - Solve a 9×9 Sudoku board
2. [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/) - Determine if a 9×9 Sudoku board is valid
3. [51. N-Queens](https://leetcode.com/problems/n-queens/) - Similar backtracking problem
