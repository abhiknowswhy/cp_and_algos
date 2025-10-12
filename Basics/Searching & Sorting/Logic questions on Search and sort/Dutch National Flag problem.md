The Dutch National Flag problem is a classic sorting algorithm that partitions an array into three sections based on a pivot value. It's named after the Dutch flag which has three horizontal stripes of different colors.

## Algorithm Explanation

The algorithm partitions an array into three regions:

* **Low region** : Elements smaller than the pivot
* **Mid region** : Elements equal to the pivot
* **High region** : Elements greater than the pivot

**Key Approach:**

1. Use three pointers: `low`, `mid`, and `high`
2. `low` points to the boundary of the low region
3. `mid` is the current element being examined
4. `high` points to the boundary of the high region
5. Iterate through the array and swap elements to maintain the three regions

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(1) - only uses constant extra space## Related LeetCode Problems

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DutchNationalFlag {
public:
    // Basic Dutch National Flag - Sort 0s, 1s, 2s
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size() - 1;
        
        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            }
            else if (nums[mid] == 1) {
                mid++;
            }
            else { // nums[mid] == 2
                swap(nums[mid], nums[high]);
                high--;
                // Don't increment mid here as we need to check the swapped element
            }
        }
    }
    
    // Generic version with custom pivot
    void dutchFlagPartition(vector<int>& arr, int pivot) {
        int low = 0, mid = 0, high = arr.size() - 1;
        
        while (mid <= high) {
            if (arr[mid] < pivot) {
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (arr[mid] == pivot) {
                mid++;
            }
            else { // arr[mid] > pivot
                swap(arr[mid], arr[high]);
                high--;
            }
        }
    }
    
    // Utility function to print array
    void printArray(const vector<int>& arr) {
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }
};

int main() {
    DutchNationalFlag dnf;
    
    // Test Case 1: Sort Colors (0s, 1s, 2s)
    cout << "=== Test Case 1: Sort Colors ===" << endl;
    vector<int> colors = {2, 0, 2, 1, 1, 0};
    cout << "Original: ";
    dnf.printArray(colors);
    
    dnf.sortColors(colors);
    cout << "Sorted: ";
    dnf.printArray(colors);
    
    // Test Case 2: Generic Dutch Flag with pivot
    cout << "\n=== Test Case 2: Generic Dutch Flag ===" << endl;
    vector<int> arr = {3, 5, 2, 6, 8, 6, 6, 6, 6};
    int pivot = 6;
    cout << "Original: ";
    dnf.printArray(arr);
    cout << "Pivot: " << pivot << endl;
    
    dnf.dutchFlagPartition(arr, pivot);
    cout << "Partitioned: ";
    dnf.printArray(arr);
    
    // Test Case 3: Edge cases
    cout << "\n=== Test Case 3: Edge Cases ===" << endl;
    
    // Single element
    vector<int> single = {1};
    cout << "Single element - Original: ";
    dnf.printArray(single);
    dnf.sortColors(single);
    cout << "Single element - Sorted: ";
    dnf.printArray(single);
    
    // All same elements
    vector<int> allSame = {1, 1, 1, 1};
    cout << "All same - Original: ";
    dnf.printArray(allSame);
    dnf.sortColors(allSame);
    cout << "All same - Sorted: ";
    dnf.printArray(allSame);
    
    // Already sorted
    vector<int> sorted = {0, 0, 1, 1, 2, 2};
    cout << "Already sorted - Original: ";
    dnf.printArray(sorted);
    dnf.sortColors(sorted);
    cout << "Already sorted - Result: ";
    dnf.printArray(sorted);
    
    return 0;
}
```

Here are the key LeetCode problems that use the Dutch National Flag algorithm:

### 1. **LeetCode 75: Sort Colors**

* **Difficulty:** Medium
* **Problem:** Sort an array containing only 0s, 1s, and 2s in-place
* **Direct application** of Dutch National Flag algorithm
* **Constraints:** Must sort in-place with O(1) extra space

### 2. **LeetCode 215: Kth Largest Element in an Array**

* **Difficulty:** Medium
* **Problem:** Find the kth largest element in an unsorted array
* **Uses Dutch Flag partitioning** as part of QuickSelect algorithm
* **Key insight:** Partition around a pivot to find the kth element

### 3. **LeetCode 912: Sort an Array**

* **Difficulty:** Medium
* **Problem:** Sort an array using various algorithms
* **Can use Dutch Flag** as part of 3-way QuickSort implementation
* **Handles duplicate elements efficiently**

### 4. **LeetCode 324: Wiggle Sort II**

* **Difficulty:** Medium
* **Problem:** Rearrange array so that nums[0] < nums[1] > nums[2] < nums[3]...
* **Uses Dutch Flag concept** for partitioning around median
* **Advanced application** requiring careful index mapping

### 5. **LeetCode 148: Sort List**

* **Difficulty:** Medium
* **Problem:** Sort a linked list in O(n log n) time
* **Variation:** Applies partitioning concept to linked lists
* **Uses merge sort** but partitioning principles apply

The Dutch National Flag algorithm is particularly powerful because it:

* Handles arrays with many duplicate elements efficiently
* Partitions in a single pass with minimal swaps
* Forms the foundation for efficient QuickSort variants
* Solves the classic "sort 0s, 1s, 2s" problem optimally

The algorithm's elegance lies in its simplicity and the fact that it maintains three invariants simultaneously while making only one pass through the data.
