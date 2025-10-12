# Knuth-Morris-Pratt (KMP) Algorithm

## Overview
The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that uses the observation that when a mismatch occurs, the pattern itself contains sufficient information to determine where the next match could begin, avoiding the need to re-examine previously matched characters.

## Time Complexity
- Time Complexity: O(n + m) where n is the length of the text and m is the length of the pattern
- Space Complexity: O(m) for the LPS (Longest Prefix Suffix) array

## How KMP Works

1. **Preprocessing Phase**: Create an LPS array that indicates the length of the longest proper prefix that is also a suffix for each substring of the pattern.
   - This preprocessing helps avoid unnecessary character comparisons when a mismatch occurs.

2. **Searching Phase**: Use the LPS array to efficiently skip characters in the text when a mismatch occurs.
   - When a mismatch happens, instead of starting over, we use the LPS array to determine how many characters we can skip.

3. **The LPS Array**: For each position i in the pattern, LPS[i] contains the length of the longest proper prefix which is also a suffix for pattern[0...i].

## Implementation

```cpp
#include <iostream>
#include <vector>

using namespace std;

// Function to compute the LPS array
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int m = pattern.length();
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // First element is always 0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Reduce length
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Matching Algorithm
void KMPSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> lps(m, 0); // LPS array

    // Compute LPS array
    computeLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) { // Found a match
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1]; // Move j using LPS
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1]; // Shift pattern using LPS
            } else {
                i++;
            }
        }
    }
}

// Driver Code
int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    KMPSearch(text, pattern);

    return 0;
}
```

## Key Insights
- The LPS array is the key component that makes KMP efficient.
- When a mismatch occurs after matching some characters, we don't need to start from the beginning of the pattern.
- The LPS array tells us how many characters we can skip, essentially reusing the information about the characters we've already matched.

## LeetCode Problems Using KMP Algorithm

1. **[28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)**
   - This is a direct application of the KMP algorithm to find the first occurrence of a pattern in a text.

2. **[459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)**
   - KMP can be used to determine if a string can be constructed by repeating a substring.

3. **[686. Repeated String Match](https://leetcode.com/problems/repeated-string-match/)**
   - A variation where KMP helps find how many times string A needs to be repeated to make string B a substring.

4. **[1392. Longest Happy Prefix](https://leetcode.com/problems/longest-happy-prefix/)**
   - This problem directly relates to finding the longest prefix that is also a suffix, which is exactly what the LPS array in KMP computes.

5. **[214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/)**
   - KMP can be used to find the shortest palindrome by adding characters in front of the given string.
