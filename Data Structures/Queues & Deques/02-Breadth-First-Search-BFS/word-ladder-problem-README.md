# Word Ladder Problem

## Problem Description

A transformation sequence from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words where:
- The first word is `beginWord`
- The last word is `endWord`  
- Each adjacent pair differs by exactly one letter
- All intermediate words are in `wordList`

Return the length of the shortest transformation sequence, or 0 if no such sequence exists.

## Approach

Model this as a shortest path problem in an unweighted graph where:
- Each word is a vertex
- Two words are connected if they differ by exactly one character
- Use BFS to find shortest path from `beginWord` to `endWord`

## Algorithm Steps

1. If `endWord` not in `wordList`, return 0
2. Add `beginWord` to `wordList` if not present
3. Build graph by connecting words that differ by one character
4. Use BFS starting from `beginWord`
5. Return distance when `endWord` is reached, or 0 if unreachable

## Implementation

### C++

```cpp
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // If endWord not in wordList, no transformation possible
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }
        
        queue<pair<string, int>> q; // {word, steps}
        unordered_set<string> visited;
        
        q.push({beginWord, 1});
        visited.insert(beginWord);
        
        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();
            
            if (word == endWord) {
                return steps;
            }
            
            // Try changing each character
            for (int i = 0; i < word.length(); i++) {
                char originalChar = word[i];
                
                // Try all 26 letters
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == originalChar) continue;
                    
                    word[i] = c;
                    
                    if (wordSet.count(word) && !visited.count(word)) {
                        visited.insert(word);
                        q.push({word, steps + 1});
                    }
                }
                
                word[i] = originalChar; // Restore original character
            }
        }
        
        return 0;
    }
    
    // Optimized version using bidirectional BFS
    int ladderLengthBidirectional(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;
        
        unordered_set<string> beginSet{beginWord};
        unordered_set<string> endSet{endWord};
        unordered_set<string> visited;
        
        int steps = 1;
        
        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand the smaller set
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextSet;
            
            for (const string& word : beginSet) {
                string temp = word;
                for (int i = 0; i < word.length(); i++) {
                    char originalChar = temp[i];
                    
                    for (char c = 'a'; c <= 'z'; c++) {
                        temp[i] = c;
                        
                        if (endSet.count(temp)) {
                            return steps + 1;
                        }
                        
                        if (wordSet.count(temp) && !visited.count(temp)) {
                            visited.insert(temp);
                            nextSet.insert(temp);
                        }
                    }
                    
                    temp[i] = originalChar;
                }
            }
            
            beginSet = nextSet;
            steps++;
        }
        
        return 0;
    }
};
```

### Time Complexity

- **O(M² × N)** where M is length of each word and N is total number of words
- For each word, we try M×26 transformations, each taking O(M) time to create

### Space Complexity

- **O(M × N)** for storing word set and visited set
- BFS queue can contain up to O(N) words

## Examples

### Example 1

```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: "hit" → "hot" → "dot" → "dog" → "cog"
```

### Example 2

```
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: endWord "cog" is not in wordList
```

## Notes

- BFS guarantees shortest transformation sequence
- Bidirectional BFS can significantly reduce search space
- Can be optimized by preprocessing word adjacency graph
- Similar to finding shortest path in unweighted graph

## Related Problems

- [Word Ladder II](https://leetcode.com/problems/word-ladder-ii/) - LeetCode 126
- [Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/) - LeetCode 433
- [Open the Lock](https://leetcode.com/problems/open-the-lock/) - LeetCode 752

## LeetCode Links

- [Word Ladder](https://leetcode.com/problems/word-ladder/) - LeetCode 127
- [Word Ladder II](https://leetcode.com/problems/word-ladder-ii/) - LeetCode 126

## Pattern: 02-Breadth-First-Search-BFS

This problem demonstrates BFS for shortest path in a graph where vertices are words and edges connect words differing by one character. BFS ensures we find the minimum number of transformations needed.
