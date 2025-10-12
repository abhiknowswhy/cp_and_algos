# Longest Common Subsequence (LCS)

## Problem Definition

The Longest Common Subsequence (LCS) is a classic dynamic programming problem that finds the longest subsequence common to two sequences. A subsequence is a sequence that appears in the same relative order but not necessarily contiguously.

For example, given two strings:
- `text1 = "abcde"`
- `text2 = "ace"`

The LCS is `"ace"` with a length of 3.

## Approaches

### 1. Recursive (Brute Force)

**Complete Implementation:**
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Recursive approach
int lcs(string text1, string text2, int m, int n) {
    // Base case: if either string is empty
    if (m == 0 || n == 0)
        return 0;
    
    // If last characters match
    if (text1[m-1] == text2[n-1])
        return 1 + lcs(text1, text2, m-1, n-1);
    
    // If last characters don't match
    return max(lcs(text1, text2, m, n-1), lcs(text1, text2, m-1, n));
}

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    int m = text1.length();
    int n = text2.length();
    
    int result = lcs(text1, text2, m, n);
    cout << "Length of Longest Common Subsequence: " << result << endl;
    
    return 0;
}
```

**Time Complexity**: O(2^(m+n)) - exponential, where m and n are lengths of the strings
**Space Complexity**: O(m+n) - recursive stack depth

### 2. Memoization (Top-Down DP)

**Complete Implementation:**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Forward declaration
int lcsHelper(string& text1, string& text2, int m, int n, vector<vector<int>>& memo);

// Main function
int lcs(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
    return lcsHelper(text1, text2, m, n, memo);
}

// Helper function with memoization
int lcsHelper(string& text1, string& text2, int m, int n, vector<vector<int>>& memo) {
    // Base case
    if (m == 0 || n == 0)
        return 0;
    
    // Return cached result if exists
    if (memo[m][n] != -1)
        return memo[m][n];
    
    // If last characters match
    if (text1[m-1] == text2[n-1])
        memo[m][n] = 1 + lcsHelper(text1, text2, m-1, n-1, memo);
    else
        // If last characters don't match
        memo[m][n] = max(lcsHelper(text1, text2, m, n-1, memo), lcsHelper(text1, text2, m-1, n, memo));
    
    return memo[m][n];
}

// Function to print the LCS
string printLCS(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
    
    // First calculate the LCS length
    lcsHelper(text1, text2, m, n, memo);
    
    // Now backtrack to find the LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (text1[i-1] == text2[j-1]) {
            lcs = text1[i-1] + lcs;
            i--; j--;
        } 
        else if ((i > 0 && j > 0) && memo[i-1][j] > memo[i][j-1])
            i--;
        else
            j--;
    }
    
    return lcs;
}

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    
    int result = lcs(text1, text2);
    cout << "Length of Longest Common Subsequence: " << result << endl;
    
    string subsequence = printLCS(text1, text2);
    cout << "The Longest Common Subsequence is: " << subsequence << endl;
    
    return 0;
}
```

**Time Complexity**: O(m×n) - each subproblem solved once
**Space Complexity**: O(m×n) - memo table + O(m+n) recursive stack

### 3. Tabulation (Bottom-Up DP)

