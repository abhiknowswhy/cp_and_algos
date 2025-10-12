# Flatten Nested List Iterator

## Problem Description

Given a nested list of integers, implement an iterator to flatten it. Each element is either an integer or a list (which can be nested). The iterator should support the following operations:

- **next()**: Returns the next integer in the flattened list.
- **hasNext()**: Returns whether there are more integers in the flattened list.

Your iterator should yield the integers in the correct order, meaning that you need to return the elements in the same order as if the nested list was flattened.

## Approaches to Solve the Problem

### 1. Flattening the List First

#### Intuition

- Convert the nested list into a flattened list during initialization
- Use a simple pointer to track the current position in the flattened list
- This approach precomputes the entire flattened list before any operations

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class NestedIterator {
private:
    vector<int> flattenedList;
    int position;
    
    // Helper function to recursively flatten the nested list
    void flatten(const vector<NestedInteger>& nestedList) {
        for (const NestedInteger& ni : nestedList) {
            if (ni.isInteger()) {
                flattenedList.push_back(ni.getInteger());
            } else {
                flatten(ni.getList());
            }
        }
    }
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        flattenedList.clear();
        position = 0;
        flatten(nestedList);
    }
    
    int next() {
        return flattenedList[position++];
    }
    
    bool hasNext() {
        return position < flattenedList.size();
    }
};
```

#### Explanation

- During initialization, we recursively flatten the nested list.
- The `flatten` method:
  - Traverses each element in the nested list.
  - If an element is an integer, it adds it to our flattened list.
  - If an element is a list, it recursively flattens that list.
- The `next` method simply returns the current element and advances the position.
- The `hasNext` method checks if there are more elements to be returned.

### 2. Stack-based Lazy Evaluation

#### Intuition

- Instead of processing the entire list at once, we can lazily evaluate elements as needed
- Use a stack to keep track of elements we need to process
- When `hasNext()` is called, prepare the next integer to be returned

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class NestedIterator {
private:
    stack<pair<vector<NestedInteger>::iterator, vector<NestedInteger>::iterator>> stk;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // Initialize stack with iterators pointing to the beginning and end of the list
        if (!nestedList.empty()) {
            stk.push({nestedList.begin(), nestedList.end()});
        }
        // Make sure the next element is ready
        findNextInteger();
    }
    
    // Helper function to prepare the next integer
    void findNextInteger() {
        while (!stk.empty()) {
            auto [current, end] = stk.top();
            
            // If we've reached the end of the current list, pop it
            if (current == end) {
                stk.pop();
                continue;
            }
            
            // If the current element is an integer, we're done
            if (current->isInteger()) {
                break;
            }
            
            // Move to the next element in the current list
            auto it = current;
            ++it;
            stk.top().first = it;
            
            // Push the nested list onto the stack
            const vector<NestedInteger>& nestedList = current->getList();
            if (!nestedList.empty()) {
                stk.push({nestedList.begin(), nestedList.end()});
            }
        }
    }
    
    int next() {
        auto [current, _] = stk.top();
        int result = current->getInteger();
        
        // Move to the next element
        ++stk.top().first;
        findNextInteger();
        
        return result;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};
```

#### Explanation

- We use a stack to keep track of iterators to the current position and end of each nested list.
- The `findNextInteger` method is responsible for preparing the next integer to be returned:
  - If the current list is exhausted, we pop it from the stack.
  - If the current element is an integer, we're done.
  - If the current element is a list, we advance to the next element in the current list and push the nested list onto the stack.
- The `next` method returns the current integer, advances the iterator, and prepares the next integer.
- The `hasNext` method simply checks if the stack is empty.

### 3. Queue-based Approach

#### Intuition

- Flatten the list during initialization, but using a queue instead of a vector
- This approach combines aspects of both previous approaches
- Good for scenarios where memory usage needs to be more dynamic

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class NestedIterator {
private:
    queue<int> elements;
    
    // Helper function to recursively flatten the nested list
    void flatten(const vector<NestedInteger>& nestedList) {
        for (const NestedInteger& ni : nestedList) {
            if (ni.isInteger()) {
                elements.push(ni.getInteger());
            } else {
                flatten(ni.getList());
            }
        }
    }
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        flatten(nestedList);
    }
    
    int next() {
        int val = elements.front();
        elements.pop();
        return val;
    }
    
    bool hasNext() {
        return !elements.empty();
    }
};
```

### 4. On-demand Stack Traversal

#### Intuition

- Similar to the second approach, but with a different stack organization
- We store actual NestedInteger objects in the stack rather than iterators
- More intuitive implementation for some developers

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class NestedIterator {
private:
    stack<NestedInteger> stk;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        // Push elements in reverse order so that when we pop them, they come out in the correct order
        for (int i = nestedList.size() - 1; i >= 0; --i) {
            stk.push(nestedList[i]);
        }
        
        // Make sure the next element is an integer
        makeStackTopAnInteger();
    }
    
    void makeStackTopAnInteger() {
        while (!stk.empty() && !stk.top().isInteger()) {
            NestedInteger top = stk.top();
            stk.pop();
            
            const vector<NestedInteger>& list = top.getList();
            for (int i = list.size() - 1; i >= 0; --i) {
                stk.push(list[i]);
            }
        }
    }
    
    int next() {
        int result = stk.top().getInteger();
        stk.pop();
        
        // Prepare next integer
        makeStackTopAnInteger();
        
        return result;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};
```

