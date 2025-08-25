### 📘 **Counting Sort Explained (with C++ Code)**

#### 🔸 What is Counting Sort?

**Counting Sort** is a **non-comparative**, **integer sorting algorithm**.
It works by **counting the frequency** of each element in the input and then **computing their positions** in the sorted array.


[Video explanation](https://www.youtube.com/watch?v=EItdcGhSLf4)

---

### 🔸 When to Use

- Works well when:

  - All elements are **non-negative integers**
  - The **maximum value (k)** is not too large compared to the number of elements (n)

---

### 🔸 Time and Space Complexity

| Case                                                           | Time               |
| -------------------------------------------------------------- | ------------------ |
| Best / Avg / Worst                                             | **O(n + k)** |
| `n` = number of elements, `k` = range of input (max value) |                    |

🧠 **Note:** It does not use comparisons, so it’s not subject to O(n log n) lower bound of comparison sorts.

---

### 🔸 How It Works (Step-by-Step)

Given array: `[4, 2, 2, 8, 3, 3, 1]`

1. Find the **max element** → 8
2. Create a `count[]` array of size `max+1` (0 to 8) → initialized to 0
3. Count frequency of each element
   `count[2] = 2`, `count[3] = 2`, etc.
4. Transform `count[]` to **prefix sum** array (cumulative counts)
   This gives **positions** in the sorted output
5. Build the **output** array from input in reverse to make it **stable**

---

### 🔸 C++ Code: Counting Sort

```cpp
#include <iostream>
#include <vector>
using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    // Step 1: Create and initialize count array
    vector<int> count(maxVal + 1, 0);

    // Step 2: Store frequency of each element
    for (int num : arr) {
        count[num]++;
    }

    // Step 3: Change count[i] so it contains actual position info
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    // Step 4: Build the output array (stable sort -> go in reverse)
    vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        int val = arr[i];
        output[count[val] - 1] = val;
        count[val]--;
    }

    // Step 5: Copy the sorted output back to original array
    arr = output;
}

// Driver code
int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    countingSort(arr);

    cout << "Sorted array:\n";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
```

---

### 🔸 Output

```
Original array:
4 2 2 8 3 3 1
Sorted array:
1 2 2 3 3 4 8
```

---

### 🔸 Limitations

- ❌ Doesn’t work with negative numbers **(can be modified to support them)**
- ❌ Inefficient if the **range (k)** is very large compared to `n`
- ✅ Works only on **discrete values** (integers or characters, not floats)

---

### ✅ Summary

- **Counting Sort** is fast when the value range is small.
- It is **stable**, which is useful in algorithms like **Radix Sort**.
- Avoid for large-range values or for sorting floating points directly.

Let me know if you want a version that supports **negative numbers**, or if you'd like to see how it's used to sort **characters/strings**!
