# Minimum Genetic Mutation

## Problem Description
A gene string can be represented by an 8-character string, using characters `'A'`, `'C'`, `'G'`, and `'T'`.

Suppose we need to investigate a mutation from a gene string `start` to a gene string `end` where one mutation is defined as one single character changed in the gene string.

- For example, `"AACCGGTT" --> "AACCGGTA"` is one mutation.

There is also a gene bank `bank` that records all the valid gene mutations. A gene must be in `bank` to make it a valid gene string.

Given the two gene strings `start` and `end` and the gene bank `bank`, return the minimum number of mutations needed to mutate from `start` to `end`. If there is no such a mutation, return `-1`.

**LeetCode Link:** [433. Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/)

## Approach
This is a **State-Space Search** problem similar to Word Ladder. We use **BFS** to find the shortest transformation sequence from start gene to end gene, where each step is a valid mutation (single character change) and the resulting gene must be in the bank.

**Key Insight:** Use BFS to explore mutations level by level, ensuring we find the minimum number of mutations.

## Algorithm Steps
1. Check if end gene is in the bank
2. Use BFS with queue to explore gene mutations
3. For each gene, try all possible single-character mutations
4. Only consider mutations that are in the bank and not visited
5. Return level when end gene is reached

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
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        
        // Check if end is in bank
        if (bankSet.find(end) == bankSet.end()) {
            return -1;
        }
        
        // Special case
        if (start == end) return 0;
        
        queue<string> q;
        unordered_set<string> visited;
        vector<char> genes = {'A', 'C', 'G', 'T'};
        
        q.push(start);
        visited.insert(start);
        
        int mutations = 0;
        
        while (!q.empty()) {
            int size = q.size();
            mutations++;
            
            for (int i = 0; i < size; i++) {
                string current = q.front();
                q.pop();
                
                // Try all possible single mutations
                for (int pos = 0; pos < 8; pos++) {
                    char originalChar = current[pos];
                    
                    for (char newChar : genes) {
                        if (newChar == originalChar) continue;
                        
                        current[pos] = newChar;
                        
                        if (current == end) {
                            return mutations;
                        }
                        
                        if (bankSet.count(current) && !visited.count(current)) {
                            visited.insert(current);
                            q.push(current);
                        }
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

### C++ - Bidirectional BFS
```cpp
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        
        if (bankSet.find(end) == bankSet.end()) {
            return -1;
        }
        
        if (start == end) return 0;
        
        unordered_set<string> visited;
        unordered_set<string> beginSet = {start};
        unordered_set<string> endSet = {end};
        vector<char> genes = {'A', 'C', 'G', 'T'};
        
        int mutations = 0;
        
        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand the smaller set
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextSet;
            mutations++;
            
            for (const string& current : beginSet) {
                for (int pos = 0; pos < 8; pos++) {
                    char originalChar = current[pos];
                    
                    for (char newChar : genes) {
                        if (newChar == originalChar) continue;
                        
                        string next = current;
                        next[pos] = newChar;
                        
                        if (endSet.count(next)) {
                            return mutations;
                        }
                        
                        if (bankSet.count(next) && !visited.count(next)) {
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

### C++ - DFS with Memoization (Alternative)
```cpp
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        
        if (bankSet.find(end) == bankSet.end()) {
            return -1;
        }
        
        unordered_map<string, int> memo;
        int result = dfs(start, end, bankSet, memo);
        return result == INT_MAX ? -1 : result;
    }
    
private:
    int dfs(const string& current, const string& end, 
            unordered_set<string>& bankSet, unordered_map<string, int>& memo) {
        if (current == end) return 0;
        
        if (memo.count(current)) return memo[current];
        
        vector<char> genes = {'A', 'C', 'G', 'T'};
        int minMutations = INT_MAX;
        
        for (int pos = 0; pos < 8; pos++) {
            char originalChar = current[pos];
            
            for (char newChar : genes) {
                if (newChar == originalChar) continue;
                
                string next = current;
                next[pos] = newChar;
                
                if (bankSet.count(next)) {
                    bankSet.erase(next); // Avoid cycles
                    int mutations = dfs(next, end, bankSet, memo);
                    if (mutations != INT_MAX) {
                        minMutations = min(minMutations, 1 + mutations);
                    }
                    bankSet.insert(next); // Backtrack
                }
            }
        }
        
        memo[current] = minMutations;
        return minMutations;
    }
};
```

### Time Complexity
- **BFS:** O(N × M × 4) where N is number of genes in bank, M is gene length (8)
- **Bidirectional BFS:** O(sqrt(N) × M × 4) - More efficient in practice

### Space Complexity
- **All approaches:** O(N) for visited set and queue/recursion stack

## Examples

### Example 1
```
Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1
Explanation: One mutation from "AACCGGTT" to "AACCGGTA"
```

### Example 2
```
Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2
Explanation: "AACCGGTT" -> "AACCGGTA" -> "AAACGGTA"
```

### Example 3
```
Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
Output: 3
Explanation: "AAAAACCC" -> "AAAACCCC" -> "AAACCCCC" -> "AACCCCCC"
```

## Notes
- **Valid mutations:** Only single character changes to A, C, G, or T
- **Bank requirement:** All intermediate genes must be in the bank
- **Shortest path:** BFS guarantees minimum number of mutations
- **Edge cases:** Start equals end, end not in bank, no valid path

## Related Problems
- [LeetCode 127: Word Ladder](https://leetcode.com/problems/word-ladder/)
- [LeetCode 752: Open the Lock](https://leetcode.com/problems/open-the-lock/)
- [LeetCode 126: Word Ladder II](https://leetcode.com/problems/word-ladder-ii/)

## Pattern: 07-State-Space-Search
This problem demonstrates **State-Space Search** where:
- **State representation:** Each gene string represents a state
- **State transitions:** Single character mutations represent valid transitions
- **Constraint satisfaction:** Only mutations in the bank are valid
- **Optimal path finding:** BFS finds minimum mutations needed for transformation
