# Jump Game IV - BFS Shortest Path in Array
**LeetCode 1345: Jump Game IV**

## Problem Description
Given an array of integers `arr`, you are initially positioned at the first index of the array. In one step you can jump from index `i` to index:
- `i + 1` where: `i + 1 < arr.length`
- `i - 1` where: `i - 1 >= 0`
- `j` where: `arr[i] == arr[j]` and `i != j`

Return the minimum number of steps to reach the last index of the array.

**Test cases guarantee that you can reach the last index.**

## Multiple Approaches

### Approach 1: Basic BFS with Queue
```cpp
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;
        
        // Build graph of same value indices
        unordered_map<int, vector<int>> graph;
        for (int i = 0; i < n; i++) {
            graph[arr[i]].push_back(i);
        }
        
        queue<int> bfs;
        unordered_set<int> visited;
        bfs.push(0);
        visited.insert(0);
        
        int steps = 0;
        while (!bfs.empty()) {
            int size = bfs.size();
            for (int i = 0; i < size; i++) {
                int curr = bfs.front();
                bfs.pop();
                
                if (curr == n - 1) return steps;
                
                // Jump to adjacent indices
                vector<int> neighbors = {curr - 1, curr + 1};
                
                // Jump to same value indices
                if (graph.count(arr[curr])) {
                    for (int next : graph[arr[curr]]) {
                        neighbors.push_back(next);
                    }
                    // Clear to avoid revisiting
                    graph.erase(arr[curr]);
                }
                
                for (int next : neighbors) {
                    if (next >= 0 && next < n && !visited.count(next)) {
                        visited.insert(next);
                        bfs.push(next);
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};
```

### Approach 2: Optimized BFS with Early Termination
```cpp
class SolutionOptimized {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;
        if (n == 2) return 1;
        
        // Special case: if first and last elements are same
        if (arr[0] == arr[n-1]) return 1;
        
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; i++) {
            valueToIndices[arr[i]].push_back(i);
        }
        
        queue<int> q;
        vector<bool> visited(n, false);
        q.push(0);
        visited[0] = true;
        
        int steps = 0;
        while (!q.empty()) {
            steps++;
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                int curr = q.front();
                q.pop();
                
                // Check adjacent positions
                for (int next : {curr - 1, curr + 1}) {
                    if (next == n - 1) return steps;
                    if (next >= 0 && next < n && !visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
                
                // Check same value positions
                if (valueToIndices.count(arr[curr])) {
                    for (int next : valueToIndices[arr[curr]]) {
                        if (next == n - 1) return steps;
                        if (!visited[next]) {
                            visited[next] = true;
                            q.push(next);
                        }
                    }
                    // Remove to avoid future processing
                    valueToIndices.erase(arr[curr]);
                }
            }
        }
        return -1;
    }
};
```

### Approach 3: Bidirectional BFS
```cpp
class SolutionBidirectional {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;
        
        unordered_map<int, vector<int>> graph;
        for (int i = 0; i < n; i++) {
            graph[arr[i]].push_back(i);
        }
        
        unordered_set<int> head{0}, tail{n-1}, visited;
        int steps = 0;
        
        while (!head.empty() && !tail.empty()) {
            // Always search from smaller set
            if (head.size() > tail.size()) {
                swap(head, tail);
            }
            
            unordered_set<int> temp;
            steps++;
            
            for (int curr : head) {
                // Check adjacent positions
                for (int next : {curr - 1, curr + 1}) {
                    if (tail.count(next)) return steps;
                    if (next >= 0 && next < n && !visited.count(next)) {
                        visited.insert(next);
                        temp.insert(next);
                    }
                }
                
                // Check same value positions
                if (graph.count(arr[curr])) {
                    for (int next : graph[arr[curr]]) {
                        if (tail.count(next)) return steps;
                        if (!visited.count(next)) {
                            visited.insert(next);
                            temp.insert(next);
                        }
                    }
                    graph.erase(arr[curr]);
                }
            }
            head = temp;
        }
        return -1;
    }
};
```