**Complete Implementation:**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Tabulation approach
int lcs(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // If characters match
            if (text1[i-1] == text2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                // If characters don't match
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    return dp[m][n];
}

// Function to print the LCS
string printLCS(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    // Backtrack to find the LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (text1[i-1] == text2[j-1]) {
            lcs = text1[i-1] + lcs;
            i--; j--;
        } 
        else if (dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    
    return lcs;
}

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    
    int result = lcs(text1, text2);
    cout << "Length of Longest Common Subsequence: " << result << endl;
    
    string subsequence = printLCS(text1, text2);
    cout << "The Longest Common Subsequence is: " << subsequence << endl;
    
    // Print the DP table (for visualization)
    cout << "\nDP Table:" << endl;
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    cout << "   ";
    for (int j = 0; j < n; j++) {
        cout << text2[j] << " ";
    }
    cout << endl;
    
    for (int i = 0; i <= m; i++) {
        if (i > 0) cout << text1[i-1] << " ";
        else cout << "  ";
        
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(m×n) - filling the dp table
**Space Complexity**: O(m×n) - dp table

### 4. Space Optimized Tabulation

**Complete Implementation:**
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Space optimized tabulation approach
int lcs(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    
    // Create two rows for DP
    vector<int> prev(n+1, 0), curr(n+1, 0);
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        // Update prev row
        prev = curr;
    }
    
    return prev[n];
}

// Print the LCS (requires full DP table, so this isn't space optimized)
string printLCS(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    // Backtrack to find the LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (text1[i-1] == text2[j-1]) {
            lcs = text1[i-1] + lcs;
            i--; j--;
        } 
        else if (dp[i-1][j] > dp[i][j-1])
            i--;
        else
            j--;
    }
    
    return lcs;
}

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    
    int result = lcs(text1, text2);
    cout << "Length of Longest Common Subsequence: " << result << endl;
    
    string subsequence = printLCS(text1, text2);
    cout << "The Longest Common Subsequence is: " << subsequence << endl;
    
    return 0;
}
```

**Time Complexity**: O(m×n)
**Space Complexity**: O(n) - only two rows needed

## Complete Implementation with All Features

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

// Class-based implementation of LCS with multiple approaches
class LongestCommonSubsequence {
private:
    // Helper for recursive memoization approach
    int memoHelper(string& text1, string& text2, int m, int n, vector<vector<int>>& memo) {
        // Base case
        if (m == 0 || n == 0)
            return 0;
        
        // Return cached result if exists
        if (memo[m][n] != -1)
            return memo[m][n];
        
        // If last characters match
        if (text1[m-1] == text2[n-1])
            memo[m][n] = 1 + memoHelper(text1, text2, m-1, n-1, memo);
        else
            // If last characters don't match
            memo[m][n] = max(memoHelper(text1, text2, m, n-1, memo), 
                             memoHelper(text1, text2, m-1, n, memo));
        
        return memo[m][n];
    }
    
public:
    // Recursive approach (brute force)
    int recursive(string text1, string text2, int m, int n) {
        // Base case: if either string is empty
        if (m == 0 || n == 0)
            return 0;
        
        // If last characters match
        if (text1[m-1] == text2[n-1])
            return 1 + recursive(text1, text2, m-1, n-1);
        
        // If last characters don't match
        return max(recursive(text1, text2, m, n-1), recursive(text1, text2, m-1, n));
    }
    
    // Memoization approach
    int memoization(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
        return memoHelper(text1, text2, m, n, memo);
    }
    
    // Tabulation approach
    int tabulation(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        return dp[m][n];
    }
    
    // Space optimized approach
    int spaceOptimized(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        vector<int> prev(n+1, 0), curr(n+1, 0);
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1])
                    curr[j] = 1 + prev[j-1];
                else
                    curr[j] = max(prev[j], curr[j-1]);
            }
            prev = curr;
        }
        
        return prev[n];
    }
    
    // Print one possible LCS
    string printOneLCS(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        // Backtrack to find the LCS
        string lcs = "";
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (text1[i-1] == text2[j-1]) {
                lcs = text1[i-1] + lcs;
                i--; j--;
            } 
            else if (dp[i-1][j] > dp[i][j-1])
                i--;
            else
                j--;
        }
        
        return lcs;
    }
    
    // Print all possible LCS (returns a set to avoid duplicates)
    unordered_set<string> printAllLCS(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        return findAllLCS(text1, text2, m, n, dp);
    }

private:
    // Recursive helper to find all possible LCS
    unordered_set<string> findAllLCS(string& text1, string& text2, int i, int j, 
                                    vector<vector<int>>& dp) {
        unordered_set<string> result;
        
        // Base case
        if (i == 0 || j == 0) {
            result.insert("");
            return result;
        }
        
        // If characters match
        if (text1[i-1] == text2[j-1]) {
            unordered_set<string> subLCS = findAllLCS(text1, text2, i-1, j-1, dp);
            for (const string& s : subLCS) {
                result.insert(s + text1[i-1]);
            }
        }
        // If not matching, we need to consider both previous cells that gave the max value
        else {
            if (dp[i-1][j] >= dp[i][j-1]) {
                unordered_set<string> subLCS = findAllLCS(text1, text2, i-1, j, dp);
                result.insert(subLCS.begin(), subLCS.end());
            }
            if (dp[i][j-1] >= dp[i-1][j]) {
                unordered_set<string> subLCS = findAllLCS(text1, text2, i, j-1, dp);
                result.insert(subLCS.begin(), subLCS.end());
            }
        }
        
        return result;
    }
};

int main() {
    string text1 = "abcde";
    string text2 = "ace";
    
    LongestCommonSubsequence lcs;
    
    cout << "Example 1: text1 = \"" << text1 << "\", text2 = \"" << text2 << "\"" << endl;
    
    // Too slow for larger inputs
    // cout << "Recursive approach: " << lcs.recursive(text1, text2, text1.length(), text2.length()) << endl;
    
    cout << "Memoization approach: " << lcs.memoization(text1, text2) << endl;
    cout << "Tabulation approach: " << lcs.tabulation(text1, text2) << endl;
    cout << "Space-optimized approach: " << lcs.spaceOptimized(text1, text2) << endl;
    cout << "LCS string: " << lcs.printOneLCS(text1, text2) << endl;
    
    // Print all possible LCS
    cout << "\nAll possible LCS:" << endl;
    unordered_set<string> allLCS = lcs.printAllLCS(text1, text2);
    for (const string& s : allLCS) {
        cout << "- " << s << endl;
    }
    
    // Example 2
    text1 = "abcd";
    text2 = "abdc";
    
    cout << "\nExample 2: text1 = \"" << text1 << "\", text2 = \"" << text2 << "\"" << endl;
    cout << "LCS length: " << lcs.tabulation(text1, text2) << endl;
    cout << "LCS string: " << lcs.printOneLCS(text1, text2) << endl;
    
    cout << "\nAll possible LCS:" << endl;
    allLCS = lcs.printAllLCS(text1, text2);
    for (const string& s : allLCS) {
        cout << "- " << s << endl;
    }
    
    return 0;
}
```

