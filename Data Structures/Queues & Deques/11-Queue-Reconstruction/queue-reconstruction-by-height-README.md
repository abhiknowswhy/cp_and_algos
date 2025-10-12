# Queue Reconstruction by Height

## Problem Description
You have a queue of people described by `[height, k]` where:
- `height` is the height of the person
- `k` is the number of people in front of this person who have a height greater than or equal to this person's height

Reconstruct and return the queue. The queue should be represented as an array of people where each person is described by `[height, k]`.

## Approach
The key insight is to use a greedy approach with proper sorting:

1. **Sort by height (descending)** and then by k (ascending) for same heights
2. **Insert each person at position k** in the result array

This works because:
- Taller people don't affect shorter people's k values
- When we process a person, all previously processed people are taller
- Position k is exactly where this person should be placed

## Algorithm Steps
1. **Sort people**: By height descending, then by k ascending
2. **Initialize result**: Empty list to build the queue
3. **For each person**: Insert at position k in the result
4. **Return reconstructed queue**

## Implementation

### Approach 1: Insert at Position K
```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // Sort by height descending, then by k ascending
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] > b[0];  // Taller person first
            }
            return a[1] < b[1];      // Smaller k first for same height
        });
        
        vector<vector<int>> result;
        
        // Insert each person at position k
        for (auto& person : people) {
            int k = person[1];
            result.insert(result.begin() + k, person);
        }
        
        return result;
    }
};
```

### Approach 2: Using Deque for Efficiency
```cpp
#include <deque>
#include <algorithm>

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // Sort by height descending, then by k ascending
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
        });
        
        deque<vector<int>> dq;
        
        // Insert each person at position k
        for (auto& person : people) {
            int k = person[1];
            dq.insert(dq.begin() + k, person);
        }
        
        return vector<vector<int>>(dq.begin(), dq.end());
    }
};
```

### Approach 3: Alternative Sorting Strategy
```cpp
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // Sort by height ascending, then by k descending
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];  // Shorter person first
            }
            return a[1] > b[1];      // Larger k first for same height
        });
        
        vector<vector<int>> result(people.size());
        vector<bool> occupied(people.size(), false);
        
        for (auto& person : people) {
            int height = person[0];
            int k = person[1];
            int count = 0;
            
            // Find the k-th available position
            for (int i = 0; i < people.size(); i++) {
                if (!occupied[i]) {
                    if (count == k) {
                        result[i] = person;
                        occupied[i] = true;
                        break;
                    }
                    count++;
                }
            }
        }
        
        return result;
    }
};
```

### Approach 4: Segment Tree Optimization
```cpp
class SegmentTree {
private:
    vector<int> tree;
    int n;
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    int query(int node, int start, int end, int k) {
        if (start == end) {
            return start;
        }
        
        int mid = (start + end) / 2;
        int leftSum = tree[2 * node];
        
        if (k <= leftSum) {
            return query(2 * node, start, mid, k);
        } else {
            return query(2 * node + 1, mid + 1, end, k - leftSum);
        }
    }
    
public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        // Initialize all positions as available
        for (int i = 0; i < n; i++) {
            update(1, 0, n - 1, i, 1);
        }
    }
    
    int findKthAvailable(int k) {
        int pos = query(1, 0, n - 1, k + 1);
        update(1, 0, n - 1, pos, 0);  // Mark as occupied
        return pos;
    }
};

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });
        
        int n = people.size();
        vector<vector<int>> result(n);
        SegmentTree st(n);
        
        for (auto& person : people) {
            int k = person[1];
            int position = st.findKthAvailable(k);
            result[position] = person;
        }
        
        return result;
    }
};
```

### Time Complexity
- **Approach 1**: O(n² log n) - O(n log n) sort + O(n²) insertions
- **Approach 2**: O(n² log n) - Similar to approach 1
- **Approach 3**: O(n² log n) - O(n log n) sort + O(n²) position finding
- **Approach 4**: O(n log² n) - O(n log n) sort + O(n log n) segment tree operations

### Space Complexity
- **Approaches 1-3**: O(n) for result array
- **Approach 4**: O(n) for segment tree

## Examples

### Example 1
```
Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]

Explanation:
Person 0 has height 5 with nobody taller in front.
Person 1 has height 7 with nobody taller in front.
Person 2 has height 5 with 2 people taller in front (persons 1 and 3).
...
```

### Example 2
```
Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
```

## Key Insights

### Queue Pattern Usage
- **Reconstruction problem**: Build final queue order from constraints
- **Insertion order**: Use position-based insertion to maintain queue properties
- **Greedy strategy**: Process in optimal order to ensure correctness

### Why the Greedy Approach Works
1. **Taller people first**: Their placement doesn't affect shorter people's k values
2. **Position k**: When processing a person, exactly k taller people have been placed
3. **No conflicts**: Inserting at position k maintains all previous constraints

### Optimization Considerations
- **Insert operation cost**: O(n) for vector insertion vs. O(1) for deque
- **Memory locality**: Vector might be faster despite higher complexity
- **Advanced structures**: Segment tree for O(log n) position finding

### Alternative Approaches
- **Bottom-up**: Sort by height ascending and use availability tracking
- **Two-pass**: First determine positions, then fill
- **Coordinate compression**: For very large height values

## Related Problems
- Reveal Cards in Increasing Order
- Design Circular Deque
- Dota2 Senate
Output: 
Explanation: 
```

### Example 2
```
Input: 
Output: 
Explanation: 
```

## Notes
<!-- Add any additional notes, edge cases, or variations -->

## Related Problems
<!-- List related problems -->

## Pattern: 11-Queue-Reconstruction
<!-- Explain how this problem fits the pattern -->