## Complexity Analysis

### Flattening the List First
- **Time Complexity**: 
  - Initialization: O(N), where N is the total number of integers in the nested list.
  - next(): O(1)
  - hasNext(): O(1)
- **Space Complexity**: O(N), to store all integers in the flattened list.

### Stack-based Lazy Evaluation
- **Time Complexity**: 
  - Initialization: O(D), where D is the maximum nesting depth. In worst case, we might need to go through all nesting levels to find the first integer.
  - next(): Amortized O(1). Each element is pushed and popped at most once.
  - hasNext(): O(1)
- **Space Complexity**: O(D), where D is the maximum nesting depth. We need to store at most one iterator pair per nesting level.

### Queue-based Approach
- **Time Complexity**: 
  - Initialization: O(N)
  - next(): O(1)
  - hasNext(): O(1)
- **Space Complexity**: O(N)

### On-demand Stack Traversal
- **Time Complexity**: 
  - Initialization: O(D)
  - next(): Amortized O(1)
  - hasNext(): O(1)
- **Space Complexity**: O(N) in the worst case, if all elements are at the same level.

## Step-by-Step Execution

Let's trace through the stack-based lazy evaluation approach with an example:

Input: `[[1,1],2,[1,1]]`

Initialization:
1. Push iterators to the beginning and end of the main list onto the stack.
   - Stack: [(iterator to [1,1], iterator to end)]
2. Call `findNextInteger`:
   - Current element is [1,1], which is not an integer.
   - Move to the next element in the main list (2).
   - Push iterators for [1,1] onto the stack.
   - Stack: [(iterator to 2, iterator to end), (iterator to 1, iterator to end)]
   - Current element is 1, which is an integer. We're done.

Call `hasNext()`: Returns true.

Call `next()`:
1. Get the current integer: 1
2. Move to the next element in the current list.
   - Stack: [(iterator to 2, iterator to end), (iterator to end, iterator to end)]
3. Call `findNextInteger`:
   - Pop the empty list from the stack.
   - Stack: [(iterator to 2, iterator to end)]
   - Current element is 2, which is an integer. We're done.
4. Return 1.

Call `hasNext()`: Returns true.

Call `next()`:
1. Get the current integer: 2
2. Move to the next element in the main list.
   - Stack: [(iterator to [1,1], iterator to end)]
3. Call `findNextInteger`:
   - Current element is [1,1], which is not an integer.
   - Move to the next element in the main list (end).
   - Push iterators for [1,1] onto the stack.
   - Stack: [(iterator to end, iterator to end), (iterator to 1, iterator to end)]
   - Current element is 1, which is an integer. We're done.
4. Return 2.

The process continues until all integers are processed.

## Related LeetCode Problems

- [LeetCode 341: Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)
- [LeetCode 339: Nested List Weight Sum](https://leetcode.com/problems/nested-list-weight-sum/)
- [LeetCode 385: Mini Parser](https://leetcode.com/problems/mini-parser/)
- [LeetCode 364: Nested List Weight Sum II](https://leetcode.com/problems/nested-list-weight-sum-ii/)
- [LeetCode 173: Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/) - Similar iterator design pattern

## Applications

- **JSON/XML Parsers**: Traversing nested data structures in document formats
- **File System Navigation**: Iterating through nested directory structures
- **Tree Traversal**: Implementing iterators for tree-like data structures
- **Expression Evaluation**: Processing nested expressions in language parsers
- **Game Development**: Traversing nested game object hierarchies

## Summary

| Approach | Time Complexity (Init) | Time Complexity (next/hasNext) | Space Complexity | Pros | Cons |
|----------|------------------------|--------------------------------|------------------|------|------|
| Flattening First | O(N) | O(1) | O(N) | Simple implementation, fast operations | High initial cost, higher memory usage |
| Stack-based Lazy Evaluation | O(D) | Amortized O(1) | O(D) | Lower memory usage, lazy evaluation | More complex implementation |
| Queue-based | O(N) | O(1) | O(N) | Simple implementation using queue | High initial cost, higher memory usage |
| On-demand Stack Traversal | O(D) | Amortized O(1) | O(N) | Intuitive stack usage | Potentially higher memory usage than the second approach |

The choice between these approaches depends on the specific requirements:

- If memory is a concern and the entire nested list is large, the **Stack-based Lazy Evaluation** approach is preferred, as it only uses memory proportional to the maximum nesting depth.
  
- If the nested list is relatively small or if the initialization cost is not a concern, the **Flattening First** approach provides simpler code and consistent O(1) operations.

- If you want a balance between simplicity and efficiency, the **On-demand Stack Traversal** approach provides a more intuitive implementation while still offering lazy evaluation benefits.
