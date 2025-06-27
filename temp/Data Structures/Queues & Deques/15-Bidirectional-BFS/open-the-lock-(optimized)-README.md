# Open the Lock (Optimized)

## Problem Description

**LeetCode Problem #752 - Medium**
🔗 [LeetCode Link](https://leetcode.com/problems/open-the-lock/)

You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: `'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'`. The wheels can rotate freely and wrap around: for example after `'9'` the next slot is `'0'`, and after `'0'` the previous slot is `'9'`. Each move consists of turning one wheel one slot.

The lock initially starts at `'0000'`, a string representing the state of the 4 wheels.

You are given a list of `deadends` dead ends, meaning if the lock displays any of these codes, the wheels of the lock will be locked and you will be unable to turn them.

Given a `target` representing the value of the wheels that will unlock the lock, return the minimum number of turns required to open the lock, or -1 if it is impossible.

**Key Constraints:**
- `1 <= deadends.length <= 500`
- `deadends[i].length == 4`
- `target.length == 4`
- `target` will not be in the list of `deadends`
- `target` and `deadends[i]` consist of digits only

## Queue Pattern Connection

This problem demonstrates **Optimized Bidirectional BFS** patterns where:
- Search from both start ('0000') and target simultaneously
- Two frontiers meet in the middle for optimal performance
- Exponential search space reduction compared to unidirectional BFS
- State space exploration with constraint handling (deadends)
- Pattern applies to shortest path problems in large discrete spaces

## Approach

### Approach 1: Bidirectional BFS (Optimal)
Search from both start and target simultaneously, always expanding the smaller frontier.

### Approach 2: Standard BFS with Pruning
Single direction BFS with early termination optimizations.

### Approach 3: A* Search with Manhattan Distance
Use heuristic to guide search toward target.

### Approach 4: Dijkstra's Algorithm
Treat as weighted graph where all edges have weight 1.

### Approach 5: IDA* (Iterative Deepening A*)
Memory-efficient search with iterative depth limits.

## Algorithm Steps

### Bidirectional BFS Approach:
1. **Initialize**: Create forward and backward search frontiers
2. **Setup**: Add start to forward, target to backward, mark deadends as visited
3. **Alternating Search**: Always expand the smaller frontier
4. **Generate Neighbors**: For each combination, generate 8 possible moves (4 wheels × 2 directions)
5. **Check Intersection**: If a state appears in opposite frontier, return total steps
6. **Pruning**: Skip deadends and already visited states
7. **Terminate**: Return -1 if both frontiers become empty

## Implementation

### Implementation 1: Optimal Bidirectional BFS

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <algorithm>

class LockOptimizer {
public:
    /**
     * Find minimum turns using Bidirectional BFS
     * Time: O(10^4) = O(1) since state space is bounded
     * Space: O(10^4) = O(1) for the same reason
     */
    int openLock(std::vector<std::string>& deadends, std::string target) {
        if (target == "0000") return 0;
        
        std::unordered_set<std::string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count("0000") || deadSet.count(target)) return -1;
        
        std::unordered_set<std::string> visitedStart{"0000"};
        std::unordered_set<std::string> visitedEnd{target};
        
        std::queue<std::string> queueStart;
        std::queue<std::string> queueEnd;
        queueStart.push("0000");
        queueEnd.push(target);
        
        int steps = 0;
        
        while (!queueStart.empty() && !queueEnd.empty()) {
            steps++;
            
            // Always expand smaller frontier for optimization
            if (queueStart.size() > queueEnd.size()) {
                std::swap(queueStart, queueEnd);
                std::swap(visitedStart, visitedEnd);
            }
            
            int size = queueStart.size();
            
            for (int i = 0; i < size; i++) {
                std::string current = queueStart.front();
                queueStart.pop();
                
                // Generate all 8 possible neighbors
                std::vector<std::string> neighbors = generateNeighbors(current);
                
                for (const std::string& neighbor : neighbors) {
                    if (deadSet.count(neighbor)) continue;
                    
                    // Check if found intersection
                    if (visitedEnd.count(neighbor)) {
                        return steps;
                    }
                    
                    // Add to current search if not visited
                    if (!visitedStart.count(neighbor)) {
                        visitedStart.insert(neighbor);
                        queueStart.push(neighbor);
                    }
                }
            }
        }
        
        return -1;  // No solution found
    }
    
private:
    std::vector<std::string> generateNeighbors(const std::string& current) {
        std::vector<std::string> neighbors;
        neighbors.reserve(8);  // 4 wheels × 2 directions
        
        for (int i = 0; i < 4; i++) {
            // Rotate wheel i up
            std::string up = current;
            up[i] = (up[i] == '9') ? '0' : (char)(up[i] + 1);
            neighbors.push_back(up);
            
            // Rotate wheel i down
            std::string down = current;
            down[i] = (down[i] == '0') ? '9' : (char)(down[i] - 1);
            neighbors.push_back(down);
        }
        
        return neighbors;
    }
    
public:
    // Analysis method to track search statistics
    struct SearchStats {
        int totalStatesExplored;
        int frontierSwitches;
        int maxFrontierSize;
        double averageBranchingFactor;
    };
    
    SearchStats analyzeSearch(std::vector<std::string>& deadends, std::string target) {
        SearchStats stats = {0, 0, 0, 0.0};
        
        // Implementation would track statistics during search
        return stats;
    }
};
```

### Implementation 2: Standard BFS with Advanced Optimizations

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

class LockOptimizerAdvanced {
public:
    int openLock(std::vector<std::string>& deadends, std::string target) {
        if (target == "0000") return 0;
        
        std::unordered_set<std::string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count("0000") || deadSet.count(target)) return -1;
        
        // Use distance map for path reconstruction
        std::unordered_map<std::string, int> distance;
        std::queue<std::string> queue;
        
        queue.push("0000");
        distance["0000"] = 0;
        
        while (!queue.empty()) {
            std::string current = queue.front();
            queue.pop();
            
            if (current == target) {
                return distance[current];
            }
            
            std::vector<std::string> neighbors = generateNeighbors(current);
            
            for (const std::string& neighbor : neighbors) {
                if (deadSet.count(neighbor) || distance.count(neighbor)) {
                    continue;
                }
                
                distance[neighbor] = distance[current] + 1;
                queue.push(neighbor);
                
                // Early termination optimization
                if (neighbor == target) {
                    return distance[neighbor];
                }
            }
        }
        
        return -1;
    }
    
    // Path reconstruction functionality
    std::vector<std::string> findPath(std::vector<std::string>& deadends, std::string target) {
        if (target == "0000") return {"0000"};
        
        std::unordered_set<std::string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count("0000") || deadSet.count(target)) return {};
        
        std::unordered_map<std::string, std::string> parent;
        std::unordered_map<std::string, int> distance;
        std::queue<std::string> queue;
        
        queue.push("0000");
        distance["0000"] = 0;
        parent["0000"] = "";
        
        while (!queue.empty()) {
            std::string current = queue.front();
            queue.pop();
            
            if (current == target) {
                // Reconstruct path
                std::vector<std::string> path;
                std::string node = target;
                
                while (node != "") {
                    path.push_back(node);
                    node = parent[node];
                }
                
                std::reverse(path.begin(), path.end());
                return path;
            }
            
            std::vector<std::string> neighbors = generateNeighbors(current);
            
            for (const std::string& neighbor : neighbors) {
                if (deadSet.count(neighbor) || distance.count(neighbor)) {
                    continue;
                }
                
                distance[neighbor] = distance[current] + 1;
                parent[neighbor] = current;
                queue.push(neighbor);
            }
        }
        
        return {};
    }
    
private:
    std::vector<std::string> generateNeighbors(const std::string& current) {
        std::vector<std::string> neighbors;
        
        for (int i = 0; i < 4; i++) {
            // Up rotation
            std::string up = current;
            up[i] = (current[i] == '9') ? '0' : (char)(current[i] + 1);
            neighbors.push_back(up);
            
            // Down rotation
            std::string down = current;
            down[i] = (current[i] == '0') ? '9' : (char)(current[i] - 1);
            neighbors.push_back(down);
        }
        
        return neighbors;
    }
};
```

