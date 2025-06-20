
# Reversing a Linked List

To reverse a linked list, we use three pointers:

- prevNode - Keeps track of the prevNodeious node (starts as NULL)
- currNode - Points to the currNode node being processed
- nextNode - Temporarily stores the next node before we change the currNode node's next pointer

```cpp
#include <iostream>
using namespace std;

// Define the structure for a linked list node
struct Node {
    int data;
    Node* next;
    
    // Constructor to initialize node with data
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Function to reverse the linked list
Node* reverseLinkedList(Node* head) {
    Node* prevNode = nullptr;
    Node* currNode = head;
    Node* nextNode = nullptr;
    
    while (currNode != nullptr) {
        nextNode = currNode->next;  // Save next node
        currNode->next = prevNode;      // Reverse currNodeent node's pointer
        prevNode = currNode;            // Move prevNode and currNode one step forward
        currNode = nextNode;
    }
    
    return prevNode;  // New head of the reversed list
}

// Function to print the linked list
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Function to insert a new node at the end of the list
void append(Node** head, int new_data) {
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
}

// Main function
int main() {
    Node* head = nullptr;
    
    // Create a linked list: 1 -> 2 -> 3 -> 4 -> 5
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);

    cout << "Original Linked List: ";
    printList(head);

    // Reverse the linked list
    head = reverseLinkedList(head);

    cout << "Reversed Linked List: ";
    printList(head);

    return 0;
}
```
