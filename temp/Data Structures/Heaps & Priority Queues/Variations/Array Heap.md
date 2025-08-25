# Array Heap Implementation

A heap is a specialized tree-based data structure that satisfies the heap property. In a max heap, for any given node, the value of the node is greater than or equal to the values of its children. In a min heap, the value of the node is less than or equal to the values of its children.

Heaps can be efficiently implemented using arrays, where for a zero-based array:
- The left child of node at index `i` is at index `2*i + 1`
- The right child of node at index `i` is at index `2*i + 2`
- The parent of node at index `i` is at index `(i-1)/2` (integer division)

## Basic Operations

### Heapify

Heapify is the process of creating a heap from an array. It ensures the heap property is maintained.

#### Algorithm:
1. Start from the last non-leaf node (parent of the last element): `(n/2)-1`
2. For each node at index i, sift-down to maintain heap property
3. Continue until the root node is processed

#### Implementation (Max Heap):

```cpp
#include <vector>
#include <iostream>

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

// Function to build max heap
void buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();
    
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// Example usage
int main() {
    std::vector<int> arr = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    buildMaxHeap(arr);
    
    std::cout << "Max Heap: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(n) where n is the number of elements in the heap.
**Space Complexity**: O(log n) for the recursion stack in worst case.

### Insert

Insertion adds a new element to the heap while maintaining the heap property.

#### Algorithm:
1. Add the element at the end of the heap
2. Perform sift-up (heapify up) operation to restore heap property

#### Implementation:

```cpp
void insert(std::vector<int>& heap, int key) {
    // Add element at the end
    heap.push_back(key);
    
    // Get the index of the newly added element
    int i = heap.size() - 1;
    
    // Perform sift up (for max heap)
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i] <= heap[parent])
            break;
        
        std::swap(heap[i], heap[parent]);
        i = parent;
    }
}

// Example usage
int main() {
    std::vector<int> heap = {};
    
    // Insert elements
    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 40);
    insert(heap, 50);
    
    std::cout << "Max Heap after insertions: ";
    for (int i : heap)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(log n) where n is the number of elements in the heap.
**Space Complexity**: O(1).

### Delete Top (Extract Max/Min)

Deleting the top element involves removing the root and then restructuring to maintain the heap property.

#### Algorithm:
1. Store the root element
2. Replace the root with the last element in the heap
3. Reduce heap size by 1
4. Perform sift-down operation on the root to restore heap property
5. Return the stored root element

#### Implementation:

```cpp
int extractMax(std::vector<int>& heap) {
    if (heap.empty())
        throw std::runtime_error("Heap is empty");
        
    int maxItem = heap[0];
    
    // Replace root with last element
    heap[0] = heap.back();
    heap.pop_back();
    
    // Heapify the root element
    if (!heap.empty())
        heapify(heap, heap.size(), 0);
        
    return maxItem;
}

// Example usage
int main() {
    std::vector<int> heap = {50, 40, 15, 10, 20};
    
    std::cout << "Extracted max: " << extractMax(heap) << std::endl;
    
    std::cout << "Heap after extraction: ";
    for (int i : heap)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(log n) where n is the number of elements in the heap.
**Space Complexity**: O(log n) due to recursive heapify call.

### Delete

Deleting an element at any position in the heap requires finding and removing the element, then restoring the heap property.

#### Algorithm:
1. Find the element to be deleted
2. Replace it with the last element
3. Remove the last element
4. Perform either sift-up or sift-down to restore the heap property

#### Implementation:

```cpp
void deleteNode(std::vector<int>& heap, int key) {
    int size = heap.size();
    int i;
    
    // Find the element
    for (i = 0; i < size; i++) {
        if (heap[i] == key)
            break;
    }
    
    // If element not found
    if (i == size)
        return;
    
    // Replace with last element
    heap[i] = heap.back();
    heap.pop_back();
    
    // If the heap property is violated, fix it
    if (i > 0 && heap[i] > heap[(i - 1) / 2]) {
        // Need to sift up
        int index = i;
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] <= heap[parent])
                break;
            
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    } else {
        // Need to sift down
        heapify(heap, heap.size(), i);
    }
}

