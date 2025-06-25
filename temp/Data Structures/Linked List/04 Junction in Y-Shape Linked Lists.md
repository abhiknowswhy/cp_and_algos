# Finding Junction in Y-Shape Linked Lists

This problem involves finding the junction point where two linked lists merge to form a Y-shape. There are multiple approaches to solve this problem:

## Approach 1: Using Hash Set
Store all nodes of the first list in a hash set, then traverse the second list and check if any node is already in the set.

## Approach 2: Count Difference
1. Get the length of both lists
2. Calculate the difference in lengths
3. Move the longer list's pointer by the difference
4. Traverse both lists together until they meet

## Approach 3: Two Pointers (Most Elegant)
We can use two pointers that traverse both lists at the same pace. When a pointer reaches the end of one list, it switches to the head of the other list. Eventually, both pointers will meet at the junction point.

```cpp
#include <iostream>
using namespace std;

// Definition for a singly linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to find the intersection node of two linked lists
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    // If either list is empty, there can't be an intersection
    if (!headA || !headB) return nullptr;
    
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    
    // If the two pointers have different lengths, they'll eventually
    // synchronize after switching because:
    // Length of list A + Length of list B = Length of list B + Length of list A
    while (ptrA != ptrB) {
        // When a pointer reaches the end of one list, switch to the head of the other list
        ptrA = ptrA ? ptrA->next : headB;
        ptrB = ptrB ? ptrB->next : headA;
    }
    
    // ptrA is either pointing to the intersection or nullptr if no intersection
    return ptrA;
}

// Helper function to create two linked lists that intersect
void createIntersectingLists(ListNode*& headA, ListNode*& headB, ListNode*& intersection) {
    // Create first linked list: 1->2->3->4->5
    headA = new ListNode(1);
    headA->next = new ListNode(2);
    headA->next->next = new ListNode(3);
    
    // Create shared part: 8->9->10
    intersection = new ListNode(8);
    intersection->next = new ListNode(9);
    intersection->next->next = new ListNode(10);
    
    // Create second linked list: 6->7->...
    headB = new ListNode(6);
    headB->next = new ListNode(7);
    
    // Connect both lists to the shared part
    headA->next->next->next = intersection;
    headB->next->next = intersection;
}

int main() {
    ListNode* headA = nullptr;
    ListNode* headB = nullptr;
    ListNode* expectedIntersection = nullptr;
    
    createIntersectingLists(headA, headB, expectedIntersection);
    
    ListNode* intersectionNode = getIntersectionNode(headA, headB);
    
    if (intersectionNode) {
        cout << "Intersection found at node with value: " << intersectionNode->val << endl;
    } else {
        cout << "No intersection found." << endl;
    }
    
    return 0;
}
```

### Time and Space Complexity
- Time Complexity: O(m + n), where m and n are the lengths of the two lists
- Space Complexity: O(1), as we only use two pointers

### Why This Works
When the two lists have different lengths, the pointers will synchronize after they both traverse both lists. If there is an intersection, they will meet at that point. If there isn't one, they will both reach null at the same time after traversing both lists.
