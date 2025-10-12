# Levenshtein Distance

## Introduction

Levenshtein distance, also known as edit distance, is a measure of the similarity between two strings. It represents the minimum number of single-character edits (insertions, deletions, or substitutions) required to change one string into the other.

For example, the Levenshtein distance between "kitten" and "sitting" is 3, because these three edits are needed:
1. **k**itten → **s**itten (substitution of "k" for "s")
2. sitt**e**n → sitt**i**n (substitution of "e" for "i")
3. sittin → sittin**g** (insertion of "g" at the end)

## Applications

Levenshtein distance has numerous practical applications:
- Spell checking and correction
- DNA sequence analysis
- Speech recognition
- Plagiarism detection
- Fuzzy string searching
- Machine translation

## Dynamic Programming Approach

The Levenshtein distance is typically calculated using dynamic programming. We create a matrix where each cell `dp[i][j]` represents the edit distance between the prefixes of the two strings up to positions `i` and `j` respectively.

### Algorithm Steps:

1. Initialize a matrix `dp` of size `(m+1) × (n+1)`, where `m` and `n` are the lengths of the two input strings.
2. Fill the first row and column with values 0 to `m` and 0 to `n`, respectively. This represents the cost of transforming a string to an empty string by deleting all characters.
3. For each cell `dp[i][j]` (where `i > 0` and `j > 0`):
   - If the characters at positions `i-1` and `j-1` of the two strings match, then `dp[i][j] = dp[i-1][j-1]` (no operation needed).
   - If they don't match, `dp[i][j]` is the minimum of:
     - `dp[i-1][j] + 1` (deletion)
     - `dp[i][j-1] + 1` (insertion)
     - `dp[i-1][j-1] + 1` (substitution)
4. The value in the bottom-right cell, `dp[m][n]`, gives the Levenshtein distance between the two strings.

### Time and Space Complexity:
- **Time Complexity**: O(m×n), where m and n are the lengths of the two strings
- **Space Complexity**: O(m×n)

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int levenshteinDistance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // Create a table to store results of subproblems
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    // Fill d[][] in bottom-up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // If first string is empty, only option is to insert all characters of second string
            if (i == 0)
                dp[i][j] = j;
            
            // If second string is empty, only option is to remove all characters of first string
            else if (j == 0)
                dp[i][j] = i;
            
            // If last characters are the same, ignore the last character and recur for remaining string
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            
            // If the last characters are different, consider all operations (insert, remove, replace)
            else
                dp[i][j] = 1 + min({dp[i][j - 1],      // Insert
                                   dp[i - 1][j],      // Remove
                                   dp[i - 1][j - 1]}); // Replace
        }
    }
    
    return dp[m][n];
}

// Space-optimized version (O(min(m,n)) space)
int levenshteinDistanceOptimized(const string& str1, const string& str2) {
    // Make sure str1 is shorter for optimization
    if (str1.length() > str2.length())
        return levenshteinDistanceOptimized(str2, str1);
    
    int m = str1.length();
    int n = str2.length();
    
    vector<int> prev(m + 1, 0);
    vector<int> curr(m + 1, 0);
    
    // Initialize the previous row
    for (int i = 0; i <= m; i++)
        prev[i] = i;
    
    // Fill the dp array
    for (int j = 1; j <= n; j++) {
        curr[0] = j;
        
        for (int i = 1; i <= m; i++) {
            if (str1[i - 1] == str2[j - 1])
                curr[i] = prev[i - 1];
            else
                curr[i] = 1 + min({curr[i - 1], prev[i], prev[i - 1]});
        }
        
        // Update previous row
        prev = curr;
    }
    
    return prev[m];
}

int main() {
    string str1 = "kitten";
    string str2 = "sitting";
    
    cout << "Levenshtein distance between '" << str1 << "' and '" 
         << str2 << "' is: " << levenshteinDistance(str1, str2) << endl;
    
    cout << "Optimized version result: " << levenshteinDistanceOptimized(str1, str2) << endl;
    
    return 0;
}
```

## LeetCode Problems Related to Edit Distance

1. **[72. Edit Distance](https://leetcode.com/problems/edit-distance/)** (Hard)
   - This is the direct implementation of the Levenshtein distance.
   - Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

2. **[583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)** (Medium)
   - A variation where only deletion operations are allowed.
   - Can be solved using Levenshtein distance principles or by finding the longest common subsequence.

3. **[712. Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/)** (Medium)
   - A weighted version of edit distance where deletions have costs equal to ASCII values.
   - Uses the same DP approach with a modification to consider character weights.

4. **[161. One Edit Distance](https://leetcode.com/problems/one-edit-distance/)** (Medium - Premium)
   - Determine if two strings are exactly one edit distance apart.
   - A simplified version of the edit distance problem.

5. **[1035. Uncrossed Lines](https://leetcode.com/problems/uncrossed-lines/)** (Medium)
   - While not directly an edit distance problem, it's related as it deals with finding matching patterns between sequences.

## Further Optimizations

- **Memory Optimization**: Since we only need the current and previous rows of the DP table, we can reduce the space complexity to O(min(m, n)).
- **Early Termination**: If the difference in string lengths exceeds the target edit distance, we can return early.
- **Heuristic Improvements**: For specific applications, additional heuristics can be used to speed up the algorithm.

## References

- Wagner, Robert A.; Fischer, Michael J. (1974). "The String-to-String Correction Problem". Journal of the ACM. 21 (1): 168–173.
- Levenshtein, Vladimir I. (1966). "Binary codes capable of correcting deletions, insertions, and reversals". Soviet Physics Doklady. 10 (8): 707–710.