### Implementation 3: A* Search with Heuristic

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <priority_queue>
#include <unordered_map>
#include <cmath>

class LockAStar {
private:
    struct Node {
        std::string state;
        int gScore;  // Actual cost from start
        int fScore;  // gScore + heuristic
        
        bool operator>(const Node& other) const {
            return fScore > other.fScore;
        }
    };
    
    // Manhattan distance heuristic for lock combinations
    int manhattanDistance(const std::string& current, const std::string& target) {
        int distance = 0;
        
        for (int i = 0; i < 4; i++) {
            int currentDigit = current[i] - '0';
            int targetDigit = target[i] - '0';
            
            // Calculate minimum rotations needed (considering wrap-around)
            int clockwise = (targetDigit - currentDigit + 10) % 10;
            int counterclockwise = (currentDigit - targetDigit + 10) % 10;
            
            distance += std::min(clockwise, counterclockwise);
        }
        
        return distance;
    }
    
public:
    int openLock(std::vector<std::string>& deadends, std::string target) {
        if (target == "0000") return 0;
        
        std::unordered_set<std::string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count("0000") || deadSet.count(target)) return -1;
        
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::unordered_map<std::string, int> gScore;
        
        pq.push({"0000", 0, manhattanDistance("0000", target)});
        gScore["0000"] = 0;
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            if (current.state == target) {
                return current.gScore;
            }
            
