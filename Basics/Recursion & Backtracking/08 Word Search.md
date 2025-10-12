# Word Search (Leetcode 79)

## Problem Definition

The Word Search problem asks:

Given an m x n grid of characters (board) and a string (word), return true if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where:
- Adjacent cells are horizontally or vertically neighboring
- The same letter cell may not be used more than once

## Implementations

### 1. Backtracking Solution

The standard approach is to use backtracking to explore all possible paths:

```cpp
#include <iostream>
#include <vector>
#include <string>

class WordSearch {
private:
    // Possible moves: Right, Down, Left, Up
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    bool search(std::vector<std::vector<char>>& board, const std::string& word, 
               int index, int i, int j, std::vector<std::vector<bool>>& visited) {
        // If we've matched all characters, return true
        if (index == word.length()) {
            return true;
        }
        
        // If out of bounds, the character doesn't match, or already visited
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            board[i][j] != word[index] || visited[i][j]) {
            return false;
        }
        
        // Mark as visited
        visited[i][j] = true;
        
        // Try all four directions
        for (const auto& dir : directions) {
            int newI = i + dir.first;
            int newJ = j + dir.second;
            
            if (search(board, word, index + 1, newI, newJ, visited)) {
                return true;
            }
        }
        
        // Backtrack
        visited[i][j] = false;
        
        return false;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        int m = board.size();
        if (m == 0) return false;
        int n = board[0].size();
        
        // Try starting from each cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
                if (search(board, word, 0, i, j, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

int main() {
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    
    WordSearch solver;
    
    std::string word1 = "ABCCED";
    std::string word2 = "SEE";
    std::string word3 = "ABCB";
    
    std::cout << "Word \"" << word1 << "\" exists: " << (solver.exist(board, word1) ? "Yes" : "No") << std::endl;
    std::cout << "Word \"" << word2 << "\" exists: " << (solver.exist(board, word2) ? "Yes" : "No") << std::endl;
    std::cout << "Word \"" << word3 << "\" exists: " << (solver.exist(board, word3) ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(N × M × 4^L), where N and M are the dimensions of the board and L is the length of the word. In the worst case, we need to check all cells as potential starting points, and for each starting point, we explore up to 4^L paths.

**Space Complexity**: O(N × M) for the visited array and O(L) for the recursion stack, where L is the length of the word.

### 2. Optimized Solution (In-place modification)

To save space, we can temporarily modify the board instead of using a separate visited array:

```cpp
#include <iostream>
#include <vector>
#include <string>

class OptimizedWordSearch {
private:
    // Possible moves: Right, Down, Left, Up
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    bool search(std::vector<std::vector<char>>& board, const std::string& word, 
               int index, int i, int j) {
        // If we've matched all characters, return true
        if (index == word.length()) {
            return true;
        }
        
        // If out of bounds or the character doesn't match
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }
        
        // Mark as visited by changing the character temporarily
        char temp = board[i][j];
        board[i][j] = '#';  // Use a marker that won't be in the word
        
        // Try all four directions
        for (const auto& dir : directions) {
            int newI = i + dir.first;
            int newJ = j + dir.second;
            
            if (search(board, word, index + 1, newI, newJ)) {
                board[i][j] = temp;  // Restore the original character
                return true;
            }
        }
        
        // Backtrack
        board[i][j] = temp;  // Restore the original character
        
        return false;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        int m = board.size();
        if (m == 0) return false;
        int n = board[0].size();
        
