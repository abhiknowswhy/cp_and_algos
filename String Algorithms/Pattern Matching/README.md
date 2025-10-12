A comparison of the three major string matching algorithms: **Boyer-Moore**, **Knuth-Morris-Pratt (KMP)**, and **Rabin-Karp**.

---

### 1. **Boyer-Moore (BM)**

**Strategy**:
Searches from **right to left** of the pattern and uses **two heuristics**:

- **Bad Character**: Mismatch? Align last occurrence of that char in pattern.
- **Good Suffix**: Some suffix matched? Align with earlier matching part.

**Best Case**: Skips large parts of the text
**Time Complexity**:

- Best: `O(n/m)`
- Worst: `O(n + m)`
- Preprocessing: `O(m + alphabet size)`

**Use When**: Large alphabet, long patterns, performance critical.

---

### 2. **Knuth-Morris-Pratt (KMP)**

**Strategy**:
Searches from **left to right**, and avoids backtracking by precomputing a **prefix table** (LPS = Longest Prefix Suffix).

**Key Idea**:
On mismatch, **reuse partial matches** rather than starting over.

**Time Complexity**:

- Always: `O(n + m)`
- Preprocessing: `O(m)`

**Use When**: Consistent linear time required, deterministic behavior.

---

### 3. **Rabin-Karp (RK)**

**Strategy**:
Uses **hashing** (e.g., rolling hash) to compare substrings.
If hash matches, then check actual characters to confirm (to avoid false positives).

**Key Idea**:
Convert pattern and text windows to numbers → compare hashes.

**Time Complexity**:

- Best/Average: `O(n + m)`
- Worst: `O(n * m)` (many hash collisions)
- Preprocessing: `O(m)`

**Use When**: Multiple pattern search or approximate matching (e.g., plagiarism detection).

---

## Comparison Table

| Feature            | Boyer-Moore          | KMP              | Rabin-Karp                           |
| ------------------ | -------------------- | ---------------- | ------------------------------------ |
| Match Direction    | Right to left        | Left to right    | Left to right                        |
| Uses Heuristics?   | Yes (2)              | No               | Hashing                              |
| Preprocessing Time | `O(m + σ)`           | `O(m)`           | `O(m)`                               |
| Worst Time         | `O(n + m)`           | `O(n + m)`       | `O(n * m)`                           |
| Best Case          | Very fast (`O(n/m)`) | `O(n + m)`       | `O(n + m)`                           |
| Space Complexity   | `O(m + σ)`           | `O(m)`           | `O(1)` (or `O(n)` if storing hashes) |
| Pros               | Skips large chunks   | Consistent speed | Easy for multiple patterns           |
| Cons               | Complex to implement | Can’t skip ahead | Hash collisions risk                 |

---

Let’s walk through a **side-by-side visual example** of how **Boyer-Moore**, **KMP**, and **Rabin-Karp** work on the **same input**:

---

### Example:

- **Text**: `"ababcabcabababd"`
- **Pattern**: `"ababd"`
- Pattern length = 5, Text length = 15

---

## 1. **Knuth-Morris-Pratt (KMP)**

### ➤ Step-by-step:

**Preprocessing LPS array** for pattern `"ababd"`:

| i   | 0   | 1   | 2   | 3   | 4   |
| --- | --- | --- | --- | --- | --- |
| P   | a   | b   | a   | b   | d   |
| LPS | 0   | 0   | 1   | 2   | 0   |

- It tells us how many characters can be reused after mismatch.

#### Matching:

```
T: a b a b c a b c a b a b a b d
             ↑
P: a b a b d
```

- Mismatch at 'c' vs 'd', LPS\[4] = 0 → move pattern forward without resetting to 0.

Match found at index **10**

---

## 2. **Boyer-Moore (BM)**

(Using **bad character + good suffix**)

### Matching:

- Start from **right end** of pattern (`'d'`).
- Align with position in text, compare backwards.
- On mismatch, use **bad char table** and **good suffix rule** to jump.

```
T: a b a b c a b c a b a b a b d
                           ↑
P:             a b a b d
                           ↑
```

- Fast skips: jumps ahead based on mismatches.
- In this example, it jumps over `"abc"` parts faster than KMP.

Match found at index **10**

---

## 3. **Rabin-Karp (RK)**

### ➤ Step-by-step:

- Compute hash of `"ababd"` (e.g., using base 256 and mod 101)
- Slide a window of length 5 over text, compute rolling hash at each step.

```
Window 0–4: "ababc" → hash1 ≠ hashP
Window 1–5: "babca" → hash2 ≠ hashP
...
Window 10–14: "ababd" → hash = hashP → compare characters
```

Match found at index **10**

---

## Summary Table (on this input)

| Step          | KMP         | Boyer-Moore    | Rabin-Karp      |
| ------------- | ----------- | -------------- | --------------- |
| Preprocessing | LPS table   | Bad char + GS  | Hash of pattern |
| Comparisons   | Linear      | Skipped chunks | Hash + verify   |
| Match found   | At index 10 | At index 10    | At index 10     |

---

## Key Observations:

- **BM** may skip the most characters (fastest in practice).
- **KMP** guarantees no backtracking, great for real-time systems.
- **RK** is great for bulk searches but slower with collisions.

---
