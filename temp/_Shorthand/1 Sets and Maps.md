
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
