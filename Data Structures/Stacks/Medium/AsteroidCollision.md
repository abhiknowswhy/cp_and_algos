# Asteroid Collision

## Problem Description

We are given an array `asteroids` representing asteroids in a row. For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

## Approaches to Solve the Problem

### 1. Stack-based Approach

#### Intuition

We can use a stack to simulate the collision process:
- Asteroids moving to the right (positive values) will never collide with previously processed asteroids
- When we encounter an asteroid moving left (negative value), it may collide with previous asteroids moving right
- We can use a stack to keep track of asteroids that have survived collisions so far

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;
    
    for (int asteroid : asteroids) {
        // Flag to determine if current asteroid survives
        bool destroyed = false;
        
        // Check for collisions only when current asteroid is moving left
        // and there are asteroids moving right in the stack
        while (!st.empty() && asteroid < 0 && st.top() > 0) {
            // Current asteroid is destroyed
            if (abs(asteroid) < st.top()) {
                destroyed = true;
                break;
            } 
            // Top of stack is destroyed (equal size or smaller)
            else if (abs(asteroid) >= st.top()) {
                // Equal size, both destroyed
                if (abs(asteroid) == st.top()) {
                    destroyed = true;
                    st.pop();
                    break;
                }
                // Smaller asteroid in stack is destroyed
                st.pop();
            }
        }
        
        // If current asteroid wasn't destroyed in a collision, add it to stack
        if (!destroyed) {
            st.push(asteroid);
        }
    }
    
    // Convert stack back to vector (in reverse order)
    vector<int> result(st.size());
    for (int i = st.size() - 1; i >= 0; i--) {
        result[i] = st.top();
        st.pop();
    }
    
    return result;
}
```

#### Explanation

- We process each asteroid from left to right
- If we encounter an asteroid moving left (negative value), we check if it will collide with any previous asteroids moving right
- We keep popping asteroids from our stack that are moving right and get destroyed in the collision
- If the current asteroid gets destroyed, we set a flag and break the loop
- Otherwise, if the current asteroid survives all possible collisions, we add it to our stack
- Finally, we convert our stack back to a vector in the correct order

### 2. Optimized Stack Approach

#### Intuition

We can optimize the previous approach by directly building the result vector instead of using a stack and then converting it back.

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
    vector<int> result;
    
    for (int asteroid : asteroids) {
        // Flag to check if current asteroid survives
        bool survives = true;
        
        // Check for collisions with previously surviving asteroids
        while (!result.empty() && asteroid < 0 && result.back() > 0 && survives) {
            // Current asteroid is destroyed
            if (abs(asteroid) < result.back()) {
                survives = false;
            }
            // Equal size, both destroyed
            else if (abs(asteroid) == result.back()) {
                result.pop_back();
                survives = false;
            }
            // Previously surviving asteroid is destroyed
            else {
                result.pop_back();
            }
        }
        
        // Add the asteroid to result if it survives
        if (survives) {
            result.push_back(asteroid);
        }
    }
    
    return result;
}
```

#### Explanation

- We build the result vector directly as we process each asteroid
- For each asteroid, we check if it collides with any previously surviving asteroids
- If the asteroid survives all collisions, we add it to our result
- This approach is cleaner and avoids having to reverse the stack at the end

### 3. Simulation with Recursion

#### Intuition

We can also solve this problem recursively by simulating the collision between the current asteroid and the result of processing the remaining asteroids.

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> asteroidCollisionRecursive(vector<int>& asteroids, int index = 0) {
    // Base case: no more asteroids
    if (index >= asteroids.size()) {
        return {};
    }
    
    // Process the rest of the asteroids
    vector<int> rest = asteroidCollisionRecursive(asteroids, index + 1);
    int current = asteroids[index];
    
    // If no more asteroids, or no collision possible
    if (rest.empty() || current > 0 || rest[0] < 0) {
        rest.insert(rest.begin(), current);
        return rest;
    }
    
    // Check for collision with first asteroid in rest
    if (abs(current) > abs(rest[0])) {
        // Current destroys first asteroid in rest
        rest.erase(rest.begin());
        // Re-process current asteroid against new remainder
        vector<int> newAsteroids = {current};
        newAsteroids.insert(newAsteroids.end(), rest.begin(), rest.end());
        return asteroidCollisionRecursive(newAsteroids, 0);
    } 
    else if (abs(current) == abs(rest[0])) {
        // Both destroy each other
        rest.erase(rest.begin());
        return rest;
    } 
    else {
        // Current asteroid is destroyed
        return rest;
    }
}

