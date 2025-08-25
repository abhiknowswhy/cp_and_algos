# Tournament Problem

## Problem Description

The **Tournament Problem** deals with efficiently finding the second largest (or more generally, the k-th largest) element in an array with the minimum number of comparisons.

## Why It's Important

In standard sorting algorithms, finding the k-th largest element would require O(n log n) time due to the need to sort the entire array. However, the tournament approach can find the second largest element in just O(n) time with a minimal number of comparisons.

The key advantage of tournament algorithms is **minimizing the number of comparisons**, which can be valuable when:
- Comparisons are expensive operations
- The problem specifically requires optimizing for the number of comparisons
- We only need the k-th largest element without sorting the entire array

## Algorithm for Finding the Second Largest Element

### Tournament Method

The tournament method works similar to a knockout tournament structure:

1. Arrange the elements in pairs and compare each pair
2. The winner (larger element) from each pair advances to the next round
3. Continue the tournament until we find the overall winner (the maximum element)
4. To find the second largest element, we only need to consider the elements that were compared with the maximum element during the tournament

### Comparison Count Analysis

For an array of n elements:
- Finding the maximum element requires n-1 comparisons
- Finding the second largest requires an additional log₂(n) comparisons
- Total: n-1+log₂(n) comparisons, which is optimal

### Detailed Steps

1. Create a binary tree structure representing the tournament
2. The leaf nodes are the original elements
3. Each internal node represents the winner of the comparison between its children
4. After constructing the tree, the root node contains the maximum element
5. The second largest element must be among the elements that lost directly to the maximum element
6. Compare all the elements that lost to the maximum to find the second largest

## Implementation in C++

Here's a C++ implementation of the tournament method for finding the second largest element:

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Tournament algorithm to find the second largest element
int findSecondLargest(const vector<int>& arr) {
    int n = arr.size();
    
    if (n < 2) {
        cout << "Array must have at least 2 elements" << endl;
        return -1;
    }
    
    // Build the tournament tree
    vector<int> winners(n);  // To store winners at each level
    vector<int> loser_to_max;  // Store elements that lost to the maximum
    
    // Initialize with original array
    for (int i = 0; i < n; i++) {
        winners[i] = arr[i];
    }
    
    int max_element_index = 0;  // Will keep track of the maximum element's index
    
    // Run the tournament
    int curr_size = n;
    while (curr_size > 1) {
        int next_level_size = (curr_size + 1) / 2;
        
        for (int i = 0; i < curr_size - 1; i += 2) {
            // Compare adjacent elements
            if (winners[i] > winners[i + 1]) {
                winners[i / 2] = winners[i];
                // If this is the first level, remember who lost to whom
                if (curr_size == n) {
                    loser_to_max.push_back(winners[i + 1]);
                }
            } else {
                winners[i / 2] = winners[i + 1];
                // If this is the first level, remember who lost to whom
                if (curr_size == n) {
                    loser_to_max.push_back(winners[i]);
                }
            }
        }
        
        // Handle odd number of elements
        if (curr_size % 2 != 0) {
            winners[next_level_size - 1] = winners[curr_size - 1];
        }
        
        curr_size = next_level_size;
    }
    
    // winners[0] now contains the maximum element
    int max_element = winners[0];
    
    // Find the second largest by checking elements that lost to the maximum
    int second_largest = INT_MIN;
    
    for (int i = 0; i < loser_to_max.size(); i++) {
        if (loser_to_max[i] > second_largest) {
            second_largest = loser_to_max[i];
        }
    }
    
    return second_largest;
}

// Alternative implementation using a more explicit tournament structure
int findSecondLargestOptimized(const vector<int>& arr) {
    int n = arr.size();
    
    if (n < 2) {
        cout << "Array must have at least 2 elements" << endl;
        return -1;
    }
    
    // Number of levels in the tournament tree
    int height = ceil(log2(n));
    int tournament_size = (1 << (height + 1)) - 1;
    int leaf_start = (1 << height) - 1;
    
    vector<int> tournament(tournament_size, INT_MIN);
    
    // Fill the leaf nodes
    for (int i = 0; i < n; i++) {
        tournament[leaf_start + i] = arr[i];
    }
    
    // Build the tournament tree bottom-up
    for (int i = leaf_start - 1; i >= 0; i--) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        tournament[i] = max(tournament[left_child], tournament[right_child]);
    }
    
    // Find the second largest
    int root_index = 0;
    int second_largest = INT_MIN;
    
    // Traverse from root to leaf to find path to maximum
    while (root_index < leaf_start) {
        int left_child = 2 * root_index + 1;
        int right_child = 2 * root_index + 2;
        
        if (tournament[left_child] == tournament[root_index]) {
            // Maximum is in left subtree
            // Check if right child is a potential second largest
            second_largest = max(second_largest, tournament[right_child]);
            root_index = left_child;
        } else {
            // Maximum is in right subtree
            // Check if left child is a potential second largest
            second_largest = max(second_largest, tournament[left_child]);
            root_index = right_child;
        }
    }
    
    return second_largest;
}