            // Skip if we've found a better path
            if (gScore.count(current.state) && current.gScore > gScore[current.state]) {
                continue;
            }
            
            std::vector<std::string> neighbors = generateNeighbors(current.state);
            
            for (const std::string& neighbor : neighbors) {
                if (deadSet.count(neighbor)) continue;
                
                int tentativeGScore = current.gScore + 1;
                
                if (!gScore.count(neighbor) || tentativeGScore < gScore[neighbor]) {
                    gScore[neighbor] = tentativeGScore;
                    int fScore = tentativeGScore + manhattanDistance(neighbor, target);
                    pq.push({neighbor, tentativeGScore, fScore});
                }
            }
        }
        
        return -1;
    }
    
private:
    std::vector<std::string> generateNeighbors(const std::string& current) {
        std::vector<std::string> neighbors;
        
        for (int i = 0; i < 4; i++) {
            // Clockwise
            std::string cw = current;
            cw[i] = (current[i] == '9') ? '0' : (char)(current[i] + 1);
            neighbors.push_back(cw);
            
            // Counterclockwise
            std::string ccw = current;
            ccw[i] = (current[i] == '0') ? '9' : (char)(current[i] - 1);
            neighbors.push_back(ccw);
        }
        
        return neighbors;
    }
};
```

### Implementation 4: IDA* (Iterative Deepening A*)

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <climits>

class LockIDAStar {
private:
    std::unordered_set<std::string> deadSet;
    std::string target;
    
    int manhattanDistance(const std::string& current, const std::string& target) {
        int distance = 0;
        
        for (int i = 0; i < 4; i++) {
            int currentDigit = current[i] - '0';
            int targetDigit = target[i] - '0';
            
            int clockwise = (targetDigit - currentDigit + 10) % 10;
            int counterclockwise = (currentDigit - targetDigit + 10) % 10;
            
            distance += std::min(clockwise, counterclockwise);
        }
        
        return distance;
    }
    
    int search(const std::string& current, int gScore, int threshold, 
               std::unordered_set<std::string>& visited) {
        int fScore = gScore + manhattanDistance(current, target);
        
        if (fScore > threshold) return fScore;
        if (current == target) return -1;  // Found solution
        
        int minNextThreshold = INT_MAX;
        std::vector<std::string> neighbors = generateNeighbors(current);
        
        for (const std::string& neighbor : neighbors) {
            if (deadSet.count(neighbor) || visited.count(neighbor)) {
                continue;
            }
            
            visited.insert(neighbor);
            int result = search(neighbor, gScore + 1, threshold, visited);
            visited.erase(neighbor);
            
            if (result == -1) return -1;  // Solution found
            if (result < minNextThreshold) minNextThreshold = result;
        }
        
        return minNextThreshold;
    }
    
    std::vector<std::string> generateNeighbors(const std::string& current) {
        std::vector<std::string> neighbors;
        
        for (int i = 0; i < 4; i++) {
            std::string cw = current;
            cw[i] = (current[i] == '9') ? '0' : (char)(current[i] + 1);
            neighbors.push_back(cw);
            
            std::string ccw = current;
            ccw[i] = (current[i] == '0') ? '9' : (char)(current[i] - 1);
            neighbors.push_back(ccw);
        }
        
        return neighbors;
    }
    
public:
    int openLock(std::vector<std::string>& deadends, std::string target) {
        if (target == "0000") return 0;
        
        deadSet = std::unordered_set<std::string>(deadends.begin(), deadends.end());
        if (deadSet.count("0000") || deadSet.count(target)) return -1;
        
        this->target = target;
        
        int threshold = manhattanDistance("0000", target);
        std::unordered_set<std::string> visited;
        
        while (threshold != INT_MAX) {
            visited.clear();
            visited.insert("0000");
            
            int result = search("0000", 0, threshold, visited);
            
            if (result == -1) {
                // Solution found - reconstruct depth
                return threshold;
            }
            
            threshold = result;
        }
        
        return -1;
    }
};
```

### Implementation 5: Parallel Bidirectional BFS

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

class LockParallel {
private:
    std::atomic<bool> solutionFound{false};
    std::atomic<int> solutionSteps{-1};
    mutable std::mutex dataMutex;
    std::condition_variable cv;
    
