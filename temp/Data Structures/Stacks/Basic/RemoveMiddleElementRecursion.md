# Remove Middle Element of a Stack Using Recursion

## Problem Description

Given a stack, delete the middle element of it without using any additional data structure. Middle element is defined as:
- If the stack has odd number of elements, the middle element is floor(n/2) + 1 from bottom
- If the stack has even number of elements, the middle element is floor(n/2) from bottom

For example:
- For a stack of size 5: [1, 2, 3, 4, 5] (5 at the top), the middle element is 3
- For a stack of size 4: [1, 2, 3, 4] (4 at the top), the middle element is 2

## Approaches to Solve the Problem

### 1. Recursive Approach

#### Intuition

The idea is to use recursion to reach the middle element and then delete it:
1. Keep popping elements and counting how many elements are removed
2. When we reach the middle element, remove it
3. While returning from recursion, push back all the popped elements except the middle one

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

// Recursive function to delete middle element
void deleteMid(stack<int> &s, int n, int curr) {
    // Base case: if stack is empty
    if (s.empty()) {
        return;
    }
    
    // If current position is the middle element
    if (curr == n/2) {
        s.pop(); // Remove the middle element
        return;
    }
    
    // Remove the current element
    int x = s.top();
    s.pop();
    
    // Recursively call for the next element
    deleteMid(s, n, curr + 1);
    
    // Put back the removed element
    s.push(x);
}

// Function to delete middle element of a stack
void deleteMiddle(stack<int> &s) {
    int n = s.size();
    if (n == 0) {
        return;
    }
    
    // Start from top (index 0) and go down
    deleteMid(s, n, 0);
}

// Utility function to print stack
void printStack(stack<int> s) {
    if (s.empty()) {
        return;
    }
    
    int x = s.top();
    s.pop();
    
    printStack(s);
    
    cout << x << " ";
    
    s.push(x);
}

