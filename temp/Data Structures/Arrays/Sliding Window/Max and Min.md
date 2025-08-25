
### Sliding‑Window Min/Max: Idea

For an array `nums` and window size `k` you want, for every index `i ≥ k − 1`, either

* **max** of `nums[i‑k+1 … i]`, or
* **min** of `nums[i‑k+1 … i]`.

A naïve “scan each window” costs **Θ(n k)**.
The optimal **Θ(n)** solution keeps a **monotonic deque** that stores *indices*:

| Operation                                  | Sliding‑Window**Maximum**                                 | Sliding‑Window **Minimum**                               |
| ------------------------------------------ | ---------------------------------------------------------------- | ---------------------------------------------------------------- |
| Maintain order inside deque                | **Decreasing** values (front ≥ back)                      | **Increasing** values (front ≤ back)                      |
| Pop when element is**out of window** | `if dq.front() == i‑k` → pop\_front                          | same                                                             |
| Pop while new element breaks monotonicity  | `while !dq.empty() && nums[dq.back()] ≤ nums[i]` → pop\_back | `while !dq.empty() && nums[dq.back()] ≥ nums[i]` → pop\_back |
| Append new index `i`                     | `dq.push_back(i)`                                              | same                                                             |
| Current answer once `i ≥ k‑1`          | `nums[dq.front()]`                                             | same                                                             |

Because each index enters and leaves the deque once, total work is O(n).

---

## 1. Sliding Window **Maximum** (LeetCode 239)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    deque<int> dq;              // stores indices, values are decreasing
    vector<int> ans;

    for (int i = 0; i < (int)nums.size(); ++i) {
        // 1. Remove indices left of window
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();

        // 2. Maintain decreasing order
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();

        dq.push_back(i);

        // 3. Record answer when first window is filled
        if (i >= k - 1) ans.push_back(nums[dq.front()]);
    }
    return ans;
}

int main() {
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    auto res = maxSlidingWindow(nums, k);
    for (int x : res) cout << x << ' ';  // 3 3 5 5 6 7
    cout << '\n';
    return 0;
}
```

---

## 2. Sliding Window **Minimum** (same idea, monotone ↑)

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> minSlidingWindow(const vector<int>& nums, int k) {
    deque<int> dq;              // stores indices, values are increasing
    vector<int> ans;

    for (int i = 0; i < (int)nums.size(); ++i) {
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] >= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(nums[dq.front()]);
    }
    return ans;
}

int main() {
    vector<int> nums = {4,2,12,3,-1,5};
    int k = 2;
    auto res = minSlidingWindow(nums, k);
    for (int x : res) cout << x << ' ';  // 2 2 3 -1 -1
    cout << '\n';
    return 0;
}
```

---

### One‑Pass Min **and** Max (useful for constraints checks)

Problems such as **LeetCode 1438 – Longest Continuous Subarray With Abs Diff ≤ Limit** run two deques simultaneously—one decreasing for max and one increasing for min—to track the current window’s min/max while expanding/contracting pointers.

---

## LeetCode Practice References

| Problem                                                                 | What to practice                      |
| ----------------------------------------------------------------------- | ------------------------------------- |
| **239. Sliding Window Maximum**                                   | Classic deque for maximum             |
| **1438. Longest Continuous Subarray With Absolute Diff ≤ Limit** | Two deques (min & max) at once        |
| **480. Sliding Window Median**                                    | Harder variant using multiset / heaps |

Use these problems to deepen mastery of the pattern.
