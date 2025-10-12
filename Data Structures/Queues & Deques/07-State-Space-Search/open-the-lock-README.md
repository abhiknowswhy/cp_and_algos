# Open the Lock

## Problem Description
You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: `'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'`. The wheels can rotate freely and wrap around: for example we can turn `'9'` to be `'0'`, or `'0'` to be `'9'`. Each move consists of turning one wheel one slot.

The lock initially starts at `'0000'`, a string representing the state of the 4 wheels.

You are given a list of `deadends` dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a `target` representing the value of the wheels that will unlock the lock, return the minimum number of turns required to open the lock, or -1 if it is impossible.

**LeetCode Link:** [752. Open the Lock](https://leetcode.com/problems/open-the-lock/)

## Approach
This is a classic **State-Space Search** problem that can be solved using **BFS**. Each state represents a 4-digit combination, and we need to find the shortest path from "0000" to the target while avoiding deadends.

**Key Insight:** Use BFS to explore all possible states level by level, ensuring we find the minimum number of moves.

## Algorithm Steps
1. Handle edge cases (target is deadend or starting position)
2. Use BFS with queue to explore states level by level
3. For each state, generate all possible next states (8 possibilities)
4. Skip visited states and deadends
5. Return level when target is reached, or -1 if impossible

## Implementation

### C++ - BFS Approach
```cpp
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadSet(deadends.begin(), deadends.end());
        
        // Check if start or target is in deadends
        if (deadSet.count("0000") || deadSet.count(target)) {
            return -1;
        }
        
        // Special case
        if (target == "0000") return 0;
        
        queue<string> q;
        unordered_set<string> visited;
        
        q.push("0000");
        visited.insert("0000");
        
        int moves = 0;
        
        while (!q.empty()) {
            int size = q.size();
            moves++;
            
            for (int i = 0; i < size; i++) {
                string current = q.front();
                q.pop();
                
                // Generate all possible next states
                for (int pos = 0; pos < 4; pos++) {
                    char originalChar = current[pos];
                    
                    // Try rotating up
                    current[pos] = (originalChar == '9') ? '0' : originalChar + 1;
                    if (current == target) return moves;
                    if (!visited.count(current) && !deadSet.count(current)) {
                        visited.insert(current);
                        q.push(current);
                    }
                    
                    // Try rotating down
                    current[pos] = (originalChar == '0') ? '9' : originalChar - 1;
                    if (current == target) return moves;
                    if (!visited.count(current) && !deadSet.count(current)) {
                        visited.insert(current);
                        q.push(current);
                    }
                    
                    // Restore original character
                    current[pos] = originalChar;
                }
            }
        }
        
        return -1;
    }
};
```

### C++ - Bidirectional BFS (Optimized)
```cpp
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadSet(deadends.begin(), deadends.end());
        
        if (deadSet.count("0000") || deadSet.count(target)) {
            return -1;
        }
        
        if (target == "0000") return 0;
        
        unordered_set<string> visited;
        unordered_set<string> beginSet = {"0000"};
        unordered_set<string> endSet = {target};
        
        int moves = 0;
        
        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand the smaller set
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextSet;
            moves++;
            
            for (const string& current : beginSet) {
                for (int pos = 0; pos < 4; pos++) {
                    char originalChar = current[pos];
                    
                    // Try both directions
                    for (int dir = -1; dir <= 1; dir += 2) {
                        string next = current;
                        next[pos] = (originalChar - '0' + dir + 10) % 10 + '0';
                        
                        if (endSet.count(next)) {
                            return moves;
                        }
                        
                        if (!visited.count(next) && !deadSet.count(next)) {
                            visited.insert(next);
                            nextSet.insert(next);
                        }
                    }
                }
            }
            
            beginSet = nextSet;
        }
        
        return -1;
    }
};
```

### Time Complexity
- **BFS:** O(10^4) = O(10000) - At most 10^4 possible states
- **Bidirectional BFS:** O(10^2) = O(100) in best case - Meet in middle

### Space Complexity
- **Both approaches:** O(10^4) for visited set and queue

## Examples

### Example 1
```
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation: 
"0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"
```

### Example 2
```
Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation: 
"0000" -> "0009"
```

### Example 3
```
Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation: Cannot reach target because it's surrounded by deadends.
```

## Notes
- **State representation:** Each 4-digit string represents a lock state
- **Move generation:** Each position can be rotated up or down (8 total moves per state)
- **Deadend handling:** Skip states that are in deadends set
- **Optimization:** Bidirectional BFS reduces search space significantly

## Related Problems
- [LeetCode 127: Word Ladder](https://leetcode.com/problems/word-ladder/)
- [LeetCode 433: Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/)
- [LeetCode 815: Bus Routes](https://leetcode.com/problems/bus-routes/)

## Pattern: 07-State-Space-Search
This problem exemplifies **State-Space Search** where:
- **State representation:** Each lock combination is a state in the search space
- **State transitions:** Moving from one state to adjacent states via wheel rotations
- **Goal-oriented search:** BFS finds shortest path from start state to goal state
- **Constraint handling:** Deadends act as forbidden states in the search space
