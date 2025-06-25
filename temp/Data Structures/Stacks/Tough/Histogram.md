# Largest Rectangle in Histogram

## Problem Description

Given n non-negative integers representing the height of bars in a histogram where the width of each bar is 1, find the area of the largest rectangle in the histogram.

## Approaches to Solve the Problem

### 1. Brute Force Approach (O(n²))

#### Intuition (Nearest Smaller Elements Approach)

- For each bar, consider it as the height of the rectangle
- Expand left and right as far as possible while maintaining that height
- Calculate the area and keep track of the maximum

#### Implementation (Nearest Smaller Elements Approach)

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // For min and max functions
using namespace std;

int largestRectangleAreaBruteForce(vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();
    for (int i = 0; i < n; ++i) {
        int minHeight = heights[i];
        for (int j = i; j < n; ++j) {
            minHeight = min(minHeight, heights[j]);
            int area = minHeight * (j - i + 1);
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

// Example usage
int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Largest rectangle area: " << largestRectangleAreaBruteForce(heights) << endl;
    return 0;
}
```

### 2. Using Nearest Smaller Elements (O(n))

#### Intuition

For each bar, we need to determine:

1. How far we can extend to the left
2. How far we can extend to the right
3. Calculate the area based on this width and the bar's height

To do this efficiently, for each bar we find:

- The nearest smaller bar to its left (NSL)
- The nearest smaller bar to its right (NSR)

Then, the width of the rectangle with the current bar's height would be:
`width = (NSR index - NSL index - 1)`

And the area would be:
`area = height[i] * width`

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // For max function
using namespace std;

int largestRectangleAreaUsingNSL_NSR(vector<int>& heights) {
    int n = heights.size();
  
    // Arrays to store indices of nearest smaller elements
    vector<int> left(n), right(n);
  
    // Stack to find nearest smaller elements
    stack<int> s;
  
    // Find nearest smaller element on the left
    for (int i = 0; i < n; i++) {
        // Remove elements from stack while they are greater than or equal to current
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
  
        // If stack is empty, there's no smaller element to the left
        left[i] = s.empty() ? -1 : s.top();
  
        // Push current index to stack
        s.push(i);
    }
  
    // Clear stack for reuse
    while (!s.empty()) {
        s.pop();
    }
  
    // Find nearest smaller element on the right
    for (int i = n - 1; i >= 0; i--) {
        // Remove elements from stack while they are greater than or equal to current
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
  
        // If stack is empty, there's no smaller element to the right
        right[i] = s.empty() ? n : s.top();
  
        // Push current index to stack
        s.push(i);
    }
  
    // Calculate maximum area
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        // Width is (right boundary - left boundary - 1)
        int width = right[i] - left[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
  
    return maxArea;
}

// Example usage
int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Largest rectangle area (NSL-NSR approach): " 
         << largestRectangleAreaUsingNSL_NSR(heights) << endl;
    return 0;
}
```

#### Visual Example

For array [2, 1, 5, 6, 2, 3]:

```
Index:  0  1  2  3  4  5
Value:  2  1  5  6  2  3
NSL:   -1 -1  1  2  1  4
NSR:    1  6  4  4  6  6
```

For each bar i:

- Bar 0 (height 2): Width = (1 - (-1) - 1) = 1, Area = 2 * 1 = 2
- Bar 1 (height 1): Width = (6 - (-1) - 1) = 6, Area = 1 * 6 = 6
- Bar 2 (height 5): Width = (4 - 1 - 1) = 2, Area = 5 * 2 = 10
- Bar 3 (height 6): Width = (4 - 2 - 1) = 1, Area = 6 * 1 = 6
- Bar 4 (height 2): Width = (6 - 1 - 1) = 4, Area = 2 * 4 = 8
- Bar 5 (height 3): Width = (6 - 4 - 1) = 1, Area = 3 * 1 = 3

The maximum area is 10 from bar 2.

#### Explanation of the NSL-NSR Approach

1. **Nearest Smaller Element to Left (NSL)**: For each position i, find the nearest position j such that j < i and heights[j] < heights[i]. If no such element exists, use -1.
2. **Nearest Smaller Element to Right (NSR)**: For each position i, find the nearest position j such that j > i and heights[j] < heights[i]. If no such element exists, use n (array length).
3. **Calculate Width**: For each bar i, the width of the maximum rectangle with height equal to heights[i] is (NSR[i] - NSL[i] - 1).
4. **Maximum Area**: Finally, calculate the area for each bar as heights[i] * width, and find the maximum.

#### Time and Space Complexity

- Time Complexity: O(n), as each bar is processed once
- Space Complexity: O(n) for the stack and arrays

### 3. Stack-Based One-Pass Approach (O(n))

#### Intuition

- Use a stack to maintain indices of bars in increasing order of height
- When we find a bar shorter than the bar at the top of the stack, we can calculate the area for the bar at the top
- This approach combines finding the boundaries and calculating areas into a single pass

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // For max function
using namespace std;

// Function to find largest rectangle in histogram
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> s;
    int maxArea = 0;
  
    // Process all bars
    for (int i = 0; i <= n; i++) {
        // Current height (use 0 for the last iteration to handle remaining elements in stack)
        int h = (i == n) ? 0 : heights[i];
  
        // If current bar is smaller than the bar at top of stack, calculate area of rectangle 
        // with the bar at top of stack as the smallest bar
        while (!s.empty() && h < heights[s.top()]) {
            // Height of top bar in stack
            int height = heights[s.top()];
            s.pop();
  
            // Calculate width of rectangle
            int width;
            if (s.empty())
                width = i;
            else
                width = i - s.top() - 1;
  
            // Calculate area and update maxArea if needed
            maxArea = max(maxArea, height * width);
        }
  
        // Push current index onto stack
        s.push(i);
    }
  
    return maxArea;
}

// Example usage
int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Largest rectangle area (Stack One-Pass): " 
         << largestRectangleArea(heights) << endl;
    return 0;
}
```

#### Explanation of the Stack-Based Algorithm

1. We use a stack to maintain indices of bars in increasing order of height
2. For each bar, we do the following:
   - If the stack is empty or the current bar's height is greater than or equal to the bar at the top of the stack, push the current index onto the stack.
   - If the current bar's height is smaller than the bar at the top of the stack, we've found a right boundary where the rectangle with the height of the stack's top bar ends.
   - We pop the stack and calculate the area of the rectangle with the popped bar as the height.
   - The width of this rectangle is determined by the current position and the new top of the stack.
3. We repeat this process for all bars and keep track of the maximum area.

### 4. Complete Example with All Approaches

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm> // For min and max functions
using namespace std;

// Brute Force approach O(n²)
int largestRectangleAreaBruteForce(vector<int>& heights) {
    int maxArea = 0;
    int n = heights.size();
    for (int i = 0; i < n; ++i) {
        int minHeight = heights[i];
        for (int j = i; j < n; ++j) {
            minHeight = min(minHeight, heights[j]);
            int area = minHeight * (j - i + 1);
            maxArea = max(maxArea, area);
        }
    }
    return maxArea;
}

// NSL-NSR approach O(n)
int largestRectangleAreaUsingNSL_NSR(vector<int>& heights) {
    int n = heights.size();
  
    // Arrays to store indices of nearest smaller elements
    vector<int> left(n), right(n);
  
    // Stack to find nearest smaller elements
    stack<int> s;
  
    // Find nearest smaller element on the left
    for (int i = 0; i < n; i++) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        left[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }
  
    // Clear stack for reuse
    while (!s.empty()) {
        s.pop();
    }
  
    // Find nearest smaller element on the right
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        right[i] = s.empty() ? n : s.top();
        s.push(i);
    }
  
    // Calculate maximum area
    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int width = right[i] - left[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
  
    return maxArea;
}

// Stack-based one-pass approach O(n)
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> s;
    int maxArea = 0;
  
    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
      
        while (!s.empty() && h < heights[s.top()]) {
            int height = heights[s.top()];
            s.pop();
          
            int width;
            if (s.empty())
                width = i;
            else
                width = i - s.top() - 1;
              
            maxArea = max(maxArea, height * width);
        }
      
        s.push(i);
    }
  
    return maxArea;
}

// Driver code to demonstrate all approaches
int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};
  
    cout << "Largest rectangle area (Brute Force): " 
         << largestRectangleAreaBruteForce(heights) << endl;
       
    cout << "Largest rectangle area (NSL-NSR approach): " 
         << largestRectangleAreaUsingNSL_NSR(heights) << endl;
       
    cout << "Largest rectangle area (Stack One-Pass): " 
         << largestRectangleArea(heights) << endl;
  
    vector<int> heights2 = {6, 2, 5, 4, 5, 1, 6};
    cout << "\nFor second example:\n";
  
    cout << "Largest rectangle area (Brute Force): " 
         << largestRectangleAreaBruteForce(heights2) << endl;
       
    cout << "Largest rectangle area (NSL-NSR approach): " 
         << largestRectangleAreaUsingNSL_NSR(heights2) << endl;
       
    cout << "Largest rectangle area (Stack One-Pass): " 
         << largestRectangleArea(heights2) << endl;
  
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 84: Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
2. [LeetCode 85: Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) (Extension of this problem to a 2D matrix)
3. [LeetCode 42: Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) (Similar approach using stacks)
4. [LeetCode 218: Skyline Problem](https://leetcode.com/problems/the-skyline-problem/description/)

## Summary

| Approach       | Time Complexity | Space Complexity | Comment                                 |
| -------------- | --------------- | ---------------- | --------------------------------------- |
| Brute Force    | O(n²)          | O(1)             | Simple but inefficient for large inputs |
| NSL-NSR        | O(n)            | O(n)             | Intuitive approach using stack twice    |
| Stack One-Pass | O(n)            | O(n)             | Most efficient, single pass solution    |
