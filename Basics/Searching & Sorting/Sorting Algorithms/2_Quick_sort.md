# Quick Sort Algorithm

- The `partition` function selects a pivot and rearranges elements so that all elements less than the pivot come before it and all elements greater come after.
- `quickSort` recursively sorts the sub-arrays.
- Time complexity is O(n log n) on average, and O(n²) in the worst case (e.g., sorted input and poor pivot choice

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // choose the last element as pivot // 5
    int i = low;        // index of smaller element // -1

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[high]); // place pivot at the correct position
    return i;
}

// QuickSort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // partition the array
        int pi = partition(arr, low, high); // 0 , 5

        // sort the sub-arrays recursively
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helper function to print the array
void printArray(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

// Main function
int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Original array: ";
    printArray(arr);

    quickSort(arr, 0, arr.size() - 1); // 0 , 5

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
```

## Nuts and Bolts Problem (Lock and Key Problem)

### Problem Statement

Given a collection of nuts of distinct sizes and the same number of bolts, where each nut matches exactly one bolt.

The challenge is to find the corresponding pairs of nuts and bolts in the minimum number of comparisons. The only allowed operation is to compare a nut with a bolt: you can't compare nuts with nuts or bolts with bolts.

In other words, we're given:

- An array of nuts: `nuts[]`
- An array of bolts: `bolts[]`

Where each element represents a size. The goal is to match each nut to its corresponding bolt.

### Solution using Quick Sort Approach

This problem can be efficiently solved using a modified QuickSort algorithm. The idea is to:

1. Pick a pivot nut and use it to partition the bolts
2. Use the matched bolt as a pivot to partition the nuts
3. Recursively apply the same process to subarrays

```cpp
#include <iostream>
#include <vector>
using namespace std;

// This function is used to match nuts and bolts
void matchPairs(vector<char>& nuts, vector<char>& bolts, int low, int high) {
    if (low < high) {
        // Choose the last bolt as pivot for nuts
        int pivot = partition(nuts, low, high, bolts[high]);
      
        // Using the matched nut as pivot for bolts
        partition(bolts, low, high, nuts[pivot]);
      
        // Recursively match remaining pairs
        matchPairs(nuts, bolts, low, pivot - 1);
        matchPairs(nuts, bolts, pivot + 1, high);
    }
}

// Modified partition function that uses a pivot element
// passed from outside the array
int partition(vector<char>& arr, int low, int high, char pivot) {
    int i = low;
  
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        } else if (arr[j] == pivot) {
            // If we find the matching element, swap it with the last element
            swap(arr[j], arr[high]);
            j--; // Process the same index again
        }
    }
  
    // Place the pivot at its correct position
    swap(arr[i], arr[high]);
    return i;
}

// Driver code
int main() {
    vector<char> nuts = {'@', '#', '$', '%', '^', '&'};
    vector<char> bolts = {'$', '%', '&', '^', '@', '#'};
  
    int n = nuts.size();
  
    cout << "Original arrays:" << endl;
    cout << "Nuts: ";
    for (char c : nuts) cout << c << " ";
    cout << endl << "Bolts: ";
    for (char c : bolts) cout << c << " ";
    cout << endl;
  
    // Match nuts and bolts
    matchPairs(nuts, bolts, 0, n - 1);
  
    cout << "\nMatched pairs:" << endl;
    cout << "Nuts: ";
    for (char c : nuts) cout << c << " ";
    cout << endl << "Bolts: ";
    for (char c : bolts) cout << c << " ";
    cout << endl;
  
    return 0;
}
```

### Time and Space Complexity

- **Time Complexity**: O(n log n) on average, where n is the number of nuts/bolts
- **Space Complexity**: O(log n) for the recursion stack

### Similar Problems

1. **LeetCode 1244 - Lock and Key (Premium)**: This is a premium problem on LeetCode that directly maps to the nuts and bolts problem.
2. **Related Problems**:

   - **LeetCode 148 - Sort List**: While not directly related, this problem also uses the divide-and-conquer approach of quicksort.
   - **LeetCode 912 - Sort an Array**: Implementing different sorting algorithms including quicksort.

### Applications

This problem has practical applications in:

1. Hardware assembly where parts need to be matched
2. Database join operations
3. Bipartite matching problems

### Notes

- The key insight is that we cannot directly compare nuts with nuts or bolts with bolts, which makes this problem unique.
- This is a classic example of how the partitioning concept from QuickSort can be adapted for specialized problems.
