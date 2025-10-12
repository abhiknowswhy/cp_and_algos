# Binomial Heap

A Binomial Heap is a collection of binomial trees that satisfies the following properties:

1. Each binomial tree in the heap obeys the min-heap property: the key of a node is greater than or equal to the key of its parent.
2. For any non-negative integer k, there is at most one binomial tree in the heap whose root has degree k.
3. The roots of the binomial trees form a linked list ordered by increasing degree.

## Binomial Tree

A binomial tree of order k, denoted as Bₖ, is defined recursively:

- B₀ is a single node.
- Bₖ consists of two b inomial trees Bₖ₋₁ that are linked together: the root of one becomes the leftmost child of the root of the other.

Properties of a binomial tree Bₖ:

- Has exactly 2ᵏ nodes
- The height is k
- The root has degree k (number of children)
- The root's children are roots of binomial trees B₀, B₁, ..., Bₖ₋₁
- The number of nodes at depth d is (k choose d)

## Operations

### Merge (Union)

The fundamental operation is merging two binomial heaps, which is used as a subroutine for other operations:

1. Merge the root lists of the two heaps in order of increasing degree.
2. Scan the merged list and link trees of same degree:
   - If there are three trees with the same degree, link the two with the smallest roots.
   - Always maintain the min-heap property by making the tree with smaller root value the parent.

Time Complexity: O(log n)

### Insert

1. Create a new binomial heap containing only the new element.
2. Merge this new heap with the existing binomial heap.

Time Complexity: O(log n) in worst case, but amortized O(1)

### Extract-Min

1. Find the binomial tree with minimum root value.
2. Remove this tree from the heap.
3. Create a new binomial heap from the children of the removed root.
4. Merge this new heap with the remaining original heap.

Time Complexity: O(log n)

### Decrease-Key

1. Decrease the key of the specified node.
2. Swap with parent if heap property is violated.
3. Continue swapping until heap property is restored.

Time Complexity: O(log n)

## C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

// Structure for Binomial Tree Node
struct Node {
    int key;
    int degree;
    Node* parent;
    Node* child;
    Node* sibling;
  
