# Alien Dictionary

## Problem Description
There is a new alien language that uses the English alphabet. However, the order among the letters is unknown to you.

You are given a list of strings `words` from the alien language's dictionary, where the strings in `words` are **sorted lexicographically** by the rules of this new language.

Return a string of the unique letters in the new alien language sorted in **lexicographically increasing order** by the new language's rules. If there is no solution, return `""`. If there are multiple solutions, return **any of them**.

**LeetCode Link:** [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) (Premium)

## Approach
This is a **Topological Sorting** problem disguised as a string problem. We need to:

1. Build a directed graph representing character order relationships
2. Use **Kahn's algorithm** (BFS with queue) for topological sorting
3. Handle edge cases like invalid ordering or cycles

**Key Insight:** If word A comes before word B in the dictionary, then the first differing character in A must come before the corresponding character in B in the alien alphabet.

## Algorithm Steps
1. Build adjacency list graph from word comparisons
2. Calculate in-degrees for each character
3. Use BFS (queue) for topological sorting starting from characters with in-degree 0
4. Check if all characters are processed (no cycles)
5. Return the topologically sorted order

## Implementation

### C++ - Kahn's Algorithm (BFS)
```cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.empty()) return "";
        
        // Step 1: Build graph and calculate in-degrees
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> inDegree;
        
        // Initialize all characters with in-degree 0
        for (const string& word : words) {
            for (char c : word) {
                inDegree[c] = 0;
            }
        }
        
        // Build graph by comparing adjacent words
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i];
            string word2 = words[i + 1];
            
            // Check for invalid case: word1 is longer and is prefix of word2
            if (word1.length() > word2.length() && word1.substr(0, word2.length()) == word2) {
                return "";
            }
            
            // Find first differing character
            for (int j = 0; j < min(word1.length(), word2.length()); j++) {
                if (word1[j] != word2[j]) {
                    // word1[j] comes before word2[j]
                    if (graph[word1[j]].find(word2[j]) == graph[word1[j]].end()) {
                        graph[word1[j]].insert(word2[j]);
                        inDegree[word2[j]]++;
                    }
                    break;
                }
            }
        }
        
        // Step 2: Topological sorting using BFS
        queue<char> q;
        for (auto& pair : inDegree) {
            if (pair.second == 0) {
                q.push(pair.first);
            }
        }
        
        string result = "";
        while (!q.empty()) {
            char current = q.front();
            q.pop();
            result += current;
            
            // Reduce in-degree of neighbors
            for (char neighbor : graph[current]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Check if all characters are processed (no cycle)
        return result.length() == inDegree.size() ? result : "";
    }
};
```

### C++ - DFS Approach
```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        if (words.empty()) return "";
        
        unordered_map<char, unordered_set<char>> graph;
        unordered_set<char> allChars;
        
        // Collect all characters
        for (const string& word : words) {
            for (char c : word) {
                allChars.insert(c);
                graph[c]; // Initialize empty set
            }
        }
        
        // Build graph
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i];
            string word2 = words[i + 1];
            
            if (word1.length() > word2.length() && word1.substr(0, word2.length()) == word2) {
                return "";
            }
            
            for (int j = 0; j < min(word1.length(), word2.length()); j++) {
                if (word1[j] != word2[j]) {
                    graph[word1[j]].insert(word2[j]);
                    break;
                }
            }
        }
        
        // DFS for topological sorting
        unordered_map<char, int> visited; // 0: unvisited, 1: visiting, 2: visited
        string result = "";
        
        for (char c : allChars) {
            if (visited[c] == 0) {
                if (!dfs(graph, visited, c, result)) {
                    return ""; // Cycle detected
                }
            }
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
    
private:
    bool dfs(unordered_map<char, unordered_set<char>>& graph,
             unordered_map<char, int>& visited, char node, string& result) {
        if (visited[node] == 1) return false; // Cycle detected
        if (visited[node] == 2) return true;  // Already processed
        
        visited[node] = 1; // Mark as visiting
        
        for (char neighbor : graph[node]) {
            if (!dfs(graph, visited, neighbor, result)) {
                return false;
            }
        }
        
        visited[node] = 2; // Mark as visited
        result += node;
        return true;
    }
};
```

### Time Complexity
- **BFS (Kahn's):** O(V + E) where V is number of unique characters, E is number of ordering relationships
- **DFS:** O(V + E) for same reasons

### Space Complexity
- **Both approaches:** O(V + E) for graph storage and auxiliary structures

## Examples

### Example 1
```
Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Explanation:
From "wrt" and "wrf", we get 't' < 'f'
From "wrf" and "er", we get 'w' < 'e'  
From "er" and "ett", we get 'r' < 't'
From "ett" and "rftt", we get 'e' < 'r'
So the order is "wertf"
```

### Example 2
```
Input: words = ["z","x"]
Output: "zx"
Explanation: From "z" and "x", we get 'z' < 'x'
```

### Example 3
```
Input: words = ["z","x","z"]
Output: ""
Explanation: Invalid ordering - creates a cycle
```

## Notes
- **Graph construction:** Only compare adjacent words in the sorted list
- **Invalid cases:** Longer word appearing as prefix before shorter word
- **Cycle detection:** If topological sort doesn't include all characters, there's a cycle
- **Multiple solutions:** Any valid topological ordering is acceptable

## Related Problems
- [LeetCode 207: Course Schedule](https://leetcode.com/problems/course-schedule/)
- [LeetCode 210: Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [LeetCode 310: Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)
- [LeetCode 953: Verifying an Alien Dictionary](https://leetcode.com/problems/verifying-an-alien-dictionary/)

## Pattern: 06-Task-Scheduling
This problem fits **Task Scheduling** pattern where:
- **Dependency management:** Characters have ordering dependencies like tasks
- **Queue-based processing:** Use BFS queue to process characters with no dependencies first
- **Topological ordering:** Schedule characters in valid order respecting all constraints
- **Conflict detection:** Detect impossible scheduling (cycles) and return appropriate result
