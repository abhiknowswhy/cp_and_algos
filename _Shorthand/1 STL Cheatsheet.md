# C++ STL Cheat Sheet for DSA/Competitive Programming

## Vector

- `push_back(val)` - Add element to end
- `pop_back()` - Remove last element
- `size()` - Number of elements
- `empty()` - Check if empty
- `clear()` - Remove all elements
- `front()` - First element
- `back()` - Last element
- `begin()`, `end()` - Iterators
- `insert(pos, val)` - Insert at position
- `erase(pos)` - Remove at position
- `resize(n)` - Change size
- `reserve(n)` - Reserve capacity

```cpp
vector<int> v = {1, 2, 3};
v.push_back(4);
v.insert(v.begin() + 1, 5); // Insert 5 at index 1
```

## String

- `length()`, `size()` - String length
- `substr(pos, len)` - Substring
- `find(str)` - Find substring (returns string::npos if not found)
- `push_back(char)` - Add character
- `pop_back()` - Remove last character
- `stoi(str)` - String to integer
- `stol(str)` - String to long
- `stoll(str)` - String to long long
- `to_string(num)` - Number to string
- `getline(cin, str)` - Read line with spaces

```cpp
string s = "hello";
string sub = s.substr(1, 3); // "ell"
int pos = s.find("ll"); // 2
int num = stoi("123"); // 123
```

## Arrays & Algorithms

### Sorting

- `sort(begin, end)` - Sort in ascending order
- `sort(begin, end, greater<int>())` - Sort in descending order
- `sort(begin, end, custom_comparator)` - Custom sort
- `stable_sort()` - Stable sorting
- `partial_sort(begin, middle, end)` - Partial sort
- `nth_element(begin, nth, end)` - Nth element

```cpp
vector<int> v = {3, 1, 4, 1, 5};
sort(v.begin(), v.end()); // {1, 1, 3, 4, 5}
sort(v.begin(), v.end(), greater<int>()); // {5, 4, 3, 1, 1}

// Custom comparator
sort(v.begin(), v.end(), [](int a, int b) {
    return a > b; // Descending order
});
```

### Binary Search (on sorted arrays)

- `lower_bound(begin, end, val)` - First element >= val
- `upper_bound(begin, end, val)` - First element > val
- `binary_search(begin, end, val)` - Returns true if found
- `equal_range(begin, end, val)` - Returns pair of lower_bound and upper_bound

```cpp
vector<int> v = {1, 2, 2, 3, 4};
auto it = lower_bound(v.begin(), v.end(), 2); // Points to first 2
auto it2 = upper_bound(v.begin(), v.end(), 2); // Points to 3
bool found = binary_search(v.begin(), v.end(), 2); // true
```

### Other Useful Algorithms

- `reverse(begin, end)` - Reverse elements
- `unique(begin, end)` - Remove consecutive duplicates (returns new end)
- `next_permutation(begin, end)` - Next permutation
- `prev_permutation(begin, end)` - Previous permutation
- `max_element(begin, end)` - Iterator to max element
- `min_element(begin, end)` - Iterator to min element
- `count(begin, end, val)` - Count occurrences
- `accumulate(begin, end, init)` - Sum of elements
- `iota(begin, end, start_val)` - Fill range with sequentially increasing values

```cpp
vector<int> v = {1, 2, 3};
reverse(v.begin(), v.end()); // {3, 2, 1}

vector<int> nums = {1, 1, 2, 2, 3};
auto new_end = unique(nums.begin(), nums.end());
nums.erase(new_end, nums.end()); // {1, 2, 3}

int sum = accumulate(v.begin(), v.end(), 0); // Sum of all elements

vector<int> parent(5);
iota(parent.begin(), parent.end(), 0); // parent = {0, 1, 2, 3, 4}
```

## Set

- `insert(val)` - Insert element
- `erase(val)` - Remove element
- `find(val)` - Find element (returns iterator)
- `count(val)` - Check if exists (0 or 1)
- `lower_bound(val)` - First element >= val
- `upper_bound(val)` - First element > val
- `size()` - Number of elements
- `empty()` - Check if empty

```cpp
set<int> s;
s.insert(3);
s.insert(1);
s.insert(2); // Set: {1, 2, 3}

if (s.count(2)) { /* 2 exists */ }
auto it = s.find(2);
if (it != s.end()) { /* 2 found */ }
```

## Multiset

- `insert(val)` - Insert element (allows duplicates)
- `erase(val)` - Remove all occurrences of val
- `erase(it)` - Remove element at iterator
- `count(val)` - Count occurrences of val
- `find(val)` - Find first occurrence (returns iterator)
- `lower_bound(val)` - First element >= val
- `upper_bound(val)` - First element > val
- `size()` - Number of elements
- `empty()` - Check if empty

```cpp
multiset<int> ms;
ms.insert(3);
ms.insert(1);
ms.insert(3); // Multiset: {1, 3, 3}

int count = ms.count(3); // 2 (there are two 3s)

// To erase just one occurrence
auto it = ms.find(3);
if (it != ms.end()) {
    ms.erase(it); // Erases only one 3
}
```

## Map

- `insert({key, value})` or `map[key] = value` - Insert/update
- `erase(key)` - Remove by key
- `find(key)` - Find by key
- `count(key)` - Check if key exists
- `lower_bound(key)` - First element >= key
- `upper_bound(key)` - First element > key

```cpp
map<string, int> m;
m["apple"] = 5;
m.insert({"banana", 3});

if (m.count("apple")) { /* key exists */ }
auto it = m.find("apple");
if (it != m.end()) {
    cout << it->second; // Value
}
```