    Node(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

// Binomial Heap
class BinomialHeap {
private:
    Node* head;
  
    // Merges two root lists in increasing order of degree
    Node* mergeRootLists(Node* h1, Node* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
      
        Node* res = nullptr;
        Node** curr = &res;
      
        while (h1 && h2) {
            if (h1->degree <= h2->degree) {
                *curr = h1;
                h1 = h1->sibling;
            } else {
                *curr = h2;
                h2 = h2->sibling;
            }
            curr = &((*curr)->sibling);
        }
      
        if (h1) *curr = h1;
        if (h2) *curr = h2;
      
        return res;
    }
  
    // Links two binomial trees of same degree
    void linkBinomialTrees(Node* y, Node* z) {
        // Make y a child of z
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree++;
    }
  
    // Consolidates the binomial heap by merging trees of the same degree
    Node* consolidate(Node* h) {
        if (!h || !h->sibling) return h;
      
        Node* curr = h;
        Node* next = h->sibling;
        curr->sibling = nullptr;
      
        // Recursively consolidate the rest of the list
        next = consolidate(next);
      
        // Merge the consolidated list with the current node
        return unionHeaps(curr, next);
    }
  
    // Unions two heaps
    Node* unionHeaps(Node* h1, Node* h2) {
        Node* merged = mergeRootLists(h1, h2);
        if (!merged) return nullptr;
      
        Node* prev = nullptr;
        Node* curr = merged;
        Node* next = curr->sibling;
      
        while (next) {
            // Case 1 and 2: Current and next have different degrees
            // or there are three trees with the same degree
            if (curr->degree != next->degree || 
                (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            }
            // Case 3: Current and next have same degree, curr->key <= next->key
            else if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                linkBinomialTrees(next, curr);
            }
            // Case 4: Current and next have same degree, curr->key > next->key
            else {
                if (!prev) {
                    merged = next;
                } else {
                    prev->sibling = next;
                }
                linkBinomialTrees(curr, next);
                curr = next;
            }
            next = curr->sibling;
        }
      
        return merged;
    }
  
    // Finds the minimum node in the root list
    Node* findMinimum() const {
        if (!head) return nullptr;
      
        Node* min = head;
        Node* curr = head->sibling;
      
        while (curr) {
            if (curr->key < min->key) {
                min = curr;
            }
            curr = curr->sibling;
        }
      
        return min;
    }
  
public:
    BinomialHeap() : head(nullptr) {}
  
    bool isEmpty() const {
        return head == nullptr;
    }
  
    void insert(int key) {
        Node* newNode = new Node(key);
        BinomialHeap tempHeap;
        tempHeap.head = newNode;
        head = unionHeaps(head, tempHeap.head);
    }
  
    int getMin() const {
        Node* min = findMinimum();
        return min ? min->key : numeric_limits<int>::max();
    }
  
    int extractMin() {
        if (!head) return numeric_limits<int>::max();
      
        Node* min = findMinimum();
        Node* prev = nullptr;
        Node* curr = head;
      
        // Find the node before min
        while (curr != min) {
            prev = curr;
            curr = curr->sibling;
        }
      
        // Remove min from root list
        if (prev) {
            prev->sibling = min->sibling;
        } else {
            head = min->sibling;
        }
      
        // Create a new heap from min's children
        Node* newHead = nullptr;
        Node* child = min->child;
      
        // Reverse the child list
        while (child) {
            Node* next = child->sibling;
            child->sibling = newHead;
            child->parent = nullptr;
            newHead = child;
            child = next;
        }
      
        // Create a heap with the reversed child list
        BinomialHeap childHeap;
        childHeap.head = newHead;
      
        // Union the original heap with the child heap
        head = unionHeaps(head, childHeap.head);
      
        int minKey = min->key;
        delete min;
        return minKey;
    }
  
    void decreaseKey(Node* node, int newKey) {
        if (!node || newKey > node->key) return;
      
        node->key = newKey;
        Node* current = node;
        Node* parent = current->parent;
      
        // Bubble up if needed
        while (parent && current->key < parent->key) {
            swap(current->key, parent->key);
            current = parent;
            parent = current->parent;
        }
    }
  
    // Helper function to print the heap (for debugging)
    void printHeap() {
        cout << "Binomial Heap: ";
        Node* curr = head;
        while (curr) {
            cout << "B" << curr->degree << "(" << curr->key << ") ";
            curr = curr->sibling;
        }
        cout << endl;
    }
};

// Example usage
int main() {
    BinomialHeap bh;
  
    bh.insert(10);
    bh.insert(20);
    bh.insert(5);
    bh.insert(15);
    bh.insert(25);
    bh.insert(12);
    bh.insert(8);
  
    bh.printHeap();
  
    cout << "Minimum element: " << bh.getMin() << endl;
  
    cout << "Extracting minimum: " << bh.extractMin() << endl;
    bh.printHeap();
  
    cout << "Extracting minimum: " << bh.extractMin() << endl;
    bh.printHeap();
  
    return 0;
}
```

## Relevant LeetCode Problems

1. [**LC #23 - Merge k Sorted Lists**](https://leetcode.com/problems/merge-k-sorted-lists/):
   A binomial heap can be used to efficiently merge multiple sorted lists by keeping track of the current minimum element.
2. [**LC #295 - Find Median from Data Stream**](https://leetcode.com/problems/find-median-from-data-stream/):
   While typically solved with two heaps, a binomial heap could be used as the underlying implementation.
3. [**LC #355 - Design Twitter**](https://leetcode.com/problems/design-twitter/):
   A binomial heap could efficiently manage the merged feed of tweets from followed users.
4. [**LC #407 - Trapping Rain Water II**](https://leetcode.com/problems/trapping-rain-water-ii/):
   This problem uses a priority queue for processing cells in order of height, where a binomial heap could serve as an efficient implementation.
5. [**LC #1642 - Furthest Building You Can Reach**](https://leetcode.com/problems/furthest-building-you-can-reach/):
   A priority queue is used to optimize ladder usage, which could be implemented using a binomial heap.

## Performance Analysis

Compared to other heap implementations:

| Operation       | Binomial Heap | Binary Heap | Fibonacci Heap |
| --------------- | ------------- | ----------- | -------------- |
| Make Heap       | O(1)          | O(1)        | O(1)           |
| Insert          | O(log n)*     | O(log n)    | O(1)*          |
| Find Minimum    | O(log n)      | O(1)        | O(1)           |
| Extract Minimum | O(log n)      | O(log n)    | O(log n)*      |
| Decrease Key    | O(log n)      | O(log n)    | O(1)*          |
| Delete          | O(log n)      | O(log n)    | O(log n)*      |
| Merge           | O(log n)      | O(n)        | O(1)           |

\* indicates amortized time complexity

## Advantages and Disadvantages

### Advantages:

- Efficient merging of two heaps
- Supports more operations than binary heaps
- Good for applications requiring frequent merges

### Disadvantages:

- More complex implementation than binary heaps
- Finding the minimum element is O(log n) rather than O(1)
- Constant factors can be high in practice
