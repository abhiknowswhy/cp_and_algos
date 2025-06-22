# Substrings and Subsequences

## Definitions

### Substring

A substring is a contiguous sequence of characters within a string. For a string of length n, there are n(n+1)/2 possible substrings.

Example: For string "abc", the substrings are:

- Single character: "a", "b", "c"
- Two characters: "ab", "bc"
- Three characters: "abc"

### Subsequence

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements. For a string of length n, there are 2^n possible subsequences.

Example: For string "abc", the subsequences are:

- Empty string: ""
- Single character: "a", "b", "c"
- Two characters: "ab", "ac", "bc"
- Three characters: "abc"

## Algorithms

### Finding All Substrings

#### Algorithm:

1. For each position i in the string (0 to length-1):
   - For each length j (1 to length-i):
     - Generate a substring starting at position i with length j

#### Time Complexity:

- O(n²) where n is the length of the string

#### C++ Implementation:

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> getAllSubstrings(const string& s) {
    vector<string> result;
    int n = s.length();
  
    // Generate all substrings
    for (int i = 0; i < n; i++) {
        for (int len = 1; i + len <= n; len++) {
            result.push_back(s.substr(i, len));
        }
    }
  
    return result;
}

// Example usage of getAllSubstrings
int main() {
    string s = "abc";
    cout << "Finding all substrings of: " << s << endl;
  
    vector<string> substrings = getAllSubstrings(s);
  
    cout << "All substrings (" << substrings.size() << "):" << endl;
    for (const string& substring : substrings) {
        cout << "\"" << substring << "\"" << endl;
    }
  
    return 0;
}
```

### Finding All Subsequences

#### Algorithm 1: Recursion

1. For each character in the string:
   - Either include it in the current subsequence
   - Or exclude it from the current subsequence

#### Algorithm 2: Binary Counter (Iterative)

1. For each number from 0 to 2^n - 1:
   - Convert the number to binary
   - Include characters from the original string where the corresponding bit is 1

#### Time Complexity:

- O(n * 2^n) where n is the length of the string

#### C++ Implementation (Recursive):

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generateSubsequences(const string& s, string current, int index, vector<string>& result) {
    if (index == s.length()) {
        if (!current.empty()) { // Skip empty subsequence if needed
            result.push_back(current);
        }
        return;
    }
  
    // Exclude current character
    generateSubsequences(s, current, index + 1, result);
  
    // Include current character
    generateSubsequences(s, current + s[index], index + 1, result);
}

vector<string> getAllSubsequences(const string& s) {
    vector<string> result;
    generateSubsequences(s, "", 0, result);
    return result;
}

// Example usage of recursive subsequence generation
int main() {
    string s = "abc";
    cout << "Finding all subsequences of: " << s << endl;
  
    vector<string> subsequences = getAllSubsequences(s);
  
    cout << "All subsequences (" << subsequences.size() << "):" << endl;
    for (const string& subsequence : subsequences) {
        cout << "\"" << subsequence << "\"" << endl;
    }
  
    return 0;
}
```

#### C++ Implementation (Iterative - Binary Counter):

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> getAllSubsequences(const string& s) {
    vector<string> result;
    int n = s.length();
  
    // 2^n possible subsequences (including empty string)
    int totalSubsequences = 1 << n;
  
    // Generate each subsequence using binary representation
    for (int i = 1; i < totalSubsequences; i++) {
        string subsequence = "";
        for (int j = 0; j < n; j++) {
            // Check if jth bit is set in i
            if (i & (1 << j)) {
                subsequence += s[j];
            }
        }
        result.push_back(subsequence);
    }
  
    return result;
}

// Example usage of iterative subsequence generation
int main() {
    string s = "abc";
    cout << "Finding all subsequences of: " << s << endl;
  
    vector<string> subsequences = getAllSubsequences(s);
  
    cout << "All subsequences (" << subsequences.size() << "):" << endl;
    for (const string& subsequence : subsequences) {
        cout << "\"" << subsequence << "\"" << endl;
    }
  
    return 0;
}
```

## Combined Executable Example:

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to get all substrings
vector<string> getAllSubstrings(const string& s) {
    vector<string> result;
    int n = s.length();
  
    for (int i = 0; i < n; i++) {
        for (int len = 1; i + len <= n; len++) {
            result.push_back(s.substr(i, len));
        }
    }
  
    return result;
}

// Function to get all subsequences (recursive approach)
void generateSubsequencesRecursive(const string& s, string current, int index, vector<string>& result) {
    if (index == s.length()) {
        if (!current.empty()) {
            result.push_back(current);
        }
        return;
    }
  
    // Exclude current character
    generateSubsequencesRecursive(s, current, index + 1, result);
  
    // Include current character
    generateSubsequencesRecursive(s, current + s[index], index + 1, result);
}

vector<string> getAllSubsequencesRecursive(const string& s) {
    vector<string> result;
    generateSubsequencesRecursive(s, "", 0, result);
    return result;
}

// Function to get all subsequences (iterative approach)
vector<string> getAllSubsequencesIterative(const string& s) {
    vector<string> result;
    int n = s.length();
  
    // 2^n possible subsequences (excluding empty string)
    int totalSubsequences = 1 << n;
  
    for (int i = 1; i < totalSubsequences; i++) {
        string subsequence = "";
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subsequence += s[j];
            }
        }
        result.push_back(subsequence);
    }
  
    return result;
}

// Function to print vector of strings
void printStrings(const vector<string>& strings, const string& label) {
    cout << label << " (" << strings.size() << "):" << endl;
    for (const string& str : strings) {
        cout << "\"" << str << "\" ";
    }
    cout << endl << endl;
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;
  
    // Get and print all substrings
    vector<string> substrings = getAllSubstrings(s);
    printStrings(substrings, "All substrings");
  
    // Get and print all subsequences using recursive approach
    vector<string> subsequencesRecursive = getAllSubsequencesRecursive(s);
    printStrings(subsequencesRecursive, "All subsequences (recursive)");
  
    // Get and print all subsequences using iterative approach
    vector<string> subsequencesIterative = getAllSubsequencesIterative(s);
    printStrings(subsequencesIterative, "All subsequences (iterative)");
  
    return 0;
}
```

## LeetCode Problems

### Substring Problems:

1. [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
2. [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
3. [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
4. [187. Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/)
5. [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

### Subsequence Problem

1. [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)
2. [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)
3. [392. Is Subsequence](https://leetcode.com/problems/is-subsequence/)
4. [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)
5. [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)

## Optimizations and Variations

### Palindromic Substrings

- For finding all palindromic substrings, can use dynamic programming or expand around center.
- LeetCode Problem: [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)

### Efficient Substring Matching

- For substring searches, consider using algorithms like KMP (Knuth-Morris-Pratt), Rabin-Karp, or suffix arrays.

### Longest Common Subsequence

- Dynamic programming problem to find the longest subsequence common to two strings.
- Time complexity: O(m*n) where m and n are string lengths.

### Counting vs. Generating

- For very large strings, often you just need to count rather than generate all substrings/subsequences.
- For substrings: n(n+1)/2 in total
- For subsequences: 2^n - 1 (excluding empty string) or 2^n (including empty string)
