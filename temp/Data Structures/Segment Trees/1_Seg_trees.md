# Segment Tree

A segment tree is a binary tree data structure used for efficiently answering range queries and updating elements in an array. It's particularly useful when:

- You have an array.
- You need to perform multiple range queries (e.g., sum, min, max, GCD, etc.).
- You need to frequently update elements of the array.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(const vector<int>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            build(data, 2 * node, start, mid);
            build(data, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // No overlap
        }
        if (l <= start && end <= r) {
            return tree[node]; // Total overlap
        }
        // Partial overlap
        int mid = (start + end) / 2;
        int left_sum = query(2 * node, start, mid, l, r);
        int right_sum = query(2 * node + 1, mid + 1, end, l, r);
        return left_sum + right_sum;
    }

    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                update(2 * node, start, mid, index, value);
            } else {
                update(2 * node + 1, mid + 1, end, index, value);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }

    int range_sum(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void point_update(int index, int value) {
        update(1, 0, n - 1, index, value);
    }
};

int main() {
    vector<int> data = {2, 4, 5, 7, 8, 9};
    SegmentTree segTree(data);

    cout << "Sum of range [1, 4]: " << segTree.range_sum(1, 4) << endl;

    segTree.point_update(2, 10);
    cout << "After updating index 2 to 10\n";
    cout << "Sum of range [1, 4]: " << segTree.range_sum(1, 4) << endl;

    return 0;
}
```
