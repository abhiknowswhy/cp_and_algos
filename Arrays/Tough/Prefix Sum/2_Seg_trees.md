# Segment tree customizations

Segment Trees can handle a wide variety of aggregation operations including

- Sum
- XOR
- AND / OR
- min / max
- GCD / LCM
- Range frequency counting.

This flexibility comes from the tree’s ability to store any `Associative function` at each node and recompute changes efficiently.

```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <climits>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;
    function<int(int, int)> combine;
    int defaultValue;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid);
            build(2 * node + 2, mid + 1, end);
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return defaultValue;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int leftResult = query(2 * node + 1, start, mid, l, r);
        int rightResult = query(2 * node + 2, mid + 1, end, l, r);
        return combine(leftResult, rightResult);
    }

    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            tree[node] = value;
            arr[index] = value;
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                update(2 * node + 1, start, mid, index, value);
            } else {
                update(2 * node + 2, mid + 1, end, index, value);
            }
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

public:
    SegmentTree(vector<int>& inputArr, function<int(int, int)> aggFunc, int defaultVal) {
        n = inputArr.size();
        arr = inputArr;
        combine = aggFunc;
        defaultValue = defaultVal;
        tree.resize(4 * n, defaultValue);
        build(0, 0, n - 1);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

    void update(int index, int value) {
        update(0, 0, n - 1, index, value);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};

    SegmentTree sumTree(arr, [](int a, int b) { return a + b; }, 0);
    cout << "Sum of range (1, 3): " << sumTree.query(1, 3) << endl;
    sumTree.update(1, 10);
    cout << "Sum of range (1, 3) after update: " << sumTree.query(1, 3) << endl;

    SegmentTree minTree(arr, [](int a, int b) { return min(a, b); }, INT_MAX);
    cout << "Min of range (1, 3): " << minTree.query(1, 3) << endl;

    SegmentTree maxTree(arr, [](int a, int b) { return max(a, b); }, INT_MIN);
    cout << "Max of range (1, 3): " << maxTree.query(1, 3) << endl;

    SegmentTree gcdTree(arr, [](int a, int b) { return gcd(a, b); }, 0);
    cout << "GCD of range (1, 3): " << gcdTree.query(1, 3) << endl;

    SegmentTree lcmTree(arr, [](int a, int b) { return (a * b) / gcd(a, b); }, 1);
    cout << "LCM of range (1, 3): " << lcmTree.query(1, 3) << endl;

    SegmentTree andTree(arr, [](int a, int b) { return a & b; }, INT_MAX);
    cout << "Bitwise AND of range (1, 3): " << andTree.query(1, 3) << endl;

    SegmentTree orTree(arr, [](int a, int b) { return a | b; }, 0);
    cout << "Bitwise OR of range (1, 3): " << orTree.query(1, 3) << endl;

    SegmentTree xorTree(arr, [](int a, int b) { return a ^ b; }, 0);
    cout << "Bitwise XOR of range (1, 3): " << xorTree.query(1, 3) << endl;

    SegmentTree productTree(arr, [](int a, int b) { return a * b; }, 1);
    cout << "Product of range (1, 3): " << productTree.query(1, 3) << endl;

    return 0;
}
```