    void searchDirection(std::queue<std::string>& queue,
                        std::unordered_set<std::string>& visited,
                        const std::unordered_set<std::string>& oppositeVisited,
                        const std::unordered_set<std::string>& deadSet,
                        int& steps) {
        while (!queue.empty() && !solutionFound.load()) {
            int size = queue.size();
            
            for (int i = 0; i < size && !solutionFound.load(); i++) {
                std::string current = queue.front();
                queue.pop();
                
                std::vector<std::string> neighbors = generateNeighbors(current);
                
                for (const std::string& neighbor : neighbors) {
                    if (deadSet.count(neighbor)) continue;
                    
                    // Check intersection (thread-safe)
                    {
                        std::lock_guard<std::mutex> lock(dataMutex);
                        if (oppositeVisited.count(neighbor)) {
                            solutionFound = true;
                            solutionSteps = steps + 1;
                            cv.notify_all();
                            return;
                        }
                    }
                    
                    // Add to current search
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        queue.push(neighbor);
                    }
                }
            }
            
            steps++;
        }
    }
    
    std::vector<std::string> generateNeighbors(const std::string& current) {
        std::vector<std::string> neighbors;
        
        for (int i = 0; i < 4; i++) {
            std::string cw = current;
            cw[i] = (current[i] == '9') ? '0' : (char)(current[i] + 1);
            neighbors.push_back(cw);
            
            std::string ccw = current;
            ccw[i] = (current[i] == '0') ? '9' : (char)(current[i] - 1);
            neighbors.push_back(ccw);
        }
        
        return neighbors;
    }
    
public:
    int openLock(std::vector<std::string>& deadends, std::string target) {
        if (target == "0000") return 0;
        
        std::unordered_set<std::string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count("0000") || deadSet.count(target)) return -1;
        
        std::unordered_set<std::string> visitedStart{"0000"};
        std::unordered_set<std::string> visitedEnd{target};
        
        std::queue<std::string> queueStart;
        std::queue<std::string> queueEnd;
        queueStart.push("0000");
        queueEnd.push(target);
        
        solutionFound = false;
        solutionSteps = -1;
        
        int stepsStart = 0, stepsEnd = 0;
        
        // Launch parallel searches
        std::thread forwardThread([&]() {
            searchDirection(queueStart, visitedStart, visitedEnd, deadSet, stepsStart);
        });
        
        std::thread backwardThread([&]() {
            searchDirection(queueEnd, visitedEnd, visitedStart, deadSet, stepsEnd);
        });
        
        // Wait for completion
        forwardThread.join();
        backwardThread.join();
        
        return solutionSteps.load();
    }
};
```

## Complexity Analysis

### Bidirectional BFS:
- **Time Complexity**: O(10^2) in practice, O(10^4) worst case
- **Space Complexity**: O(10^2) average case for frontiers
- **Advantage**: ~100x speedup over unidirectional BFS in worst case

### Standard BFS:
- **Time Complexity**: O(10^4) = O(1) since state space is bounded
- **Space Complexity**: O(10^4) = O(1) for visited set
- **State Space**: Exactly 10,000 possible combinations

### A* Search:
- **Time Complexity**: O(10^4 × log(10^4)) due to priority queue
- **Space Complexity**: O(10^4) for priority queue and visited set
- **Advantage**: Guided search reduces explored states

### IDA* Search:
- **Time Complexity**: O(10^4) but with better memory usage
- **Space Complexity**: O(depth) = O(20) linear space
- **Advantage**: Memory-optimal for deep searches

## Examples

### Example 1: Simple Case

```cpp
void example1() {
    LockOptimizer optimizer;
    
    std::vector<std::string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    std::string target = "0202";
    
    int result = optimizer.openLock(deadends, target);
    std::cout << "Minimum turns: " << result << std::endl;  // Output: 6
    
    // Show optimal path
    LockOptimizerAdvanced pathFinder;
    auto path = pathFinder.findPath(deadends, target);
    
    std::cout << "Optimal path: ";
    for (const auto& state : path) {
        std::cout << state << " -> ";
    }
    std::cout << "DONE" << std::endl;
}
```

### Example 2: Impossible Case

```cpp
void example2() {
    LockOptimizer optimizer;
    
    std::vector<std::string> deadends = {"8888"};
    std::string target = "0009";
    
    int result = optimizer.openLock(deadends, target);
    std::cout << "Minimum turns: " << result << std::endl;  // Output: 1
    
    // Explanation: 0000 -> 0009 (just turn last wheel once)
}
```

### Example 3: Blocked Start

```cpp
void example3() {
    LockOptimizer optimizer;
    
    std::vector<std::string> deadends = {"0000"};
    std::string target = "8888";
    
    int result = optimizer.openLock(deadends, target);
    std::cout << "Minimum turns: " << result << std::endl;  // Output: -1
    
    std::cout << "Cannot start - initial position is blocked!" << std::endl;
}
```

### Example 4: Algorithm Comparison Benchmark

```cpp
#include <chrono>

