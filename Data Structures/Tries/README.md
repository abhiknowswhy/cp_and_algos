# Trie (Prefix Tree) Data Structure

A Trie is a tree-like data structure used to store strings where each node represents a single character. It is especially efficient for prefix-based search operations, making it the backbone of features like autocomplete, spell checkers, and IP routing tables.

## How it works

1. The root node is empty and represents the start of all strings
2. Each node contains:
   - An array (or map) of children, one per possible character
   - A boolean `isEnd` flag marking if a valid word ends at that node
3. **Insert:** Walk down the trie character by character; create nodes where they don't exist, then mark `isEnd = true` at the last character
4. **Search:** Walk down the trie character by character; return `true` only if all characters are found **and** `isEnd` is set at the last node
5. **Starts With (Prefix Search):** Same as search but skip the `isEnd` check — just confirm all prefix characters exist

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| Insert | O(L) |
| Search | O(L) |
| Prefix Search | O(L) |
| Delete | O(L) |

*where L is the length of the string/prefix*

## Space Complexity

- O(N × M) where N is the number of inserted strings and M is the average string length
- In the worst case (no shared prefixes), every character occupies its own node

## Implementation in C++

```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd;

    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie
    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c))
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    // Returns true if the exact word exists
    bool search(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c))
                return false;
            curr = curr->children[c];
        }
        return curr->isEnd;
    }

    // Returns true if any word starts with the given prefix
    bool startsWith(const string& prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (!curr->children.count(c))
                return false;
            curr = curr->children[c];
        }
        return true;
    }

    // Delete a word from the trie (recursive helper)
    bool deleteHelper(TrieNode* curr, const string& word, int depth) {
        if (!curr) return false;

        if (depth == word.size()) {
            if (!curr->isEnd) return false;
            curr->isEnd = false;
            return curr->children.empty(); // Safe to delete if no children
        }

        char c = word[depth];
        if (!curr->children.count(c)) return false;

        bool shouldDelete = deleteHelper(curr->children[c], word, depth + 1);
        if (shouldDelete) {
            delete curr->children[c];
            curr->children.erase(c);
            return curr->children.empty() && !curr->isEnd;
        }
        return false;
    }

    void remove(const string& word) {
        deleteHelper(root, word, 0);
    }
};

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apt");
    trie.insert("bat");

    cout << "Trie Operations:\n";
    cout << "search(\"app\")         : " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "search(\"apple\")       : " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "search(\"ap\")          : " << (trie.search("ap") ? "Found" : "Not Found") << endl;
    cout << "startsWith(\"app\")     : " << (trie.startsWith("app") ? "Yes" : "No") << endl;
    cout << "startsWith(\"bat\")     : " << (trie.startsWith("bat") ? "Yes" : "No") << endl;
    cout << "startsWith(\"cat\")     : " << (trie.startsWith("cat") ? "Yes" : "No") << endl;

    trie.remove("app");
    cout << "\nAfter deleting \"app\":\n";
    cout << "search(\"app\")         : " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "search(\"apple\")       : " << (trie.search("apple") ? "Found" : "Not Found") << endl;

    return 0;
}
```

## Example Explanation

In the example above:
- We insert five words: `apple`, `app`, `application`, `apt`, and `bat`
- `search("app")` returns **Found** — it was explicitly inserted with `isEnd = true`
- `search("ap")` returns **Not Found** — `ap` was never inserted; its node exists but `isEnd` is `false`
- `startsWith("app")` returns **Yes** — `app` is a valid prefix of `apple`, `app`, and `application`
- `startsWith("cat")` returns **No** — no inserted word starts with `cat`
- After `remove("app")`, searching for `app` returns **Not Found**, but `apple` remains intact since they share nodes but have independent `isEnd` flags

## Common Applications

- **Autocomplete systems** — search engines and IDEs suggest completions using prefix traversal
- **Spell checkers** — quickly validate if a word or prefix exists in a dictionary
- **IP routing (Longest Prefix Match)** — routers use tries to match destination addresses
- **Word games** — Boggle and Scrabble solvers use tries to validate words efficiently
- **DNA sequence matching** — store and query biological sequences with shared prefixes

---

Here's the combined, deduplicated list organized by difficulty with category tags:

## LeetCode Problems

### Easy
| # | Problem | Key Idea |
|---|---------|----------|
| 14 | [Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/) | Insert all strings, traverse until a branch or `isEnd` is hit |
| 720 | [Longest Word in Dictionary](https://leetcode.com/problems/longest-word-in-dictionary/) | Build trie, find longest word where every prefix is also a valid word |

### Medium
| # | Problem | Category | Key Idea |
|---|---------|----------|----------|
| 208 | [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) | Basic | Classic trie implementation — the essential starting point |
| 211 | [Design Add and Search Words](https://leetcode.com/problems/design-add-and-search-words-data-structure/) | Basic | Trie with wildcard `.` matching using DFS |
| 421 | [Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/) | Advanced | Store binary representations; greedily pick opposite bits |
| 648 | [Replace Words](https://leetcode.com/problems/replace-words/) | Advanced | Store roots in trie, replace each word with its shortest matching root |
| 676 | [Implement Magic Dictionary](https://leetcode.com/problems/implement-magic-dictionary/) | Modified | Search with exactly one character substitution allowed |
| 677 | [Map Sum Pairs](https://leetcode.com/problems/map-sum-pairs/) | Advanced | Augment trie nodes with values; sum all values under a prefix |
| 820 | [Short Encoding of Words](https://leetcode.com/problems/short-encoding-of-words/) | Modified | Insert reversed words; shared suffixes collapse into shared paths |
| 1268 | [Search Suggestions System](https://leetcode.com/problems/search-suggestions-system/) | Advanced | After each keystroke, return up to 3 lexicographically smallest matches |

### Hard
| # | Problem | Category | Key Idea |
|---|---------|----------|----------|
| 212 | [Word Search II](https://leetcode.com/problems/word-search-ii/) | Basic | Build trie from word list, DFS on board pruning with trie nodes |
| 336 | [Palindrome Pairs](https://leetcode.com/problems/palindrome-pairs/) | Advanced | Insert reversed words; for each word, check trie for palindrome-forming matches |
| 472 | [Concatenated Words](https://leetcode.com/problems/concatenated-words/) | Advanced | For each word, check if it can be split into 2+ other words in the trie |
| 745 | [Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/) | Modified | Combine prefix and suffix into a single key; use trie or hashmap for lookup |
| 1032 | [Stream of Characters](https://leetcode.com/problems/stream-of-characters/) | Advanced | Insert reversed words; match suffix of stream against trie |

