# Word Ladder - Bidirectional BFS Optimization

**LeetCode 127: Word Ladder**

## Problem Description

A transformation sequence from word `beginWord` to word `endWord` using a dictionary `wordList` is a sequence of words `beginWord -> s1 -> s2 -> ... -> sk` such that:

- Every adjacent pair of words differs by exactly one letter
- Every `si` for `1 <= i <= k` is in `wordList`. Note that `beginWord` does not need to be in `wordList`
- `sk == endWord`

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return the length of the shortest transformation sequence from `beginWord` to `endWord`, or 0 if no such sequence exists.

## Multiple Approaches

### Approach 1: Standard BFS

```cpp
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;
        
        queue<string> q;
        unordered_set<string> visited;
        q.push(beginWord);
        visited.insert(beginWord);
        
        int level = 1;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                
                if (word == endWord) return level;
                
                // Try all possible one-character changes
                for (int j = 0; j < word.length(); j++) {
                    char original = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original) continue;
                        word[j] = c;
                        
                        if (wordSet.count(word) && !visited.count(word)) {
                            visited.insert(word);
                            q.push(word);
                        }
                    }
                    word[j] = original; // backtrack
                }
            }
            level++;
        }
        return 0;
    }
};
```

### Approach 2: Bidirectional BFS (Optimized)

```cpp
class SolutionBidirectional {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;
        
        unordered_set<string> beginSet{beginWord}, endSet{endWord};
        unordered_set<string> visited;
        
        int level = 1;
        while (!beginSet.empty() && !endSet.empty()) {
            // Always search from the smaller set
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }
            
            unordered_set<string> nextSet;
            level++;
            
            for (const string& word : beginSet) {
                for (int i = 0; i < word.length(); i++) {
                    string newWord = word;
                    for (char c = 'a'; c <= 'z'; c++) {
                        newWord[i] = c;
                        
                        // Check if we've found the path
                        if (endSet.count(newWord)) return level;
                        
                        // Add to next level if valid and unvisited
                        if (wordSet.count(newWord) && !visited.count(newWord)) {
                            visited.insert(newWord);
                            nextSet.insert(newWord);
                        }
                    }
                }
            }
            beginSet = nextSet;
        }
        return 0;
    }
};
```

### Approach 3: Pattern-Based BFS

```cpp
class SolutionPattern {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return 0;
        
        // Build pattern dictionary
        unordered_map<string, vector<string>> patterns;
        wordSet.insert(beginWord);
        
        for (const string& word : wordSet) {
            for (int i = 0; i < word.length(); i++) {
                string pattern = word.substr(0, i) + "*" + word.substr(i + 1);
                patterns[pattern].push_back(word);
            }
        }
        
        queue<string> q;
        unordered_set<string> visited;
        q.push(beginWord);
        visited.insert(beginWord);
        
        int level = 1;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                
                if (word == endWord) return level;
                
                // Find all neighbors using patterns
                for (int j = 0; j < word.length(); j++) {
                    string pattern = word.substr(0, j) + "*" + word.substr(j + 1);
                    
                    for (const string& neighbor : patterns[pattern]) {
                        if (!visited.count(neighbor)) {
                            visited.insert(neighbor);
                            q.push(neighbor);
                        }
                    }
                }
            }
            level++;
        }
        return 0;
    }
};
```

### Approach 4: A* Algorithm with Heuristic

```cpp
class SolutionAStar {
private:
    int heuristic(const string& word1, const string& word2) {
        int diff = 0;
        for (int i = 0; i < word1.length(); i++) {
            if (word1[i] != word2[i]) diff++;
        }
        return diff;
    }
    
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return 0;
        
        // Priority queue: {f_score, g_score, word}
        priority_queue<tuple<int, int, string>, 
                      vector<tuple<int, int, string>>, 
                      greater<tuple<int, int, string>>> pq;
        
        unordered_map<string, int> gScore;
        unordered_set<string> visited;
        
        int h = heuristic(beginWord, endWord);
        pq.push({1 + h, 1, beginWord});
        gScore[beginWord] = 1;
        
        while (!pq.empty()) {
            auto [f, g, word] = pq.top();
            pq.pop();
            
            if (word == endWord) return g;
            if (visited.count(word)) continue;
            visited.insert(word);
            
            // Generate neighbors
            for (int i = 0; i < word.length(); i++) {
                char original = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == original) continue;
                    word[i] = c;
                    
                    if (wordSet.count(word) && !visited.count(word)) {
                        int newG = g + 1;
                        if (!gScore.count(word) || newG < gScore[word]) {
                            gScore[word] = newG;
                            int h = heuristic(word, endWord);
                            pq.push({newG + h, newG, word});
                        }
                    }
                }
                word[i] = original;
            }
        }
        return 0;
    }
};
```

