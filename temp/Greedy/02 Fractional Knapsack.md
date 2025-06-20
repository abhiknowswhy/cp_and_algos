# Fractional Knapsack Problem

## Description:
The Fractional Knapsack problem is a variation of the knapsack problem where we can take fractions of items instead of having to take the complete item or leave it. This means we can break items into smaller pieces, allowing us to always fill the knapsack to its full capacity (if there are enough items).

**Problem Statement:**
- Input: weights[0...n-1], values[0...n-1], capacity W
- Output: Maximum value that can be obtained while keeping total weight ≤ W, where we can take fractions of items

## Key Concepts:

1. **Greedy Approach**:
   - Unlike 0/1 Knapsack, Fractional Knapsack can be solved using a greedy algorithm which is optimal.
   - We compute the value-to-weight ratio for each item.
   - We sort the items based on this ratio in non-increasing order.
   - We start adding items from highest value-to-weight ratio to the lowest until the knapsack is full.
   - If an item can't be added completely, we add a fraction of it to fill the knapsack exactly.

2. **Time Complexity**:
   - The time complexity is O(n log n) due to the sorting operation.
   - Space complexity is O(1) if we modify the input arrays, or O(n) if we create a separate data structure.

3. **Comparison with 0/1 Knapsack**:
   - 0/1 Knapsack: Items are indivisible, requires dynamic programming, O(nW) time.
   - Fractional Knapsack: Items are divisible, uses greedy approach, O(n log n) time.

## Sample Implementation:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to store item information
struct Item {
    int weight;
    int value;
    double ratio; // value-to-weight ratio
};

// Comparison function for sorting items based on value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio; // Sort in non-increasing order
}

// Function to solve fractional knapsack problem
double fractionalKnapsack(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<Item> items(n);
    
    // Create item structures with their value-to-weight ratios
    for (int i = 0; i < n; i++) {
        items[i].weight = weights[i];
        items[i].value = values[i];
        items[i].ratio = (double)values[i] / weights[i];
    }
    
    // Sort items by value-to-weight ratio in non-increasing order
    sort(items.begin(), items.end(), compare);
    
    double totalValue = 0.0;
    
    // Add items to knapsack
    for (int i = 0; i < n; i++) {
        // If adding the item doesn't exceed capacity, add it completely
        if (capacity >= items[i].weight) {
            totalValue += items[i].value;
            capacity -= items[i].weight;
        }
        // Otherwise, add a fraction of the item
        else {
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break; // Knapsack is full
        }
    }
    
    return totalValue;
}

// Alternative implementation using pair
double fractionalKnapsackAlternative(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<pair<double, int>> valuePerWeight(n);
    
    // Calculate value-to-weight ratio for each item
    for (int i = 0; i < n; i++) {
        valuePerWeight[i] = {(double)values[i] / weights[i], i};
    }
    
    // Sort by value-to-weight ratio in non-increasing order
    sort(valuePerWeight.rbegin(), valuePerWeight.rend());
    
    double totalValue = 0.0;
    int remainingCapacity = capacity;
    
    for (const auto& item : valuePerWeight) {
        int idx = item.second;
        
        // If we can take the whole item
        if (weights[idx] <= remainingCapacity) {
            totalValue += values[idx];
            remainingCapacity -= weights[idx];
        }
        // Take a fraction of the item
        else {
            double fraction = (double)remainingCapacity / weights[idx];
            totalValue += values[idx] * fraction;
            break;
        }
    }
    
    return totalValue;
}

int main() {
    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int capacity = 50;
    
    // Using the first implementation
    cout << "Maximum value (fractional): " << fractionalKnapsack(weights, values, capacity) << endl;
    
    // Using the alternative implementation
    cout << "Maximum value (alternative): " << fractionalKnapsackAlternative(weights, values, capacity) << endl;
    
    return 0;
}
```

## Sample Problems:

1. **Basic Fractional Knapsack**: [GeeksForGeeks - Fractional Knapsack Problem](https://practice.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1)
   - Standard implementation of the fractional knapsack algorithm.

2. **Water Jug Problem**: Fill a set of jugs with different capacities to maximize the value of water collected.

3. **Job Scheduling**: [LeetCode 1235 - Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/)
   - While this typically uses 0/1 Knapsack or other approaches, variants can be solved using fractional knapsack principles.

4. **Weighted Activity Selection**: Choose activities with weights that maximize total value, allowing partial completion.

5. **Cargo Loading**: Pack a ship with various goods where goods can be partially loaded to maximize value.

## Practical Applications:

1. **Resource Allocation**: Allocate limited resources to different tasks based on their efficiency.

2. **Investment Strategies**: Decide how to allocate investment funds across different assets to maximize returns.

3. **Logistics and Transportation**: Optimize cargo loads when items can be divided.

4. **Manufacturing**: Determine production quantities when materials can be used in varying amounts.
