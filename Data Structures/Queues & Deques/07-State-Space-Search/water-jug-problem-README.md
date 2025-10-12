# Water Jug Problem

## Problem Description
You are given two jugs with capacities `jug1Capacity` and `jug2Capacity` liters. There is an infinite amount of water supply available. Determine whether it is possible to measure exactly `targetCapacity` liters using these two jugs.

Operations allowed:
- Fill any of the jugs with water completely
- Empty any of the jugs completely
- Pour water from one jug into another until the destination jug is full or the source jug is empty

## Approach
This is a classic state-space search problem where each state represents the current water levels in both jugs. We use BFS to explore all possible states until we find the target capacity.

**Key insights:**
1. **State representation**: (water_in_jug1, water_in_jug2)
2. **Six possible operations** from any state
3. **Mathematical optimization**: Can use GCD theorem for early termination
4. **Visited tracking**: Avoid revisiting same states

## Algorithm Steps
1. **Check mathematical possibility**: Target must be achievable using GCD
2. **Initialize BFS** with state (0, 0)
3. **For each state**: Apply all 6 possible operations
4. **Track visited states** to avoid cycles
5. **Return true** when target capacity is found in either jug

## Implementation

### Approach 1: BFS State-Space Search
```cpp
#include <queue>
#include <unordered_set>
#include <string>

class Solution {
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        // Early termination checks
        if (targetCapacity > jug1Capacity + jug2Capacity) {
            return false;
        }
        if (targetCapacity == 0) {
            return true;
        }
        
        queue<pair<int, int>> q;
        unordered_set<string> visited;
        
        q.push({0, 0});
        visited.insert("0,0");
        
        while (!q.empty()) {
            auto [jug1, jug2] = q.front();
            q.pop();
            
            // Check if target is reached
            if (jug1 == targetCapacity || jug2 == targetCapacity || 
                jug1 + jug2 == targetCapacity) {
                return true;
            }
            
            // Generate all possible next states
            vector<pair<int, int>> nextStates = {
                // Fill jug1 completely
                {jug1Capacity, jug2},
                // Fill jug2 completely
                {jug1, jug2Capacity},
                // Empty jug1
                {0, jug2},
                // Empty jug2
                {jug1, 0},
                // Pour jug1 into jug2
                {max(0, jug1 - (jug2Capacity - jug2)), 
                 min(jug2Capacity, jug1 + jug2)},
                // Pour jug2 into jug1
                {min(jug1Capacity, jug1 + jug2), 
                 max(0, jug2 - (jug1Capacity - jug1))}
            };
            
            for (auto [nextJug1, nextJug2] : nextStates) {
                string state = to_string(nextJug1) + "," + to_string(nextJug2);
                
                if (visited.find(state) == visited.end()) {
                    visited.insert(state);
                    q.push({nextJug1, nextJug2});
                }
            }
        }
        
        return false;
    }
};
```

### Approach 2: Mathematical Solution (GCD)
```cpp
class Solution {
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        // Mathematical approach using Bezout's identity
        // ax + by = gcd(a,b) has integer solutions
        // We can measure any multiple of gcd(jug1, jug2)
        
        if (targetCapacity > jug1Capacity + jug2Capacity) {
            return false;
        }
        
        if (targetCapacity == 0) {
            return true;
        }
        
        int gcdValue = gcd(jug1Capacity, jug2Capacity);
        return targetCapacity % gcdValue == 0;
    }
    
private:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};
```

### Approach 3: Optimized BFS with Early Mathematical Check
```cpp
class Solution {
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        // Quick mathematical check first
        if (targetCapacity > jug1Capacity + jug2Capacity) {
            return false;
        }
        if (targetCapacity == 0) {
            return true;
        }
        
        int gcdValue = gcd(jug1Capacity, jug2Capacity);
        if (targetCapacity % gcdValue != 0) {
            return false;
        }
        
        // If mathematically possible, use BFS for verification
        return bfsSearch(jug1Capacity, jug2Capacity, targetCapacity);
    }
    
private:
    bool bfsSearch(int cap1, int cap2, int target) {
        queue<pair<int, int>> q;
        unordered_set<long long> visited;
        
        q.push({0, 0});
        visited.insert(0);
        
        while (!q.empty()) {
            auto [j1, j2] = q.front();
            q.pop();
            
            if (j1 == target || j2 == target || j1 + j2 == target) {
                return true;
            }
            
            vector<pair<int, int>> nextStates = {
                {cap1, j2},           // Fill jug1
                {j1, cap2},           // Fill jug2
                {0, j2},              // Empty jug1
                {j1, 0},              // Empty jug2
                {max(0, j1 - (cap2 - j2)), min(cap2, j1 + j2)}, // Pour j1->j2
                {min(cap1, j1 + j2), max(0, j2 - (cap1 - j1))}  // Pour j2->j1
            };
            
            for (auto [next1, next2] : nextStates) {
                long long state = (long long)next1 * 10000 + next2;
                if (visited.find(state) == visited.end()) {
                    visited.insert(state);
                    q.push({next1, next2});
                }
            }
        }
        
        return false;
    }
    
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};
```

### Time Complexity
- **BFS Approach**: O(jug1Capacity × jug2Capacity) - maximum possible states
- **GCD Approach**: O(log(min(jug1Capacity, jug2Capacity))) - for GCD calculation
- **Hybrid Approach**: O(log(min(cap1, cap2))) for GCD + O(cap1 × cap2) for BFS if needed

### Space Complexity
- **BFS Approach**: O(jug1Capacity × jug2Capacity) for visited states
- **GCD Approach**: O(1) - constant space
- **Hybrid Approach**: O(jug1Capacity × jug2Capacity) in worst case

## Examples

### Example 1
```
Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
Output: true
Explanation: 
- Fill jug2 (0, 5)
- Pour jug2 into jug1 (3, 2)
- Empty jug1 (0, 2)
- Pour jug2 into jug1 (2, 0)
- Fill jug2 (2, 5)
- Pour jug2 into jug1 (3, 4) ← Target reached!
```

### Example 2
```
Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
Output: false
Explanation: GCD(2, 6) = 2, and 5 % 2 ≠ 0, so it's impossible.
```

## Key Insights

### Queue Pattern Usage
- **State-space exploration**: Each water level combination is a state
- **Systematic search**: BFS ensures all reachable states are explored
- **Optimal solution**: BFS finds minimum steps if needed

### Mathematical Optimization
- **Bezout's Identity**: For integers a, b, equation ax + by = c has solution iff gcd(a,b) divides c
- **Early termination**: Check mathematical feasibility before BFS
- **Reduced search space**: Mathematical insights prevent unnecessary exploration

### State Representation
- **Compact encoding**: Use string or integer encoding for visited states
- **Operation enumeration**: Six possible operations from any state
- **Boundary handling**: Ensure operations respect jug capacities

## Related Problems
- Minimum Genetic Mutation
- Word Ladder
- 8-Puzzle Problem
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
