#include <iostream>
#include <vector>

using namespace std;

// Function to solve 0/1 Knapsack Problem using 1D DP array
int knapsack(int W, vector<int>& weights, vector<int>& values, int n) {
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= weights[i]; w--) {
            dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
        }
    }

    return dp[W];
}

int main() {
    int n = 4; // Number of items
    int W = 8; // Knapsack capacity
    vector<int> values = {10, 40, 30, 50}; // Values of items
    vector<int> weights = {5, 4, 6, 3}; // Weights of items

    cout << "Maximum value in knapsack = " << knapsack(W, weights, values, n) << endl;
    
    return 0;
}