        // Try starting from each cell
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (search(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

int main() {
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    
    OptimizedWordSearch solver;
    
    std::string word1 = "ABCCED";
    std::string word2 = "SEE";
    std::string word3 = "ABCB";
    
    std::cout << "Word \"" << word1 << "\" exists: " << (solver.exist(board, word1) ? "Yes" : "No") << std::endl;
    std::cout << "Word \"" << word2 << "\" exists: " << (solver.exist(board, word2) ? "Yes" : "No") << std::endl;
    std::cout << "Word \"" << word3 << "\" exists: " << (solver.exist(board, word3) ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(N × M × 4^L), same as the previous solution.
**Space Complexity**: O(L) for the recursion stack, where L is the length of the word. We save the O(N×M) space by modifying the board in-place.

### 3. Further Optimizations

Several optimizations can improve the performance:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class HighlyOptimizedWordSearch {
private:
    // Possible moves: Right, Down, Left, Up
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    bool search(std::vector<std::vector<char>>& board, const std::string& word, 
               int index, int i, int j) {
        // If we've matched all characters, return true
        if (index == word.length()) {
            return true;
        }
        
        // If out of bounds or the character doesn't match
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }
        
        // Mark as visited
        char temp = board[i][j];
        board[i][j] = '#';
        
        // Try all four directions
        for (const auto& dir : directions) {
            int newI = i + dir.first;
            int newJ = j + dir.second;
            
            if (search(board, word, index + 1, newI, newJ)) {
                board[i][j] = temp;  // Restore the original character
                return true;
            }
        }
        
        // Backtrack
        board[i][j] = temp;
        
        return false;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        int m = board.size();
        if (m == 0) return false;
        int n = board[0].size();
        
        // Check if the word is longer than the total cells in the board
        if (word.length() > m * n) {
            return false;
        }
        
        // Count character frequencies in the word and the board
        std::unordered_map<char, int> wordFreq;
        std::unordered_map<char, int> boardFreq;
        
        for (char c : word) wordFreq[c]++;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                boardFreq[board[i][j]]++;
            }
        }
        
        // If any character in the word appears more times than in the board, return false
        for (const auto& pair : wordFreq) {
            if (boardFreq[pair.first] < pair.second) {
                return false;
            }
        }
        
        // Start the search from cells that match the first character
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0] && search(board, word, 0, i, j)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

int main() {
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    
    HighlyOptimizedWordSearch solver;
    
    std::string word1 = "ABCCED";
    std::string word2 = "SEE";
    std::string word3 = "ABCB";
    
    std::cout << "Word \"" << word1 << "\" exists: " << (solver.exist(board, word1) ? "Yes" : "No") << std::endl;
    std::cout << "Word \"" << word2 << "\" exists: " << (solver.exist(board, word2) ? "Yes" : "No") << std::endl;
    std::cout << "Word \"" << word3 << "\" exists: " << (solver.exist(board, word3) ? "Yes" : "No") << std::endl;
    
    return 0;
}
```

**Time Complexity**: Still O(N × M × 4^L) in the worst case, but with practical improvements.
**Space Complexity**: O(L) for recursion, plus O(1) for the character frequency maps (as there are only 26 possible characters).

## Common Pitfalls

1. **Visiting the Same Cell**: Make sure not to visit the same cell twice in a path.
2. **Boundary Checks**: Always check if the indices are within bounds before accessing the board.
3. **Early Termination**: Add checks to terminate early if a solution is impossible (e.g., word length exceeds total cells).
4. **Direction Management**: Be careful with the direction offsets and make sure to explore all four directions.

## Extensions

### Word Search II (Leetcode 212)

Find all words from a dictionary that can be formed in a board. This usually requires a Trie data structure for efficiency:

```cpp
// Trie node
struct TrieNode {
    TrieNode* children[26];
    std::string word;  // Store the complete word at leaf nodes
    
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        word = "";
    }
};

// Build Trie from words
TrieNode* buildTrie(std::vector<std::string>& words) {
    TrieNode* root = new TrieNode();
    
    for (const std::string& word : words) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->word = word;  // Mark the end and store the word
    }
    
    return root;
}

// Search in the board using Trie
void search(std::vector<std::vector<char>>& board, int i, int j, 
           TrieNode* node, std::vector<std::string>& result) {
    char c = board[i][j];
    
    // If the current cell is visited or has no child in the Trie
    if (c == '#' || !node->children[c - 'a']) {
        return;
    }
    
    node = node->children[c - 'a'];
    
    // If we found a word
    if (!node->word.empty()) {
        result.push_back(node->word);
        node->word = "";  // De-duplicate
    }
    
    // Mark as visited
    board[i][j] = '#';
    
    // Explore neighbors
    if (i > 0) search(board, i - 1, j, node, result);
    if (j > 0) search(board, i, j - 1, node, result);
    if (i < board.size() - 1) search(board, i + 1, j, node, result);
    if (j < board[0].size() - 1) search(board, i, j + 1, node, result);
    
    // Restore
    board[i][j] = c;
}

std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
    std::vector<std::string> result;
    TrieNode* root = buildTrie(words);
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            search(board, i, j, root, result);
        }
    }
    
    return result;
}
```

## Related LeetCode Problems

1. [79. Word Search](https://leetcode.com/problems/word-search/) - Check if a word exists in a board
2. [212. Word Search II](https://leetcode.com/problems/word-search-ii/) - Find all words from a dictionary that exist in a board
3. [200. Number of Islands](https://leetcode.com/problems/number-of-islands/) - Similar DFS/BFS grid traversal
4. [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/) - Similar grid pathfinding with constraints
5. [1219. Path with Maximum Gold](https://leetcode.com/problems/path-with-maximum-gold/) - Find path with max sum using backtracking
