This is something that **trips up even experienced coders** — the different binary search loop styles (`while (l < r)` vs `while (l <= r)`) and how to adapt them to problems like _search, lower bound, upper bound, floor/ceil_.

Let’s go step by step.

---

## 🔹 Two Main Binary Search Loop Styles

### 1. **Closed interval (`[l, r]`)**

- Invariant: search space includes both ends.
- Loop: `while (l <= r)`
- Midpoint: `mid = l + (r - l) / 2`
- Updates:

  - If `nums[mid] < target`, move left bound up: `l = mid + 1`.
  - If `nums[mid] > target`, move right bound down: `r = mid - 1`.

- When loop ends: `l` is the first index where `target` could be inserted.

This is the **classic template** (used in "search insert position" problems).

---

### 2. **Half-open interval (`[l, r)`)**

- Invariant: search space is `[l, r)`, i.e. `l` inclusive, `r` exclusive.
- Loop: `while (l < r)`
- Midpoint: `mid = l + (r - l) / 2`
- Updates:

  - If `nums[mid] < target`, `l = mid + 1`.
  - Else, `r = mid`.

- When loop ends: `l == r` and is the **lower bound** (first index ≥ target).

This style is very neat when you want to mimic **`lower_bound` and `upper_bound`**.

---

## 🔹 Patterns: How to Get What You Want

1. **Find exact index of `target`**

   ```cpp
   int l = 0, r = n - 1;
   while (l <= r) {
       int mid = l + (r - l) / 2;
       if (nums[mid] == target) return mid;
       else if (nums[mid] < target) l = mid + 1;
       else r = mid - 1;
   }
   return -1; // not found
   ```

2. **First index `>= target` (lower bound)**

   ```cpp
   int l = 0, r = n;
   while (l < r) {
       int mid = l + (r - l) / 2;
       if (nums[mid] < target) l = mid + 1;
       else r = mid;
   }
   return l; // first index with nums[l] >= target
   ```

3. **First index `> target` (upper bound)**

   ```cpp
   int l = 0, r = n;
   while (l < r) {
       int mid = l + (r - l) / 2;
       if (nums[mid] <= target) l = mid + 1;
       else r = mid;
   }
   return l; // first index with nums[l] > target
   ```

4. **Last index `<= target` (floor)**
   This is basically upper bound - 1:

   ```cpp
   int l = 0, r = n;
   while (l < r) {
       int mid = l + (r - l) / 2;
       if (nums[mid] <= target) l = mid + 1;
       else r = mid;
   }
   return l - 1; // last index with nums[idx] <= target
   ```

---

## 🔹 When to Use `l <= r` vs `l < r`

- Use **`while (l <= r)`** when:

  - You are working with **closed intervals** `[l, r]`.
  - You need to check mid directly for equality (`nums[mid] == target`).
  - Example: _search exact index, search insert position._

- Use **`while (l < r)`** when:

  - You are working with **half-open intervals** `[l, r)`.
  - You want **bounds (lower/upper)** rather than exact match.
  - Example: _first element ≥ target, first element > target, last element ≤ target._

---

## 🔹 Quick Summary Table

| Goal                            | Loop Style       | Return      |
| ------------------------------- | ---------------- | ----------- |
| Search exact element            | `while (l <= r)` | index or -1 |
| First index `>= target` (lower) | `while (l < r)`  | `l`         |
| First index `> target` (upper)  | `while (l < r)`  | `l`         |
| Last index `<= target` (floor)  | `while (l < r)`  | `l - 1`     |

---

👉 Pro tip:
If you’re unsure, always start with \*\*`l = 0, r = n` and while (l < r)`** (half-open). It matches how STL `lower_bound`/`upper_bound\` behave in C++ and is less bug-prone.

---

Do you want me to also make a **visual example walkthrough** (like with an array `[1,3,5,6]` and target `5` / `2` / `7`) so you can see how each variant behaves step by step?
