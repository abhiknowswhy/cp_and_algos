# Knight's Shortest Path on Chessboard

## Problem Description

Given a chessboard of size n×n, find the minimum number of moves required for a knight to reach from a source position to a destination position.

A knight moves in an L-shape: 2 squares in one direction and 1 square perpendicular to that, or 1 square in one direction and 2 squares perpendicular.

## Approach

Use BFS to find the shortest path. Since all moves have equal cost (1), BFS guarantees the minimum number of moves. Treat each position as a node and knight moves as edges.

## Algorithm Steps

1. If source equals destination, return 0
2. Initialize queue with source position and distance 0
3. Mark source as visited
4. For each position in queue:
   - Try all 8 possible knight moves
   - If move leads to destination, return distance + 1
   - If move is valid and unvisited, add to queue with distance + 1
5. Continue until destination found

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Solution {
public:
    int minKnightMoves(int n, pair<int,int> source, pair<int,int> dest) {
        if (source == dest) return 0;
        
        // 8 possible knight moves
        vector<pair<int,int>> directions = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        queue<pair<pair<int,int>, int>> q; // {{x,y}, distance}
        set<pair<int,int>> visited;
        
        q.push({source, 0});
        visited.insert(source);
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            
            pair<int,int> pos = current.first;
            int dist = current.second;
            
            // Try all 8 knight moves
            for (auto& dir : directions) {
                int newX = pos.first + dir.first;
                int newY = pos.second + dir.second;
                pair<int,int> newPos = {newX, newY};
                
                // Check if destination reached
                if (newPos == dest) {
                    return dist + 1;
                }
                
                // Check bounds and if not visited
                if (isValid(newX, newY, n) && visited.find(newPos) == visited.end()) {
                    visited.insert(newPos);
                    q.push({newPos, dist + 1});
                }
            }
        }
        
        return -1; // Should not reach here for valid input
    }
    
private:
    bool isValid(int x, int y, int n) {
        return x >= 0 && x < n && y >= 0 && y < n;
    }
};

// Alternative implementation for infinite chessboard (LeetCode 1197)
class Solution2 {
public:
    int minKnightMoves(int x, int y) {
        // Use symmetry - work in first quadrant
        x = abs(x);
        y = abs(y);
        
        if (x + y == 1) return 3; // Special case
        
        queue<pair<pair<int,int>, int>> q;
        set<pair<int,int>> visited;
        
        q.push({{0, 0}, 0});
        visited.insert({0, 0});
        
        vector<pair<int,int>> directions = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        while (!q.empty()) {
            auto current = q.front();
            q.pop();
            
            int curX = current.first.first;
            int curY = current.first.second;
            int dist = current.second;
            
            if (curX == x && curY == y) {
                return dist;
            }
            
            for (auto& dir : directions) {
                int newX = curX + dir.first;
                int newY = curY + dir.second;
                
                // Pruning: don't go too far from target
                if (newX >= -1 && newY >= -1 && newX <= x + 2 && newY <= y + 2) {
                    pair<int,int> newPos = {newX, newY};
                    if (visited.find(newPos) == visited.end()) {
                        visited.insert(newPos);
                        q.push({newPos, dist + 1});
                    }
                }
            }
        }
        
        return -1;
    }
};
```

### Time Complexity

- **O(n²)** for n×n chessboard (worst case visit all squares)
- **O(max(|x|, |y|)²)** for infinite board with target (x,y)

### Space Complexity

- **O(n²)** for visited set and queue storage
- In practice, much smaller due to BFS early termination

## Examples

### Example 1

```
Input: n = 8, source = (0,0), dest = (7,7)
Output: 6
Explanation: One possible path: (0,0) → (2,1) → (4,2) → (6,3) → (7,5) → (5,6) → (7,7)
```

### Example 2

```
Input: n = 5, source = (0,0), dest = (4,4)  
Output: 4
Explanation: Shortest path requires 4 knight moves
```

## Notes

- BFS guarantees minimum moves since all moves have equal weight
- Knight's move pattern creates 8 possible directions
- For infinite board, use pruning to avoid exploring too far from target
- Can optimize using bidirectional BFS for very large distances

## Related Problems

- [Minimum Knight Moves](https://leetcode.com/problems/minimum-knight-moves/) - LeetCode 1197
- [Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/) - LeetCode 688
- [Word Ladder](https://leetcode.com/problems/word-ladder/) - LeetCode 127 (similar BFS shortest path)

## LeetCode Links

- [Minimum Knight Moves](https://leetcode.com/problems/minimum-knight-moves/) - LeetCode 1197 (Premium)

## Pattern: 02-Breadth-First-Search-BFS

This problem exemplifies using BFS for shortest path in unweighted graphs. The chessboard positions are nodes, knight moves are edges, and BFS finds the minimum number of moves (shortest path) to reach the destination.
