
# Sets and Maps in C++ STL

## Set Containers

| Operation | Description | Set (Red-Black Tree) | Multiset (Red-Black Tree) | Unordered Set (Hash Table) | Unordered Multiset (Hash Table) |
|-----------|-------------|-------------------------|------------------------------|-------------------------------|-----------------------------------|
| `insert(val)` | Insert element | O(log n) | O(log n), Allows duplicates | O(1) avg, O(n) worst | O(1) avg, O(n) worst, Allows duplicates |
| `erase(val)` | Remove element | O(log n), Removes single value | O(log n), Removes all instances | O(1) avg, O(n) worst, Removes single value | O(1) avg, O(n) worst, Removes all instances |
| `erase(it)` | Remove at iterator | O(1) amortized | O(1) amortized | O(1) avg | O(1) avg |
| `find(val)` | Find element | O(log n) | O(log n), First occurrence | O(1) avg, O(n) worst | O(1) avg, O(n) worst, First occurrence |
| `count(val)` | Count occurrences | O(log n), Returns 0 or 1 | O(log n + count) | O(1) avg, O(n) worst, Returns 0 or 1 | O(1) avg, O(n) worst + count |
| `lower_bound(val)` | First element ≥ val | O(log n) | O(log n) | Not supported | Not supported |
| `upper_bound(val)` | First element > val | O(log n) | O(log n) | Not supported | Not supported |
| `equal_range(val)` | Range of equal elements | O(log n) | O(log n) | O(count) avg | O(count) avg |
| `size()` | Number of elements | O(1) | O(1) | O(1) | O(1) |
| `empty()` | Check if empty | O(1) | O(1) | O(1) | O(1) |
| `clear()` | Remove all elements | O(n) | O(n) | O(n) | O(n) |
| `begin()`, `end()` | Iterators | O(1) | O(1) | O(1) | O(1) |
| `rehash(n)` | Set bucket count | Not applicable | Not applicable | O(n) | O(n) |
| `load_factor()` | Get load factor | Not applicable | Not applicable | O(1) | O(1) |

### Implementation Details:

- **Set/Multiset**: Implemented as balanced binary search trees (typically Red-Black Trees)
  - Elements are always sorted
  - Guaranteed log(n) time complexity for most operations
  - Iterating yields elements in sorted order

- **Unordered Set/Multiset**: Implemented as hash tables
  - Faster lookups on average (O(1))
  - No inherent ordering of elements
  - Performance depends on hash function and load factor
  - May degrade to O(n) in worst case (many collisions)

#### Usage

```cpp
// Set example
set<int> s;
s.insert(3);
s.insert(1);
s.insert(2);   // Set: {1, 2, 3}
s.insert(2);   // Duplicate ignored, set remains {1, 2, 3}

// Multiset example
multiset<int> ms;
ms.insert(3);
ms.insert(1);
ms.insert(3);  // Multiset: {1, 3, 3}

// Erase single occurrence in multiset
auto it = ms.find(3);
if (it != ms.end()) {
    ms.erase(it);  // Erases only one 3
}
```


## Map Containers

| Operation | Description | Map (Red-Black Tree) | Multimap (Red-Black Tree) | Unordered Map (Hash Table) | Unordered Multimap (Hash Table) |
|-----------|-------------|-------------------------|------------------------------|-------------------------------|-----------------------------------|
| `insert({key,val})` | Insert key-value pair | O(log n), Unique keys | O(log n), Allows duplicate keys | O(1) avg, O(n) worst, Unique keys | O(1) avg, O(n) worst, Allows duplicate keys |
| `map[key] = val` | Insert/update value | O(log n), Not available in multimap | Not available | O(1) avg, O(n) worst, Not available in multimap | Not available |
| `erase(key)` | Remove by key | O(log n) | O(log n + count), Removes all with key | O(1) avg, O(n) worst | O(1) avg, O(n) worst + count, Removes all with key |
| `erase(it)` | Remove at iterator | O(1) amortized | O(1) amortized | O(1) avg | O(1) avg |
| `find(key)` | Find by key | O(log n) | O(log n), First occurrence | O(1) avg, O(n) worst | O(1) avg, O(n) worst, First occurrence |
| `count(key)` | Count occurrences | O(log n), Returns 0 or 1 | O(log n + count) | O(1) avg, O(n) worst, Returns 0 or 1 | O(1) avg, O(n) worst + count |
| `lower_bound(key)` | First pair with key ≥ specified key | O(log n) | O(log n) | Not supported | Not supported |
| `upper_bound(key)` | First pair with key > specified key | O(log n) | O(log n) | Not supported | Not supported |
| `equal_range(key)` | Range with specified key | O(log n) | O(log n) | O(count) avg | O(count) avg |
| `size()` | Number of pairs | O(1) | O(1) | O(1) | O(1) |
| `empty()` | Check if empty | O(1) | O(1) | O(1) | O(1) |
| `clear()` | Remove all pairs | O(n) | O(n) | O(n) | O(n) |
| `begin()`, `end()` | Iterators | O(1) | O(1) | O(1) | O(1) |
| `rehash(n)` | Set bucket count | Not applicable | Not applicable | O(n) | O(n) |
| `load_factor()` | Get load factor | Not applicable | Not applicable | O(1) | O(1) |

