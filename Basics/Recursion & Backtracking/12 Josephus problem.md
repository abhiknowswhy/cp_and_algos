# Josephus Problem

## Problem Statement
The Josephus problem is a classic problem in computer science and mathematics. Given `n` people standing in a circle, and we eliminate every `k`-th person until only one person remains. The task is to find the position of the last remaining person.

## Problem Explanation
- `n` people are arranged in a circle (positions 0 to n-1)
- Starting from position 0, we count `k` positions and eliminate that person
- Continue this process until only one person remains
- Return the position of the survivor

## Approach 1: Recursive Solution

The recursive relation is: `J(n, k) = (J(n-1, k) + k) % n`

```cpp
class Solution {
public:
    // Recursive approach
    int josephus(int n, int k) {
        // Base case: if only 1 person, they survive at position 0
        if (n == 1) {
            return 0;
        }
        
        // Recursive relation: J(n,k) = (J(n-1,k) + k) % n
        return (josephus(n - 1, k) + k) % n;
    }
};
```

**Time Complexity:** O(n)  
**Space Complexity:** O(n) due to recursion stack

## Approach 2: Iterative Solution

```cpp
class Solution {
public:
    // Iterative approach (more space efficient)
    int josephus(int n, int k) {
        int result = 0;
        
        // Apply the recurrence relation iteratively
        for (int i = 2; i <= n; i++) {
            result = (result + k) % i;
        }
        
        return result;
    }
};
```

**Time Complexity:** O(n)  
**Space Complexity:** O(1)

## Approach 3: Complete Implementation with 1-based indexing

```cpp
#include <iostream>
#include <vector>
using namespace std;

class JosephusProblem {
public:
    // 0-based indexing solution
    int josephusZeroBased(int n, int k) {
        if (n == 1) return 0;
        return (josephusZeroBased(n - 1, k) + k) % n;
    }
    
    // 1-based indexing solution (more intuitive)
    int josephusOneBased(int n, int k) {
        return josephusZeroBased(n, k) + 1;
    }
    
    // Simulation approach (for better understanding)
    int josephusSimulation(int n, int k) {
        vector<int> people;
        for (int i = 0; i < n; i++) {
            people.push_back(i);
        }
        
        int index = 0;
        while (people.size() > 1) {
            // Find the person to eliminate
            index = (index + k - 1) % people.size();
            people.erase(people.begin() + index);
            // After elimination, index stays the same
            // because we removed an element before it
        }
        
        return people[0];
    }
    
    // Print elimination order for visualization
    vector<int> josephusEliminationOrder(int n, int k) {
        vector<int> people;
        vector<int> eliminationOrder;
        
        for (int i = 1; i <= n; i++) {
            people.push_back(i);
        }
        
        int index = 0;
        while (people.size() > 1) {
            index = (index + k - 1) % people.size();
            eliminationOrder.push_back(people[index]);
            people.erase(people.begin() + index);
        }
        
        eliminationOrder.push_back(people[0]); // Last survivor
        return eliminationOrder;
    }
};

// Test function
void testJosephus() {
    JosephusProblem jp;
    
    cout << "Josephus Problem Test Cases:\n";
    cout << "n=5, k=2: Position = " << jp.josephusOneBased(5, 2) << endl;
    cout << "n=7, k=3: Position = " << jp.josephusOneBased(7, 3) << endl;
    
    cout << "\nElimination order for n=5, k=2: ";
    vector<int> order = jp.josephusEliminationOrder(5, 2);
    for (int i = 0; i < order.size(); i++) {
        cout << order[i];
        if (i < order.size() - 1) cout << " -> ";
    }
    cout << " (survivor)" << endl;
}
```

## Mathematical Insight

The recursive formula `J(n, k) = (J(n-1, k) + k) % n` works because:
1. When we eliminate one person, we have `n-1` people left
2. The positions shift by `k` positions due to the elimination
3. We use modulo to handle the circular nature

## LeetCode Related Problems

### 1. [LeetCode 1823: Find the Winner of the Circular Game](https://leetcode.com/problems/find-the-winner-of-the-circular-game/)
**Direct Josephus Problem Implementation**

```cpp
class Solution {
public:
    int findTheWinner(int n, int k) {
        // Using 1-based indexing as required by the problem
        return josephus(n, k) + 1;
    }
    
private:
    int josephus(int n, int k) {
        if (n == 1) return 0;
        return (josephus(n - 1, k) + k) % n;
    }
};
```

### 2. [LeetCode 390: Elimination Game](https://leetcode.com/problems/elimination-game/)
**Variation of Josephus Problem**

```cpp
class Solution {
public:
    int lastRemaining(int n) {
        bool leftToRight = true;
        int remaining = n;
        int step = 1;
        int head = 1;
        
        while (remaining > 1) {
            if (leftToRight || remaining % 2 == 1) {
                head += step;
            }
            remaining /= 2;
            step *= 2;
            leftToRight = !leftToRight;
        }
        
        return head;
    }
};
```

## Example Walkthrough

**Example: n=5, k=2**
- Initial: [1, 2, 3, 4, 5]
- Start at position 1, count 2: eliminate 2 → [1, 3, 4, 5]
- Start at position 3, count 2: eliminate 4 → [1, 3, 5]
- Start at position 5, count 2: eliminate 1 → [3, 5]
- Start at position 3, count 2: eliminate 5 → [3]
- Survivor: 3

## Key Points to Remember

1. **0-based vs 1-based indexing**: Be careful about the problem requirements
2. **Recursive relation**: `J(n, k) = (J(n-1, k) + k) % n`
3. **Base case**: When n=1, the survivor is at position 0 (0-based)
4. **Optimization**: Iterative solution is more space-efficient
5. **Applications**: Used in operating systems, distributed systems, and game theory

## Practice Problems

1. LeetCode 1823 - Find the Winner of the Circular Game
2. LeetCode 390 - Elimination Game
3. Find the k-th person to be eliminated
4. Josephus problem with varying step sizes
5. Multiple elimination rounds

## Time and Space Complexity Summary

| Approach | Time Complexity | Space Complexity |
|----------|----------------|------------------|
| Recursive | O(n) | O(n) |
| Iterative | O(n) | O(1) |
| Simulation | O(n²) | O(n) |