## Multimap

- `insert({key, value})` - Insert key-value pair (allows duplicate keys)
- `erase(key)` - Remove all pairs with specified key
- `erase(it)` - Remove pair at iterator
- `count(key)` - Count occurrences of key
- `find(key)` - Find first occurrence of key (returns iterator)
- `lower_bound(key)` - First pair with key >= specified key
- `upper_bound(key)` - First pair with key > specified key
- `equal_range(key)` - Range containing all elements with given key
- `size()` - Number of key-value pairs
- `empty()` - Check if empty

```cpp
multimap<string, int> mm;
mm.insert({"apple", 5});
mm.insert({"banana", 3});
mm.insert({"apple", 7}); // Multimap allows duplicate keys

int count = mm.count("apple"); // 2 (there are two "apple" entries)

// To access all values with a specific key
auto range = mm.equal_range("apple");
for (auto it = range.first; it != range.second; ++it) {
    cout << it->second << " "; // 5 7
}

// To erase just one occurrence
auto it = mm.find("apple");
if (it != mm.end()) {
    mm.erase(it); // Erases only one "apple" entry
}
```

## Unordered Set & Map (Hash-based)

- Similar methods to set/map but O(1) average time
- `unordered_set<int>`, `unordered_map<string, int>`
- No ordering, but faster for lookup/insert/delete

```cpp
unordered_set<int> us;
unordered_map<string, int> um;
```

## Unordered Multiset & Multimap (Hash-based)

- Similar methods to multiset/multimap but with O(1) average time
- `unordered_multiset<int>`, `unordered_multimap<string, int>`
- Allows duplicates while maintaining O(1) operations
- No ordering, optimized for frequent insertions/lookups with duplicates

```cpp
unordered_multiset<int> ums;
ums.insert(3);
ums.insert(1);
ums.insert(3); // Contains: 3, 1, 3 (in any order)

int count = ums.count(3); // 2 (there are two 3s)

// To erase just one occurrence
auto it = ums.find(3);
if (it != ums.end()) {
    ums.erase(it); // Erases only one 3
}

// Unordered multimap example
unordered_multimap<string, int> umm;
umm.insert({"apple", 1});
umm.insert({"apple", 2}); // Multiple values for same key
```

## Queue

- `push(val)` - Add to back
- `pop()` - Remove from front
- `front()` - Front element
- `back()` - Back element
- `size()` - Number of elements
- `empty()` - Check if empty

```cpp
queue<int> q;
q.push(1);
q.push(2);
int front = q.front(); // 1
q.pop(); // Remove 1
```

## Stack

- `push(val)` - Add to top
- `pop()` - Remove from top
- `top()` - Top element
- `size()` - Number of elements
- `empty()` - Check if empty

```cpp
stack<int> st;
st.push(1);
st.push(2);
int top = st.top(); // 2
st.pop(); // Remove 2
```

## Priority Queue (Max Heap by default)

- `push(val)` - Insert element
- `pop()` - Remove top element
- `top()` - Get top element
- `size()` - Number of elements
- `empty()` - Check if empty

```cpp
priority_queue<int> pq; // Max heap
pq.push(3);
pq.push(1);
pq.push(4);
int max_val = pq.top(); // 4

// Min heap
priority_queue<int, vector<int>, greater<int>> min_pq;
```

## Deque (Double-ended queue)

- `push_front(val)` - Add to front
- `push_back(val)` - Add to back
- `pop_front()` - Remove from front
- `pop_back()` - Remove from back
- `front()`, `back()` - Access ends

```cpp
deque<int> dq;
dq.push_front(1);
dq.push_back(2); // {1, 2}
```

## Pair

- `make_pair(a, b)` - Create pair
- `pair.first` - First element
- `pair.second` - Second element

```cpp
pair<int, string> p = make_pair(1, "hello");
// or
pair<int, string> p = {1, "hello"};
cout << p.first << " " << p.second;
```

## Useful Math Functions

- `abs(x)` - Absolute value
- `max(a, b)` - Maximum of two values
- `min(a, b)` - Minimum of two values
- `swap(a, b)` - Swap two values
- `gcd(a, b)` - Greatest common divisor (C++14+)
- `pow(base, exp)` - Power function
- `sqrt(x)` - Square root
- `ceil(x)` - Ceiling
- `floor(x)` - Floor

```cpp
int g = gcd(12, 8); // 4
int maximum = max({1, 5, 3, 2}); // 5 (initializer list)
```

## Bitwise Operations

- `__builtin_popcount(x)` - Count set bits
- `__builtin_clz(x)` - Count leading zeros
- `__builtin_ctz(x)` - Count trailing zeros
- `1 << n` - 2^n
- `x & (x-1)` - Remove rightmost set bit
- `x & (-x)` - Get rightmost set bit

```cpp
int bits = __builtin_popcount(5); // 2 (binary: 101)
int power_of_2 = 1 << 3; // 8
```

## Common Patterns

### Fast I/O

```cpp
ios_base::sync_with_stdio(false);
cin.tie(NULL);
```

### Reading until EOF

```cpp
string line;
while (getline(cin, line)) {
    // Process line
}
```

### Custom Comparator for Sort

```cpp
// Sort by second element of pair
sort(pairs.begin(), pairs.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.second < b.second;
});
```

### 2D Vector

```cpp
vector<vector<int>> matrix(rows, vector<int>(cols, 0));
```

### Frequency Map

```cpp
unordered_map<int, int> freq;
for (int x : arr) {
    freq[x]++;
}
```
