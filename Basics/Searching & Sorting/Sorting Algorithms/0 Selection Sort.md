# Selection Sort

Selection Sort is a simple comparison-based sorting algorithm. It works by repeatedly finding the minimum element from the unsorted part of the array and moving it to the beginning. The algorithm maintains two subarrays in a given array:

- The subarray which is already sorted.
- The remaining subarray which is unsorted.

On each iteration, the minimum element from the unsorted subarray is picked and moved to the end of the sorted subarray.

**Time Complexity:** O(n²) comparisons and O(n) swaps. It is not stable by default and is generally not used for large datasets, but is useful for its simplicity and educational value.

### LeetCode References

- [LeetCode 912. Sort an Array](https://leetcode.com/problems/sort-an-array/) (implement any sorting algorithm)
- [LeetCode 2423. Remove Letter To Equalize Frequency](https://leetcode.com/problems/remove-letter-to-equalize-frequency/) (sorting as a subtask)

---

## C++ Implementations of Selection Sort

### 1. Basic Selection Sort (Simple, Not Stable)

```cpp
#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    selectionSort(arr);
    for (int x : arr) cout << x << ' ';
    cout << endl;
    return 0;
}
```

### 2. Selection Sort (Stable Version)

```cpp
#include <iostream>
#include <vector>
using namespace std;

void stableSelectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        int key = arr[minIdx];
        while (minIdx > i) {
            arr[minIdx] = arr[minIdx - 1];
            minIdx--;
        }
        arr[i] = key;
    }
}

int main() {
    vector<int> arr = {4, 5, 3, 2, 4, 1};
    stableSelectionSort(arr);
    for (int x : arr) cout << x << ' ';
    cout << endl;
    return 0;
}
```

### 3. Selection Sort (Descending Order)

```cpp
#include <iostream>
#include <vector>
using namespace std;

void selectionSortDesc(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] > arr[maxIdx]) maxIdx = j;
        }
        swap(arr[i], arr[maxIdx]);
    }
}

int main() {
    vector<int> arr = {7, 2, 9, 4, 3};
    selectionSortDesc(arr);
    for (int x : arr) cout << x << ' ';
    cout << endl;
    return 0;
}
```

---

These implementations show how Selection Sort can be adapted for different requirements. For more practice, see the LeetCode problems above.

---

## Merge K Sorted Lists

### Problem Explanation

Given K sorted linked lists, merge them into a single sorted linked list. This is a classic problem that tests your ability to work with data structures and optimize for time and space.

- **Input:** An array of K sorted linked lists.
- **Output:** A single sorted linked list containing all elements from the input lists.

#### Real-World Use

This problem is common in scenarios like merging log files, external sorting, and combining results from distributed systems.

### LeetCode References

- [LeetCode 23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)
- [LeetCode 373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) (related)

---

### C++ Solutions

#### 1. Naive Solution (Repeatedly Merge Lists)

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    ListNode* result = lists[0];
    for (int i = 1; i < lists.size(); ++i) {
        result = mergeTwoLists(result, lists[i]);
    }
    return result;
}

// Helper functions for testing
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}
void printList(ListNode* head) {
    while (head) {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<vector<int>> input = {{1,4,5},{1,3,4},{2,6}};
    vector<ListNode*> lists;
    for (auto& v : input) lists.push_back(buildList(v));
    ListNode* merged = mergeKLists(lists);
    printList(merged);
    return 0;
}
```

#### 2. Min-Heap (Priority Queue) Solution (Efficient)

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, Compare> pq;
    for (auto l : lists) if (l) pq.push(l);
    ListNode dummy(0), *tail = &dummy;
    while (!pq.empty()) {
        ListNode* node = pq.top(); pq.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) pq.push(node->next);
    }
    return dummy.next;
}

// Helper functions for testing
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}
void printList(ListNode* head) {
    while (head) {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<vector<int>> input = {{1,4,5},{1,3,4},{2,6}};
    vector<ListNode*> lists;
    for (auto& v : input) lists.push_back(buildList(v));
    ListNode* merged = mergeKLists(lists);
    printList(merged);
    return 0;
}
```

#### 3. Divide and Conquer (Optimal for Large K)

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    int n = lists.size();
    while (n > 1) {
        int k = (n + 1) / 2;
        for (int i = 0; i < n / 2; ++i) {
            lists[i] = mergeTwoLists(lists[i], lists[i + k]);
        }
        n = k;
    }
    return lists[0];
}

// Helper functions for testing
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}
void printList(ListNode* head) {
    while (head) {
        cout << head->val << ' ';
        head = head->next;
    }
    cout << endl;
}

int main() {
    vector<vector<int>> input = {{1,4,5},{1,3,4},{2,6}};
    vector<ListNode*> lists;
    for (auto& v : input) lists.push_back(buildList(v));
    ListNode* merged = mergeKLists(lists);
    printList(merged);
    return 0;
}
```

---

These approaches cover the spectrum from simple to optimal. For interviews, always discuss trade-offs and prefer the heap or divide-and-conquer methods for large K.
