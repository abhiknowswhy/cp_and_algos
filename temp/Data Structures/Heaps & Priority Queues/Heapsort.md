# Heapsort

[Video Explanation](https://www.youtube.com/watch?v=2DmK_H7IdTo)

## Algorithm Overview

Heapsort is an efficient, comparison-based sorting algorithm that uses a binary heap data structure. It works by:

1. Building a max heap from the input array (heapify)
2. Repeatedly extracting the maximum element from the heap and putting it at the end of the array
3. Reducing the heap size and restoring the heap property

Heapsort has several advantages:
- Guaranteed O(n log n) time complexity
- In-place sorting (no extra space needed except for a constant amount)
- Not stable (relative order of equal elements may change)

## Step-by-Step Explanation

### Step 1: Build Max Heap
- Start with an unsorted array
- Rearrange the array to form a max heap (where parent nodes are greater than child nodes)
- This is done by starting from the last non-leaf node and performing sift-down operations

### Step 2: Extract Elements
- Swap the root (maximum element) with the last element in the heap
- Reduce the heap size by 1 (exclude the sorted element)
- Restore the heap property by performing sift-down on the root node
- Repeat until all elements are sorted

## Implementation

Here's an executable C++ implementation of heapsort:

```cpp
#include <iostream>
#include <vector>

// Function to maintain the max-heap property (sift down)
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child
  
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
  
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
  
    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main heapsort function
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
  
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
  
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);
  
        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Utility function to print an array
void printArray(const std::vector<int>& arr) {
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
}

// Driver code
int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Original array: ";
    printArray(arr);
    
    heapSort(arr);
    
    std::cout << "Sorted array: ";
    printArray(arr);
    
    return 0;
}
```

## Time and Space Complexity Analysis

### Time Complexity
- **Building the heap**: O(n)
  - Although it might seem like O(n log n) since we call heapify n/2 times, a tighter analysis shows it's actually O(n)
- **Extracting elements**: O(n log n)
  - We perform n-1 extractions, each taking O(log n) time
- **Overall**: O(n log n) in all cases (best, average, worst)

### Space Complexity
- O(1) auxiliary space (in-place algorithm)
- O(log n) recursive call stack space for heapify

## Iterative Heapsort Implementation

Here's an alternative implementation that uses an iterative approach for heapify, which avoids the recursive call stack:

```cpp
#include <iostream>
#include <vector>

// Iterative function to maintain the max-heap property (sift down)
void heapifyIterative(std::vector<int>& arr, int n, int i) {
    while (true) {
        int largest = i;        // Initialize largest as root
        int left = 2 * i + 1;   // Left child
        int right = 2 * i + 2;  // Right child
    
        // If left child is larger than root
        if (left < n && arr[left] > arr[largest])
            largest = left;
    
        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest])
            largest = right;
    
        // If largest is not root
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            i = largest;  // Continue heapifying the affected sub-tree
        } else {
            break;  // If no swap is needed, we're done
        }
    }
}

// Main heapsort function using iterative heapify
void heapSortIterative(std::vector<int>& arr) {
    int n = arr.size();
  
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyIterative(arr, n, i);
  
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);
  
        // Call max heapify on the reduced heap
        heapifyIterative(arr, i, 0);
    }
}

// Driver code
int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Original array: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    
    heapSortIterative(arr);
    
    std::cout << "Sorted array: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

## Comparison with Other Sorting Algorithms

| Algorithm | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity | Stable |
|-----------|--------------------------|-------------------------|------------------|--------|
| Heapsort  | O(n log n)               | O(n log n)              | O(1)             | No     |
| Quicksort | O(n log n)               | O(n²)                   | O(log n)         | No     |
| Mergesort | O(n log n)               | O(n log n)              | O(n)             | Yes    |

## Practical Applications

Heapsort is particularly useful when:
- Guaranteed worst-case performance is important
- Memory usage is a concern (in-place sorting)
- Stable sorting is not required

## Related LeetCode Problems

1. **[Sort an Array (LeetCode 912)](https://leetcode.com/problems/sort-an-array/)** - Implement various sorting algorithms, including heapsort

2. **[Kth Largest Element in an Array (LeetCode 215)](https://leetcode.com/problems/kth-largest-element-in-an-array/)** - Can be solved efficiently using heap operations

3. **[Sort Characters By Frequency (LeetCode 451)](https://leetcode.com/problems/sort-characters-by-frequency/)** - Can use a max heap to sort elements by frequency

4. **[Top K Frequent Elements (LeetCode 347)](https://leetcode.com/problems/top-k-frequent-elements/)** - Use a heap to find the k most frequent elements

5. **[K Closest Points to Origin (LeetCode 973)](https://leetcode.com/problems/k-closest-points-to-origin/)** - Find the k closest points using heap operations

## Variations

### In-Place Bottom-Up Heap Construction

A more efficient way to build the initial heap:

```cpp
#include <iostream>
#include <vector>

// Sift-down function
void siftDown(std::vector<int>& arr, int start, int end) {
    int root = start;
    
    while (2 * root + 1 <= end) {
        int child = 2 * root + 1;  // Left child
        int swap = root;
        
        // Compare with left child
        if (arr[swap] < arr[child])
            swap = child;
            
        // Compare with right child
        if (child + 1 <= end && arr[swap] < arr[child + 1])
            swap = child + 1;
            
        if (swap == root)
            return;  // Heap property satisfied
            
        std::swap(arr[root], arr[swap]);
        root = swap;
    }
}

// Optimized bottom-up heap construction
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap (in-place)
    for (int i = n / 2 - 1; i >= 0; i--)
        siftDown(arr, i, n - 1);
        
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        siftDown(arr, 0, i - 1);
    }
}
```

## References

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Introduction to Algorithms (3rd ed.). MIT Press.
- Sedgewick, R., & Wayne, K. (2011). Algorithms (4th ed.). Addison-Wesley Professional.
- Knuth, D. E. (1998). The Art of Computer Programming, Volume 3: Sorting and Searching (2nd ed.). Addison-Wesley.