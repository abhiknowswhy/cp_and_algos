# Boyer-Moore Algorithm

The Boyer-Moore algorithm is an efficient string-searching algorithm that skips sections of the text to be searched, resulting in a lower constant factor than many other string algorithms. It preprocesses the pattern to enable these skips.

## Key Concepts

The Boyer-Moore algorithm uses two main heuristics to skip characters:

1. **Bad Character Heuristic**: When a mismatch occurs, shift the pattern so that the mismatched character in the text aligns with the rightmost occurrence of that character in the pattern.
2. **Good Suffix Heuristic**: After a mismatch, shift the pattern to align any matching suffix with a corresponding substring in the pattern.

Understand this better - [YouTube video](https://www.youtube.com/watch?v=4Xyhb72LCX4)

## Time Complexity

- Preprocessing: O(m + σ) where m is the pattern length and σ is the alphabet size
- Best case: O(n/m) where n is the text length
- Worst case: O(n*m)

In practice, the algorithm typically performs better than its worst-case complexity suggests.

## C++ Implementation

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class BoyerMoore {
private:
    string pattern;
    unordered_map<char, int> badCharTable;
    vector<int> goodSuffixTable;
    vector<int> fullSuffixShift;
  
    // Preprocessing for bad character heuristic
    void preprocessBadChar() {
        int m = pattern.length();
        for (int i = 0; i < m; i++) {
            badCharTable[pattern[i]] = i;
        }
    }
  
    // Preprocessing for good suffix heuristic
    void preprocessGoodSuffix() {
        int m = pattern.length();
        goodSuffixTable.resize(m, 0);
        fullSuffixShift.resize(m + 1, 0);
    
        // Case 1: Matching suffix occurs elsewhere in pattern
        vector<int> suffixes = computeSuffixes();
    
        int j = 0;
        for (int i = m - 1; i >= 0; i--) {
            if (suffixes[i] == i + 1) {
                for (; j < m - 1 - i; j++) {
                    if (fullSuffixShift[j] == 0) {
                        fullSuffixShift[j] = m - 1 - i;
                    }
                }
            }
        }
    
        // Case 2: Prefix of pattern matches suffix of mismatch position
        for (int i = 0; i < m - 1; i++) {
            fullSuffixShift[m - 1 - suffixes[i]] = m - 1 - i;
        }
    
        // Fill goodSuffixTable
        for (int i = 0; i < m; i++) {
            goodSuffixTable[i] = fullSuffixShift[i];
        }
    }
  
    // Helper function for good suffix preprocessing
    vector<int> computeSuffixes() {
        int m = pattern.length();
        vector<int> suffixes(m, 0);
    
        int f = 0, g = m - 1;
    
        for (int i = m - 2; i >= 0; i--) {
            if (i > g && suffixes[i + m - 1 - f] < i - g) {
                suffixes[i] = suffixes[i + m - 1 - f];
            } else {
                if (i < g) g = i;
                f = i;
                while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                    g--;
                }
                suffixes[i] = f - g;
            }
        }
    
        return suffixes;
    }

public:
    BoyerMoore(const string& pat) : pattern(pat) {
        preprocessBadChar();
        preprocessGoodSuffix();
    }
  
    vector<int> search(const string& text) {
        vector<int> matches;
        int n = text.length();
        int m = pattern.length();
    
        if (n < m) return matches;
    
        int s = 0;  // shift of the pattern
        while (s <= (n - m)) {
            int j = m - 1;
        
            // Match from right to left
            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }
        
            // Pattern found
            if (j < 0) {
                matches.push_back(s);
                // Shift using good suffix rule for next search
                s += (s + m < n) ? m - badCharTable[text[s + m]] : 1;
            } else {
                // Calculate shift using both heuristics
                int badCharShift = j - badCharTable.count(text[s + j]) ? badCharTable[text[s + j]] : -1;
                int goodSuffixShift = goodSuffixTable[j];
            
                // Take the maximum shift
                s += max(1, max(j - badCharShift, goodSuffixShift));
            }
        }
    
        return matches;
    }
};

int main() {
    string text = "ABAAABCDABABBABAABCD";
    string pattern = "ABAB";
  
    BoyerMoore bm(pattern);
    vector<int> positions = bm.search(text);
  
    cout << "Pattern found at positions: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;
  
    return 0;
}
```

## Applications

Boyer-Moore is highly effective for:

- Large alphabets (like ASCII text)
- Long patterns
- Text editors (for search functions)
- DNA sequencing

## Related LeetCode Problems

1. **[28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)**

   - Implementation of string matching algorithms like Boyer-Moore
   - Difficulty: Easy
2. **[459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)**

   - Can be optimized using Boyer-Moore concepts
   - Difficulty: Easy
3. **[1392. Longest Happy Prefix](https://leetcode.com/problems/longest-happy-prefix/)**

   - Uses string pattern matching concepts similar to those in Boyer-Moore
   - Difficulty: Hard
4. **[686. Repeated String Match](https://leetcode.com/problems/repeated-string-match/)**

   - Can be solved efficiently using Boyer-Moore
   - Difficulty: Medium
5. **[796. Rotate String](https://leetcode.com/problems/rotate-string/)**

   - Pattern matching can be optimized with Boyer-Moore
   - Difficulty: Easy

## Further Reading

1. Boyer, R. S., & Moore, J. S. (1977). A fast string searching algorithm. Communications of the ACM, 20(10), 762-772.
2. Gusfield, D. (1997). Algorithms on Strings, Trees, and Sequences: Computer Science and Computational Biology. Cambridge University Press.
3. Charras, C., & Lecroq, T. (2004). Handbook of Exact String Matching Algorithms. King's College Publications.