## Complexity Analysis

**Time Complexity:**
- **Standard BFS**: O(M² × N) where M is word length, N is number of words
- **Bidirectional BFS**: O(M² × N) but much faster in practice
- **Pattern-Based**: O(M² × N) with better constants
- **A\* Algorithm**: O(M² × N) with optimized search

**Space Complexity:**
- **Standard BFS**: O(M × N) for queue and visited set
- **Bidirectional BFS**: O(M × N) for two sets
- **Pattern-Based**: O(M² × N) for pattern mapping
- **A\* Algorithm**: O(M × N) for priority queue and maps

## Example Walkthrough

### Example 1

```plaintext
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: "hit" -> "hot" -> "dot" -> "dog" -> "cog"
```

### Example 2

```plaintext
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: endWord "cog" is not in wordList
```

## Key Optimization Techniques

### 1. Bidirectional Search

```cpp
// Always search from smaller frontier
if (beginSet.size() > endSet.size()) {
    swap(beginSet, endSet);
}
```

### 2. Early Termination

```cpp
// Check intersection immediately
if (endSet.count(newWord)) return level;
```

### 3. Pattern Preprocessing

```cpp
// Precompute patterns to avoid repeated character changes
string pattern = word.substr(0, i) + "*" + word.substr(i + 1);
```

## Real-World Applications

### 1. Spell Checker with Suggestions

```cpp
class SpellChecker {
private:
    unordered_set<string> dictionary;
    
public:
    vector<string> getSuggestions(const string& misspelled, int maxEdits = 2) {
        vector<string> suggestions;
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({misspelled, 0});
        visited.insert(misspelled);
        
        while (!q.empty() && suggestions.size() < 10) {
            auto [word, edits] = q.front();
            q.pop();
            
            if (edits > 0 && dictionary.count(word)) {
                suggestions.push_back(word);
            }
            
            if (edits < maxEdits) {
                // Generate all one-edit neighbors
                for (int i = 0; i < word.length(); i++) {
                    char original = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c != original) {
                            word[i] = c;
                            if (!visited.count(word)) {
                                visited.insert(word);
                                q.push({word, edits + 1});
                            }
                        }
                    }
                    word[i] = original;
                }
            }
        }
        return suggestions;
    }
};
```

### 2. Gene Mutation Analysis

```cpp
class GeneMutationAnalyzer {
private:
    unordered_set<string> validGenes;
    
public:
    int minMutationSteps(string startGene, string targetGene) {
        if (!validGenes.count(targetGene)) return -1;
        
        queue<string> q;
        unordered_set<string> visited;
        
        q.push(startGene);
        visited.insert(startGene);
        
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string gene = q.front();
                q.pop();
                
                if (gene == targetGene) return steps;
                
                // Try all possible single nucleotide mutations
                for (int j = 0; j < gene.length(); j++) {
                    char original = gene[j];
                    for (char nucleotide : {'A', 'C', 'G', 'T'}) {
                        if (nucleotide != original) {
                            gene[j] = nucleotide;
                            if (validGenes.count(gene) && !visited.count(gene)) {
                                visited.insert(gene);
                                q.push(gene);
                            }
                        }
                    }
                    gene[j] = original;
                }
            }
            steps++;
        }
        return -1;
    }
};
```

### 3. Word Game Solver

```cpp
class WordGameSolver {
private:
    unordered_set<string> dictionary;
    
public:
    vector<vector<string>> findAllPaths(string start, string end) {
        vector<vector<string>> result;
        if (!dictionary.count(end)) return result;
        
        queue<vector<string>> q;
        unordered_set<string> visited;
        
        q.push({start});
        visited.insert(start);
        
        bool found = false;
        while (!q.empty() && !found) {
            int size = q.size();
            unordered_set<string> levelVisited;
            
            for (int i = 0; i < size; i++) {
                vector<string> path = q.front();
                q.pop();
                
                string word = path.back();
                if (word == end) {
                    result.push_back(path);
                    found = true;
                    continue;
                }
                
                // Generate neighbors
                for (int j = 0; j < word.length(); j++) {
                    char original = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c != original) {
                            word[j] = c;
                            if (dictionary.count(word) && !visited.count(word)) {
                                vector<string> newPath = path;
                                newPath.push_back(word);
                                q.push(newPath);
                                levelVisited.insert(word);
                            }
                        }
                    }
                    word[j] = original;
                }
            }
            
            // Update visited after processing current level
            for (const string& word : levelVisited) {
                visited.insert(word);
            }
        }
        return result;
    }
};
```

