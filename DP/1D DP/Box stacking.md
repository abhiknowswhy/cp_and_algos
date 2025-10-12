# Box Stacking Problem

## Problem Description

The Box Stacking problem involves finding the tallest possible stack of boxes where boxes can be rotated but must follow the constraint that a box can only be placed on top of another box if the base dimensions of the top box are strictly smaller than the base dimensions of the box below it.

## Algorithm Approach

1. **Generate All Rotations**: For each box, we create three different orientations by rotating it in all possible ways.
2. **Sort by Base Area**: Sort all box orientations in descending order of their base area to efficiently build the solution.
3. **Dynamic Programming**: Use a 1D DP approach similar to the Longest Increasing Subsequence problem.
   - `dp[i]` represents the maximum height possible with box `i` at the top of the stack.
   - For each box, we look at all previous boxes that can support it and update the maximum height.

## Time and Space Complexity

- **Time Complexity**: O(n²) where n is the number of boxes (after generating all rotations)
- **Space Complexity**: O(n) for the DP array

## Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Box {
    int height, breadth, depth;

    Box(int h, int b, int d) {
        height = h;
        breadth = b;
        depth = d;
    }

    // base area
    int area() const {
        return breadth * depth;
    }

    // For sorting boxes in descending order of base area
    bool operator<(const Box& other) const {
        return area() > other.area();
    }
};

// Check if box `top` can be placed on box `bottom`
bool canPlace(const Box& top, const Box& bottom) {
    return top.breadth < bottom.breadth && top.depth < bottom.depth;
}

// Main function to compute tallest tower
int maxStackHeight(vector<tuple<int, int, int>>& inputBoxes) {
    vector<Box> boxes;

    // Generate all 3 rotations for each box
    for (auto& [h, b, d] : inputBoxes) {
        boxes.emplace_back(h, min(b, d), max(b, d));
        boxes.emplace_back(b, min(h, d), max(h, d));
        boxes.emplace_back(d, min(h, b), max(h, b));
    }

    // Sort boxes by base area in descending order
    sort(boxes.begin(), boxes.end());

    int n = boxes.size();
    vector<int> dp(n);

    // Initialize dp with box heights
    for (int i = 0; i < n; ++i) {
        dp[i] = boxes[i].height;
    }

    // Build up dp[i] = max height ending at box i
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (canPlace(boxes[i], boxes[j])) {
                dp[i] = max(dp[i], dp[j] + boxes[i].height);
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

int main() {
    // Input: list of 3D box dimensions
    vector<tuple<int, int, int>> boxes = {
        {4, 6, 7},
        {1, 2, 3},
        {4, 5, 6}
    };

    cout << "Maximum stack height is: " << maxStackHeight(boxes) << endl;
    return 0;
}
```

## Key Insights

1. **Box Rotation**: We generate all possible orientations for each box. For a box with dimensions (h, w, d), the possible orientations are:

   - (h, min(w, d), max(w, d))
   - (w, min(h, d), max(h, d))
   - (d, min(h, w), max(h, w))
2. **Base Area Sorting**: Sorting by base area is a heuristic that works well with the dynamic programming approach. Larger base areas tend to be better candidates for the bottom of the stack.
3. **1D DP Solution**: This problem is a variation of the Longest Increasing Subsequence (LIS) problem, where the "sequence" is the stack of boxes and the "increasing" property is the ability to place one box on top of another.

## Related LeetCode Problems

- [1691. Maximum Height by Stacking Cuboids](https://leetcode.com/problems/maximum-height-by-stacking-cuboids/) - Direct application of this algorithm
- [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) - 2D version of this problem
- [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) - The foundational algorithm upon which thiolution is based

## Extensions and Variations

- You can modify this algorithm to track which boxes are actually used in the optimal solution by maintaining parent pointers.
- A more efficient O(n log n) solution is possible using a modified LIS approach with binary search, similar to how the LIS problem can be optimized

# LeetCode 1691: Maximum Height by Stacking Cuboids

This is a similar problem to the box stacking problem above, but with a key difference: each cuboid can only be used once (no repetitions allowed). Let's implement the solution:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Solution for LeetCode 1691: Maximum Height by Stacking Cuboids
int maxHeight(vector<vector<int>>& cuboids) {
    // Step 1: Sort each cuboid's dimensions in non-decreasing order
    for (auto& cuboid : cuboids) {
        sort(cuboid.begin(), cuboid.end());
    }
    
    // Step 2: Sort cuboids by volume (or any consistent measure)
    sort(cuboids.begin(), cuboids.end(), [](const vector<int>& a, const vector<int>& b) {
        if (a[0] != b[0]) return a[0] < b[0];
        if (a[1] != b[1]) return a[1] < b[1];
        return a[2] < b[2];
    });
    
    int n = cuboids.size();
    vector<int> dp(n);
    
    // Initialize dp with the height of each cuboid itself
    for (int i = 0; i < n; i++) {
        dp[i] = cuboids[i][2]; // Height is the largest dimension after sorting
    }
    
    // Build the solution using dynamic programming
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // Check if cuboid j can be placed below cuboid i
            if (cuboids[j][0] <= cuboids[i][0] && 
                cuboids[j][1] <= cuboids[i][1] && 
                cuboids[j][2] <= cuboids[i][2]) {
                dp[i] = max(dp[i], dp[j] + cuboids[i][2]);
            }
        }
    }
    
    // Return the maximum height possible
    return *max_element(dp.begin(), dp.end());
}

// Demo function to test the implementation
void testMaxHeight() {
    // Example 1
    vector<vector<int>> cuboids1 = {{50,45,20},{95,37,53},{45,23,12}};
    cout << "Example 1 result: " << maxHeight(cuboids1) << endl; // Expected: 190
    
    // Example 2
    vector<vector<int>> cuboids2 = {{38,25,45},{76,35,3}};
    cout << "Example 2 result: " << maxHeight(cuboids2) << endl; // Expected: 76
    
    // Example 3
    vector<vector<int>> cuboids3 = {{7,11,17},{7,17,11},{11,7,17},{11,17,7},{17,7,11},{17,11,7}};
    cout << "Example 3 result: " << maxHeight(cuboids3) << endl; // Expected: 102
}
```

### Key Differences from Original Box Stacking Problem

1. **No Repetition**: Each cuboid can be used at most once in the stack.
2. **Rotation Handling**: We sort each cuboid's dimensions first, effectively considering all rotations implicitly.
3. **Comparison Logic**: A cuboid can be placed on top of another if all its dimensions are less than or equal to the dimensions of the cuboid below it.

### Algorithm Explained

1. **Sort Cuboid Dimensions**: For each cuboid, sort its dimensions in non-decreasing order to standardize the orientation.
2. **Sort All Cuboids**: Sort all cuboids by their dimensions to make the DP solution more efficient.
3. **Dynamic Programming**: Use 1D DP where `dp[i]` represents the maximum height possible with cuboid `i` at the top.
4. **Build Solution**: For each cuboid, consider all previous cuboids that can support it and update the maximum height.

### Time and Space Complexity

- **Time Complexity**: O(n²) where n is the number of cuboids
- **Space Complexity**: O(n) for the DP array

### Comparison with Original Box Stacking Problem

The LeetCode 1691 problem is more constrained than the general box stacking problem:

1. **Original Problem**: Each box can be used multiple times with different rotations.
2. **LeetCode 1691**: Each cuboid can only be used once, but in any valid rotation.

Both problems use similar dynamic programming approaches but with different constraints on how boxes/cuboids can be used in the optimal stack.
