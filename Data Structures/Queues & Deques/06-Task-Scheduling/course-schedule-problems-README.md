# Course Schedule Problems

## Problem Description

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you must take course `bi` first if you want to take course `ai`.

Return `true` if you can finish all courses. Otherwise, return `false`.

## Approach

Model this as a directed graph where courses are vertices and prerequisites are edges. Use topological sorting with BFS (Kahn's algorithm) to detect cycles. If a cycle exists, it's impossible to complete all courses.

## Algorithm Steps

1. Build adjacency list and calculate indegree for each course
2. Add all courses with indegree 0 to queue (no prerequisites)
3. While queue is not empty:
   - Dequeue a course and increment completed count
   - For each dependent course, decrease its indegree
   - If indegree becomes 0, add to queue
4. Return true if all courses completed

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // Course Schedule I - Can finish all courses?
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // Build graph and calculate indegrees
        for (auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            graph[prerequisite].push_back(course);
            indegree[course]++;
        }
        
        // Start with courses having no prerequisites
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int completed = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            completed++;
            
            // Reduce indegree for dependent courses
            for (int dependent : graph[course]) {
                indegree[dependent]--;
                if (indegree[dependent] == 0) {
                    q.push(dependent);
                }
            }
        }
        
        return completed == numCourses;
    }
    
    // Course Schedule II - Return order of courses
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            graph[prerequisite].push_back(course);
            indegree[course]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> result;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            result.push_back(course);
            
            for (int dependent : graph[course]) {
                indegree[dependent]--;
                if (indegree[dependent] == 0) {
                    q.push(dependent);
                }
            }
        }
        
        return result.size() == numCourses ? result : vector<int>();
    }
    
    // DFS approach for cycle detection
    bool canFinishDFS(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for (auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
        }
        
        vector<int> state(numCourses, 0); // 0: unvisited, 1: visiting, 2: visited
        
        for (int i = 0; i < numCourses; i++) {
            if (hasCycle(graph, i, state)) {
                return false;
            }
        }
        
        return true;
    }
    
private:
    bool hasCycle(vector<vector<int>>& graph, int node, vector<int>& state) {
        if (state[node] == 1) return true;  // Back edge found (cycle)
        if (state[node] == 2) return false; // Already processed
        
        state[node] = 1; // Mark as visiting
        
        for (int neighbor : graph[node]) {
            if (hasCycle(graph, neighbor, state)) {
                return true;
            }
        }
        
        state[node] = 2; // Mark as visited
        return false;
    }
};
```

### Time Complexity

- **O(V + E)** where V is number of courses and E is number of prerequisites
- Each course and prerequisite is processed once

### Space Complexity

- **O(V + E)** for adjacency list and auxiliary data structures

## Examples

### Example 1 (Course Schedule I)

```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: Take course 0 first, then course 1
```

### Example 2 (Course Schedule I)

```
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: Circular dependency between courses 0 and 1
```

### Example 3 (Course Schedule II)

```
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,1,2,3] or [0,2,1,3]
Explanation: Multiple valid orderings exist
```

## Notes

- Topological sort works only on Directed Acyclic Graphs (DAGs)
- BFS approach (Kahn's algorithm) uses indegree counting
- DFS approach uses three-color marking to detect back edges
- If cycle exists, topological ordering is impossible

## Related Problems

- [Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) - LeetCode 269
- [Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/) - LeetCode 310
- [Parallel Courses](https://leetcode.com/problems/parallel-courses/) - LeetCode 1136

## LeetCode Links

- [Course Schedule](https://leetcode.com/problems/course-schedule/) - LeetCode 207
- [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) - LeetCode 210
- [Course Schedule III](https://leetcode.com/problems/course-schedule-iii/) - LeetCode 630

## Pattern: 06-Task-Scheduling

This pattern uses topological sorting to order tasks with dependencies. BFS with indegree tracking (Kahn's algorithm) naturally handles task scheduling by processing tasks as their dependencies are satisfied.
