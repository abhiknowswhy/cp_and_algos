# Design Tic-Tac-Toe Game

## Problem Description
**LeetCode Problem #348 - Medium**
🔗 [LeetCode Link](https://leetcode.com/problems/design-tic-tac-toe/)

Design a Tic-tac-toe game that is played between two players on an `n x n` grid. You may assume the following rules:

1. A player wins if they get n of their marks in a row (horizontal, vertical, or diagonal)
2. The game ends in a draw if all positions are filled without a winner
3. Players alternate turns starting with player 1

**Key Requirements:**
- Implement the `TicTacToe` class constructor and `move` method
- The `move` method should return 0 if no winner yet, or the player number (1 or 2) who wins
- Optimize for space and time efficiency

## Queue Pattern Connection
This problem demonstrates **Event Queue Simulation** patterns where:
- Each move represents an event in the game state
- We need to efficiently track and validate win conditions
- Optimal solution requires maintaining running counts rather than full board state
- Pattern applies to real-time game systems and state validation

## Approach

### Approach 1: Optimized Counter-Based (Recommended)
Instead of maintaining the full board, track running sums for each row, column, and diagonal. When a player makes a move, increment their counter in the relevant positions. A win occurs when any counter reaches `n` or `-n`.

### Approach 2: Full Board Simulation
Maintain the complete game board and check all win conditions after each move.

### Approach 3: Bitmask Optimization
Use bitmasks to represent player positions for ultra-fast win detection.

## Algorithm Steps

### Optimized Counter Approach:
1. **Initialize**: Create arrays for row, column, and diagonal counters
2. **Process Move**: Update relevant counters (+1 for player 1, -1 for player 2)
3. **Check Win**: If any counter equals ±n, return the winning player
4. **Continue**: Return 0 if no winner detected

## Implementation

### Implementation 1: Optimized Counter-Based Solution
```cpp
#include <vector>
#include <iostream>
#include <cassert>

class TicTacToe {
private:
    std::vector<int> rows;      // Row counters
    std::vector<int> cols;      // Column counters
    int diagonal;               // Main diagonal counter
    int antiDiagonal;           // Anti-diagonal counter
    int n;                      // Board size
    
public:
    /**
     * Initialize the TicTacToe object with board size n
     * Time: O(n), Space: O(n)
     */
    TicTacToe(int n) : n(n), diagonal(0), antiDiagonal(0) {
        rows.resize(n, 0);
        cols.resize(n, 0);
    }
    
    /**
     * Makes a move and returns winner (0: no winner, 1/2: player number)
     * Time: O(1), Space: O(1)
     */
    int move(int row, int col, int player) {
        // Convert player to increment value: +1 for player 1, -1 for player 2
        int increment = (player == 1) ? 1 : -1;
        int target = (player == 1) ? n : -n;
        
        // Update counters
        rows[row] += increment;
        cols[col] += increment;
        
        // Update diagonals if applicable
        if (row == col) {
            diagonal += increment;
        }
        if (row + col == n - 1) {
            antiDiagonal += increment;
        }
        
        // Check win conditions
        if (rows[row] == target || cols[col] == target || 
            diagonal == target || antiDiagonal == target) {
            return player;
        }
        
        return 0;  // No winner yet
    }
    
    // Utility method for debugging
    void printGameState() const {
        std::cout << "Rows: ";
        for (int r : rows) std::cout << r << " ";
        std::cout << "\nCols: ";
        for (int c : cols) std::cout << c << " ";
        std::cout << "\nDiag: " << diagonal << ", Anti-diag: " << antiDiagonal << std::endl;
    }
};
```

### Implementation 2: Full Board with Enhanced Features
```cpp
#include <vector>
#include <iostream>
#include <string>

class TicTacToeAdvanced {
private:
    std::vector<std::vector<int>> board;
    int n;
    int totalMoves;
    std::vector<std::pair<int, int>> moveHistory;
    
public:
    TicTacToeAdvanced(int n) : n(n), totalMoves(0) {
        board.assign(n, std::vector<int>(n, 0));
    }
    
    int move(int row, int col, int player) {
        if (board[row][col] != 0) {
            return -1;  // Invalid move
        }
        
        board[row][col] = player;
        moveHistory.push_back({row, col});
        totalMoves++;
        
        // Check all win conditions
        if (checkWin(row, col, player)) {
            return player;
        }
        
        // Check for draw
        if (totalMoves == n * n) {
            return 3;  // Draw
        }
        
        return 0;  // Game continues
    }
    
private:
    bool checkWin(int row, int col, int player) {
        // Check row
        int count = 0;
        for (int c = 0; c < n; c++) {
            if (board[row][c] == player) count++;
        }
        if (count == n) return true;
        
        // Check column
        count = 0;
        for (int r = 0; r < n; r++) {
            if (board[r][col] == player) count++;
        }
        if (count == n) return true;
        
        // Check main diagonal
        if (row == col) {
            count = 0;
            for (int i = 0; i < n; i++) {
                if (board[i][i] == player) count++;
            }
            if (count == n) return true;
        }
        
        // Check anti-diagonal
        if (row + col == n - 1) {
            count = 0;
            for (int i = 0; i < n; i++) {
                if (board[i][n - 1 - i] == player) count++;
            }
            if (count == n) return true;
        }
        
        return false;
    }
    
public:
    void printBoard() const {
        for (const auto& row : board) {
            for (int cell : row) {
                char symbol = (cell == 0) ? '.' : (cell == 1) ? 'X' : 'O';
                std::cout << symbol << " ";
            }
            std::cout << std::endl;
        }
    }
    
    std::vector<std::pair<int, int>> getMoveHistory() const {
        return moveHistory;
    }
    
    bool undoLastMove() {
        if (moveHistory.empty()) return false;
        
        auto lastMove = moveHistory.back();
        board[lastMove.first][lastMove.second] = 0;
        moveHistory.pop_back();
        totalMoves--;
        return true;
    }
};
```

### Implementation 3: Bitmask Optimization
```cpp
#include <vector>
#include <iostream>

class TicTacToeBitmask {
private:
    std::vector<long long> player1Rows, player1Cols;
    std::vector<long long> player2Rows, player2Cols;
    long long player1Diag, player1AntiDiag;
    long long player2Diag, player2AntiDiag;
    long long winMask;
    int n;
    
public:
    TicTacToeBitmask(int n) : n(n) {
        player1Rows.assign(n, 0);
        player1Cols.assign(n, 0);
        player2Rows.assign(n, 0);
        player2Cols.assign(n, 0);
        player1Diag = player1AntiDiag = 0;
        player2Diag = player2AntiDiag = 0;
        
        // Create win mask (n consecutive 1s)
        winMask = (1LL << n) - 1;
    }
    
    int move(int row, int col, int player) {
        long long bitPos = 1LL << col;
        
        if (player == 1) {
            player1Rows[row] |= bitPos;
            player1Cols[col] |= (1LL << row);
            
            if (row == col) {
                player1Diag |= (1LL << row);
            }
            if (row + col == n - 1) {
                player1AntiDiag |= (1LL << row);
            }
            
            // Check win
            if (player1Rows[row] == winMask || 
                player1Cols[col] == winMask ||
                player1Diag == winMask || 
                player1AntiDiag == winMask) {
                return 1;
            }
        } else {
            player2Rows[row] |= bitPos;
            player2Cols[col] |= (1LL << row);
            
            if (row == col) {
                player2Diag |= (1LL << row);
            }
            if (row + col == n - 1) {
                player2AntiDiag |= (1LL << row);
            }
            
            // Check win
            if (player2Rows[row] == winMask || 
                player2Cols[col] == winMask ||
                player2Diag == winMask || 
                player2AntiDiag == winMask) {
                return 2;
            }
        }
        
        return 0;
    }
};
```

### Implementation 4: Thread-Safe Multiplayer Version
```cpp
#include <vector>
#include <mutex>
#include <atomic>
#include <iostream>

class TicTacToeThreadSafe {
private:
    std::vector<std::atomic<int>> rows;
    std::vector<std::atomic<int>> cols;
    std::atomic<int> diagonal;
    std::atomic<int> antiDiagonal;
    std::atomic<int> gameState;  // 0: ongoing, 1: player1 wins, 2: player2 wins
    mutable std::mutex moveMutex;
    int n;
    
public:
    TicTacToeThreadSafe(int n) : n(n), diagonal(0), antiDiagonal(0), gameState(0) {
        rows.resize(n);
        cols.resize(n);
        for (int i = 0; i < n; i++) {
            rows[i] = 0;
            cols[i] = 0;
        }
    }
    
    int move(int row, int col, int player) {
        std::lock_guard<std::mutex> lock(moveMutex);
        
        // Check if game already ended
        if (gameState.load() != 0) {
            return gameState.load();
        }
        
        int increment = (player == 1) ? 1 : -1;
        int target = (player == 1) ? n : -n;
        
        // Update counters atomically
        rows[row] += increment;
        cols[col] += increment;
        
        if (row == col) {
            diagonal += increment;
        }
        if (row + col == n - 1) {
            antiDiagonal += increment;
        }
        
        // Check win conditions
        if (rows[row].load() == target || cols[col].load() == target || 
            diagonal.load() == target || antiDiagonal.load() == target) {
            gameState = player;
            return player;
        }
        
        return 0;
    }
    
    int getGameState() const {
        return gameState.load();
    }
    
    void reset() {
        std::lock_guard<std::mutex> lock(moveMutex);
        for (int i = 0; i < n; i++) {
            rows[i] = 0;
            cols[i] = 0;
        }
        diagonal = 0;
        antiDiagonal = 0;
        gameState = 0;
    }
};
```

## Complexity Analysis

### Optimized Counter Solution:
- **Time Complexity**: O(1) per move
- **Space Complexity**: O(n) for storing counters
- **Total Game Time**: O(moves) where moves ≤ n²

### Full Board Solution:
- **Time Complexity**: O(n) per move (checking win conditions)
- **Space Complexity**: O(n²) for storing the board
- **Total Game Time**: O(moves × n)

### Bitmask Solution:
- **Time Complexity**: O(1) per move
- **Space Complexity**: O(n) with better constant factors
- **Cache Performance**: Excellent due to bit operations

## Examples

### Example 1: 3x3 Game
```cpp
void example1() {
    TicTacToe game(3);
    
    std::cout << game.move(0, 0, 1) << std::endl; // 0
    std::cout << game.move(0, 2, 2) << std::endl; // 0
    std::cout << game.move(2, 2, 1) << std::endl; // 0
    std::cout << game.move(1, 1, 2) << std::endl; // 0
    std::cout << game.move(2, 0, 1) << std::endl; // 0
    std::cout << game.move(1, 0, 2) << std::endl; // 0
    std::cout << game.move(2, 1, 1) << std::endl; // 1 (Player 1 wins!)
}
```

### Example 2: Advanced Features Demo
```cpp
void example2() {
    TicTacToeAdvanced game(3);
    
    game.move(0, 0, 1);  // X
    game.move(0, 1, 2);  // O
    game.move(1, 1, 1);  // X
    game.move(0, 2, 2);  // O
    
    game.printBoard();
    /*
    X O O
    . X .
    . . .
    */
    
    std::cout << "Move " << game.move(2, 2, 1) << std::endl; // 1 (X wins diagonally)
}
```

### Example 3: Performance Benchmark
```cpp
#include <chrono>
#include <random>

void performanceBenchmark() {
    const int n = 100;
    const int trials = 10000;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int t = 0; t < trials; t++) {
        TicTacToe game(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, n-1);
        
        for (int moves = 0; moves < n; moves++) {
            int row = dis(gen);
            int col = dis(gen);
            int player = (moves % 2) + 1;
            int result = game.move(row, col, player);
            if (result != 0) break;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Processed " << trials << " games in " 
              << duration.count() << " microseconds" << std::endl;
    std::cout << "Average: " << (double)duration.count() / trials 
              << " microseconds per game" << std::endl;
}
```

## Real-World Applications

### 1. **Online Gaming Platforms**
```cpp
class GameServer {
private:
    std::unordered_map<int, TicTacToeThreadSafe> activeGames;
    std::mutex gamesMutex;
    
public:
    int createGame(int gameId, int boardSize) {
        std::lock_guard<std::mutex> lock(gamesMutex);
        activeGames[gameId] = TicTacToeThreadSafe(boardSize);
        return gameId;
    }
    
    int processMove(int gameId, int row, int col, int playerId) {
        auto it = activeGames.find(gameId);
        if (it != activeGames.end()) {
            return it->second.move(row, col, playerId);
        }
        return -1;  // Game not found
    }
};
```

### 2. **AI Game Training System**
```cpp
class TicTacToeAI {
private:
    TicTacToe game;
    std::vector<std::vector<float>> qTable;
    
public:
    TicTacToeAI(int n) : game(n) {
        // Initialize Q-learning table
        int states = pow(3, n * n);  // 3^(n²) possible states
        qTable.assign(states, std::vector<float>(n * n, 0.0f));
    }
    
    int getOptimalMove(int gameState) {
        // Q-learning implementation for optimal move selection
        // This would integrate with the TicTacToe class for training
        return 0;  // Simplified
    }
};
```

### 3. **Educational Game Analytics**
```cpp
class GameAnalytics {
private:
    struct GameSession {
        std::vector<std::pair<int, int>> moves;
        int winner;
        std::chrono::milliseconds duration;
        int playerSkillLevel;
    };
    
    std::vector<GameSession> sessions;
    
public:
    void recordGame(const TicTacToeAdvanced& game, int winner, 
                   std::chrono::milliseconds duration) {
        GameSession session;
        session.moves = game.getMoveHistory();
        session.winner = winner;
        session.duration = duration;
        sessions.push_back(session);
    }
    
    double calculateWinRate(int player) {
        int wins = 0;
        int totalGames = 0;
        for (const auto& session : sessions) {
            if (session.winner == player) wins++;
            if (session.winner != 0) totalGames++;  // Exclude draws
        }
        return totalGames > 0 ? (double)wins / totalGames : 0.0;
    }
};
```

### 4. **Mobile Game Framework**
```cpp
class MobileGameEngine {
private:
    TicTacToe* currentGame;
    bool touchEnabled;
    
public:
    struct TouchEvent {
        float x, y;
        int timestamp;
    };
    
    int processTouchEvent(const TouchEvent& event, int boardSize) {
        if (!touchEnabled || !currentGame) return -1;
        
        // Convert touch coordinates to board position
        int row = static_cast<int>(event.y * boardSize);
        int col = static_cast<int>(event.x * boardSize);
        
        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
            return currentGame->move(row, col, getCurrentPlayer());
        }
        return -1;
    }
    
private:
    int getCurrentPlayer() {
        // Implementation to track current player
        return 1;  // Simplified
    }
};
```

### 5. **Tournament Management System**
```cpp
class TournamentManager {
private:
    struct Tournament {
        std::vector<int> players;
        std::vector<std::pair<int, int>> matches;
        std::map<int, int> scores;
        int boardSize;
    };
    
    std::map<int, Tournament> tournaments;
    
public:
    int createTournament(const std::vector<int>& playerIds, int boardSize) {
        Tournament tournament;
        tournament.players = playerIds;
        tournament.boardSize = boardSize;
        
        // Generate round-robin matches
        for (size_t i = 0; i < playerIds.size(); i++) {
            for (size_t j = i + 1; j < playerIds.size(); j++) {
                tournament.matches.push_back({playerIds[i], playerIds[j]});
            }
        }
        
        int tournamentId = tournaments.size();
        tournaments[tournamentId] = tournament;
        return tournamentId;
    }
    
    int playMatch(int tournamentId, int player1, int player2) {
        auto& tournament = tournaments[tournamentId];
        TicTacToe game(tournament.boardSize);
        
        // Simulate or play actual match
        // Return winner and update scores
        return 0;  // Simplified
    }
};
```

## Pattern Insights

### Key Observations:
1. **Counter Optimization**: The optimal solution demonstrates how tracking aggregated state (counters) can be more efficient than maintaining full state (board)

2. **Win Condition Checking**: Different approaches to win detection show trade-offs between time complexity and code simplicity

3. **Scalability**: The counter-based approach scales to large boards (1000x1000) while maintaining O(1) move processing

4. **Thread Safety**: Real-world applications require careful synchronization for multiplayer scenarios

### Related Patterns:
- **State Machine**: Game states and transitions
- **Observer Pattern**: Game event notifications
- **Strategy Pattern**: Different AI players
- **Command Pattern**: Move history and undo functionality

### Advanced Optimizations:
- **Memory Pool**: Pre-allocate game objects for high-frequency gaming
- **SIMD Instructions**: Vectorized win condition checking for very large boards
- **Cache-Friendly Data Layout**: Optimize memory access patterns for performance
- **Lock-Free Programming**: Advanced concurrency for real-time multiplayer games

This problem excellently demonstrates how simple game logic can be optimized through clever data structure choices and algorithmic thinking, making it valuable for both competitive programming and real-world software development.
