# 8-Puzzle Problem

## Problem Description
The 8-puzzle consists of a 3×3 grid with 8 numbered tiles (1-8) and one empty space (represented by 0). The goal is to rearrange the tiles from an initial configuration to reach the target configuration by sliding tiles into the empty space.

**Valid moves**: A tile can only move into the empty space if it's adjacent (up, down, left, right).

**Goal state**: Usually arranged as:
```
1 2 3
4 5 6  
7 8 0
```

## Approach
This is a classic state-space search problem where each board configuration represents a state. We use BFS to find the minimum number of moves to reach the goal state.

**Key insights:**
1. **State representation**: 3×3 grid flattened to string or vector
2. **State transitions**: Move empty space (0) in 4 possible directions
3. **Goal checking**: Compare current state with target configuration
4. **Optimizations**: A* search with Manhattan distance heuristic

## Algorithm Steps
1. **Represent board state** as a string or vector for easy comparison
2. **Initialize BFS** with starting configuration
3. **For each state**: Generate all possible moves of the empty space
4. **Validate moves**: Ensure moves stay within grid boundaries
5. **Track visited states** and return steps when goal is reached

## Implementation

### Approach 1: BFS Solution
```cpp
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string target = "123450";
        string start = "";
        
        // Convert board to string representation
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                start += to_string(board[i][j]);
            }
        }
        
        if (start == target) return 0;
        
        // BFS
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({start, 0});
        visited.insert(start);
        
        // Possible moves for each position of '0'
        vector<vector<int>> moves = {
            {1, 3},       // Position 0: can move to 1, 3
            {0, 2, 4},    // Position 1: can move to 0, 2, 4
            {1, 5},       // Position 2: can move to 1, 5
            {0, 4},       // Position 3: can move to 0, 4
            {1, 3, 5},    // Position 4: can move to 1, 3, 5
            {2, 4}        // Position 5: can move to 2, 4
        };
        
        while (!q.empty()) {
            auto [state, steps] = q.front();
            q.pop();
            
            // Find position of '0'
            int zeroPos = state.find('0');
            
            // Try all possible moves
            for (int nextPos : moves[zeroPos]) {
                string nextState = state;
                swap(nextState[zeroPos], nextState[nextPos]);
                
                if (nextState == target) {
                    return steps + 1;
                }
                
                if (visited.find(nextState) == visited.end()) {
                    visited.insert(nextState);
                    q.push({nextState, steps + 1});
                }
            }
        }
        
        return -1; // No solution exists
    }
};
```

### Approach 2: General 8-Puzzle (3×3 grid)
```cpp
class EightPuzzle {
private:
    vector<vector<int>> target = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    
public:
    int solvePuzzle(vector<vector<int>>& board) {
        string targetStr = boardToString(target);
        string startStr = boardToString(board);
        
        if (startStr == targetStr) return 0;
        
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({startStr, 0});
        visited.insert(startStr);
        
        while (!q.empty()) {
            auto [currentStr, moves] = q.front();
            q.pop();
            
            vector<vector<int>> currentBoard = stringToBoard(currentStr);
            
            // Find empty space (0)
            int emptyRow = -1, emptyCol = -1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (currentBoard[i][j] == 0) {
                        emptyRow = i;
                        emptyCol = j;
                        break;
                    }
                }
            }
            
            // Try all 4 directions
            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            
            for (auto [dx, dy] : directions) {
                int newRow = emptyRow + dx;
                int newCol = emptyCol + dy;
                
                if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                    // Create new board state
                    vector<vector<int>> newBoard = currentBoard;
                    swap(newBoard[emptyRow][emptyCol], newBoard[newRow][newCol]);
                    
                    string newStr = boardToString(newBoard);
                    
                    if (newStr == targetStr) {
                        return moves + 1;
                    }
                    
                    if (visited.find(newStr) == visited.end()) {
                        visited.insert(newStr);
                        q.push({newStr, moves + 1});
                    }
                }
            }
        }
        
        return -1; // No solution
    }
    
private:
    string boardToString(const vector<vector<int>>& board) {
        string result = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result += to_string(board[i][j]);
            }
        }
        return result;
    }
    
    vector<vector<int>> stringToBoard(const string& str) {
        vector<vector<int>> board(3, vector<int>(3));
        for (int i = 0; i < 9; i++) {
            board[i / 3][i % 3] = str[i] - '0';
        }
        return board;
    }
};
```

