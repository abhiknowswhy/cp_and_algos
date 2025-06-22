# Longest Palindromic Substring

A palindrome is a sequence of characters that reads the same backward as forward. The longest palindromic substring problem asks us to find the longest substring within a given string that is also a palindrome.

## Algorithms for Finding Longest Palindromic Substring

### 1. Brute Force Approach

The naive approach checks every possible substring and verifies if it's a palindrome:

1. Generate all possible substrings
2. Check each substring if it's a palindrome
3. Track the longest palindromic substring found

This approach has O(n³) time complexity, which is inefficient for long strings.

### 2. Expand Around Center

This efficient approach is based on the observation that a palindrome mirrors around its center:

1. For each position in the string, consider it as a potential center of a palindrome
2. Expand outward from the center, comparing characters on both sides
3. Continue expansion as long as the characters match
4. Track the longest palindrome found

Note that we need to check both even-length palindromes (with two characters at the center) and odd-length palindromes (with one character at the center).

#### C++ Implementation (Expand Around Center)

```cpp
#include <iostream>
#include <string>
using namespace std;

string longestPalindrome(string s) {
    if (s.empty() || s.length() < 1) return "";
    
    int start = 0, maxLength = 1;
    
    // Helper function to expand around center
    auto expandAroundCenter = [&s](int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1; // Length of palindrome
    };
    
    for (int i = 0; i < s.length(); i++) {
        // Odd length palindromes (single character center)
        int len1 = expandAroundCenter(i, i);
        
        // Even length palindromes (two character center)
        int len2 = expandAroundCenter(i, i + 1);
        
        // Find the maximum length from both cases
        int len = max(len1, len2);
        
        // Update result if current palindrome is longer
        if (len > maxLength) {
            maxLength = len;
            start = i - (len - 1) / 2;
        }
    }
    
    return s.substr(start, maxLength);
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    
    string result = longestPalindrome(input);
    cout << "Longest palindromic substring: " << result << endl;
    cout << "Length: " << result.length() << endl;
    
    return 0;
}
```

### 3. Dynamic Programming Approach

The dynamic programming approach uses a 2D table to store whether substrings are palindromes:

1. Create a boolean table `dp[i][j]` that is true if the substring from i to j is a palindrome
2. A single character is always a palindrome: `dp[i][i] = true`
3. For two characters, they form a palindrome if they're equal: `dp[i][i+1] = (s[i] == s[i+1])`
4. For longer substrings: `dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]`
5. Track the longest palindromic substring as we fill the table

#### C++ Implementation (Dynamic Programming)

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string longestPalindromeDP(string s) {
    int n = s.length();
    if (n == 0) return "";
    
    // dp[i][j] will be 'true' if substring s[i..j] is palindrome
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    int start = 0;     // Starting index of palindrome
    int maxLength = 1; // Length of longest palindrome
    
    // All substrings of length 1 are palindromes
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    // Check for substrings of length 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }
    
    // Check for substrings of length 3 to n
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            // j is the ending index of substring from index i and length len
            int j = i + len - 1;
            
            // Substring from i to j is palindrome if s[i] == s[j] and
            // substring from i+1 to j-1 is also palindrome
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                
                if (len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }
    
    return s.substr(start, maxLength);
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    
    string result = longestPalindromeDP(input);
    cout << "Longest palindromic substring (DP): " << result << endl;
    cout << "Length: " << result.length() << endl;
    
    return 0;
}
```

### 4. Manacher's Algorithm

Manacher's algorithm is a specialized technique that solves the longest palindromic substring problem in linear time O(n):

1. Transform the string by inserting special characters between each character and at the edges
2. Use an array to keep track of palindrome lengths at each position
3. Leverage the symmetry of palindromes to avoid redundant comparisons
4. Expand around centers where needed

#### C++ Implementation (Manacher's Algorithm)

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string manacher(string s) {
    // Preprocess the string to handle even length palindromes
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }
    
    int n = t.length();
    vector<int> p(n, 0); // p[i] = radius of palindrome centered at i
    
    int center = 0, right = 0;
    int maxLen = 0, maxCenter = 0;
    
    for (int i = 0; i < n; i++) {
        // Mirror of i with respect to center
        int mirror = 2 * center - i;
        
        // If i is within the right boundary, use the mirror value
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        // Try to expand palindrome centered at i
        int a = i + (1 + p[i]);
        int b = i - (1 + p[i]);
        
        while (a < n && b >= 0 && t[a] == t[b]) {
            p[i]++;
            a++;
            b--;
        }
        
        // If palindrome centered at i expands past right,
        // adjust center and right boundary
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
        
        // Update maximum length palindrome if needed
        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
        }
    }
    
    // Extract the longest palindromic substring from the original string
    int start = (maxCenter - maxLen) / 2;  // Convert back to original string index
    return s.substr(start, maxLen);
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    
    string result = manacher(input);
    cout << "Longest palindromic substring (Manacher): " << result << endl;
    cout << "Length: " << result.length() << endl;
    
    return 0;
}
```

## Time and Space Complexity

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Brute Force | O(n³) | O(1) |
| Expand Around Center | O(n²) | O(1) |
| Dynamic Programming | O(n²) | O(n²) |
| Manacher's Algorithm | O(n) | O(n) |

## Related LeetCode Problems

1. [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) - Find the longest palindromic substring in a string
2. [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) - Count how many palindromic substrings are in a string
3. [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/) - Find the longest subsequence that is a palindrome
4. [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) - Convert a string to a palindrome by adding characters to the beginning
5. [336. Palindrome Pairs](https://leetcode.com/problems/palindrome-pairs/) - Find all pairs of words that form a palindrome when concatenated

## Key Takeaways

1. The Expand Around Center approach is intuitive and reasonably efficient for most cases
2. Dynamic Programming provides a systematic way to solve the problem but requires O(n²) space
3. Manacher's Algorithm is the most efficient approach with linear time complexity
4. Even though Manacher's Algorithm is theoretically superior, the simpler approaches are often sufficient for typical problem constraints
5. Understanding palindrome properties (especially symmetry) is key to solving these problems efficiently