### Approach 4: Memory-Optimized BFS
```cpp
class SolutionMemoryOptimized {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;
        
        // Use compact representation for same values
        unordered_map<int, vector<int>> sameValue;
        for (int i = 0; i < n; i++) {
            if (sameValue[arr[i]].size() < 2) {
                sameValue[arr[i]].push_back(i);
            } else if (i == n - 1) {
                sameValue[arr[i]].push_back(i);
            }
        }
        
        queue<pair<int, int>> q; // {index, steps}
        vector<bool> visited(n, false);
        q.push({0, 0});
        visited[0] = true;
        
        while (!q.empty()) {
            auto [curr, steps] = q.front();
            q.pop();
            
            if (curr == n - 1) return steps;
            
            // Adjacent moves
            for (int next : {curr - 1, curr + 1}) {
                if (next >= 0 && next < n && !visited[next]) {
                    visited[next] = true;
                    q.push({next, steps + 1});
                }
            }
            
            // Same value moves
            for (int next : sameValue[arr[curr]]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push({next, steps + 1});
                }
            }
            sameValue[arr[curr]].clear(); // Prevent revisit
        }
        return -1;
    }
};
```

## Complexity Analysis

**Time Complexity:**
- **Basic BFS**: O(N) where N is array length
- **Optimized BFS**: O(N) with better constants
- **Bidirectional BFS**: O(N) but typically faster in practice
- **Memory-Optimized**: O(N) with reduced memory usage

**Space Complexity:**
- **Basic BFS**: O(N) for visited set and graph
- **Optimized BFS**: O(N) for queue and visited array
- **Bidirectional BFS**: O(N) for two sets
- **Memory-Optimized**: O(N) with optimized graph representation

## Example Walkthrough

### Example 1
```
Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: 
- Start at index 0 (value 100)
- Jump to index 4 (same value 100) → 1 step
- Jump to index 3 (adjacent to 4) → 2 steps
- Jump to index 9 (same value 404) → 3 steps
```

### Example 2
```
Input: arr = [7]
Output: 0
Explanation: Start index is the last index
```

### Example 3
```
Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: Jump from index 0 to index 7 (same value 7)
```

## Key Optimization Techniques

### 1. Graph Pruning
```cpp
// After visiting all nodes with same value, remove the entry
graph.erase(arr[curr]);
```

### 2. Early Termination
```cpp
// Check if we can reach target immediately
if (next == n - 1) return steps;
```

### 3. Bidirectional Search
```cpp
// Search from both ends to reduce search space
if (head.size() > tail.size()) {
    swap(head, tail);
}
```

## Real-World Applications

### 1. Network Routing Optimization
```cpp
class NetworkRouter {
private:
    vector<int> linkQuality;
    unordered_map<int, vector<int>> sameQualityLinks;
    
public:
    int findOptimalPath(int source, int destination) {
        // Similar BFS approach for network routing
        // where same quality links allow instant switching
        return minJumps(linkQuality);
    }
};
```

### 2. Game Level Progression
```cpp
class GameLevelManager {
private:
    vector<int> levelDifficulty;
    
public:
    int minMovesToCompleteGame(int startLevel, int endLevel) {
        // Players can jump between levels of same difficulty
        // or move to adjacent levels
        return minJumps(levelDifficulty);
    }
};
```

### 3. Resource Allocation System
```cpp
class ResourceAllocator {
private:
    vector<int> resourceTypes;
    
public:
    int minTransfersToTarget(int currentResource, int targetResource) {
        // Resources of same type can be transferred instantly
        // Adjacent resources require one transfer operation
        return minJumps(resourceTypes);
    }
};
```

## Advanced Features

