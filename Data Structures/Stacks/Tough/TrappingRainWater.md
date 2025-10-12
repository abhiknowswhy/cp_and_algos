# Trapping Rain Water

## Problem Description

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

For example, given the array [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], the answer is 6 units of water.

## Approaches to Solve the Problem

### 1. Brute Force Approach

#### Intuition

For each element in the array, find the maximum level of water it can trap. The amount of water at any element is determined by the minimum of the maximum height to its left and right, minus the height of the element itself.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int trapBruteForce(vector<int>& height) {
    int n = height.size();
    int result = 0;
    
    // For each element in the array
    for (int i = 1; i < n - 1; i++) {
        int leftMax = 0, rightMax = 0;
        
        // Find maximum height to the left
        for (int j = 0; j <= i; j++) {
            leftMax = max(leftMax, height[j]);
        }
        
        // Find maximum height to the right
        for (int j = i; j < n; j++) {
            rightMax = max(rightMax, height[j]);
        }
        
        // Add the water trapped at current position
        result += min(leftMax, rightMax) - height[i];
    }
    
    return result;
}

int main() {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water: " << trapBruteForce(height) << " units" << endl;
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n²), where n is the size of the array
- Space Complexity: O(1), only constant space is used

### 2. Dynamic Programming Approach

#### Intuition

Instead of computing the left and right maximums repeatedly, we can precompute them using dynamic programming:
- Create two arrays leftMax and rightMax
- leftMax[i] stores the maximum height from the beginning to position i
- rightMax[i] stores the maximum height from position i to the end
- Then for each position, calculate the trapped water

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int trapDP(vector<int>& height) {
    int n = height.size();
    if (n <= 2) return 0; // Need at least 3 bars to trap water
    
    vector<int> leftMax(n), rightMax(n);
    int result = 0;
    
    // Precompute the leftMax array
    leftMax[0] = height[0];
    for (int i = 1; i < n; i++) {
        leftMax[i] = max(leftMax[i-1], height[i]);
    }
    
    // Precompute the rightMax array
    rightMax[n-1] = height[n-1];
    for (int i = n-2; i >= 0; i--) {
        rightMax[i] = max(rightMax[i+1], height[i]);
    }
    
    // Calculate water trapped at each position
    for (int i = 1; i < n - 1; i++) {
        result += min(leftMax[i], rightMax[i]) - height[i];
    }
    
    return result;
}

int main() {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water (DP): " << trapDP(height) << " units" << endl;
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the size of the array
- Space Complexity: O(n) for the two additional arrays

### 3. Two-Pointer Approach

#### Intuition

We can optimize the space complexity by using two pointers. The idea is to maintain two pointers (left and right) and two variables (leftMax and rightMax):
- If height[left] < height[right], we know that the water trapped at position left is determined by leftMax
- Similarly, if height[left] >= height[right], the water trapped at position right is determined by rightMax
- Move the pointers toward each other until they meet

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

int trapTwoPointers(vector<int>& height) {
    int n = height.size();
    if (n <= 2) return 0;
    
    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int result = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            // Water trapped at left position is determined by leftMax
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                result += leftMax - height[left];
            }
            left++;
        } else {
            // Water trapped at right position is determined by rightMax
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                result += rightMax - height[right];
            }
            right--;
        }
    }
    
    return result;
}

int main() {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water (Two-Pointers): " << trapTwoPointers(height) << " units" << endl;
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the size of the array
- Space Complexity: O(1), only constant space is used

### 4. Stack-based Approach

#### Intuition

We can use a stack to keep track of indices of bars that are bounded by higher bars. When we find a bar that is higher than the one at the current stack top, we know that water can be trapped between them:
1. Keep a stack of indices
2. For each bar:
   - While current height is greater than the height at stack top
   - Pop the stack and calculate the trapped water
   - Push the current index to the stack

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int trapStack(vector<int>& height) {
    int n = height.size();
    int result = 0;
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        // If current bar is higher than the bar at stack top
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top();
            st.pop();
            
            // If stack becomes empty, no left boundary
            if (st.empty()) {
                break;
            }
            
            // Calculate width between current and previous bar
            int width = i - st.top() - 1;
            
            // Calculate height (bounded by the shorter of the left and right boundaries)
            int bounded_height = min(height[i], height[st.top()]) - height[top];
            
            // Add trapped water
            result += width * bounded_height;
        }
        
        // Push current index to stack
        st.push(i);
    }
    
    return result;
}

