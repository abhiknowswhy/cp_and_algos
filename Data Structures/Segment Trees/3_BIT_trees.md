# BIT Tree (Fenwick tree)

A Fenwick Tree or Binary Indexed Tree (BIT) is a simpler and more space-efficient structure optimized for prefix-based operations like prefix sum and prefix XOR.

Unlike Segment tree, fenwick tree doesn't support range queries for operations which don't have inverses.

Fenwick tree supports only `Associative and Invertible` operations

- Sum
- Product
- Frequency counting
- XOR

```cpp
#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
    vector<int> bit; // Binary Indexed Tree array
    int n;

public:
    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0); // 1-based indexing
    }

    // Update the tree at index 'i' with value 'delta'
    void update(int i, int delta) {
        while (i <= n) {
            bit[i] += delta;
            i += i & -i; // move to the next index
        }
    }

    // Get prefix sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & -i; // move to the parent index
        }
        return sum;
    }

    // Get the range sum from l to r (inclusive)
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    vector<int> arr = {0, 3, 2, -1, 6, 5, 4, -3}; // 1-based indexing (0th index is dummy)
    int n = arr.size() - 1;

    FenwickTree ft(n);

    // Build the tree
    for (int i = 1; i <= n; i++) {
        ft.update(i, arr[i]);
    }

    cout << "Sum of first 5 elements: " << ft.query(5) << endl;
    cout << "Sum from index 3 to 6: " << ft.rangeQuery(3, 6) << endl;

    // Update index 4 by +2
    ft.update(4, 2);
    cout << "After updating index 4 by +2, sum from index 3 to 6: " << ft.rangeQuery(3, 6) << endl;

    return 0;
}
```

## Explanation:

### 📊 BIT Range Table (for reference)

Let's start with a BIT tree array of size 8. The array would contain the following elements.

| Index (i) | `bit[i]` stores sum of              |
| --------- | ----------------------------------- |
| 1         | `arr[1]`                            |
| 2         | `arr[1] + arr[2]`                   |
| 3         | `arr[3]`                            |
| 4         | `arr[1] + arr[2] + arr[3] + arr[4]` |
| 5         | `arr[5]`                            |
| 6         | `arr[5] + arr[6]`                   |
| 7         | `arr[7]`                            |
| 8         | `arr[1] + ... + arr[8]`             |

---

### ✅ `update(3, 5)`

We want to add `5` to `arr[3]`. So we update all `bit[i]` that include `arr[3]` in their sum.

```
i = 3
bit[3] += 5        // bit[3] stores arr[3]
i += i & -i = 3 + 1 = 4

bit[4] += 5        // bit[4] stores arr[1] + arr[2] + arr[3] + arr[4]
i += i & -i = 4 + 4 = 8

bit[8] += 5        // bit[8] stores arr[1] + ... + arr[8]
i += i & -i = 8 + 8 = 16 → exit (out of bounds)
```

✅ Final update complete: `bit[3]`, `bit[4]`, and `bit[8]` are incremented by `5`.

---

### 🔍 `query(6)`

We want the prefix sum from `arr[1]` to `arr[6]`.

```
i = 6
sum += bit[6]        // bit[6] stores arr[5] + arr[6]
i -= i & -i = 6 - 2 = 4

sum += bit[4]        // bit[4] stores arr[1] + arr[2] + arr[3] + arr[4]
i -= i & -i = 4 - 4 = 0 → exit
```

✅ Final sum = `arr[1] + arr[2] + ... + arr[6]`

---

Let me know if you'd like to try a `query(7)` or `update(5, 2)` next!
