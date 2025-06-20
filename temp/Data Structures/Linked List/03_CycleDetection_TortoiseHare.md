
# Floyd’s Tortoise and Hare Algorithm (Cycle Detection)

This algorithm uses two pointers (slow and fast), where the slow pointer moves one step at a time, and the fast pointer moves two steps at a time. If there is a cycle, the fast pointer will eventually meet the slow pointer.

Identifying the Node Where the Cycle Begins: Once we detect that a cycle exists, we can find the node where the cycle starts by moving one pointer to the head of the list and leaving the other pointer where they met. Move both pointers one step at a time, and the node they meet at will be the start of the cycle.

```cpp
#include <iostream>
using namespace std;

// Definition for a singly linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to detect if there is a cycle using Floyd's Tortoise and Hare
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;

    // Phase 1: Detect if there is a cycle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {  // Cycle detected
            // Phase 2: Find the entry point of the cycle
            ListNode* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;  // The start of the cycle
        }
    }

    return nullptr;  // No cycle detected
}

// Helper function to create a linked list with a cycle
ListNode* createLinkedListWithCycle() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = head->next->next;  // Cycle starts at node with value 3
    return head;
}

int main() {
    ListNode* head = createLinkedListWithCycle();
    
    ListNode* cycleStartNode = detectCycle(head);
    
    if (cycleStartNode) {
        cout << "Cycle detected. The cycle starts at node with value: " << cycleStartNode->val << endl;
    } else {
        cout << "No cycle detected." << endl;
    }

    return 0;
}
```