## Advanced Variations

### 1. Longest Common Substring

Unlike subsequences, substrings require consecutive characters. Here's the implementation:

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to find the longest common substring
pair<int, string> longestCommonSubstring(string text1, string text2) {
    int m = text1.length();
    int n = text2.length();
    int maxLength = 0;
    int endIndex = 0;
    
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            }
            // If characters don't match, reset to 0
            // (this is the key difference from LCS)
        }
    }
    
    string result = "";
    if (maxLength > 0) {
        result = text1.substr(endIndex - maxLength + 1, maxLength);
    }
    
    return {maxLength, result};
}

int main() {
    string text1 = "abcdxyz";
    string text2 = "xyzabcd";
    
    auto [length, substring] = longestCommonSubstring(text1, text2);
    
    cout << "Length of Longest Common Substring: " << length << endl;
    cout << "Longest Common Substring: " << substring << endl;
    
    return 0;
}
```

### 2. LCS for Three Strings

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to find LCS of three strings
int LCSof3(string X, string Y, string Z) {
    int m = X.length();
    int n = Y.length();
    int o = Z.length();
    
    // Create a 3D DP table
    vector<vector<vector<int>>> dp(m+1, 
                                  vector<vector<int>>(n+1, 
                                                    vector<int>(o+1, 0)));
    
    // Fill the dp table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= o; k++) {
                // If characters match in all strings
                if (X[i-1] == Y[j-1] && Y[j-1] == Z[k-1])
                    dp[i][j][k] = 1 + dp[i-1][j-1][k-1];
                else
                    // Take the maximum of leaving one character out
                    dp[i][j][k] = max(max(dp[i-1][j][k], dp[i][j-1][k]), dp[i][j][k-1]);
            }
        }
    }
    
    return dp[m][n][o];
}

int main() {
    string X = "AGGT12";
    string Y = "12TXAYB";
    string Z = "12XBA";
    
    cout << "Length of LCS of three strings: " << LCSof3(X, Y, Z) << endl;
    
    return 0;
}
```

### 3. Print Shortest Common Supersequence

The shortest common supersequence contains both strings with minimal length.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Function to print shortest common supersequence
string shortestCommonSupersequence(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();
    
    // dp[i][j] contains length of LCS of str1[0..i-1] and str2[0..j-1]
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    // Build LCS table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    
    // Create supersequence by backtracking
    string result = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        // If current characters match, include only once
        if (str1[i-1] == str2[j-1]) {
            result = str1[i-1] + result;
            i--; j--;
        }
        // Take the character from str1
        else if (dp[i-1][j] > dp[i][j-1]) {
            result = str1[i-1] + result;
            i--;
        }
        // Take the character from str2
        else {
            result = str2[j-1] + result;
            j--;
        }
    }
    
    // Add remaining characters
    while (i > 0) {
        result = str1[i-1] + result;
        i--;
    }
    
    while (j > 0) {
        result = str2[j-1] + result;
        j--;
    }
    
    return result;
}

int main() {
    string str1 = "abac";
    string str2 = "cab";
    
    string scs = shortestCommonSupersequence(str1, str2);
    
    cout << "Shortest Common Supersequence: " << scs << endl;
    cout << "Length: " << scs.length() << endl;
    
    return 0;
}
```

## LeetCode Problems

1. [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) - The direct implementation of LCS
2. [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) - Can be solved by finding LCS of the string and its reverse
3. [1092. Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/) - Related to LCS
4. [72. Edit Distance](https://leetcode.com/problems/edit-distance/) - Similar approach
5. [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/) - Can be solved using LCS
