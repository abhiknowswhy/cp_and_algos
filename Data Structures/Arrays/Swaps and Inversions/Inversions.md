# Count number of inversions in an array

To count the number of **inversions** in an unsorted array efficiently, we can use a modified version of **Merge Sort**, which runs in `O(n log n)` time.

### What is an inversion?

An **inversion** is a pair `(i, j)` such that:

- `i < j` and
- `arr[i] > arr[j]`

Examples:

- [Number of reverse pairs](https://leetcode.com/problems/reverse-pairs/description/)

### C++ Code (Using Merge Sort)

```cpp
#include <iostream>
#include <vector>

using namespace std;

long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    long long invCount = 0;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
            // All remaining elements in leftArr will form inversions with rightArr[j]
            invCount += leftArr.size() - i;
        }
    }

    while (i < leftArr.size())
        arr[k++] = leftArr[i++];

    while (j < rightArr.size())
        arr[k++] = rightArr[j++];

    return invCount;
}

long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    long long invCount = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        invCount += mergeSortAndCount(arr, left, mid);
        invCount += mergeSortAndCount(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }

    return invCount;
}

int main() {
    vector<int> arr = {8, 4, 2, 1};
    long long invCount = mergeSortAndCount(arr, 0, arr.size() - 1);

    cout << "Number of inversions: " << invCount << endl;
    return 0;
}
```

---

### Example:

Input: `{8, 4, 2, 1}`
Output: `6`
Explanation: Inversions are `(8,4), (8,2), (8,1), (4,2), (4,1), (2,1)`

## Count Inversions using Binary Indexed Tree (Fenwick Tree)

This approach works by processing the array from right to left, using a BIT to keep track of the number of elements less than the current element that have already been seen. The array is first coordinate-compressed to handle large values efficiently.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BIT {
    vector<int> tree;
    int n;
public:
    BIT(int size) : n(size) { tree.assign(n + 1, 0); }
    void update(int idx, int val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }
    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

long long countInversionsBIT(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp = arr;
    sort(temp.begin(), temp.end());
    // Coordinate compression
    for (int& x : arr)
        x = lower_bound(temp.begin(), temp.end(), x) - temp.begin() + 1;
    BIT bit(n);
    long long invCount = 0;
    for (int i = n - 1; i >= 0; --i) {
        invCount += bit.query(arr[i] - 1);
        bit.update(arr[i], 1);
    }
    return invCount;
}

// Usage:
// vector<int> arr = {8, 4, 2, 1};
// cout << countInversionsBIT(arr) << endl; // Output: 6
```

---

## Count Inversions using Segment Tree

This method is similar to the BIT approach, but uses a Segment Tree for range queries and updates. It is also efficient for this problem.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;
public:
    SegmentTree(int size) : n(size) { tree.assign(4 * n, 0); }
    void update(int node, int l, int r, int idx) {
        if (l == r) {
            tree[node]++;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(2 * node, l, mid, idx);
        else update(2 * node + 1, mid + 1, r, idx);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
    }
};

long long countInversionsSegTree(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp = arr;
    sort(temp.begin(), temp.end());
    for (int& x : arr)
        x = lower_bound(temp.begin(), temp.end(), x) - temp.begin() + 1;
    SegmentTree st(n);
    long long invCount = 0;
    for (int i = n - 1; i >= 0; --i) {
        invCount += st.query(1, 1, n, 1, arr[i] - 1);
        st.update(1, 1, n, arr[i]);
    }
    return invCount;
}

// Usage:
// vector<int> arr = {8, 4, 2, 1};
// cout << countInversionsSegTree(arr) << endl; // Output: 6
```

---
