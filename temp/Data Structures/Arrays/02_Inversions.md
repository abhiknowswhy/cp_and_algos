# Count number of inversions in an array

To count the number of **inversions** in an unsorted array efficiently, we can use a modified version of **Merge Sort**, which runs in `O(n log n)` time.

### What is an inversion?

An **inversion** is a pair `(i, j)` such that:

- `i < j` and
- `arr[i] > arr[j]`

Examples:

- [Number of reverse pairs](https://leetcode.com/problems/reverse-pairs/description/)

### C++ Code (Using Merge Sort)

```cpp
#include <iostream>
#include <vector>

using namespace std;

long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    long long invCount = 0;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
            // All remaining elements in leftArr will form inversions with rightArr[j]
            invCount += leftArr.size() - i;
        }
    }

    while (i < leftArr.size())
        arr[k++] = leftArr[i++];

    while (j < rightArr.size())
        arr[k++] = rightArr[j++];

    return invCount;
}

long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    long long invCount = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        invCount += mergeSortAndCount(arr, left, mid);
        invCount += mergeSortAndCount(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }

    return invCount;
}

int main() {
    vector<int> arr = {8, 4, 2, 1};
    long long invCount = mergeSortAndCount(arr, 0, arr.size() - 1);

    cout << "Number of inversions: " << invCount << endl;
    return 0;
}
```

---

### Example:

Input: `{8, 4, 2, 1}`
Output: `6`
Explanation: Inversions are `(8,4), (8,2), (8,1), (4,2), (4,1), (2,1)`
