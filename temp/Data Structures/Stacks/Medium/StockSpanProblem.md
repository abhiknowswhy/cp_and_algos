# Stock Span Problem

## Problem Description

The stock span problem is a financial problem where we have a series of n daily price quotes for a stock. The span of the stock's price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the stock price on the current day is greater than or equal to its price on the previous days.

For example, if an array of 7 days' prices is given as {100, 80, 60, 70, 60, 75, 85}, then the span values for corresponding 7 days are {1, 1, 1, 2, 1, 4, 6}.

## Approaches to Solve the Problem

### 1. Brute Force Approach

#### Intuition

For each day, scan backwards to find the longest consecutive sequence of days with prices less than or equal to the current day's price.

#### Implementations

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> calculateSpanBruteForce(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n, 1); // Initialize all spans to 1
  
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        // Look backwards while prices are less than or equal to current price
        while (j >= 0 && prices[j] <= prices[i]) {
            j--;
        }
        // Span is the distance from current day to the day with higher price
        span[i] = i - j;
    }
  
    return span;
}

int main() {
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span = calculateSpanBruteForce(prices);
  
    cout << "Stock spans: [";
    for (int i = 0; i < span.size(); i++) {
        cout << span[i];
        if (i < span.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n²), where n is the number of days
- Space Complexity: O(n) for the span array

### 2. Stack-based Approach

#### Intuition

Use a stack to keep track of days with higher prices. When calculating the span for a given day, pop days with lower prices from the stack and calculate the span based on the nearest day with a higher price.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> calculateSpan(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> s; // Stack to store indices of days
  
    // Span of first day is always 1
    span[0] = 1;
    s.push(0);
  
    // Calculate span for remaining days
    for (int i = 1; i < n; i++) {
        // Pop elements from stack while stack is not empty and prices of
        // stack top are less than or equal to current price
        while (!s.empty() && prices[s.top()] <= prices[i]) {
            s.pop();
        }
      
        // If stack becomes empty, all previous prices are less than or equal
        // to current price, so span is i + 1
        // Otherwise, span is the difference between current day and the day
        // at the top of stack (nearest day with higher price)
        span[i] = s.empty() ? i + 1 : i - s.top();
      
        // Push this day's index onto the stack
        s.push(i);
    }
  
    return span;
}

int main() {
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span = calculateSpan(prices);
  
    cout << "Stock spans: [";
    for (int i = 0; i < span.size(); i++) {
        cout << span[i];
        if (i < span.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  
    return 0;
}
```

#### Detailed Stack-based Approach

Let's trace through the algorithm for the input `{100, 80, 60, 70, 60, 75, 85}`:

1. Initialize span array and stack: span = [0, 0, 0, 0, 0, 0, 0], stack = []
2. i=0, price=100:
   - span[0] = 1 (first day always has span 1)
   - Push 0 to stack. Stack: [0]
3. i=1, price=80:
   - 80 < 100, so stack top remains
   - span[1] = 1 - 0 = 1
   - Push 1 to stack. Stack: [0, 1]
4. i=2, price=60:
   - 60 < 80, so stack top remains
   - span[2] = 2 - 1 = 1
   - Push 2 to stack. Stack: [0, 1, 2]
5. i=3, price=70:
   - 70 > 60, so pop 2 from stack
   - 70 < 80, so stack top remains
   - span[3] = 3 - 1 = 2
   - Push 3 to stack. Stack: [0, 1, 3]
6. i=4, price=60:
   - 60 < 70, so stack top remains
   - span[4] = 4 - 3 = 1
   - Push 4 to stack. Stack: [0, 1, 3, 4]
7. i=5, price=75:
   - 75 > 60, so pop 4 from stack
   - 75 > 70, so pop 3 from stack
   - 75 < 80, so stack top remains
   - span[5] = 5 - 1 = 4
   - Push 5 to stack. Stack: [0, 1, 5]
8. i=6, price=85:
   - 85 > 75, so pop 5 from stack
   - 85 > 80, so pop 1 from stack
   - 85 < 100, so stack top remains
   - span[6] = 6 - 0 = 6
   - Push 6 to stack. Stack: [0, 6]
9. Final span array: [1, 1, 1, 2, 1, 4, 6]

#### Time and Space Complexity

- Time Complexity: O(n), where n is the number of days
- Space Complexity: O(n) for the stack and span array

### 3. Online Stock Span (Streaming Approach)

#### Intuition

In a real-world scenario, stock prices arrive as a stream. We need to compute spans on-the-fly without having the entire array in advance.

#### Implementation

```cpp
#include <iostream>
#include <stack>
using namespace std;

class StockSpanner {
private:
    stack<pair<int, int>> s; // Stack of (price, span) pairs
  
public:
    StockSpanner() {
    }
  
    int next(int price) {
        int span = 1; // Span is at least 1 (the day itself)
      
        // Pop elements from stack while stack is not empty and prices of
        // stack top are less than or equal to current price
        while (!s.empty() && s.top().first <= price) {
            // Add the span of the popped element to the current span
            span += s.top().second;
            s.pop();
        }
      
        // Push the current price and its span to the stack
        s.push({price, span});
      
        return span;
    }
};

int main() {
    StockSpanner spanner;
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
  
    cout << "Stock spans: [";
    for (int i = 0; i < prices.size(); i++) {
        int span = spanner.next(prices[i]);
        cout << span;
        if (i < prices.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity:
  - O(1) amortized per call to `next()`
  - O(n) total for n calls
- Space Complexity: O(n) for the stack

### 4. Dynamic Programming Approach

#### Intuition

We can use dynamic programming to calculate the span by using previously calculated spans, potentially reducing the number of comparisons.

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> calculateSpanDP(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n, 1); // Initialize all spans to 1
  
    for (int i = 1; i < n; i++) {
        int j = i - 1;
      
        // Use previously calculated spans to skip days
        while (j >= 0 && prices[j] <= prices[i]) {
            // Jump directly to the day before the span of j
            j = j - span[j];
        }
      
        // Span is the distance from current day to j
        span[i] = i - j;
    }
  
    return span;
}

int main() {
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span = calculateSpanDP(prices);
  
    cout << "Stock spans: [";
    for (int i = 0; i < span.size(); i++) {
        cout << span[i];
        if (i < span.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n) in best case, O(n²) in worst case
- Space Complexity: O(n) for the span array

### 5. Stack with Pairs Approach

#### Intuition

We can use a stack to store pairs of (price, index) to simplify the calculations and make the code more readable.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> calculateSpanPair(vector<int>& prices) {
    int n = prices.size();
    vector<int> span(n);
    stack<pair<int, int>> s; // Stack to store (price, index) pairs
  
    for (int i = 0; i < n; i++) {
        // Pop elements from stack while stack is not empty and prices of
        // stack top are less than or equal to current price
        while (!s.empty() && s.top().first <= prices[i]) {
            s.pop();
        }
      
        // If stack becomes empty, span is i + 1, otherwise it's i - j
        span[i] = s.empty() ? i + 1 : i - s.top().second;
      
        // Push this day's price and index onto the stack
        s.push({prices[i], i});
    }
  
    return span;
}

int main() {
    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> span = calculateSpanPair(prices);
  
    cout << "Stock spans: [";
    for (int i = 0; i < span.size(); i++) {
        cout << span[i];
        if (i < span.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
  
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 901: Online Stock Span](https://leetcode.com/problems/online-stock-span/)
2. [LeetCode 739: Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
3. [LeetCode 496: Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
4. [LeetCode 503: Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)

## Applications

1. **Financial Analysis**: Analyzing stock price trends and patterns
2. **Technical Indicators**: Building technical indicators like the "Price Rate of Change"
3. **Market Volatility**: Measuring periods of stability or volatility in markets
4. **Trading Strategies**: Developing trading strategies based on price momentum

## Extensions and Variations

### 1. Maximum Span Between Similar Prices

```cpp
vector<int> maxSpanBetweenSimilarPrices(vector<int>& prices) {
    int n = prices.size();
    vector<int> result(n, 0);
    unordered_map<int, int> lastSeen;
  
    for (int i = 0; i < n; i++) {
        if (lastSeen.find(prices[i]) != lastSeen.end()) {
            result[i] = i - lastSeen[prices[i]];
        }
        lastSeen[prices[i]] = i;
    }
  
    return result;
}
```

### 2. Weighted Stock Span

```cpp
vector<int> weightedStockSpan(vector<int>& prices, vector<int>& weights) {
    int n = prices.size();
    vector<int> span(n);
    stack<int> s;
  
    for (int i = 0; i < n; i++) {
        while (!s.empty() && prices[s.top()] <= prices[i]) {
            s.pop();
        }
      
        int j = s.empty() ? -1 : s.top();
        span[i] = 0;
      
        // Calculate weighted span
        for (int k = j + 1; k <= i; k++) {
            span[i] += weights[k];
        }
      
        s.push(i);
    }
  
    return span;
}
```

## Summary

| Approach            | Time Complexity | Space Complexity | Notes                                      |
| ------------------- | --------------- | ---------------- | ------------------------------------------ |
| Brute Force         | O(n²)          | O(n)             | Simple but inefficient for large inputs    |
| Stack-based         | O(n)            | O(n)             | Efficient solution using a monotonic stack |
| Online Stock Span   | O(n)            | O(n)             | Stream processing approach                 |
| Dynamic Programming | O(n) to O(n²)  | O(n)             | Uses previous spans to optimize            |
| Stack with Pairs    | O(n)            | O(n)             | More readable with price-index pairs       |
