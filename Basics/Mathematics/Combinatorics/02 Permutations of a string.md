# Permutations of a String

A permutation is an arrangement of all the elements of a set in a specific order. For a string with `n` distinct characters, there are `n!` possible permutations.

## Algorithms for Finding All Permutations

### 1. Backtracking Approach

The backtracking approach involves building permutations character by character:

1. Start with an empty string and gradually add characters
2. For each position, try all available characters that haven't been used yet
3. After adding a character, recursively generate all permutations with the remaining characters
4. When all characters are used, we've found one permutation

#### C++ Implementation (Backtracking)

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generatePermutationsHelper(string& s, int index, vector<string>& result) {
    // Base case: if we've processed all characters
    if (index == s.length()) {
        result.push_back(s);
        return;
    }
    
    // Try placing each character at the current position
    for (int i = index; i < s.length(); i++) {
        // Swap characters at position index and i
        swap(s[index], s[i]);
        
        // Recursively generate permutations for the next position
        generatePermutationsHelper(s, index + 1, result);
        
        // Backtrack - restore the original string
        swap(s[index], s[i]);
    }
}

vector<string> generatePermutations(string s) {
    vector<string> result;
    generatePermutationsHelper(s, 0, result);
    return result;
}

int main() {
    string input = "abc";
    vector<string> permutations = generatePermutations(input);
    
    cout << "All permutations of " << input << ":" << endl;
    for (const string& perm : permutations) {
        cout << perm << endl;
    }
    
    cout << "Total permutations: " << permutations.size() << endl;
    return 0;
}
```

### 2. STL Approach (Using next_permutation)

C++ provides a built-in function `next_permutation()` that can generate all permutations of a range:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> generatePermutationsSTL(string s) {
    vector<string> result;
    
    // Sort the string to start with the lexicographically smallest permutation
    sort(s.begin(), s.end());
    
    do {
        result.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
    
    return result;
}

int main() {
    string input = "abc";
    vector<string> permutations = generatePermutationsSTL(input);
    
    cout << "All permutations of " << input << ":" << endl;
    for (const string& perm : permutations) {
        cout << perm << endl;
    }
    
    cout << "Total permutations: " << permutations.size() << endl;
    return 0;
}
```

### 3. Heap's Algorithm

Heap's algorithm is an efficient way to generate all permutations recursively:

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void heapPermutationHelper(string& s, int size, vector<string>& result) {
    // If size is 1, we have one permutation
    if (size == 1) {
        result.push_back(s);
        return;
    }

    for (int i = 0; i < size; i++) {
        heapPermutationHelper(s, size - 1, result);

        // If size is odd, swap the first and last element
        // If size is even, swap the ith and last element
        if (size % 2 == 1) {
            swap(s[0], s[size - 1]);
        } else {
            swap(s[i], s[size - 1]);
        }
    }
}

vector<string> heapPermutation(string s) {
    vector<string> result;
    heapPermutationHelper(s, s.length(), result);
    return result;
}

int main() {
    string input = "abc";
    vector<string> permutations = heapPermutation(input);
    
    cout << "All permutations of " << input << " using Heap's Algorithm:" << endl;
    for (const string& perm : permutations) {
        cout << perm << endl;
    }
    
    cout << "Total permutations: " << permutations.size() << endl;
    return 0;
}
```

## Time and Space Complexity

For all approaches:
- Time complexity: O(n!) where n is the length of the string
- Space complexity: O(n) for recursion call stack (excluding the storage of results)

## Handling Duplicates

If the string contains duplicate characters, we need to modify our approach to avoid duplicate permutations:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

vector<string> generatePermutationsWithDuplicates(string s) {
    set<string> uniquePermutations;
    
    // Sort the string to start with the lexicographically smallest permutation
    sort(s.begin(), s.end());
    
    do {
        uniquePermutations.insert(s);
    } while (next_permutation(s.begin(), s.end()));
    
    return vector<string>(uniquePermutations.begin(), uniquePermutations.end());
}

int main() {
    string input = "aba"; // Contains duplicate 'a'
    vector<string> permutations = generatePermutationsWithDuplicates(input);
    
    cout << "All unique permutations of " << input << ":" << endl;
    for (const string& perm : permutations) {
        cout << perm << endl;
    }
    
    cout << "Total unique permutations: " << permutations.size() << endl;
    return 0;
}
```

## Related LeetCode Problems

1. [46. Permutations](https://leetcode.com/problems/permutations/) - Generate all permutations of an array of distinct integers
2. [47. Permutations II](https://leetcode.com/problems/permutations-ii/) - Generate all unique permutations of an array with possibly duplicate integers
3. [31. Next Permutation](https://leetcode.com/problems/next-permutation/) - Find the lexicographically next greater permutation
4. [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/) - Find the kth permutation sequence
5. [784. Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation/) - Generate all possible strings by changing the case of letters

## Key Takeaways

1. The backtracking approach is intuitive and can be adapted for many problems
2. STL's `next_permutation()` provides a convenient way to generate permutations in C++
3. Heap's algorithm is efficient for generating permutations without extra space
4. When dealing with duplicate characters, we need an additional mechanism to avoid duplicate permutations
5. The number of permutations grows factorially with the length of the string, making it impractical for long strings
