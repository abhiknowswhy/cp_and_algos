# Jump Game Problems

## Problem Description
This document covers multiple jump game problems that can be solved using **State-Space Search** with BFS/Queue.

### Jump Game I (Can Reach End)
Given an array of non-negative integers `nums`, you are initially positioned at the **first index**. Each element represents your maximum jump length at that position. Determine if you are able to reach the last index.

### Jump Game II (Minimum Jumps)
Given an array of non-negative integers `nums`, find the minimum number of jumps to reach the last index.

**LeetCode Links:**
- [55. Jump Game](https://leetcode.com/problems/jump-game/)
- [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)

## Approach
These problems can be solved using **BFS** (for guaranteed minimum jumps) or **Greedy** approaches. The BFS approach treats each position as a state and explores reachable positions level by level.

**Key Insight:** Use BFS to find the minimum number of jumps needed to reach the end position.

## Algorithm Steps
1. Use BFS with queue to explore positions level by level
2. For each position, add all reachable positions to next level
3. Track visited positions to avoid cycles
4. Return level when end position is reached

## Implementation

### C++ - Jump Game I (BFS)
```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() <= 1) return true;
        
        int n = nums.size();
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(0);
        visited[0] = true;
        
        while (!q.empty()) {
            int pos = q.front();
            q.pop();
            
            // Try all possible jumps from current position
            for (int jump = 1; jump <= nums[pos]; jump++) {
                int nextPos = pos + jump;
                
                if (nextPos >= n - 1) {
                    return true; // Reached or passed the end
                }
                
                if (!visited[nextPos]) {
                    visited[nextPos] = true;
                    q.push(nextPos);
                }
            }
        }
        
        return false;
    }
};
```

### C++ - Jump Game II (BFS)
```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        
        int n = nums.size();
        vector<bool> visited(n, false);
        queue<int> q;
        
        q.push(0);
        visited[0] = true;
        int jumps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            jumps++;
            
            for (int i = 0; i < size; i++) {
                int pos = q.front();
                q.pop();
                
                // Try all possible jumps
                for (int jump = 1; jump <= nums[pos]; jump++) {
                    int nextPos = pos + jump;
                    
                    if (nextPos >= n - 1) {
                        return jumps; // Reached the end
                    }
                    
                    if (!visited[nextPos]) {
                        visited[nextPos] = true;
                        q.push(nextPos);
                    }
                }
            }
        }
        
        return -1; // Cannot reach the end
    }
};
```

### C++ - Greedy Approach (More Efficient)
```cpp
class Solution {
public:
    // Jump Game I - Greedy
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > maxReach) return false;
            maxReach = max(maxReach, i + nums[i]);
        }
        return true;
    }
    
    // Jump Game II - Greedy
    int jump(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        
        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;
        
        for (int i = 0; i < nums.size() - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
            }
        }
        
        return jumps;
    }
};
```

### Time Complexity
- **BFS Approach:** O(n²) in worst case - May visit each position multiple times
- **Greedy Approach:** O(n) - Single pass through array

### Space Complexity
- **BFS:** O(n) - Queue and visited array
- **Greedy:** O(1) - Only variables

## Examples

### Example 1 (Jump Game I)
```
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

### Example 2 (Jump Game II)
```
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: Minimum jumps: 0 -> 1 -> 4 (2 jumps)
```

## Notes
- **BFS guarantees minimum:** Level-by-level exploration ensures minimum jumps
- **Greedy is more efficient:** O(n) time vs O(n²) for BFS
- **State space:** Each array position represents a state
- **Transitions:** Jump lengths define valid state transitions

## Related Problems
- [LeetCode 1306: Jump Game III](https://leetcode.com/problems/jump-game-iii/)
- [LeetCode 1345: Jump Game IV](https://leetcode.com/problems/jump-game-iv/)
- [LeetCode 1696: Jump Game VI](https://leetcode.com/problems/jump-game-vi/)

## Pattern: 07-State-Space-Search
Jump Game problems demonstrate **State-Space Search** where:
- **State representation:** Each array index represents a game state
- **State transitions:** Jump lengths determine valid moves between states
- **Goal-oriented search:** BFS finds shortest path to target state (end position)
- **Level-by-level exploration:** BFS guarantees minimum number of moves
