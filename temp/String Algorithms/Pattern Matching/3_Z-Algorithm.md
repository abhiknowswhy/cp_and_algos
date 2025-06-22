# Z-Algorithm for Pattern Matching

## Introduction
The Z-algorithm is a linear time string matching algorithm that finds all occurrences of a pattern in a text. It works by maintaining an array Z, where Z[i] represents the length of the longest substring starting at position i that is also a prefix of the string.

## How the Z-Algorithm Works

1. **Concept**: The Z-algorithm computes the Z-array for a string S. For each position i, Z[i] is the length of the longest substring starting at position i that matches a prefix of S.

2. **Z-Box**: When computing Z[i], the algorithm maintains a "Z-box" (or "Z-interval") [L, R], where:
   - L is the leftmost position of the current Z-box
   - R is the rightmost position of the current Z-box
   - This Z-box represents the substring that has already been processed and matched with a prefix of S

3. **Computing Z-values**:
   - If i > R: We compute Z[i] by explicit character comparisons
   - If i ≤ R: We can use already computed Z-values to get a starting value for Z[i], then potentially extend it
     - Let k = i - L (position i inside the Z-box relative to its start)
     - If Z[k] < R - i + 1: Then Z[i] = Z[k] (we're inside the Z-box and won't extend beyond R)
     - If Z[k] ≥ R - i + 1: Z[i] = R - i + 1, then we try to extend it by explicit character comparisons

## Pattern Matching with Z-Algorithm

For pattern matching, we concatenate the pattern P, a special character (like '$'), and the text T to form a new string S = P$T. Then we compute the Z-array for S. Any position i in the Z-array such that Z[i] = |P| indicates a pattern match starting at position i-|P|-1 in the original text.

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to compute the Z array
vector<int> computeZArray(const string& s) {
    int n = s.length();
    vector<int> Z(n, 0);
    int L = 0, R = 0;
    
    for (int i = 1; i < n; i++) {
        // Case 1: i > R, we compute Z[i] by comparing characters explicitly
        if (i > R) {
            L = R = i;
            while (R < n && s[R-L] == s[R])
                R++;
            
            Z[i] = R - L;
            R--;
        } 
        // Case 2: i <= R, we can use previously computed Z values
        else {
            int k = i - L;
            
            // If Z[k] doesn't reach the boundary of the Z-box, we can directly use it
            if (Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } 
            // If Z[k] reaches or exceeds the boundary, we need to do explicit comparisons 
            else {
                L = i;
                while (R < n && s[R-L] == s[R])
                    R++;
                
                Z[i] = R - L;
                R--;
            }
        }
    }
    
    return Z;
}

// Function to find all occurrences of pattern in text using Z algorithm
vector<int> findPatternZ(const string& text, const string& pattern) {
    string concatenated = pattern + "$" + text;
    vector<int> Z = computeZArray(concatenated);
    vector<int> result;
    
    for (int i = 0; i < Z.size(); i++) {
        // If Z value equals pattern length, we found a match
        if (Z[i] == pattern.length()) {
            // Convert to original text index (i - pattern.length() - 1)
            result.push_back(i - pattern.length() - 1);
        }
    }
    
    return result;
}

// Example usage
int main() {
    string text = "ababcabababa";
    string pattern = "aba";
    
    vector<int> positions = findPatternZ(text, pattern);
    
    cout << "Pattern found at positions: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;
    
    // Example 2
    text = "ababababa";
    pattern = "aba";
    positions = findPatternZ(text, pattern);
    
    cout << "Pattern found at positions: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Z-Algorithm Complexity

- **Time Complexity**: O(n + m), where n is the length of the text and m is the length of the pattern
- **Space Complexity**: O(n + m) for storing the concatenated string and Z array

## Related LeetCode Problems

1. **Leetcode 28: Find the Index of the First Occurrence in a String**
   - Description: Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
   - Link: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/

2. **Leetcode 1392: Longest Happy Prefix**
   - Description: A string is called a happy prefix if it is a non-empty prefix which is also a suffix.
   - Link: https://leetcode.com/problems/longest-happy-prefix/
   - Note: Can be solved using Z-algorithm to find the longest prefix that is also a suffix.

3. **Leetcode 459: Repeated Substring Pattern**
   - Description: Check if a string can be constructed by taking a substring and repeating it.
   - Link: https://leetcode.com/problems/repeated-substring-pattern/

4. **Leetcode 214: Shortest Palindrome**
   - Description: Convert a string to a palindrome by adding characters to the beginning.
   - Link: https://leetcode.com/problems/shortest-palindrome/
   - Note: Z-algorithm can be used to find the longest palindromic prefix.

## Additional Z-Algorithm Implementation for Specific Use Cases

Below is a standalone Z-algorithm implementation that can be used for specific string manipulation tasks:

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Z-Algorithm to compute the Z array directly
vector<int> calculateZ(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);
    
    // Z for first character is always 0
    // (length of matching prefix starting at position 0 is trivially the whole string)
    
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right) {
            // We're inside a Z-box, use previously computed values to initialize
            z[i] = min(right - i + 1, z[i - left]);
        }
        
        // Try to extend the Z-box
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        
        // Update Z-box if this extends beyond previous right boundary
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    
    return z;
}

// Function to solve LeetCode 28: Find the Index of the First Occurrence in a String
int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    if (needle.length() > haystack.length()) return -1;
    
    string combined = needle + "$" + haystack;
    vector<int> z = calculateZ(combined);
    
    for (int i = 0; i < z.size(); i++) {
        if (z[i] == needle.length()) {
            return i - needle.length() - 1;
        }
    }
    
    return -1;
}

int main() {
    // Demonstrate solution for LeetCode 28
    cout << "First occurrence at index: " << strStr("hello", "ll") << endl;
    cout << "First occurrence at index: " << strStr("aaaaa", "bba") << endl;
    
    // Demonstrate basic Z-array calculation
    string s = "abababa";
    vector<int> z = calculateZ(s);
    cout << "Z array for " << s << ": ";
    for (int val : z) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
```

## References

1. Gusfield, Dan. "Algorithms on Strings, Trees and Sequences: Computer Science and Computational Biology." Cambridge University Press, 1997.
2. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. "Introduction to Algorithms." MIT Press, 2009.
