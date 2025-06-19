# Binary search on a rotated sorted array

To perform **binary search on a rotated sorted array**, we need to modify standard binary search. A rotated sorted array is an array that was originally sorted but then rotated at some pivot point. For example:

```
Original:       [1, 2, 3, 4, 5, 6, 7]
Rotated:        [4, 5, 6, 7, 1, 2, 3]
```

### Idea:

At each step of binary search:

* One side of the array (either left or right of mid) is **always sorted**.
* Check which part is sorted.
* Decide where the target might lie, and adjust the search boundaries accordingly.

---

### C++ Complete Executable Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

class RotatedBinarySearch {
public:
    // Iterative Binary Search
    int searchIterative(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target)
                return mid;

            // Check if left half is sorted
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            // Right half is sorted
            else {
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }

        return -1; // not found
    }

    // Recursive Binary Search
    int searchRecursive(vector<int>& nums, int target) {
        return binarySearch(nums, 0, nums.size() - 1, target);
    }

private:
    int binarySearch(vector<int>& nums, int left, int right, int target) {
        if (left > right)
            return -1;

        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;

        // Left half is sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid])
                return binarySearch(nums, left, mid - 1, target);
            else
                return binarySearch(nums, mid + 1, right, target);
        }
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[right])
                return binarySearch(nums, mid + 1, right, target);
            else
                return binarySearch(nums, left, mid - 1, target);
        }
    }
};

int main() {
    vector<int> nums = {6, 7, 8, 1, 2, 3, 4, 5};
    int target = 3;

    RotatedBinarySearch searcher;
    int indexIter = searcher.searchIterative(nums, target);
    int indexRecur = searcher.searchRecursive(nums, target);

    cout << "Iterative approach: Element found at index " << indexIter << endl;
    cout << "Recursive approach: Element found at index " << indexRecur << endl;

    return 0;
}
```

---

### 🧠 Time Complexity:

* Both recursive and iterative: **O(log n)**
* Space: O(1) for iterative, O(log n) stack space for recursion.
