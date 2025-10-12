# Longest Palindromic Subsequence

## Problem Description

The Longest Palindromic Subsequence (LPS) problem asks us to find the length of the longest subsequence in a string that is also a palindrome. A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

## Algorithm

### Approach: Dynamic Programming

The key insight for solving this problem is that the longest palindromic subsequence has an optimal substructure, making it suitable for dynamic programming.

1. Let `dp[i][j]` represent the length of the longest palindromic subsequence in the substring `s[i...j]`.
2. Base cases:
   - For all `i`, `dp[i][i] = 1` (a single character is a palindrome of length 1)
3. Recursive relation:
   - If `s[i] == s[j]`, then `dp[i][j] = dp[i+1][j-1] + 2`
   - If `s[i] != s[j]`, then `dp[i][j] = max(dp[i+1][j], dp[i][j-1])`
4. The final answer is `dp[0][n-1]` where `n` is the length of the string.

### Time and Space Complexity

- Time Complexity: O(n²) where n is the length of the string
- Space Complexity: O(n²) for the DP table

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int longestPalindromeSubseq(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
  
    // Base case: single characters are palindromes of length 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
  
    // Fill the DP table
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
  
    return dp[0][n-1];
}

// Complete example program
int main() {
    string s = "bbbab";
    cout << "Longest Palindromic Subsequence length: " << longestPalindromeSubseq(s) << endl;
  
    s = "cbbd";
    cout << "Longest Palindromic Subsequence length: " << longestPalindromeSubseq(s) << endl;
  
    return 0;
}
```

### Alternative: Space-Optimized Implementation

We can optimize the space complexity to O(n) by using only two rows of the DP table:

```cpp
 #include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int longestPalindromeSubseq_optimized(string s) {
    int n = s.length();
    vector<int> dp(n, 0);
    vector<int> dpPrev(n, 0);
  
    // Base case: single characters
    for (int i = n-1; i >= 0; i--) {
        dp[i] = 1;
        for (int j = i+1; j < n; j++) {
            if (s[i] == s[j]) {
                dp[j] = dpPrev[j-1] + 2;
            } else {
                dp[j] = max(dpPrev[j], dp[j-1]);
            }
        }
        dpPrev = dp;
    }
  
    return dp[n-1];
}

// Complete example program
int main() {
    string s = "bbbab";
    cout << "Longest Palindromic Subsequence length (optimized): " 
         << longestPalindromeSubseq_optimized(s) << endl;
  
    return 0;
}
```

## Visualization of the Algorithm

For string "bbbab":

1. Initialize DP table with base case (diagonal = 1)
2. Fill the table for increasing substring lengths
3. Final answer is in dp[0][4] = 4

The longest palindromic subsequence is "bbbb".

## Related Problems on LeetCode

1. [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) - The exact problem we've solved
2. [1312. Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/) - Can be solved using LPS
3. [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) - Related problem, LPS can be found by finding LCS of the string and its reverse
4. [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) - Different from subsequence, requires contiguous characters

## Key Insights

- If the characters at both ends match, we can include them in our palindrome and look for a palindrome in the remaining substring.
- If they don't match, we have to choose the better of two options: exclude the first character or exclude the last character.
- The optimal solution builds upon optimal solutions to smaller subproblems, making dynamic programming a perfect fit.