// Example usage
int main() {
    std::vector<int> heap = {50, 40, 15, 10, 20};
    
    deleteNode(heap, 40);
    
    std::cout << "Heap after deletion: ";
    for (int i : heap)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(n + log n) = O(n), where n is the number of elements in the heap.
- O(n) to find the element
- O(log n) to restore heap property

**Space Complexity**: O(log n) due to recursive heapify call.

### Merge Two Heaps

Merging two heaps involves combining their elements and re-establishing the heap property.

#### Algorithm:
1. Append all elements from the second heap to the first heap
2. Build heap from the combined array

#### Implementation:

```cpp
std::vector<int> mergeHeaps(std::vector<int>& heap1, std::vector<int>& heap2) {
    // Create a new vector and copy elements from both heaps
    std::vector<int> mergedHeap = heap1;
    mergedHeap.insert(mergedHeap.end(), heap2.begin(), heap2.end());
    
    // Build heap from the merged array
    buildMaxHeap(mergedHeap);
    
    return mergedHeap;
}

// Example usage
int main() {
    std::vector<int> heap1 = {50, 40, 15, 10, 20};
    std::vector<int> heap2 = {60, 30, 25};
    
    std::vector<int> merged = mergeHeaps(heap1, heap2);
    
    std::cout << "Merged heap: ";
    for (int i : merged)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(n), where n is the total number of elements in both heaps.
**Space Complexity**: O(n) for the merged heap.

## Additional Heap Operations

### Heap Sort

Heap sort uses the heap property to sort an array in ascending or descending order.

#### Algorithm:
1. Build a heap from the array
2. Extract the top element repeatedly and put it at the end of the array
3. Reduce heap size by 1 and heapify the root
4. Repeat until heap size is 1

#### Implementation:

```cpp
void heapSort(std::vector<int>& arr) {
    // Build heap (rearrange array)
    buildMaxHeap(arr);
    
    // One by one extract an element from heap
    for (int i = arr.size() - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);
        
        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Example usage
int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Original array: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    
    heapSort(arr);
    
    std::cout << "Sorted array: ";
    for (int i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(n log n)
**Space Complexity**: O(log n) for the recursive heapify call.

### Increase Key (or Decrease Key)

Changes the priority of a key and adjusts the heap accordingly.

#### Implementation (Increase Key for Max Heap):

```cpp
void increaseKey(std::vector<int>& heap, int i, int newValue) {
    if (newValue < heap[i]) {
        std::cout << "New value is smaller than current value" << std::endl;
        return;
    }
    
    heap[i] = newValue;
    
    // Bubble up if needed
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Example usage
int main() {
    std::vector<int> heap = {50, 40, 15, 10, 20};
    
    std::cout << "Original heap: ";
    for (int i : heap)
        std::cout << i << " ";
    std::cout << std::endl;
    
    increaseKey(heap, 3, 45); // Increase value at index 3 (value 10) to 45
    
    std::cout << "Heap after increasing key: ";
    for (int i : heap)
        std::cout << i << " ";
    std::cout << std::endl;
    
    return 0;
}
```

**Time Complexity**: O(log n)
**Space Complexity**: O(1)

## Complete Implementation of a Max Heap Class

```cpp
#include <vector>
#include <iostream>
#include <stdexcept>

class MaxHeap {
private:
    std::vector<int> heap;
    
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && heap[parent] < heap[index]) {
            std::swap(heap[parent], heap[index]);
            heapifyUp(parent);
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < size && heap[left] > heap[largest])
            largest = left;
        
        if (right < size && heap[right] > heap[largest])
            largest = right;
        
        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap() {}
    
    MaxHeap(const std::vector<int>& arr) : heap(arr) {
        buildHeap();
    }
    
    void buildHeap() {
        for (int i = heap.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }
    
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }
    
    int extractMax() {
        if (heap.empty())
            throw std::runtime_error("Heap is empty");
        
        int maxItem = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty())
            heapifyDown(0);
            
        return maxItem;
    }
    
    void remove(int key) {
        int size = heap.size();
        int i;
        
        for (i = 0; i < size; i++) {
            if (heap[i] == key)
                break;
        }
        
        if (i == size)
            return;
        
        heap[i] = heap.back();
        heap.pop_back();
        
        if (i > 0 && heap[i] > heap[(i - 1) / 2]) {
            heapifyUp(i);
        } else {
            heapifyDown(i);
        }
    }
    
    void increaseKey(int i, int newValue) {
        if (i >= heap.size() || newValue < heap[i])
            return;
        
        heap[i] = newValue;
        heapifyUp(i);
    }
    
    int getMax() {
        if (heap.empty())
            throw std::runtime_error("Heap is empty");
        return heap[0];
    }
    
    bool isEmpty() {
        return heap.empty();
    }
    
    int size() {
        return heap.size();
    }
    
    void print() {
        for (int i : heap)
            std::cout << i << " ";
        std::cout << std::endl;
    }
};

// Example usage
int main() {
    MaxHeap maxHeap;
    
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(15);
    maxHeap.insert(40);
    maxHeap.insert(50);
    
    std::cout << "Max Heap: ";
    maxHeap.print();
    
    std::cout << "Maximum element: " << maxHeap.getMax() << std::endl;
    
    std::cout << "Extracted max: " << maxHeap.extractMax() << std::endl;
    std::cout << "Heap after extraction: ";
    maxHeap.print();
    
    maxHeap.remove(15);
    std::cout << "Heap after removing 15: ";
    maxHeap.print();
    
    maxHeap.increaseKey(1, 45);
    std::cout << "Heap after increasing key: ";
    maxHeap.print();
    
    // Initialize heap from array
    std::vector<int> arr = {5, 10, 15, 20, 25};
    MaxHeap anotherHeap(arr);
    std::cout << "Another heap: ";
    anotherHeap.print();
    
    return 0;
}
```

## LeetCode Problems Related to Heaps

1. **[Kth Largest Element in an Array (LeetCode 215)](https://leetcode.com/problems/kth-largest-element-in-an-array/)** - Use a min heap of size K to find the Kth largest element.

2. **[Find Median from Data Stream (LeetCode 295)](https://leetcode.com/problems/find-median-from-data-stream/)** - Use two heaps (max heap and min heap) to efficiently find the median.

3. **[Merge K Sorted Lists (LeetCode 23)](https://leetcode.com/problems/merge-k-sorted-lists/)** - Use a min heap to efficiently merge k sorted linked lists.

4. **[Top K Frequent Elements (LeetCode 347)](https://leetcode.com/problems/top-k-frequent-elements/)** - Use a heap to find the k most frequent elements in an array.

5. **[K Closest Points to Origin (LeetCode 973)](https://leetcode.com/problems/k-closest-points-to-origin/)** - Use a max heap to find k closest points to the origin.

6. **[Sliding Window Maximum (LeetCode 239)](https://leetcode.com/problems/sliding-window-maximum/)** - Can be solved using a heap to find the maximum in a sliding window.

7. **[Last Stone Weight (LeetCode 1046)](https://leetcode.com/problems/last-stone-weight/)** - Use a max heap to simulate the stone smashing process.

8. **[Minimum Cost to Connect Sticks (LeetCode 1167)](https://leetcode.com/problems/minimum-cost-to-connect-sticks/)** - Use a min heap to greedily connect sticks with minimum cost.

## References

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Introduction to Algorithms (3rd ed.). MIT Press.
- Sedgewick, R., & Wayne, K. (2011). Algorithms (4th ed.). Addison-Wesley Professional.