vector<int> asteroidCollision(vector<int>& asteroids) {
    return asteroidCollisionRecursive(asteroids);
}
```

**Note:** This recursive approach is less efficient than the iterative ones and may cause stack overflow for large inputs, but it demonstrates an alternative way of thinking about the problem.

## Complexity Analysis

### Stack-based Approach
- **Time Complexity**: O(n), where n is the number of asteroids. Each asteroid is pushed and popped at most once.
- **Space Complexity**: O(n) in the worst case, where no collisions occur.

### Optimized Stack Approach
- **Time Complexity**: O(n), where n is the number of asteroids.
- **Space Complexity**: O(n) for the result vector.

### Recursive Approach
- **Time Complexity**: O(n²) in the worst case, as we might need to reprocess asteroids multiple times.
- **Space Complexity**: O(n) for the recursion stack and intermediate results.

## Step-by-Step Execution

Let's trace through an example using the optimized stack approach:

Input: `[5, 10, -5]`

1. Process asteroid 5:
   - No collisions possible (first asteroid)
   - result = [5]

2. Process asteroid 10:
   - No collisions (both moving in same direction)
   - result = [5, 10]

3. Process asteroid -5:
   - Collision with previous asteroid 10
   - |−5| < 10, so -5 is destroyed
   - result = [5, 10]

Final result: `[5, 10]`

Another example:
Input: `[8, -8]`

1. Process asteroid 8:
   - No collisions possible (first asteroid)
   - result = [8]

2. Process asteroid -8:
   - Collision with 8
   - |−8| == 8, so both are destroyed
   - result = []

Final result: `[]`

Complex example:
Input: `[10, 2, -5]`

1. Process asteroid 10:
   - No collisions possible (first asteroid)
   - result = [10]

2. Process asteroid 2:
   - No collisions (both moving in same direction)
   - result = [10, 2]

3. Process asteroid -5:
   - Collision with asteroid 2
   - |-5| > 2, so 2 is destroyed
   - result = [10]
   - Collision continues with asteroid 10
   - |-5| < 10, so -5 is destroyed
   - result = [10]

Final result: `[10]`

## Related LeetCode Problems

- [LeetCode 735: Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)
- [LeetCode 402: Remove K Digits](https://leetcode.com/problems/remove-k-digits/) - Uses a similar stack-based approach
- [LeetCode 316: Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/) - Stack-based greedy approach
- [LeetCode 1047: Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/) - Stack-based collision concept

## Applications

- **Collision Detection Systems**: Simulating collision detection between objects moving in opposite directions
- **Particle Physics Simulations**: Modeling particle interactions and collisions
- **Game Development**: Implementing collision mechanics in games like Asteroids or Breakout
- **Text Editors**: Implementing undo/redo functionality with complex operations
- **Network Packet Processing**: Managing packet collisions in network protocols

## Summary

| Approach | Time Complexity | Space Complexity | Pros | Cons |
|----------|-----------------|------------------|------|------|
| Stack-based | O(n) | O(n) | Simple implementation, handles all cases | Requires converting stack back to vector |
| Optimized Stack | O(n) | O(n) | More efficient, builds result directly | Similar to stack approach with slight optimization |
| Recursive | O(n²) | O(n) | Different perspective, cleaner logic | Less efficient, risk of stack overflow |

The optimized stack approach is generally preferred for this problem due to its simplicity and efficiency. The stack data structure is a perfect fit for this problem because it naturally models the collision process where we need to keep track of surviving asteroids and check for collisions with the most recently added asteroid moving in the opposite direction.
