# **Radix Sort**

**Radix Sort** is a **non-comparative** sorting algorithm that sorts integers by processing individual digits. It works best for **fixed-length integers** or strings.
It processes digits from **least significant digit (LSD)** to the **most significant digit (MSD)** (in the LSD Radix Sort version, which is the most commonly used).

### How It Works

Let’s say we are sorting the list:
`[170, 45, 75, 90, 802, 24, 2, 66]`

#### Step-by-step (LSD):

1. Sort numbers by **unit place** (1s digit)
2. Then sort by **tens** place
3. Then by **hundreds** place
   → Each step uses a **stable sorting algorithm** (commonly **Counting Sort**)

### Time and Space Complexity

| Case                                                                              | Time Complexity |
| --------------------------------------------------------------------------------- | --------------- |
| Best / Average / Worst                                                            | O(d × (n + k))  |
| `n` = number of elements, `d` = max number of digits, `k` = base (10 for decimal) |                 |

- **Efficient when** `d` is not large compared to `n`
- Not good for floating points or negatives (unless modified)

### Code for Radix Sort (Using Counting Sort)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A function to get the maximum value in an array
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// A stable counting sort for a specific digit (exp = 1 for units, 10 for tens, etc.)
void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);  // output array
    int count[10] = {0};    // count array for base 10 (digits 0-9)

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Update count[i] so it contains actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (in reverse to maintain stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output[] to arr[]
    arr = output;
}

// The main radix sort function
void radixSort(vector<int>& arr) {
    int maxVal = getMax(arr);

    // Apply counting sort to sort elements based on each digit
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

// Test the radix sort
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    radixSort(arr);

    cout << "Sorted array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
```

### Generalized Radix sort

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to get the maximum value in the array
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// Stable counting sort for a given base and digit (exp)
void countingSort(vector<int>& arr, int exp, int base) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(base, 0);  // Base-sized count array

    // Count occurrences of digits at current place value
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % base;
        count[digit]++;
    }

    // Accumulate count to get positions
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    // Build output array in reverse to maintain stability
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % base;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back to original array
    arr = output;
}

// Main Radix Sort function with base as parameter
void radixSort(vector<int>& arr, int base) {
    if (arr.empty()) return;

    int maxVal = getMax(arr);

    // Loop through each digit, from LSD to MSD
    for (int exp = 1; maxVal / exp > 0; exp *= base) {
        countingSort(arr, exp, base);
    }
}

// Test the generalized radix sort
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    int base;
    cout << "Enter base for radix sort (e.g., 2 for binary, 10 for decimal): ";
    cin >> base;

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    radixSort(arr, base);

    cout << "Sorted array in base-" << base << " logic:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
```

### C++ Code for Radix Sort for Base 2

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to get the maximum value in the array
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// Counting sort based on the bit at position 'bitPos'
void countingSortBitwise(vector<int>& arr, int bitPos) {
    int n = arr.size();
    vector<int> output(n);
    int count[2] = {0};  // only 0 and 1 for base 2

    // Count number of 0s and 1s at this bit position
    for (int i = 0; i < n; i++) {
        int bit = (arr[i] >> bitPos) & 1;
        count[bit]++;
    }

    // Update count to hold actual positions
    count[1] += count[0];  // only two values, so just one step

    // Place elements in output array in reverse for stability
    for (int i = n - 1; i >= 0; i--) {
        int bit = (arr[i] >> bitPos) & 1;
        output[--count[bit]] = arr[i];
    }

    // Copy output back to arr
    arr = output;
}

// Radix sort using bitwise operations for base 2
void radixSortBase2(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = getMax(arr);
    int maxBits = 0;

    // Find number of bits needed for maxVal
    while ((1 << maxBits) <= maxVal) {
        maxBits++;
    }

    // Apply counting sort for each bit position
    for (int bitPos = 0; bitPos < maxBits; bitPos++) {
        countingSortBitwise(arr, bitPos);
    }
}

// Test function
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    radixSortBase2(arr);

    cout << "Sorted array (using optimized base-2 radix sort):\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
```

### MSD Radix Sort

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Get the digit at a given position (from left), padded to width `width`
int getDigit(int number, int pos, int width) {
    int totalDigits = width;
    int digit = (number / static_cast<int>(pow(10, totalDigits - pos - 1))) % 10;
    return digit;
}

// Recursive MSD radix sort
void msdRadixSort(vector<int>& arr, int left, int right, int digitPos, int width) {
    if (left >= right || digitPos >= width) return;

    const int RADIX = 10;
    vector<vector<int>> buckets(RADIX);

    // Distribute numbers into buckets based on current digit
    for (int i = left; i <= right; ++i) {
        int digit = getDigit(arr[i], digitPos, width);
        buckets[digit].push_back(arr[i]);
    }

    // Copy back to original array and recurse on each bucket
    int index = left;
    for (int d = 0; d < RADIX; ++d) {
        int size = buckets[d].size();
        for (int i = 0; i < size; ++i) {
            arr[index++] = buckets[d][i];
        }

        // Recursively sort bucket if it has more than 1 element
        if (size > 1) {
            msdRadixSort(arr, index - size, index - 1, digitPos + 1, width);
        }
    }
}

// Public interface to MSD Radix Sort
void msdRadixSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Determine max number of digits (width)
    int maxVal = *max_element(arr.begin(), arr.end());
    int width = 0;
    while (maxVal > 0) {
        width++;
        maxVal /= 10;
    }

    msdRadixSort(arr, 0, arr.size() - 1, 0, width);
}

// Example usage
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    msdRadixSort(arr);

    cout << "Sorted array using MSD Radix Sort:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
```

---

### Trivia

- A non-comparative sorting algorithm does not rely on comparisons. Instead, it uses properties of the data (like digits or characters) to sort.
- Non-comparative sorts

  - Counting Sort – uses frequency counts.
  - Radix Sort – uses digits or characters to bucket items.
  - Bucket Sort – distributes elements into "buckets" based on value ranges.

- A sorting algorithm is stable if it preserves the relative order of elements that are equal.

| Stable         | Not Stable     |
| -------------- | -------------- |
| Merge Sort     | Quick Sort     |
| Bubble Sort    | Heap Sort      |
| Insertion Sort | Selection Sort |
| Radix Sort     | -              |