### Implementation Details:

- **Map/Multimap**: Implemented as balanced binary search trees (typically Red-Black Trees)
  - Keys are always sorted
  - Key-value pairs are stored as `std::pair<const Key, T>`
  - Guaranteed log(n) time complexity for most operations
  - Iterating yields elements in key-sorted order

- **Unordered Map/Multimap**: Implemented as hash tables
  - Keys are hashed to determine bucket location
  - Faster lookups on average (O(1))
  - No inherent ordering of keys
  - Performance depends on hash function and load factor
  - May degrade to O(n) in worst case (many collisions)

#### Usage

```cpp
// Map example
map<string, int> m;
m["apple"] = 5;
m.insert({"banana", 3});
m["apple"] = 7;  // Updates value, map contains {("apple",7), ("banana",3)}

// Multimap example
multimap<string, int> mm;
mm.insert({"apple", 5});
mm.insert({"banana", 3});
mm.insert({"apple", 7});  // Multimap: {("apple",5), ("apple",7), ("banana",3)}

// Access all values with a specific key in multimap
auto range = mm.equal_range("apple");
for (auto it = range.first; it != range.second; ++it) {
    cout << it->second << " ";  // Outputs: 5 7
}
```

### Unordered Set & Map
```cpp
// Unordered set
unordered_set<int> us;
us.insert(3);
us.insert(1);
us.insert(2);  // Order not guaranteed: e.g., {2, 3, 1}

// Unordered map
unordered_map<string, int> um;
um["apple"] = 5;
um.insert({"banana", 3});  // Order not guaranteed
```

### Custom Hash Functions for Non-Primitive Types in `unordered_map`

When using **`unordered_map`** or **`unordered_set`** with *non-primitive* or *custom data types* (like structs or pairs), you must define how to **hash** and **compare** these objects — since the STL doesn’t automatically know how to do that.

#### Why Needed

The hash table inside an `unordered_map` needs two things for your key type:

1. **Hash function** – Converts the key into a `size_t` hash value.
2. **Equality function** – Checks if two keys are equal (defaults to `operator==`).

Primitive types (like `int`, `string`, `double`) already have these defined, but custom structs or pairs do not.

---

#### Example 1: Using Custom Struct as Key

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

// Define custom hash function
struct PointHash {
    size_t operator()(const Point &p) const {
        // Combine hash of x and y
        return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
    }
};

int main() {
    unordered_map<Point, string, PointHash> umap;

    umap[{1, 2}] = "A";
    umap[{3, 4}] = "B";

    for (auto &[k, v] : umap) {
        cout << "(" << k.x << "," << k.y << ") => " << v << "\n";
    }
}
```

✅ **Key points:**

* `operator==` is required to compare keys.
* `operator()` in `PointHash` defines how to hash `Point`.
* Use bitwise operations or functions like `std::hash_combine` (C++20) to mix values.

---

#### Example 2: Hashing Standard Containers (like `pair`)

You can also define hash functions for STL containers such as `pair` or `tuple`.

```cpp
struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        return hash<T1>()(p.first) ^ (hash<T2>()(p.second) << 1);
    }
};

int main() {
    unordered_map<pair<int, int>, string, PairHash> pairMap;
    pairMap[{1, 2}] = "X";
    pairMap[{3, 4}] = "Y";

    for (auto &[k, v] : pairMap)
        cout << "(" << k.first << "," << k.second << ") => " << v << "\n";
}
```

---

#### Example 3: Using Lambdas (C++20 Onwards)

From C++20, you can also use **lambda-based custom hash** and equality directly:

```cpp
auto hash_pair = [](const pair<int, int> &p) {
    return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
};

auto eq_pair = [](const pair<int, int> &a, const pair<int, int> &b) {
    return a == b;
};

unordered_map<pair<int, int>, string, decltype(hash_pair), decltype(eq_pair)>
    umap(10, hash_pair, eq_pair);

umap[{1, 2}] = "Hello";
umap[{2, 3}] = "World";
```

---

#### Best Practices

* Always define `operator==` when using a custom type as key.
* Keep your hash function **fast** and **uniformly distributed**.
* Avoid collisions by combining multiple fields wisely (e.g., shifting and XOR).
* For multiple fields, consider using `std::hash` recursively or `std::tie`.

---

Next Section Suggestion (if you plan to extend the blog):

> **"Comparing Performance: Ordered vs Unordered Containers in Real Scenarios"** – a practical benchmark showing when `unordered_map` truly outperforms `map`.