// Driver code to test the algorithm
int main() {
    vector<int> arr = {5, 20, 12, 8, 10, 15, 3, 18};
    cout << "Original Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "Second largest element: " << findSecondLargest(arr) << endl;
    cout << "Second largest element (optimized): " << findSecondLargestOptimized(arr) << endl;
    
    return 0;
}
```

## Extension to Finding K-th Largest Element

The tournament method can be extended to find the k-th largest element, though the algorithm becomes more complex:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
using namespace std;

// Tournament algorithm to find the kth largest element
int findKthLargest(const vector<int>& nums, int k) {
    int n = nums.size();
    
    if (k > n) {
        cout << "k cannot be greater than the size of the array" << endl;
        return -1;
    }
    
    // Create a max heap for the tournament
    priority_queue<pair<int, int>> pq; // (value, index)
    
    // Initialize the tournament with leaf nodes
    for (int i = 0; i < n; i++) {
        pq.push({nums[i], i});
    }
    
    // Process the tournament k-1 times to find the kth largest
    vector<bool> eliminated(n, false);
    int result;
    
    for (int i = 0; i < k; i++) {
        auto [val, idx] = pq.top();
        pq.pop();
        result = val;
        
        // Mark this index as eliminated
        eliminated[idx] = true;
        
        // For the first k-1 iterations, find potential candidates
        if (i < k - 1) {
            // Add potential candidates for the next largest
            if (idx > 0 && !eliminated[idx - 1]) {
                pq.push({nums[idx - 1], idx - 1});
            }
            if (idx < n - 1 && !eliminated[idx + 1]) {
                pq.push({nums[idx + 1], idx + 1});
            }
        }
    }
    
    return result;
}

// Driver code to test the kth largest element algorithm
int main() {
    vector<int> arr = {5, 20, 12, 8, 10, 15, 3, 18};
    int k = 3; // Find the 3rd largest element
    
    cout << "Original Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << k << "-th largest element: " << findKthLargest(arr, k) << endl;
    
    return 0;
}
```

## Related LeetCode Problems

1. [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
   - Problem: Find the kth largest element in an unsorted array.
   - The tournament method can be applied here, though other approaches like QuickSelect and Heap are also common.

2. [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)
   - While not directly a tournament problem, it deals with finding the kth element.

3. [414. Third Maximum Number](https://leetcode.com/problems/third-maximum-number/)
   - Problem: Find the third maximum distinct number in an array.
   - The tournament approach can be adapted to solve this efficiently.

4. [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)
   - Problem: Find the k points closest to the origin.
   - The tournament method concepts can be applied here.

## Time and Space Complexity

### Finding the Second Largest Element
- **Time Complexity**: O(n) - We need n-1 comparisons to find the maximum, and then at most log₂(n) additional comparisons.
- **Space Complexity**: O(n) - For storing the tournament tree.

### Finding the Kth Largest Element
- **Time Complexity**: O(n + k log n) - O(n) to build the initial heap and O(k log n) for k extract-max operations.
- **Space Complexity**: O(n) - For storing the heap and auxiliary data structures.

## References

1. Introduction to Algorithms (CLRS) - Chapter on Comparison Networks
2. The Art of Computer Programming, Volume 3: Sorting and Searching - Donald Knuth
3. Competitive Programming 3 by Steven Halim & Felix Halim

## Conclusion

The tournament algorithm provides an efficient way to find the second largest or kth largest element with a minimal number of comparisons. While it may not always be the most practical approach for all scenarios (especially with modern hardware optimizations), understanding this algorithm is valuable for competitive programming and computer science fundamentals.