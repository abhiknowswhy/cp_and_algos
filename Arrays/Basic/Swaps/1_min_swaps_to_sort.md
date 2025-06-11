# Min Swaps

Given an array of distinct integers, determine the minimum number of swaps required to sort the array in ascending order.

Steps:

1. Pair each element with its original index.
2. Sort the array by values.
3. Detect cycles in the array by checking how far each element is from its original position.
4. For each cycle of length k, you need k - 1 swaps.

Sample leet question(s):

- [Minimum Swaps to Sort by Digit Sum](https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minSwapsToSort(vector<int>& arr) {
    int n = arr.size();
    vector<pair<int, int>> arrPos(n);  // pair of value and original index

    // Step 1: Store value with original index
    for (int i = 0; i < n; ++i) {
        arrPos[i] = {arr[i], i};
    }

    // Step 2: Sort the array by values
    sort(arrPos.begin(), arrPos.end());

    // Step 3: Track visited elements
    vector<bool> visited(n, false);
    int swaps = 0;

    // Step 4: Detect cycles
    for (int i = 0; i < n; ++i) {
        // If already visited or already in correct position, skip
        if (visited[i] || arrPos[i].second == i)
            continue;

        int cycle_size = 0;
        int j = i;

        // Follow the cycle
        while (!visited[j]) {
            visited[j] = true;
            j = arrPos[j].second; // Move to next index in the cycle
            ++cycle_size;
        }

        // Add (cycle_size - 1) to swaps
        if (cycle_size > 1) {
            swaps += (cycle_size - 1);
        }
    }

    return swaps;
}

int main() {
    vector<int> nums = {4, 3, 2, 1};
    int result = minSwapsToSort(nums);
    cout << "Minimum number of swaps = " << result << endl;
    return 0;
}
```
