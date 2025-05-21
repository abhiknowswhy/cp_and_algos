Quick sort algorithm:

- The `partition` function selects a pivot and rearranges elements so that all elements less than the pivot come before it and all elements greater come after.
- `quickSort` recursively sorts the sub-arrays.
- Time complexity is O(n log n) on average, and O(n²) in the worst case (e.g., sorted input and poor pivot choice).

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