void algorithmComparison() {
    std::vector<std::string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    std::string target = "0202";
    
    // Test Bidirectional BFS
    auto start = std::chrono::high_resolution_clock::now();
    LockOptimizer bidirectional;
    int result1 = bidirectional.openLock(deadends, target);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test Standard BFS
    start = std::chrono::high_resolution_clock::now();
    LockOptimizerAdvanced standard;
    int result2 = standard.openLock(deadends, target);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test A* Search
    start = std::chrono::high_resolution_clock::now();
    LockAStar aStar;
    int result3 = aStar.openLock(deadends, target);
    end = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test IDA*
    start = std::chrono::high_resolution_clock::now();
    LockIDAStar idaStar;
    int result4 = idaStar.openLock(deadends, target);
    end = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "All results: " << result1 << ", " << result2 << ", " << result3 << ", " << result4 << std::endl;
    std::cout << "Bidirectional BFS: " << duration1.count() << " μs" << std::endl;
    std::cout << "Standard BFS: " << duration2.count() << " μs" << std::endl;
    std::cout << "A* Search: " << duration3.count() << " μs" << std::endl;
    std::cout << "IDA* Search: " << duration4.count() << " μs" << std::endl;
    
    std::cout << "Bidirectional speedup: " << (double)duration2.count() / duration1.count() << "x" << std::endl;
}
```

### Example 5: Memory Usage Analysis

```cpp
void memoryUsageAnalysis() {
    std::vector<std::string> deadends = {"0201", "0101", "0102", "1212", "2002"};
    std::string target = "0202";
    
    // Measure memory usage of different approaches
    size_t bidirectionalMemory = sizeof(std::unordered_set<std::string>) * 2 + 
                                 sizeof(std::queue<std::string>) * 2;
    
    size_t standardMemory = sizeof(std::unordered_set<std::string>) + 
                           sizeof(std::queue<std::string>) + 
                           sizeof(std::unordered_map<std::string, int>);
    
    size_t aStarMemory = sizeof(std::priority_queue<void*>) + 
                        sizeof(std::unordered_map<std::string, int>);
    
    std::cout << "Memory usage comparison:" << std::endl;
    std::cout << "Bidirectional BFS: ~" << bidirectionalMemory << " bytes base" << std::endl;
    std::cout << "Standard BFS: ~" << standardMemory << " bytes base" << std::endl;
    std::cout << "A* Search: ~" << aStarMemory << " bytes base" << std::endl;
    std::cout << "IDA*: ~" << sizeof(std::unordered_set<std::string>) << " bytes base (minimal)" << std::endl;
}
```

## Real-World Applications

### 1. **Physical Security Systems**

```cpp
class SecuritySystem {
private:
    LockOptimizer optimizer;
    
public:
    struct SecurityEvent {
        std::string currentCombination;
        std::string targetCombination;
        std::vector<std::string> attemptHistory;
        int timeToBreak;
        double securityLevel;
    };
    
    SecurityEvent analyzeBreakAttempt(const std::string& currentState,
                                     const std::string& targetState,
                                     const std::vector<std::string>& knownBadCombos) {
        SecurityEvent event;
        event.currentCombination = currentState;
        event.targetCombination = targetState;
        
        // Calculate minimum steps to break
        std::vector<std::string> deadends = knownBadCombos;
        event.timeToBreak = optimizer.openLock(deadends, targetState);
        
        // Calculate security level based on breaking difficulty
        if (event.timeToBreak == -1) {
            event.securityLevel = 1.0;  // Unbreakable
        } else {
            event.securityLevel = std::max(0.0, 1.0 - (double)event.timeToBreak / 20.0);
        }
        
        return event;
    }
    
    std::vector<std::string> generateSecureCombinations(int count) {
        std::vector<std::string> secureCombos;
        
        // Generate combinations that are far from common patterns
        std::vector<std::string> commonPatterns = {
            "0000", "1111", "2222", "3333", "4444", "5555",
            "6666", "7777", "8888", "9999", "1234", "4321"
        };
        
        for (int i = 0; i < 10000 && secureCombos.size() < count; i++) {
            std::string combo = std::to_string(i);
            combo = std::string(4 - combo.length(), '0') + combo;
            
            // Check if sufficiently far from common patterns
            bool isSecure = true;
            for (const auto& pattern : commonPatterns) {
                int distance = optimizer.openLock(std::vector<std::string>{}, combo);
                if (distance != -1 && distance < 5) {
                    isSecure = false;
                    break;
                }
            }
            
            if (isSecure) {
                secureCombos.push_back(combo);
            }
        }
        
        return secureCombos;
    }
};
```

### 2. **Game Puzzle Design**

```cpp
class PuzzleGame {
private:
    LockOptimizerAdvanced solver;
    
public:
    struct PuzzleLevel {
        std::string startState;
        std::string goalState;
        std::vector<std::string> obstacles;
        int difficulty;  // 1-10 scale
        int minSolution;
        std::vector<std::string> hints;
    };
    