### Approach 3: A* Search with Manhattan Distance Heuristic
```cpp
class AStar8Puzzle {
private:
    struct State {
        vector<vector<int>> board;
        int moves;
        int heuristic;
        
        bool operator>(const State& other) const {
            return moves + heuristic > other.moves + other.heuristic;
        }
    };
    
public:
    int solvePuzzleAStar(vector<vector<int>>& board) {
        vector<vector<int>> target = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
        
        if (board == target) return 0;
        
        priority_queue<State, vector<State>, greater<State>> pq;
        set<vector<vector<int>>> visited;
        
        pq.push({board, 0, manhattanDistance(board, target)});
        visited.insert(board);
        
        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();
            
            if (current.board == target) {
                return current.moves;
            }
            
            // Find empty space
            int emptyRow = -1, emptyCol = -1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (current.board[i][j] == 0) {
                        emptyRow = i;
                        emptyCol = j;
                        break;
                    }
                }
            }
            
            // Try all moves
            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            
            for (auto [dx, dy] : directions) {
                int newRow = emptyRow + dx;
                int newCol = emptyCol + dy;
                
                if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                    vector<vector<int>> newBoard = current.board;
                    swap(newBoard[emptyRow][emptyCol], newBoard[newRow][newCol]);
                    
                    if (visited.find(newBoard) == visited.end()) {
                        visited.insert(newBoard);
                        pq.push({newBoard, current.moves + 1, 
                               manhattanDistance(newBoard, target)});
                    }
                }
            }
        }
        
        return -1;
    }
    
private:
    int manhattanDistance(const vector<vector<int>>& current, 
                         const vector<vector<int>>& target) {
        int distance = 0;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current[i][j] != 0) {
                    int value = current[i][j];
                    
                    // Find target position of this value
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < 3; y++) {
                            if (target[x][y] == value) {
                                distance += abs(i - x) + abs(j - y);
                                break;
                            }
                        }
                    }
                }
            }
        }
        
        return distance;
    }
};
```

### Time Complexity
- **BFS**: O(9!) in worst case - all possible permutations of the puzzle
- **A* Search**: Much better in practice due to heuristic guidance
- **Practical**: Most solvable puzzles solved in reasonable time

### Space Complexity
- **BFS**: O(9!) for visited states storage
- **A* Search**: O(9!) but typically much less due to pruning

## Examples

### Example 1 (LeetCode 773 - Sliding Puzzle)
```
Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
```

### Example 2
```
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
```

### Example 3 (Classic 8-Puzzle)
```
Initial: [[2,8,3],[1,6,4],[7,0,5]]
Target:  [[1,2,3],[4,5,6],[7,8,0]]
Output: Number of moves to solve (varies)
```

## Key Insights

### Queue Pattern Usage
- **State-space exploration**: Each board configuration is a unique state
- **Breadth-first guarantee**: BFS finds minimum number of moves
- **Systematic search**: All reachable states explored level by level

### Optimization Strategies
1. **State encoding**: Convert 2D board to string for fast comparison
2. **Precomputed moves**: Store valid move positions for each empty space location
3. **A* heuristic**: Manhattan distance guides search toward solution
4. **Solvability check**: Not all configurations are solvable

### Practical Considerations
- **Memory usage**: Can be high for complex puzzles
- **Solvability**: Check if puzzle is solvable before attempting to solve
- **Heuristic choice**: Manhattan distance is admissible and consistent

## Related Problems
- Sliding Puzzle (LeetCode 773)
- 15-Puzzle (4×4 variant)
- Word Ladder
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

## Pattern: 07-State-Space-Search
<!-- Explain how this problem fits the pattern -->
