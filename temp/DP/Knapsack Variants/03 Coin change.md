# Coin Change Problem

The coin change problem is a classic dynamic programming problem with two common variants:

1. **Minimum Coins**: Find the minimum number of coins needed to make a given amount.
2. **Number of Ways**: Count the total number of ways to make a given amount using the available coins.

## Problem Description

**Given**:
- An array of coin denominations `coins[]` (e.g., [1, 2, 5])
- A target amount `amount`

**To Find**:
- Minimum Coins Variant: The minimum number of coins needed to make up the amount
- Number of Ways Variant: The total number of ways to make up the amount using the given coins

## Dynamic Programming Approach

### Variant 1: Minimum Coins

We use a bottom-up DP approach where `dp[i]` represents the minimum number of coins needed to make up amount `i`.

**Recurrence Relation**:
```
dp[i] = min(dp[i], dp[i-coin] + 1) for each coin in coins[]
```

**Base Case**:
- `dp[0] = 0` (No coins needed to make amount 0)
- Initialize all other values to a large number (infinity)

**C++ Implementation**:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int coinChange(vector<int>& coins, int amount) {
    // dp[i] represents the minimum number of coins needed to make amount i
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;  // Base case: no coins needed to make amount 0
    
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            // Only if dp[i-coin] is reachable
            if (dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    
    int result = coinChange(coins, amount);
    if (result != -1) {
        cout << "Minimum coins needed: " << result << endl;
    } else {
        cout << "Amount cannot be made with given coins" << endl;
    }
    
    return 0;
}
```

### Variant 2: Number of Ways

Here, `dp[i]` represents the number of ways to make up amount `i` using the given coins.

**Recurrence Relation**:
```
dp[i] += dp[i-coin] for each coin in coins[]
```

**Base Case**:
- `dp[0] = 1` (There's one way to make amount 0: use no coins)

**C++ Implementation**:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int coinChangeWays(vector<int>& coins, int amount) {
    // dp[i] represents the number of ways to make amount i
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;  // Base case: one way to make amount 0 (use no coins)
    
    // For each coin, update all possible amounts
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }
    
    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    
    cout << "Number of ways to make amount " << amount << ": " 
         << coinChangeWays(coins, amount) << endl;
    
    return 0;
}
```

## Important Notes

1. **Time Complexity**: O(amount * n) where n is the number of coins
2. **Space Complexity**: O(amount)

3. **Order of Loops**:
   - For "minimum coins" variant, the order of loops doesn't matter
   - For "number of ways" variant, the outer loop must be over coins to avoid counting the same combination multiple times

4. **Unbounded Knapsack**: The coin change problem is a variant of the unbounded knapsack problem, where we can use each coin any number of times

## LeetCode Problems

1. [LeetCode 322: Coin Change](https://leetcode.com/problems/coin-change/)
   - Problem: Find the minimum number of coins to make up an amount
   - Difficulty: Medium

2. [LeetCode 518: Coin Change 2](https://leetcode.com/problems/coin-change-2/)
   - Problem: Find the number of ways to make up an amount
   - Difficulty: Medium

3. [LeetCode 983: Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/)
   - A variant where "coins" have different values and can cover different ranges
   - Difficulty: Medium

## Common Pitfalls

1. Not handling the case where an amount cannot be formed (should return -1)
2. Integer overflow when calculating the number of ways for large amounts
3. Confusing the loop order for the "number of ways" variant
4. Forgetting to initialize `dp[0] = 1` for the "number of ways" variant

## Additional Optimization

For the "minimum coins" variant, we can use a queue and BFS to find the solution in some cases more efficiently.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

int coinChangeBFS(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    
    queue<int> q;
    unordered_set<int> visited;
    q.push(0);
    visited.insert(0);
    
    int level = 0;
    
    while (!q.empty()) {
        int size = q.size();
        level++;
        
        for (int i = 0; i < size; i++) {
            int curr = q.front();
            q.pop();
            
            for (int coin : coins) {
                int next = curr + coin;
                
                if (next == amount) return level;
                
                if (next < amount && visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }
    }
    
    return -1;  // Cannot make the amount with given coins
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    
    cout << "Minimum coins needed (BFS): " << coinChangeBFS(coins, amount) << endl;
    
    return 0;
}
```