    PuzzleLevel generateLevel(int targetDifficulty) {
        PuzzleLevel level;
        
        // Generate random start and goal
        level.startState = generateRandomState();
        level.goalState = generateRandomState();
        
        // Ensure they're different
        while (level.goalState == level.startState) {
            level.goalState = generateRandomState();
        }
        
        // Add obstacles to increase difficulty
        level.obstacles = generateObstacles(targetDifficulty);
        
        // Calculate actual difficulty
        level.minSolution = solver.openLock(level.obstacles, level.goalState);
        level.difficulty = calculateDifficulty(level.minSolution, level.obstacles.size());
        
        // Generate hints
        level.hints = generateHints(level);
        
        return level;
    }
    
    bool validatePlayerSolution(const PuzzleLevel& level, 
                               const std::vector<std::string>& playerPath) {
        if (playerPath.empty() || playerPath[0] != level.startState ||
            playerPath.back() != level.goalState) {
            return false;
        }
        
        // Check if each step is valid
        for (size_t i = 1; i < playerPath.size(); i++) {
            if (!isValidMove(playerPath[i-1], playerPath[i])) {
                return false;
            }
            
            // Check if step hits obstacle
            for (const auto& obstacle : level.obstacles) {
                if (playerPath[i] == obstacle) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
private:
    std::string generateRandomState() {
        std::string state = "0000";
        for (int i = 0; i < 4; i++) {
            state[i] = '0' + (rand() % 10);
        }
        return state;
    }
    
    std::vector<std::string> generateObstacles(int difficulty) {
        std::vector<std::string> obstacles;
        int obstacleCount = difficulty * 2;  // More obstacles = harder
        
        for (int i = 0; i < obstacleCount; i++) {
            obstacles.push_back(generateRandomState());
        }
        
        return obstacles;
    }
    
    int calculateDifficulty(int minSolution, int obstacleCount) {
        if (minSolution == -1) return 10;  // Impossible = max difficulty
        
        return std::min(10, std::max(1, minSolution + obstacleCount / 5));
    }
    
    std::vector<std::string> generateHints(const PuzzleLevel& level) {
        std::vector<std::string> hints;
        
        auto path = solver.findPath(level.obstacles, level.goalState);
        
        if (!path.empty() && path.size() > 3) {
            hints.push_back("Try reaching: " + path[path.size() / 2]);
        }
        
        return hints;
    }
    
    bool isValidMove(const std::string& from, const std::string& to) {
        int differences = 0;
        int changedWheel = -1;
        
        for (int i = 0; i < 4; i++) {
            if (from[i] != to[i]) {
                differences++;
                changedWheel = i;
            }
        }
        
        if (differences != 1) return false;
        
        // Check if it's a valid wheel rotation
        int fromDigit = from[changedWheel] - '0';
        int toDigit = to[changedWheel] - '0';
        
        return (toDigit == (fromDigit + 1) % 10) || (toDigit == (fromDigit + 9) % 10);
    }
};
```

### 3. **Robotics Path Planning**

```cpp
class RobotNavigator {
private:
    LockAStar pathPlanner;
    
public:
    struct RobotPosition {
        int x, y, orientation, tool;  // 4D state space like lock wheels
        
        std::string toString() const {
            return std::to_string(x % 10) + std::to_string(y % 10) + 
                   std::to_string(orientation % 10) + std::to_string(tool % 10);
        }
        
        static RobotPosition fromString(const std::string& str) {
            return {str[0] - '0', str[1] - '0', str[2] - '0', str[3] - '0'};
        }
    };
    
    struct NavigationResult {
        std::vector<RobotPosition> path;
        int totalSteps;
        double estimatedTime;
        bool feasible;
    };
    
    NavigationResult planPath(const RobotPosition& start,
                             const RobotPosition& goal,
                             const std::vector<RobotPosition>& obstacles) {
        NavigationResult result;
        
        // Convert to string format for lock algorithm
        std::string startStr = start.toString();
        std::string goalStr = goal.toString();
        std::vector<std::string> obstacleStrs;
        
        for (const auto& obstacle : obstacles) {
            obstacleStrs.push_back(obstacle.toString());
        }
        
        // Plan path using lock algorithm
        result.totalSteps = pathPlanner.openLock(obstacleStrs, goalStr);
        result.feasible = (result.totalSteps != -1);
        
        if (result.feasible) {
            // Convert back to robot positions (simplified)
            result.estimatedTime = result.totalSteps * 0.5;  // 0.5 seconds per step
        }
        
        return result;
    }
    
    std::vector<RobotPosition> generateSafeZones(const RobotPosition& current,
                                                int safetyRadius) {
        std::vector<RobotPosition> safeZones;
        
        // Generate positions within safety radius
        for (int dx = -safetyRadius; dx <= safetyRadius; dx++) {
            for (int dy = -safetyRadius; dy <= safetyRadius; dy++) {
                for (int dOri = -1; dOri <= 1; dOri++) {
                    RobotPosition safe = {
                        (current.x + dx + 10) % 10,
                        (current.y + dy + 10) % 10,
                        (current.orientation + dOri + 10) % 10,
                        current.tool
                    };
                    safeZones.push_back(safe);
                }
            }
        }
        
        return safeZones;
    }
};
```

### 4. **Cryptographic Key Space Analysis**

```cpp
class CryptographicAnalyzer {
private:
    LockOptimizer keyAnalyzer;
    
public:
    struct KeyAnalysis {
        std::string keySpace;
        int minDistance;
        double entropy;
        std::vector<std::string> vulnerableKeys;
        double attackComplexity;
    };
    
    KeyAnalysis analyzeKeySpace(const std::string& targetKey,
                               const std::vector<std::string>& knownWeakKeys) {
        KeyAnalysis analysis;
        analysis.keySpace = "4-digit decimal (10^4 space)";
        
        // Find minimum distance to weak keys
        analysis.minDistance = INT_MAX;
        for (const auto& weakKey : knownWeakKeys) {
            std::vector<std::string> deadends;  // No restrictions for pure distance
            int distance = keyAnalyzer.openLock(deadends, targetKey);
            if (distance != -1) {
                analysis.minDistance = std::min(analysis.minDistance, distance);
            }
        }
        
        // Calculate entropy
        analysis.entropy = calculateEntropy(targetKey);
        
        // Find vulnerable neighboring keys
        analysis.vulnerableKeys = findVulnerableNeighbors(targetKey, knownWeakKeys);
        
        // Estimate attack complexity
        analysis.attackComplexity = estimateAttackComplexity(analysis);
        
        return analysis;
    }
    
    std::vector<std::string> generateSecureKeys(int count, 
                                               const std::vector<std::string>& avoidKeys) {
        std::vector<std::string> secureKeys;
        
        for (int i = 0; i < 10000 && secureKeys.size() < count; i++) {
            std::string candidate = std::to_string(i);
            candidate = std::string(4 - candidate.length(), '0') + candidate;
            
            // Check if far enough from avoid keys
            bool isSecure = true;
            for (const auto& avoidKey : avoidKeys) {
                std::vector<std::string> deadends;
                int distance = keyAnalyzer.openLock(deadends, candidate);
                
                if (distance != -1 && distance < 3) {  // Too close to weak key
                    isSecure = false;
                    break;
                }
            }
            
            if (isSecure && calculateEntropy(candidate) > 0.7) {
                secureKeys.push_back(candidate);
            }
        }
        
        return secureKeys;
    }
    
private:
    double calculateEntropy(const std::string& key) {
        std::unordered_map<char, int> freq;
        for (char c : key) freq[c]++;
        
        double entropy = 0.0;
        for (const auto& [digit, count] : freq) {
            double p = (double)count / key.length();
            entropy -= p * log2(p);
        }
        
        return entropy / 2.0;  // Normalize to [0,1]
    }
    
    std::vector<std::string> findVulnerableNeighbors(const std::string& target,
                                                    const std::vector<std::string>& weakKeys) {
        std::vector<std::string> vulnerable;
        
        // Check all single-step neighbors
        for (int pos = 0; pos < 4; pos++) {
            for (int delta = -1; delta <= 1; delta += 2) {
                std::string neighbor = target;
                neighbor[pos] = '0' + ((neighbor[pos] - '0' + delta + 10) % 10);
                
                // Check if neighbor is close to any weak key
                for (const auto& weakKey : weakKeys) {
                    std::vector<std::string> deadends;
                    int distance = keyAnalyzer.openLock(deadends, neighbor);
                    
                    if (distance != -1 && distance <= 2) {
                        vulnerable.push_back(neighbor);
                        break;
                    }
                }
            }
        }
        
        return vulnerable;
    }
    
    double estimateAttackComplexity(const KeyAnalysis& analysis) {
        double baseComplexity = 10000.0;  // Total key space
        
        // Reduce complexity based on proximity to weak keys
        double proximityFactor = std::max(0.1, (double)analysis.minDistance / 10.0);
        
        // Reduce complexity based on low entropy
        double entropyFactor = std::max(0.1, analysis.entropy);
        
        return baseComplexity * proximityFactor * entropyFactor;
    }
};
```

### 5. **Manufacturing Automation**

```cpp
class ManufacturingController {
private:
    LockIDAStar processOptimizer;
    
public:
    struct MachineState {
        int temperature;  // 0-9 (scaled)
        int pressure;     // 0-9 (scaled)
        int speed;        // 0-9 (scaled)
        int toolPosition; // 0-9 (discrete positions)
        
        std::string toString() const {
            return std::to_string(temperature) + std::to_string(pressure) + 
                   std::to_string(speed) + std::to_string(toolPosition);
        }
        
        static MachineState fromString(const std::string& str) {
            return {str[0] - '0', str[1] - '0', str[2] - '0', str[3] - '0'};
        }
    };
    
    struct ProcessPlan {
        std::vector<MachineState> sequence;
        int totalSteps;
        double estimatedTime;
        double energyCost;
        bool feasible;
    };
    
    ProcessPlan optimizeProcess(const MachineState& currentState,
                               const MachineState& targetState,
                               const std::vector<MachineState>& dangerousStates) {
        ProcessPlan plan;
        
        // Convert to string format
        std::string currentStr = currentState.toString();
        std::string targetStr = targetState.toString();
        std::vector<std::string> dangerousStrs;
        
        for (const auto& dangerous : dangerousStates) {
            dangerousStrs.push_back(dangerous.toString());
        }
        
        // Optimize using IDA* for memory efficiency
        plan.totalSteps = processOptimizer.openLock(dangerousStrs, targetStr);
        plan.feasible = (plan.totalSteps != -1);
        
        if (plan.feasible) {
            plan.estimatedTime = plan.totalSteps * 30.0;  // 30 seconds per step
            plan.energyCost = calculateEnergyCost(currentState, targetState, plan.totalSteps);
        }
        
        return plan;
    }
    
    std::vector<MachineState> generateSafeStates(const MachineState& current,
                                                const std::vector<MachineState>& forbidden) {
        std::vector<MachineState> safeStates;
        
        // Generate all single-step neighbors
        for (int param = 0; param < 4; param++) {
            for (int delta = -1; delta <= 1; delta += 2) {
                MachineState neighbor = current;
                int* paramValue = nullptr;
                
                switch (param) {
                    case 0: paramValue = &neighbor.temperature; break;
                    case 1: paramValue = &neighbor.pressure; break;
                    case 2: paramValue = &neighbor.speed; break;
                    case 3: paramValue = &neighbor.toolPosition; break;
                }
                
                *paramValue = (*paramValue + delta + 10) % 10;
                
                // Check if state is safe
                bool isSafe = true;
                for (const auto& forbidden : forbidden) {
                    if (neighbor.toString() == forbidden.toString()) {
                        isSafe = false;
                        break;
                    }
                }
                
                if (isSafe) {
                    safeStates.push_back(neighbor);
                }
            }
        }
        
        return safeStates;
    }
    
private:
    double calculateEnergyCost(const MachineState& start, 
                              const MachineState& end, 
                              int steps) {
        // Simplified energy cost calculation
        double baseCost = steps * 10.0;  // Base cost per step
        
        // Additional cost for parameter changes
        int tempChange = abs(end.temperature - start.temperature);
        int pressureChange = abs(end.pressure - start.pressure);
        int speedChange = abs(end.speed - start.speed);
        
        double changeCost = (tempChange * 5.0) + (pressureChange * 3.0) + (speedChange * 2.0);
        
        return baseCost + changeCost;
    }
};
```

## Pattern Insights

### Key Observations:

1. **Exponential Reduction**: Bidirectional search reduces search space from O(b^d) to O(b^(d/2)) where b=branching factor, d=depth

2. **Frontier Management**: Always expanding smaller frontier minimizes total work and memory usage

3. **Early Termination**: Meeting point detection provides immediate optimal solution

4. **Memory vs. Time**: Different algorithms offer various trade-offs between memory usage and computation time

### Related Patterns:
- **Meet-in-the-Middle**: Classic divide-and-conquer optimization
- **Breadth-First Search**: Foundation algorithm for shortest paths
- **A* Search**: Heuristic-guided optimization
- **Dynamic Programming**: Optimal substructure exploitation

### Advanced Optimizations:
- **Parallel Bidirectional Search**: Multiple threads exploring different frontiers
- **Hierarchical Search**: Multi-level decomposition for very large spaces
- **Memory-Bounded Search**: IDA* and RBFS for memory-constrained environments
- **Anytime Algorithms**: Progressive improvement with time constraints
- **Pattern Databases**: Precomputed heuristics for guided search

This problem demonstrates how algorithmic choice dramatically impacts performance in bounded discrete spaces, making it invaluable for both competitive programming and real-world applications involving combinatorial optimization, robotics, security systems, and automated planning.
