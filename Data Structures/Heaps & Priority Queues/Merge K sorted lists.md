# Merge K Sorted Lists

## Problem Statement

Given `k` sorted linked lists, merge them into one sorted linked list and return its head.

## Algorithm Explanation

The most efficient way to merge k sorted lists is to use a min-heap (priority queue):

1. **Initialize a Min-Heap:** Insert the head of each list into the min-heap.
2. **Pop the Smallest Node:** Extract the node with the smallest value from the heap and add it to the merged list.
3. **Push Next Node:** If the extracted node has a next node, push it into the heap.
4. **Repeat:** Continue until the heap is empty.

This approach ensures that at each step, the smallest available node is chosen, resulting in an overall time complexity of O(N log k), where N is the total number of nodes.

## C++ Code (Executable)

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

struct compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;
    for (auto node : lists) {
        if (node) minHeap.push(node);
    }
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) minHeap.push(node->next);
    }
    return dummy.next;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Example: [[1,4,5],[1,3,4],[2,6]]
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);
    vector<ListNode*> lists = {l1, l2, l3};
    ListNode* merged = mergeKLists(lists);
    printList(merged);
    // Free memory (not shown for brevity)
    return 0;
}
```

## References

- [LeetCode 23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)
- [LeetCode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
