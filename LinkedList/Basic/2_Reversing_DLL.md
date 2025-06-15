# Reversing a Doubly Linked List

To reverse the doubly linked list:

1. Traverse through the list: Start from the head node.
2. Swap the `next` and `prev` pointers for each node. For example, for a node `current`, after the swap:

   * `current->next` becomes `current->prev`
   * `current->prev` becomes `current->next`
3. Update the head pointer: After the list is reversed, the last node will become the new head of the list.

```cpp
#include <iostream>
using namespace std;

// Define the structure for a doubly linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;

    // Constructor to initialize node with data
    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// Function to reverse the doubly linked list
Node* reverseDoublyLinkedList(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* temp = nullptr;
    Node* current = head;

    // Traverse through the list and swap next and prev pointers for each node
    while (current != nullptr) {
        // Swap the prev and next pointers
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        // Move to the next node (which is now prev)
        current = current->prev;
    }

    // The last node is the new head of the list
    if (temp != nullptr) {
        head = temp->prev;
    }

    return head;
}

// Function to print the doubly linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Function to insert a new node at the end of the list
void append(Node head, int new_data) {
    Node* new_node = new Node(new_data);
    
    // If the list is empty, make the new node the head
    if (*head == nullptr) {
        *head = new_node;
        return;
    }

    // Otherwise, traverse to the end and add the new node
    Node* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

// Main function
int main() {
    Node* head = nullptr;
    
    // Create a doubly linked list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);

    cout << "Original Doubly Linked List: ";
    printList(head);

    // Reverse the doubly linked list
    head = reverseDoublyLinkedList(head);

    cout << "Reversed Doubly Linked List: ";
    printList(head);

    return 0;
}
```