int main() {
    stack<int> st;
    // Push elements (bottom to top)
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    
    cout << "Original Stack (bottom to top): ";
    printStack(st);
    cout << endl;
    
    deleteMiddle(st);
    
    cout << "Stack after deletion of middle element (bottom to top): ";
    printStack(st);
    cout << endl;
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the number of elements in the stack
- Space Complexity: O(n) for the recursion call stack

### 2. Alternative Position Calculation

In some implementations, the middle element is defined differently. Here's a variation where the middle element is calculated from the top of the stack:

```cpp
#include <iostream>
#include <stack>
using namespace std;

// Recursive function to delete middle element
// This time middle is calculated from bottom of stack
void deleteMidFromBottom(stack<int> &s, int sizeOfStack, int current = 0) {
    // If stack is empty or all elements are traversed
    if (s.empty() || current == sizeOfStack) {
        return;
    }
    
    // Remove the current item
    int x = s.top();
    s.pop();
    
    // Recursively call for the next item
    deleteMidFromBottom(s, sizeOfStack, current + 1);
    
    // Put all items back except the middle one
    if (current != sizeOfStack / 2) {
        s.push(x);
    }
}

// Function to delete middle element
void deleteMiddleElement(stack<int> &s) {
    int n = s.size();
    deleteMidFromBottom(s, n);
}

int main() {
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    
    cout << "Original Stack (top to bottom): ";
    stack<int> temp = st;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
    
    deleteMiddleElement(st);
    
    cout << "Stack after deletion of middle element (top to bottom): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
    
    return 0;
}
```

### 3. Detailed Step-by-Step Execution

Let's trace through an example with a stack containing [1, 2, 3, 4, 5] (with 5 at the top):

1. Call `deleteMiddle([1, 2, 3, 4, 5])`
   - n = 5, middle = floor(5/2) = 2 (from top)
   - Call `deleteMid([1, 2, 3, 4, 5], 5, 0)`
     - curr = 0, not equal to n/2 = 2
     - Pop 5, stack becomes [1, 2, 3, 4]
     - Call `deleteMid([1, 2, 3, 4], 5, 1)`
       - curr = 1, not equal to n/2 = 2
       - Pop 4, stack becomes [1, 2, 3]
       - Call `deleteMid([1, 2, 3], 5, 2)`
         - curr = 2, equal to n/2 = 2
         - Pop 3 (the middle element), stack becomes [1, 2]
         - Return
       - Push 4 back, stack becomes [1, 2, 4]
       - Return
     - Push 5 back, stack becomes [1, 2, 4, 5]
     - Return
   - Stack after deletion: [1, 2, 4, 5]

### 4. Visual Representation of the Algorithm

For stack [1, 2, 3, 4, 5] with 5 at the top:

```
Original Stack:
top -> 5
       4
       3 (middle element to be removed)
       2
       1

Recursive call sequence:
1. deleteMid([1,2,3,4,5], 5, 0)
   - Pop 5, remember it
   - Call deleteMid([1,2,3,4], 5, 1)
     - Pop 4, remember it
     - Call deleteMid([1,2,3], 5, 2)
       - Middle element (3) found! Pop and discard
       - Return to previous call
     - Push 4 back
     - Return to previous call
   - Push 5 back
   - Return final stack

Stack after deletion:
top -> 5
       4
       2
       1
```

### 5. Without Using Recursion

While the problem asks for a recursive solution, here's an alternative approach using a temporary stack:

```cpp
#include <iostream>
#include <stack>
using namespace std;

void deleteMiddleIterative(stack<int> &s) {
    int n = s.size();
    if (n == 0) {
        return;
    }
    
    int middlePos = n / 2;
    stack<int> tempStack;
    
    // Remove elements until middle
    for (int i = 0; i < middlePos; i++) {
        tempStack.push(s.top());
        s.pop();
    }
    
    // Remove the middle element
    s.pop();
    
    // Put back the other elements
    while (!tempStack.empty()) {
        s.push(tempStack.top());
        tempStack.pop();
    }
}

int main() {
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    
    cout << "Original Stack (top to bottom): ";
    stack<int> temp = st;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
    
    deleteMiddleIterative(st);
    
    cout << "Stack after deletion of middle element (top to bottom): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
    
    return 0;
}
```

### 6. Alternative Method for Even-sized Stacks

For even-sized stacks, the "middle" element can be defined in different ways. Here's a variation where the middle element is defined as floor((n-1)/2) from top:

```cpp
#include <iostream>
#include <stack>
using namespace std;

// Returns the middle element position from top
int findMiddle(int size) {
    return (size - 1) / 2;
}

void deleteMid(stack<int> &s, int position) {
    if (position == 0) {
        s.pop(); // Remove the top element
        return;
    }
    
    int temp = s.top();
    s.pop();
    
    deleteMid(s, position - 1);
    
    s.push(temp);
}

void deleteMiddleElement(stack<int> &s) {
    int n = s.size();
    if (n == 0) {
        return;
    }
    
    int middle = findMiddle(n);
    deleteMid(s, middle);
}

int main() {
    // Test for odd-sized stack
    stack<int> odd;
    odd.push(1);
    odd.push(2);
    odd.push(3);
    odd.push(4);
    odd.push(5);
    
    cout << "Odd stack before deletion (top to bottom): 5 4 3 2 1" << endl;
    deleteMiddleElement(odd);
    cout << "Odd stack after deletion (top to bottom): ";
    while (!odd.empty()) {
        cout << odd.top() << " ";
        odd.pop();
    }
    cout << endl << endl;
    
    // Test for even-sized stack
    stack<int> even;
    even.push(1);
    even.push(2);
    even.push(3);
    even.push(4);
    
    cout << "Even stack before deletion (top to bottom): 4 3 2 1" << endl;
    deleteMiddleElement(even);
    cout << "Even stack after deletion (top to bottom): ";
    while (!even.empty()) {
        cout << even.top() << " ";
        even.pop();
    }
    cout << endl;
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 1019: Next Greater Node In Linked List](https://leetcode.com/problems/next-greater-node-in-linked-list/) (Similar stack manipulation)
2. [LeetCode 155: Min Stack](https://leetcode.com/problems/min-stack/) (Stack operations)
3. [LeetCode 1209: Remove All Adjacent Duplicates in String II](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/) (Stack manipulation)

## Applications

1. **Expression Evaluation**: Removing redundant operators
2. **Text Processing**: Removing specific elements from a sequence
3. **Backtracking Algorithms**: Removing invalid states

## Summary

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| Basic Recursion | O(n) | O(n) | Uses recursion to track position |
| Alternative Position | O(n) | O(n) | Different way to calculate middle position |
| Iterative with Temp Stack | O(n) | O(n) | Non-recursive solution |
| Even/Odd Stack Handling | O(n) | O(n) | Different middle definition for even-sized stack |
