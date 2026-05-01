# Union Find (Disjoint Set Union) Algorithm

Union Find is a data structure that tracks a set of elements partitioned into disjoint (non-overlapping) subsets. It supports two primary operations efficiently: finding which subset an element belongs to, and merging two subsets together.

## How it works

1. Initialize each element as its own parent (each element is its own set)
2. Apply **Path Compression** in `find()`:
   - While finding the root of an element, make every visited node point directly to the root
3. Apply **Union by Rank** in `union()`:
   - Always attach the smaller tree under the root of the larger tree
   - This keeps the tree flat and operations fast
4. Two elements are in the same set if and only if they share the same root

## Time Complexity

- O(α(N)) per operation (nearly O(1)), where α is the inverse Ackermann function — effectively constant for all practical input sizes

## Space Complexity

- O(N) for storing the `parent` and `rank` arrays

## Implementation in C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i; // Each element is its own parent initially
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Flatten the tree
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false; // Already in the same set

        if (rank[rootX] < rank[rootY])
            swap(rootX, rootY);

        parent[rootY] = rootX; // Attach smaller tree under larger
        if (rank[rootX] == rank[rootY])
            rank[rootX]++;

        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    UnionFind uf(6); // 6 elements: 0 to 5

    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);

    cout << "Union Find connectivity checks:\n";
    cout << "0 and 2 connected? " << (uf.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "0 and 3 connected? " << (uf.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "3 and 4 connected? " << (uf.connected(3, 4) ? "Yes" : "No") << endl;

    uf.unite(2, 3); // Merge the two components
    cout << "After uniting 2 and 3:\n";
    cout << "0 and 4 connected? " << (uf.connected(0, 4) ? "Yes" : "No") << endl;

    return 0;
}
```

## Example Explanation

In the example above:
- We create a Union Find structure for 6 elements (0 to 5)
- After `unite(0,1)` and `unite(1,2)`, elements 0, 1, and 2 form one component
- After `unite(3,4)`, elements 3 and 4 form a separate component
- Element 5 remains isolated in its own set
- `connected(0, 2)` returns **Yes** — same component
- `connected(0, 3)` returns **No** — different components
- After `unite(2, 3)`, all of 0–4 merge into a single component, so `connected(0, 4)` returns **Yes**

## Common Applications

- **Kruskal's MST algorithm** — detecting cycles while building a minimum spanning tree
- **Network connectivity** — checking if two nodes are in the same network
- **Image processing** — connected component labeling
- **Percolation problems** — used in physics/engineering simulations

## Sample leetcode questions

- https://leetcode.com/problems/find-if-path-exists-in-graph/description/
- https://leetcode.com/problems/number-of-provinces/description/
- https://leetcode.com/problems/accounts-merge/description/
- https://leetcode.com/problems/redundant-connection/description/
- https://leetcode.com/problems/redundant-connection/description/
- https://leetcode.com/problems/number-of-operations-to-make-network-connected/
- https://leetcode.com/problems/smallest-string-with-swaps/description/
- https://leetcode.com/problems/bricks-falling-when-hit/description/
