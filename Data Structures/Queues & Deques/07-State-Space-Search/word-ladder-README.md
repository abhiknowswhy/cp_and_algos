# Word Ladder

## Problem Description
Given two words `beginWord` and `endWord`, and a dictionary `wordList`, find the length of the shortest transformation sequence from `beginWord` to `endWord`, such that:
- Only one letter can be changed at a time
- Each transformed word must exist in the word list

Return 0 if there is no such transformation sequence.

## Approach
This is a classic BFS state-space search problem. We treat each word as a state and each valid transformation as an edge. The shortest path represents the minimum transformation sequence.

**Key insights:**
1. **State representation**: Each word is a state
2. **State transitions**: Change one character at a time to get valid neighbors
3. **Goal condition**: Reach the `endWord`
4. **Optimization**: Use bidirectional BFS for better performance

## Algorithm Steps
1. **Initialize BFS queue** with `beginWord` and distance 1
2. **For each word in queue**: Generate all possible one-character transformations
3. **Check validity**: Only consider transformations that exist in `wordList`
4. **Track visited**: Avoid cycles by marking visited words
5. **Return distance** when `endWord` is reached

## Implementation

### Approach 1: Standard BFS
```cpp
#include <queue>
#include <unordered_set>
#include <string>
#include <vector>

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // If endWord is not in wordList, no transformation possible
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        while (!q.empty()) {
            auto [currentWord, level] = q.front();
            q.pop();
            
            // Try changing each character
            for (int i = 0; i < currentWord.length(); i++) {
                string originalWord = currentWord;
                
                // Try all 26 possible characters
                for (char c = 'a'; c <= 'z'; c++) {
                    currentWord[i] = c;
                    
                    // If we found the endWord
                    if (currentWord == endWord) {
                        return level + 1;
                    }
                    
                    // If this transformation exists in wordList
                    if (wordSet.find(currentWord) != wordSet.end()) {
                        q.push({currentWord, level + 1});
                        wordSet.erase(currentWord); // Mark as visited
                    }
                }
                currentWord = originalWord; // Restore word
            }
        }
        
        return 0; // No transformation found
    }
};
```

### Approach 2: Bidirectional BFS
```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        unordered_set<string> beginSet{beginWord};
        unordered_set<string> endSet{endWord};
        int level = 1;
        
        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand the smaller set for efficiency
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextSet;
            for (const string& word : beginSet) {
                for (int i = 0; i < word.length(); i++) {
                    string currentWord = word;
                    
                    for (char c = 'a'; c <= 'z'; c++) {
                        currentWord[i] = c;
                        
                        // Found intersection
                        if (endSet.find(currentWord) != endSet.end()) {
                            return level + 1;
                        }
                        
                        // Valid transformation
                        if (wordSet.find(currentWord) != wordSet.end()) {
                            nextSet.insert(currentWord);
                            wordSet.erase(currentWord);
                        }
                    }
                }
            }
            
            beginSet = nextSet;
            level++;
        }
        
        return 0;
    }
};
```

### Approach 3: Using Word Patterns (Optimized)
```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Build adjacency list using word patterns
        unordered_map<string, vector<string>> patternMap;
        
        // Add beginWord to wordList for processing
        wordList.push_back(beginWord);
        
        for (const string& word : wordList) {
            for (int i = 0; i < word.length(); i++) {
                string pattern = word.substr(0, i) + "*" + word.substr(i + 1);
                patternMap[pattern].push_back(word);
            }
        }
        
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({beginWord, 1});
        visited.insert(beginWord);
        
        while (!q.empty()) {
            auto [currentWord, level] = q.front();
            q.pop();
            
            if (currentWord == endWord) {
                return level;
            }
            
            // Check all patterns for current word
            for (int i = 0; i < currentWord.length(); i++) {
                string pattern = currentWord.substr(0, i) + "*" + currentWord.substr(i + 1);
                
                for (const string& neighbor : patternMap[pattern]) {
                    if (visited.find(neighbor) == visited.end()) {
                        if (neighbor == endWord) {
                            return level + 1;
                        }
                        
                        visited.insert(neighbor);
                        q.push({neighbor, level + 1});
                    }
                }
            }
        }
        
        return 0;
    }
};
```

### Time Complexity
- **Standard BFS**: O(M² × N), where M is word length and N is number of words
- **Bidirectional BFS**: O(M² × N), but with better practical performance
- **Pattern-based**: O(M × N) for preprocessing + O(M² × N) for BFS

### Space Complexity
- **Standard BFS**: O(M × N) for queue and visited set
- **Bidirectional BFS**: O(M × N) for both sets
- **Pattern-based**: O(M² × N) for pattern map

## Examples

### Example 1
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: "hit" -> "hot" -> "dot" -> "dog" -> "cog"
```

### Example 2
```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: endWord "cog" is not in wordList, so no transformation sequence exists.
```

## Key Insights

### Queue Pattern Usage
- **State-space search**: Each word represents a state in the search space
- **Level-order exploration**: BFS ensures shortest path is found first
- **Visited tracking**: Prevents infinite loops and redundant computations

### Optimization Techniques
1. **Bidirectional BFS**: Search from both ends to reduce search space
2. **Pattern mapping**: Pre-compute word relationships for faster neighbor lookup
3. **Early termination**: Stop as soon as target is reached

### Common Pitfalls
- Forgetting to check if `endWord` exists in `wordList`
- Not marking words as visited, leading to infinite loops
- Inefficient neighbor generation without pattern optimization

## Related Problems
- Word Ladder II (return all shortest paths)
- Minimum Genetic Mutation
- Open the Lock

## Pattern: 07-State-Space-Search
This problem exemplifies state-space search where:
- **States**: Individual words
- **Actions**: Single character transformations
- **Goal**: Reach target word with minimum steps
- **Strategy**: BFS for shortest path guarantee
Explanation: "hit" -> "hot" -> "dot" -> "dog" -> "cog"
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