### 1. Path Reconstruction
```cpp
class SolutionWithPath {
public:
    pair<int, vector<int>> minJumpsWithPath(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return {0, {0}};
        
        unordered_map<int, vector<int>> graph;
        for (int i = 0; i < n; i++) {
            graph[arr[i]].push_back(i);
        }
        
        queue<int> q;
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);
        
        q.push(0);
        visited[0] = true;
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int curr = q.front();
                q.pop();
                
                if (curr == n - 1) {
                    // Reconstruct path
                    vector<int> path;
                    int node = n - 1;
                    while (node != -1) {
                        path.push_back(node);
                        node = parent[node];
                    }
                    reverse(path.begin(), path.end());
                    return {steps, path};
                }
                
                // Process neighbors
                vector<int> neighbors = {curr - 1, curr + 1};
                if (graph.count(arr[curr])) {
                    for (int next : graph[arr[curr]]) {
                        neighbors.push_back(next);
                    }
                    graph.erase(arr[curr]);
                }
                
                for (int next : neighbors) {
                    if (next >= 0 && next < n && !visited[next]) {
                        visited[next] = true;
                        parent[next] = curr;
                        q.push(next);
                    }
                }
            }
            steps++;
        }
        return {-1, {}};
    }
};
```

### 2. Performance Benchmarking
```cpp
#include <chrono>
#include <random>

class PerformanceTester {
public:
    static void benchmarkSolutions() {
        vector<int> sizes = {100, 1000, 10000, 50000};
        
        for (int n : sizes) {
            vector<int> arr = generateTestCase(n);
            
            auto start = chrono::high_resolution_clock::now();
            Solution().minJumps(arr);
            auto end = chrono::high_resolution_clock::now();
            
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Size " << n << ": " << duration.count() << " microseconds\n";
        }
    }
    
private:
    static vector<int> generateTestCase(int n) {
        vector<int> arr(n);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, n/10);
        
        for (int i = 0; i < n; i++) {
            arr[i] = dis(gen);
        }
        return arr;
    }
};
```

## Testing Framework
```cpp
#include <cassert>

class TestSuite {
public:
    static void runAllTests() {
        testBasicCases();
        testEdgeCases();
        testPerformance();
        cout << "All tests passed!\n";
    }
    
private:
    static void testBasicCases() {
        Solution sol;
        
        // Test case 1
        vector<int> arr1 = {100,-23,-23,404,100,23,23,23,3,404};
        assert(sol.minJumps(arr1) == 3);
        
        // Test case 2
        vector<int> arr2 = {7};
        assert(sol.minJumps(arr2) == 0);
        
        // Test case 3
        vector<int> arr3 = {7,6,9,6,9,6,9,7};
        assert(sol.minJumps(arr3) == 1);
    }
    
    static void testEdgeCases() {
        Solution sol;
        
        // Two elements
        vector<int> arr1 = {1, 2};
        assert(sol.minJumps(arr1) == 1);
        
        // All same elements
        vector<int> arr2 = {5, 5, 5, 5, 5};
        assert(sol.minJumps(arr2) == 1);
        
        // Ascending order
        vector<int> arr3 = {1, 2, 3, 4, 5};
        assert(sol.minJumps(arr3) == 4);
    }
    
    static void testPerformance() {
        // Test with large arrays
        PerformanceTester::benchmarkSolutions();
    }
};
```

## Pattern Analysis: Matrix-Grid-BFS

This problem exemplifies the **Matrix-Grid-BFS** pattern because:

1. **State Space**: Each array index represents a node in a graph
2. **Transitions**: Three types of moves create edges between nodes
3. **Shortest Path**: BFS guarantees minimum steps to reach target
4. **Level-by-Level**: Process all nodes at distance k before distance k+1

### Key Pattern Elements:
- **Queue-based exploration** for level-order traversal
- **Visited tracking** to prevent cycles
- **Graph construction** for same-value connections
- **Early termination** when target is reached

### Pattern Variations:
- **Bidirectional BFS**: Search from both ends
- **A\* Algorithm**: Use heuristics for faster search
- **Dijkstra's Algorithm**: When edges have different weights

## Related Problems
- **LeetCode 45**: Jump Game II
- **LeetCode 55**: Jump Game
- **LeetCode 1306**: Jump Game III
- **LeetCode 127**: Word Ladder
- **LeetCode 773**: Sliding Puzzle

## Tags
`BFS` `Queue` `Graph` `Array` `Shortest Path` `Dynamic Programming`