## Advanced Features

### 1. Path Reconstruction

```cpp
class SolutionWithPath {
public:
    pair<int, vector<string>> ladderLengthWithPath(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (!wordSet.count(endWord)) return {0, {}};
        
        queue<string> q;
        unordered_map<string, string> parent;
        unordered_set<string> visited;
        
        q.push(beginWord);
        visited.insert(beginWord);
        parent[beginWord] = "";
        
        int level = 1;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                string word = q.front();
                q.pop();
                
                if (word == endWord) {
                    // Reconstruct path
                    vector<string> path;
                    string current = endWord;
                    while (!current.empty()) {
                        path.push_back(current);
                        current = parent[current];
                    }
                    reverse(path.begin(), path.end());
                    return {level, path};
                }
                
                // Generate neighbors
                for (int j = 0; j < word.length(); j++) {
                    char original = word[j];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c != original) {
                            word[j] = c;
                            if (wordSet.count(word) && !visited.count(word)) {
                                visited.insert(word);
                                parent[word] = q.front();
                                q.push(word);
                            }
                        }
                    }
                    word[j] = original;
                }
            }
            level++;
        }
        return {0, {}};
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
        vector<string> testWords = generateWordList(1000, 4);
        string begin = testWords[0];
        string end = testWords.back();
        
        // Test Standard BFS
        auto start = chrono::high_resolution_clock::now();
        Solution().ladderLength(begin, end, testWords);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::microseconds>(end_time - start);
        
        // Test Bidirectional BFS
        start = chrono::high_resolution_clock::now();
        SolutionBidirectional().ladderLength(begin, end, testWords);
        end_time = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(end_time - start);
        
        cout << "Standard BFS: " << duration1.count() << " μs\n";
        cout << "Bidirectional BFS: " << duration2.count() << " μs\n";
        cout << "Speedup: " << (double)duration1.count() / duration2.count() << "x\n";
    }
    
private:
    static vector<string> generateWordList(int count, int length) {
        vector<string> words;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis('a', 'z');
        
        for (int i = 0; i < count; i++) {
            string word;
            for (int j = 0; j < length; j++) {
                word += static_cast<char>(dis(gen));
            }
            words.push_back(word);
        }
        return words;
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
        vector<string> wordList1 = {"hot","dot","dog","lot","log","cog"};
        assert(sol.ladderLength("hit", "cog", wordList1) == 5);
        
        // Test case 2
        vector<string> wordList2 = {"hot","dot","dog","lot","log"};
        assert(sol.ladderLength("hit", "cog", wordList2) == 0);
        
        // Test case 3
        vector<string> wordList3 = {"a","b","c"};
        assert(sol.ladderLength("a", "c", wordList3) == 0);
    }
    
    static void testEdgeCases() {
        Solution sol;
        
        // Same begin and end word
        vector<string> wordList1 = {"hit"};
        assert(sol.ladderLength("hit", "hit", wordList1) == 1);
        
        // Empty word list
        vector<string> wordList2 = {};
        assert(sol.ladderLength("hit", "cog", wordList2) == 0);
        
        // Single character words
        vector<string> wordList3 = {"a","b","c"};
        assert(sol.ladderLength("a", "b", wordList3) == 2);
    }
    
    static void testPerformance() {
        PerformanceTester::benchmarkSolutions();
    }
};
```

## Pattern Analysis: Bidirectional-BFS

This problem is perfect for the **Bidirectional-BFS** pattern because:

1. **Fixed Start and End**: We know both source and destination
2. **Symmetric Search**: We can search from both directions
3. **Exponential Reduction**: Bidirectional search reduces complexity from O(b^d) to O(b^(d/2))
4. **Early Meeting**: Paths meet in the middle, reducing search space

### Key Pattern Elements

- **Dual Frontier**: Maintain sets for both directions
- **Intersection Detection**: Check when frontiers meet
- **Alternating Search**: Process smaller frontier first
- **Level Synchronization**: Ensure proper level tracking

### Pattern Variations

- **Breadth-First**: Standard BFS from both ends
- **Best-First**: Use heuristics (A\* algorithm)
- **Depth-Limited**: Limit search depth
- **Iterative Deepening**: Gradually increase depth

## Related Problems

- **LeetCode 126**: Word Ladder II
- **LeetCode 433**: Minimum Genetic Mutation
- **LeetCode 752**: Open the Lock
- **LeetCode 773**: Sliding Puzzle
- **LeetCode 1162**: As Far from Land as Possible

## Tags

`BFS` `Bidirectional BFS` `Graph` `String` `Hash Table` `Shortest Path`
