### Minimum swaps to sort an Array

The minimum swaps to sort an array problem involves rearranging an array into sorted order using the least number of swap operations. Here's a clear explanation of the primary approach:

1. **Problem Overview**:

   - Given an array of distinct integers, determine the minimum number of swaps required to sort it in ascending order.
   - Example: For `arr = [4, 3, 1, 2]`, the sorted array is `[1, 2, 3, 4]`. We need to compute the minimum swaps to achieve this.
2. **Key Insight**:

   - Each swap involves exchanging two elements.
   - The array can be viewed as a permutation, and sorting it is equivalent to transforming it into the identity permutation (sorted order).
   - The problem can be modeled as a graph where each element's current position points to its correct position in the sorted array.
   - Cycles in this graph represent elements that need to be swapped to reach their correct positions.
3. **Cycle-Based Approach** (Primary Method):

   - **Step 1**: Create a mapping of elements to their current indices in the array.
   - **Step 2**: Create a sorted version of the array to know each element's correct position.
   - **Step 3**: For each element, trace the cycle of positions it must go through to reach its correct position.
   - **Step 4**: For each cycle of length `k`, the minimum number of swaps required is `k - 1` (since a cycle of length `k` can be resolved with `k - 1` swaps).
   - **Step 5**: Sum the swaps needed for all cycles.
   - Time Complexity: O(n log n) due to sorting.
   - Space Complexity: O(n) for storing the sorted array and visited flags.
4. **Alternative Approach (Using Visited Array)**:

   - Instead of explicitly detecting cycles, use a visited array to mark processed elements.
   - Iterate through the array, and for each unvisited element, follow its cycle until all elements in the cycle are placed correctly.
   - Count swaps as you resolve each cycle.
5. **Greedy Swap Approach** (Simpler but Less Efficient):

   - Repeatedly scan the array and swap elements that are out of place with their correct position based on the sorted order.
   - This is less efficient (O(n²) in worst cases) but easier to understand.

---

### C++ Implementations

Below are three C++ implementations:

1. **Cycle-Based Approach** (Most efficient, using graph cycle detection).
2. **Visited Array Approach** (Similar to cycle-based but uses a visited array).
3. **Greedy Swap Approach** (Simpler but less efficient).

Each code is a full, executable program that takes an array as input and outputs the minimum number of swaps.

#### Count all cycle lengths method

```cpp
#include <bits/stdc++.h>
using namespace std;

int minSwaps(vector<int>& arr) {
    int n = arr.size();
    // Create a vector of pairs {value, index}
    vector<pair<int, int>> arrPos(n);
    for (int i = 0; i < n; i++) {
        arrPos[i] = {arr[i], i};
    }
  
    // Sort by value to get correct positions
    sort(arrPos.begin(), arrPos.end());
  
    // Visited array to track processed elements
    vector<bool> visited(n, false);
    int swaps = 0;
  
    // Process each cycle
    for (int i = 0; i < n; i++) {
        if (visited[i] || arrPos[i].second == i) {
            continue; // Skip if already visited or in correct position
        }
        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = arrPos[j].second; // Move to the next index in the cycle
            cycle_size++;
        }
        if (cycle_size > 0) {
            swaps += (cycle_size - 1); // k-1 swaps for a cycle of size k
        }
    }
    return swaps;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Minimum swaps required: " << minSwaps(arr) << endl;
    return 0;
}
```

#### Visited array - swaps

```cpp
#include <bits/stdc++.h>
using namespace std;

int minSwaps(vector<int>& arr) {
    int n = arr.size();
    // Create a map of value to index
    unordered_map<int, int> indexMap;
    for (int i = 0; i < n; i++) {
        indexMap[arr[i]] = i;
    }
  
    // Create sorted array
    vector<int> sortedArr = arr;
    sort(sortedArr.begin(), sortedArr.end());
  
    // Visited array
    vector<bool> visited(n, false);
    int swaps = 0;
  
    // Process each element
    for (int i = 0; i < n; i++) {
        if (visited[i] || arr[i] == sortedArr[i]) {
            continue; // Skip if visited or in correct position
        }
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            // Find where arr[j] should go
            j = indexMap[sortedArr[j]];
            swaps++;
        }
        swaps--; // Adjust for the last swap in cycle
    }
    return swaps;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Minimum swaps required: " << minSwaps(arr) << endl;
    return 0;
}
```

#### Brute force with selection sort

```cpp
#include <bits/stdc++.h>
using namespace std;

int minSwaps(vector<int>& arr) {
    int n = arr.size();
    // Create a vector of pairs {value, index}
    vector<pair<int, int>> arrPos(n);
    for (int i = 0; i < n; i++) {
        arrPos[i] = {arr[i], i};
    }
  
    // Sort by value
    sort(arrPos.begin(), arrPos.end());
  
    int swaps = 0;
    for (int i = 0; i < n; i++) {
        while (arrPos[i].second != i) {
            // Swap elements to their correct position
            swap(arrPos[arrPos[i].second], arrPos[i]);
            swaps++;
        }
    }
    return swaps;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Minimum swaps required: " << minSwaps(arr) << endl;
    return 0;
}
```

---

### How to Use the Code

- **Input**: The program prompts for the array size `n`, followed by `n` integers.
- **Output**: The minimum number of swaps required to sort the array.
- **Example**:
  ```
  Enter array size: 4
  Enter array elements: 4 3 1 2
  Minimum swaps required: 3
  ```

  Explanation: For `[4, 3, 1, 2]`, one possible sequence is:- Swap 4 and 1: `[1, 3, 4, 2]`
  - Swap 3 and 2: `[1, 2, 4, 3]`
  - Swap 4 and 3: `[1, 2, 3, 4]`
    Total swaps = 3.

---

### LeetCode References

The minimum swaps to sort an array problem appears in various forms on LeetCode. Here are relevant problems:

- [LeetCode 1536: Minimum Swaps to Arrange a Binary Grid](https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/description)
  - Involves a similar concept of swapping rows to achieve a sorted-like structure.
- [LeetCode 1460: Make Two Arrays Equal by Reversing Sub-arrays](https://leetcode.com/problems/make-two-arrays-equal-by-reversing-sub-arrays/description)
  - Related to transforming one array into another, which can be solved using cycle detection.
- [LeetCode 768: Max Chunks To Make Sorted II](https://leetcode.com/problems/max-chunks-to-make-sorted-ii/description)
  - Involves understanding array permutations, which ties to the cycle-based approach.

---

### Comparison of Approaches

- **Cycle-Based Approach** (`min_swaps_cycle.cpp`):
  - Most efficient for large arrays.
  - Uses O(n log n) time due to sorting and O(n) space.
  - Explicitly counts cycles, making it intuitive for permutation problems.
- **Visited Array Approach** (`min_swaps_visited.cpp`):
  - Similar efficiency to the cycle-based approach.
  - Uses a hash map for faster lookups but requires slightly more memory.
  - Easier to modify for variations (e.g., handling duplicates).
- **Greedy Swap Approach** (`min_swaps_greedy.cpp`):
  - Simpler to understand but less efficient (O(n²) in worst cases).
  - Directly swaps elements to their correct positions, which is intuitive but not optimal for large inputs.

Each implementation is robust and handles various input cases, including unsorted arrays, already sorted arrays, and arrays with repeated swaps needed.

If you have specific test cases or want further optimization, let me know!
