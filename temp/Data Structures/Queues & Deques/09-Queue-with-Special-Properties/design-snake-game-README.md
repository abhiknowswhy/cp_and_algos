# Design Snake Game

## Problem Description

Design a Snake game that is played on a device with screen size = `width x height`. The snake is initially positioned at the top left corner `(0,0)` with length = 1 unit.

You are given a list of food's positions in order. When a snake eats the food, its length and the player's score both increase by 1.

Each food appears one by one on the screen. For example, the second food will not appear until the first food was eaten by the snake.

When a food does appear on the screen, it is guaranteed that it will not appear on a body of the snake.

A game is over if the snake goes out of bounds or if it bites itself.

**LeetCode Problem:** [353. Design Snake Game](https://leetcode.com/problems/design-snake-game/)

## Approach

Use a deque (double-ended queue) to efficiently manage the snake's body. The key insights are:
1. **Head Management**: Add new head position when moving
2. **Tail Management**: Remove tail when not eating food
3. **Collision Detection**: Check bounds and self-collision
4. **Food Tracking**: Maintain current food index and position

## Algorithm Steps

1. **Initialize**: Set up game board, snake deque, and food list
2. **Move Operation**: 
   - Calculate new head position based on direction
   - Check for boundary collision
   - Check for self-collision
   - Handle food consumption or tail removal
3. **Score Tracking**: Increment score when food is consumed
4. **Game State**: Return current score or -1 for game over

## Implementation

### Approach 1: Deque + Hash Set (Optimal)
```cpp
#include <deque>
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>

class SnakeGame {
private:
    int width, height;
    std::vector<std::vector<int>> food;
    int foodIndex;
    int score;
    std::deque<std::pair<int, int>> snake;
    std::unordered_set<std::string> snakeSet;
    
    std::string positionToString(int row, int col) {
        return std::to_string(row) + "," + std::to_string(col);
    }
    
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, std::vector<std::vector<int>>& food) 
        : width(width), height(height), food(food), foodIndex(0), score(0) {
        
        // Initialize snake at (0,0)
        snake.push_back({0, 0});
        snakeSet.insert(positionToString(0, 0));
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. */
    int move(std::string direction) {
        // Get current head position
        auto head = snake.front();
        int newRow = head.first;
        int newCol = head.second;
        
        // Calculate new head position
        if (direction == "U") newRow--;
        else if (direction == "D") newRow++;
        else if (direction == "L") newCol--;
        else if (direction == "R") newCol++;
        
        // Check boundary collision
        if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
            return -1;
        }
        
        // Check if eating food
        bool ateFood = false;
        if (foodIndex < food.size() && 
            newRow == food[foodIndex][0] && newCol == food[foodIndex][1]) {
            ateFood = true;
            foodIndex++;
            score++;
        }
        
        // If not eating food, remove tail
        if (!ateFood) {
            auto tail = snake.back();
            snake.pop_back();
            snakeSet.erase(positionToString(tail.first, tail.second));
        }
        
        // Check self-collision (after potentially removing tail)
        std::string newPosStr = positionToString(newRow, newCol);
        if (snakeSet.find(newPosStr) != snakeSet.end()) {
            return -1;
        }
        
        // Add new head
        snake.push_front({newRow, newCol});
        snakeSet.insert(newPosStr);
        
        return score;
    }
};
```

### Approach 2: Deque Only (Space Optimized)
```cpp
#include <deque>
#include <vector>
#include <string>

class SnakeGameDequeOnly {
private:
    int width, height;
    std::vector<std::vector<int>> food;
    int foodIndex;
    int score;
    std::deque<std::pair<int, int>> snake;
    
    bool isInSnake(int row, int col) {
        for (const auto& segment : snake) {
            if (segment.first == row && segment.second == col) {
                return true;
            }
        }
        return false;
    }
    
public:
    SnakeGameDequeOnly(int width, int height, std::vector<std::vector<int>>& food) 
        : width(width), height(height), food(food), foodIndex(0), score(0) {
        snake.push_back({0, 0});
    }
    
    int move(std::string direction) {
        auto head = snake.front();
        int newRow = head.first;
        int newCol = head.second;
        
        // Calculate new position
        if (direction == "U") newRow--;
        else if (direction == "D") newRow++;
        else if (direction == "L") newCol--;
        else if (direction == "R") newCol++;
        
        // Check bounds
        if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
            return -1;
        }
        
        // Check food
        bool ateFood = false;
        if (foodIndex < food.size() && 
            newRow == food[foodIndex][0] && newCol == food[foodIndex][1]) {
            ateFood = true;
            foodIndex++;
            score++;
        }
        
        // Remove tail if not eating
        if (!ateFood) {
            snake.pop_back();
        }
        
        // Check self-collision
        if (isInSnake(newRow, newCol)) {
            return -1;
        }
        
        // Add new head
        snake.push_front({newRow, newCol});
        
        return score;
    }
};
```

### Approach 3: Advanced Features Implementation
```cpp
#include <deque>
#include <unordered_set>
#include <vector>
#include <string>
#include <random>
#include <chrono>

class AdvancedSnakeGame {
private:
    int width, height;
    std::vector<std::vector<int>> food;
    int foodIndex;
    int score;
    std::deque<std::pair<int, int>> snake;
    std::unordered_set<std::string> snakeSet;
    
    // Game state
    bool gameOver;
    int moveCount;
    std::chrono::steady_clock::time_point startTime;
    
    // Power-ups and bonuses
    std::vector<std::vector<int>> powerUps;
    int powerUpIndex;
    bool invincible;
    int invincibleMoves;
    
    std::string positionToString(int row, int col) {
        return std::to_string(row) + "," + std::to_string(col);
    }
    
public:
    AdvancedSnakeGame(int width, int height, std::vector<std::vector<int>>& food) 
        : width(width), height(height), food(food), foodIndex(0), score(0),
          gameOver(false), moveCount(0), powerUpIndex(0), invincible(false), invincibleMoves(0) {
        
        snake.push_back({0, 0});
        snakeSet.insert(positionToString(0, 0));
        startTime = std::chrono::steady_clock::now();
        
        // Generate random power-ups
        generatePowerUps();
    }
    
    void generatePowerUps() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> rowDis(0, height - 1);
        std::uniform_int_distribution<> colDis(0, width - 1);
        
        // Generate 5 random power-up positions
        for (int i = 0; i < 5; i++) {
            powerUps.push_back({rowDis(gen), colDis(gen)});
        }
    }
    
    int move(std::string direction) {
        if (gameOver) return -1;
        
        moveCount++;
        
        // Handle invincibility countdown
        if (invincible) {
            invincibleMoves--;
            if (invincibleMoves <= 0) {
                invincible = false;
            }
        }
        
        auto head = snake.front();
        int newRow = head.first;
        int newCol = head.second;
        
        // Calculate new position
        if (direction == "U") newRow--;
        else if (direction == "D") newRow++;
        else if (direction == "L") newCol--;
        else if (direction == "R") newCol++;
        
        // Check bounds
        if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
            if (!invincible) {
                gameOver = true;
                return -1;
            }
            return score; // Invincible, bounce off walls
        }
        
        // Check food
        bool ateFood = false;
        if (foodIndex < food.size() && 
            newRow == food[foodIndex][0] && newCol == food[foodIndex][1]) {
            ateFood = true;
            foodIndex++;
            score += 10; // Bonus points
        }
        
        // Check power-ups
        bool atePowerUp = false;
        if (powerUpIndex < powerUps.size() && 
            newRow == powerUps[powerUpIndex][0] && newCol == powerUps[powerUpIndex][1]) {
            atePowerUp = true;
            powerUpIndex++;
            invincible = true;
            invincibleMoves = 10; // Invincible for 10 moves
            score += 50; // Bonus points for power-up
        }
        
        // Remove tail if not eating
        if (!ateFood && !atePowerUp) {
            auto tail = snake.back();
            snake.pop_back();
            snakeSet.erase(positionToString(tail.first, tail.second));
        }
        
        // Check self-collision
        std::string newPosStr = positionToString(newRow, newCol);
        if (snakeSet.find(newPosStr) != snakeSet.end()) {
            if (!invincible) {
                gameOver = true;
                return -1;
            }
            return score; // Invincible, pass through self
        }
        
        // Add new head
        snake.push_front({newRow, newCol});
        snakeSet.insert(newPosStr);
        
        return score;
    }
    
    // Additional game information
    int getLength() const { return snake.size(); }
    int getMoveCount() const { return moveCount; }
    bool isGameOver() const { return gameOver; }
    bool isInvincible() const { return invincible; }
    
    std::vector<std::pair<int, int>> getSnakeBody() const {
        std::vector<std::pair<int, int>> body;
        for (const auto& segment : snake) {
            body.push_back(segment);
        }
        return body;
    }
    
    double getElapsedTime() const {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
        return duration.count();
    }
};
```

### Time Complexity
- **Move Operation**: O(1) with hash set, O(n) without hash set for collision detection
- **Space**: O(n) where n is the length of the snake

### Space Complexity
- **Snake Storage**: O(n) for deque where n is snake length
- **Hash Set**: O(n) for fast lookup (optional optimization)
- **Food Array**: O(f) where f is number of food items

## Examples

### Example 1: Basic Game Flow
```cpp
void testBasicGameFlow() {
    std::vector<std::vector<int>> food = {{1,2},{0,1}};
    SnakeGame game(3, 2, food);
    
    // Initial state: snake at (0,0), score = 0
    std::cout << "Initial score: " << 0 << std::endl;
    
    // Move right: score = 0 (no food eaten)
    int score1 = game.move("R");
    std::cout << "After move R: " << score1 << std::endl; // 0
    
    // Move down: score = 0
    int score2 = game.move("D");
    std::cout << "After move D: " << score2 << std::endl; // 0
    
    // Move right: eat food at (1,2), score = 1
    int score3 = game.move("R");
    std::cout << "After move R (eat food): " << score3 << std::endl; // 1
    
    // Move up: eat food at (0,1), score = 2
    int score4 = game.move("U");
    std::cout << "After move U (eat food): " << score4 << std::endl; // 2
    
    // Move left: hit wall, game over
    int score5 = game.move("L");
    std::cout << "After move L (hit wall): " << score5 << std::endl; // -1
}
```

### Example 2: Self-Collision Test
```cpp
void testSelfCollision() {
    std::vector<std::vector<int>> food = {{2,0},{0,0},{0,2},{0,1}};
    SnakeGame game(3, 3, food);
    
    // Create a scenario where snake bites itself
    game.move("D"); // (1,0)
    game.move("D"); // (2,0) - eat food, snake length = 2
    game.move("R"); // (2,1)
    game.move("U"); // (1,1)
    game.move("U"); // (0,1) - eat food, snake length = 3
    game.move("L"); // (0,0) - eat food, snake length = 4
    
    // Now snake occupies (0,0), (0,1), (1,1), (2,1)
    // Move down to (1,0) should be safe
    int score = game.move("D");
    std::cout << "Safe move score: " << score << std::endl;
    
    // Move right to (1,1) - self collision!
    int gameOver = game.move("R");
    std::cout << "Self collision result: " << gameOver << std::endl; // -1
}
```

## Advanced Features

### Performance Benchmarking
```cpp
#include <chrono>

void benchmarkSnakeGame() {
    const int iterations = 100000;
    std::vector<std::vector<int>> food;
    
    // Generate random food
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    
    for (int i = 0; i < 1000; i++) {
        food.push_back({dis(gen), dis(gen)});
    }
    
    SnakeGame game(100, 100, food);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::string> directions = {"U", "D", "L", "R"};
    for (int i = 0; i < iterations; i++) {
        std::string dir = directions[i % 4];
        int result = game.move(dir);
        if (result == -1) break;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Benchmark: " << iterations << " moves in " 
              << duration.count() << " microseconds" << std::endl;
}
```

### AI Snake Player
```cpp
class AISnakePlayer {
private:
    SnakeGame& game;
    int width, height;
    
    std::string findBestMove(const std::vector<std::pair<int, int>>& snake, 
                            const std::pair<int, int>& food) {
        auto head = snake.front();
        std::vector<std::string> validMoves;
        
        // Check all possible moves
        std::vector<std::pair<std::string, std::pair<int, int>>> moves = {
            {"U", {head.first - 1, head.second}},
            {"D", {head.first + 1, head.second}},
            {"L", {head.first, head.second - 1}},
            {"R", {head.first, head.second + 1}}
        };
        
        for (const auto& move : moves) {
            int newRow = move.second.first;
            int newCol = move.second.second;
            
            // Check bounds
            if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {
                // Check self-collision (simplified)
                bool collision = false;
                for (const auto& segment : snake) {
                    if (segment.first == newRow && segment.second == newCol) {
                        collision = true;
                        break;
                    }
                }
                if (!collision) {
                    validMoves.push_back(move.first);
                }
            }
        }
        
        if (validMoves.empty()) return "U"; // Default
        
        // Simple heuristic: move towards food
        std::string bestMove = validMoves[0];
        int bestDistance = INT_MAX;
        
        for (const std::string& move : validMoves) {
            auto newPos = moves[0].second; // Get position for this move
            for (const auto& m : moves) {
                if (m.first == move) {
                    newPos = m.second;
                    break;
                }
            }
            
            int distance = abs(newPos.first - food.first) + abs(newPos.second - food.second);
            if (distance < bestDistance) {
                bestDistance = distance;
                bestMove = move;
            }
        }
        
        return bestMove;
    }
    
public:
    AISnakePlayer(SnakeGame& g, int w, int h) : game(g), width(w), height(h) {}
    
    void playGame(int maxMoves = 1000) {
        for (int i = 0; i < maxMoves; i++) {
            // This is a simplified AI - in practice you'd need game state access
            std::vector<std::string> moves = {"R", "D", "L", "U"};
            std::string move = moves[i % 4]; // Simple pattern
            
            int result = game.move(move);
            if (result == -1) {
                std::cout << "Game over at move " << i << " with score " << result << std::endl;
                break;
            }
        }
    }
};
```

## Real-World Applications

### 1. Game Development Engine
```cpp
class GameEngine {
private:
    AdvancedSnakeGame game;
    bool running;
    
public:
    GameEngine(int width, int height, std::vector<std::vector<int>>& food) 
        : game(width, height, food), running(true) {}
    
    void gameLoop() {
        while (running && !game.isGameOver()) {
            // Get user input (simplified)
            std::string direction = getUserInput();
            
            int score = game.move(direction);
            
            // Render game state
            renderGame();
            
            // Check win conditions
            if (score >= 100) {
                std::cout << "You win!" << std::endl;
                running = false;
            }
            
            // Add delay for game speed
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
private:
    std::string getUserInput() {
        // Simplified input - in practice use proper input handling
        return "R";
    }
    
    void renderGame() {
        std::cout << "Score: " << game.getLength() - 1 
                  << " Length: " << game.getLength()
                  << " Moves: " << game.getMoveCount() << std::endl;
    }
};
```

### 2. Educational Programming Tool
```cpp
class SnakeProgrammingChallenge {
private:
    SnakeGame game;
    std::vector<std::string> solution;
    
public:
    SnakeProgrammingChallenge(int width, int height, std::vector<std::vector<int>>& food)
        : game(width, height, food) {}
    
    bool validateSolution(const std::vector<std::string>& moves) {
        SnakeGame testGame = game; // Copy constructor needed
        
        for (const std::string& move : moves) {
            int result = testGame.move(move);
            if (result == -1) {
                return false; // Invalid solution
            }
        }
        return true;
    }
    
    std::vector<std::string> generateOptimalSolution() {
        // AI-based solution generation
        std::vector<std::string> solution;
        // Implementation would use pathfinding algorithms
        return solution;
    }
};
```

## Notes

- **Deque Efficiency**: O(1) insertion/deletion at both ends makes deque perfect for snake body management
- **Collision Detection**: Hash set provides O(1) lookup vs O(n) linear search
- **Memory Management**: Deque provides better cache locality than linked list
- **Game State**: Consider preserving game state for save/load functionality
- **Real-time Constraints**: Game loop timing critical for smooth gameplay

## Related Problems

- [LeetCode 353. Design Snake Game](https://leetcode.com/problems/design-snake-game/)
- [LeetCode 1670. Design Front Middle Back Queue](https://leetcode.com/problems/design-front-middle-back-queue/)
- [LeetCode 362. Design Hit Counter](https://leetcode.com/problems/design-hit-counter/)
- [LeetCode 1352. Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/)
- [LeetCode 622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)

## Pattern: 09-Queue-with-Special-Properties

This problem exemplifies the Queue with Special Properties pattern through:

1. **Dynamic Size Management**: Snake body grows/shrinks dynamically using deque operations
2. **FIFO with Modifications**: Snake movement follows FIFO (head addition, tail removal) with exceptions for food consumption
3. **State Preservation**: Deque maintains snake body order while allowing efficient head/tail operations
4. **Collision Detection Optimization**: Combining deque with hash set for O(1) collision checks

The deque serves as the primary data structure for the snake's body, providing O(1) operations for adding new head segments and removing tail segments, which are the core operations in the Snake game mechanics.
