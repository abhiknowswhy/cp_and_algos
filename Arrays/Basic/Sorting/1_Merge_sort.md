Merge sort algorithm:

Merge Sort is a divide and conquer algorithm. It works by recursively dividing the array into two halves, sorting each half, and then merging the sorted halves back together.
- Recursively split the array in half until each part has only one element (a single-element array is always sorted).
- Start merging the smaller arrays into sorted arrays.

```cpp
#include <iostream>
#include <vector>

using namespace std;

// Global temporary array for merging
vector<int> temp;

// Merge function using global temp array
void merge(vector<int>& arr, int left, int mid, int right) {
    int i = left;     // Index for left subarray
    int j = mid + 1;  // Index for right subarray
    int k = left;     // Index for temp array

    // Merge both halves into temp
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements of left half
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copy remaining elements of right half
    while (j <= right)
        temp[k++] = arr[j++];

    // Copy temp back into original array
    for (int idx = left; idx <= right; ++idx)
        arr[idx] = temp[idx];
}

// Recursive merge sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    // Initialize temp array with same size
    temp.resize(arr.size());

    cout << "Original array: ";
    printArray(arr);

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
```
