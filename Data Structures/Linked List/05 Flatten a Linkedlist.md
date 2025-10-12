# Flatten a Linkedlist with Child Pointers

This problem involves flattening a linked list where each node has two pointers:
1. A `next` pointer to the next node in the current level
2. A `child` pointer that may point to a separate linked list

The goal is to flatten the list so that all nodes appear in a single-level, doubly linked list.

## Approach: Depth-First Search (DFS)
We use a recursive or iterative approach to flatten the list where we:
1. Find a node with a child
2. Insert the child's list between the current node and its next
3. Continue this process until the entire list is flattened

```cpp
#include <iostream>
using namespace std;

// Definition for a multi-level doubly linked list node
struct Node {
    int val;
    Node* prev;
    Node* next;
    Node* child;
    
    Node(int value) : val(value), prev(nullptr), next(nullptr), child(nullptr) {}
};

// Function to flatten a multi-level linked list
Node* flatten(Node* head) {
    if (!head) return nullptr;
    
    // Pointer to the current node being processed
    Node* current = head;
    
    // Process all nodes in the list
    while (current) {
        // If there's no child, move to the next node
        if (!current->child) {
            current = current->next;
            continue;
        }
        
        // Save the child list
        Node* childList = current->child;
        
        // Find the tail of the child list
        Node* childTail = childList;
        while (childTail->next) {
            childTail = childTail->next;
        }
        
        // Save the current's next node
        Node* nextNode = current->next;
        
        // Connect current node to the child list
        current->next = childList;
        childList->prev = current;
        
        // Connect child list tail to the next node (if it exists)
        if (nextNode) {
            childTail->next = nextNode;
            nextNode->prev = childTail;
        }
        
        // Remove the child pointer as it's now flattened
        current->child = nullptr;
        
        // Move to the next node
        current = current->next;
    }
    
    return head;
}

// Helper function to print the flattened list
void printList(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->val;
        if (current->next) cout << " <-> ";
        current = current->next;
    }
    cout << endl;
}

// Helper function to create a test multi-level linked list
// Structure to create:
// 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
//           |
//           7 <-> 8 <-> 9
//                |
//                10 <-> 11
Node* createMultiLevelList() {
    // Create the main level
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->prev = head;
    
    head->next->next = new Node(3);
    head->next->next->prev = head->next;
    
    head->next->next->next = new Node(4);
    head->next->next->next->prev = head->next->next;
    
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->prev = head->next->next->next;
    
    head->next->next->next->next->next = new Node(6);
    head->next->next->next->next->next->prev = head->next->next->next->next;
    
    // Create the second level
    head->next->next->child = new Node(7);
    
    head->next->next->child->next = new Node(8);
    head->next->next->child->next->prev = head->next->next->child;
    
    head->next->next->child->next->next = new Node(9);
    head->next->next->child->next->next->prev = head->next->next->child->next;
    
    // Create the third level
    head->next->next->child->next->child = new Node(10);
    
    head->next->next->child->next->child->next = new Node(11);
    head->next->next->child->next->child->next->prev = head->next->next->child->next->child;
    
    return head;
}

int main() {
    // Create a multi-level linked list
    Node* head = createMultiLevelList();
    
    // Flatten the list
    head = flatten(head);
    
    // Print the flattened list
    cout << "Flattened List: ";
    printList(head);
    
    return 0;
}
```

### Time and Space Complexity
- Time Complexity: O(n), where n is the total number of nodes in the linked list
- Space Complexity: O(1) as we modify the list in-place without using extra space

### Key Observations
1. We maintain the doubly linked list structure throughout the flattening process
2. We handle the child pointers by inserting them into the main list
3. The flattening process preserves the original order: first the nodes from the main list, then the nodes from the child list

This is similar to the flattening process used in DOM tree traversal, where we convert a tree structure into a linear structure while maintaining the relationship between nodes.