int main() {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water (Stack): " << trapStack(height) << " units" << endl;
    return 0;
}
```

#### Visual Example of the Stack Approach

For the array [0, 1, 0, 2, 1, 0, 1, 3]:

```
index: 0 1 2 3 4 5 6 7
value: 0 1 0 2 1 0 1 3

1. i=0, height[0]=0: Push index 0 to stack: [0]
2. i=1, height[1]=1 > height[0]=0:
   - Pop index 0, but since stack is now empty, no water is trapped
   - Push index 1 to stack: [1]
3. i=2, height[2]=0 < height[1]=1: Push index 2 to stack: [1, 2]
4. i=3, height[3]=2 > height[2]=0:
   - Pop index 2, top=2, height[top]=0
   - Left boundary: index 1, height[1]=1
   - Width = 3 - 1 - 1 = 1
   - Bounded height = min(2, 1) - 0 = 1
   - Water += 1 * 1 = 1
   - height[3]=2 > height[1]=1:
     - Pop index 1, but since stack is now empty, no more water trapped
   - Push index 3 to stack: [3]
...

Final trapped water = 6 units
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the size of the array
- Space Complexity: O(n) for the stack in the worst case

### 5. 3D Extension: Trapping Rain Water II

In the 2D version, water flows only in one direction. In a 3D extension, water can flow in multiple directions:

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Cell {
    int x, y, height;
    Cell(int x, int y, int h) : x(x), y(y), height(h) {}
};

// Comparator for min-heap to get the cell with minimum height
struct Compare {
    bool operator()(const Cell& a, const Cell& b) {
        return a.height > b.height;
    }
};

int trapRainWaterII(vector<vector<int>>& heightMap) {
    if (heightMap.empty() || heightMap[0].empty()) return 0;
    
    int m = heightMap.size();
    int n = heightMap[0].size();
    
    // Special case: if the grid is too small
    if (m < 3 || n < 3) return 0;
    
    // Min-heap to store cells from the boundary
    priority_queue<Cell, vector<Cell>, Compare> pq;
    
    // Mark visited cells
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    // Add all boundary cells to the priority queue
    for (int i = 0; i < m; i++) {
        pq.push(Cell(i, 0, heightMap[i][0]));
        pq.push(Cell(i, n-1, heightMap[i][n-1]));
        visited[i][0] = true;
        visited[i][n-1] = true;
    }
    
    for (int j = 1; j < n-1; j++) {
        pq.push(Cell(0, j, heightMap[0][j]));
        pq.push(Cell(m-1, j, heightMap[m-1][j]));
        visited[0][j] = true;
        visited[m-1][j] = true;
    }
    
    // Direction arrays for 4-way movement
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    int result = 0;
    
    // Process cells starting from the boundary
    while (!pq.empty()) {
        Cell curr = pq.top();
        pq.pop();
        
        // Check all 4 adjacent cells
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            
            // If the adjacent cell is within bounds and not visited
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                // Calculate water trapped at this cell
                result += max(0, curr.height - heightMap[nx][ny]);
                
                // Add the adjacent cell with its new "effective height"
                pq.push(Cell(nx, ny, max(heightMap[nx][ny], curr.height)));
                visited[nx][ny] = true;
            }
        }
    }
    
    return result;
}

int main() {
    vector<vector<int>> heightMap = {
        {1, 4, 3, 1, 3, 2},
        {3, 2, 1, 3, 2, 4},
        {2, 3, 3, 2, 3, 1}
    };
    
    cout << "Trapped water in 3D: " << trapRainWaterII(heightMap) << " units" << endl;
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 42: Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
2. [LeetCode 407: Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)
3. [LeetCode 11: Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
4. [LeetCode 84: Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## Applications

1. **Hydrological Modeling**: Simulating water accumulation in terrain
2. **Image Processing**: Filling "valleys" in image data
3. **Geographic Information Systems (GIS)**: Analyzing water flow in elevation models
4. **Architectural Design**: Estimating water accumulation on roofs

## Summary

| Approach | Time Complexity | Space Complexity | Notes |
| --- | --- | --- | --- |
| Brute Force | O(n²) | O(1) | Simple but inefficient for large inputs |
| Dynamic Programming | O(n) | O(n) | Uses precomputed arrays for efficiency |
| Two-Pointers | O(n) | O(1) | Most space-efficient approach |
| Stack-based | O(n) | O(n) | Good for visualizing the problem |
| 3D Extension | O(mn log(mn)) | O(mn) | For a 2D elevation map |
