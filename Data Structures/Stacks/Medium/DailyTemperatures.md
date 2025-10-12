# Daily Temperatures

## Problem Description

Given an array of integers representing daily temperatures, your task is to return an array where each element indicates the number of days you would have to wait until a warmer temperature. If there is no future day with a warmer temperature, put 0 in that position.

For example, given the array of temperatures `[73, 74, 75, 71, 69, 72, 76, 73]`, the output should be `[1, 1, 4, 2, 1, 1, 0, 0]`.

## Approaches to Solve the Problem

### 1. Brute Force Approach

#### Intuition

For each day, scan forward to find the first day with a higher temperature and calculate the number of days between them.

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> dailyTemperaturesBruteForce(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temperatures[j] > temperatures[i]) {
                result[i] = j - i; // Number of days to wait
                break;
            }
        }
    }
    
    return result;
}

int main() {
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result = dailyTemperaturesBruteForce(temps);
    
    cout << "Days to wait until warmer: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n²), where n is the number of days
- Space Complexity: O(n) for the result array

### 2. Stack-based Approach

#### Intuition

Use a stack to keep track of days for which we haven't found a warmer day yet. When we find a warmer day, update all the days in the stack that are colder than the current day.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> s; // Stack to store indices
    
    for (int i = 0; i < n; i++) {
        // While stack is not empty and current temperature is higher
        // than the temperature at the stack's top index
        while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
            int prevDay = s.top();
            s.pop();
            
            // Number of days to wait = current day - previous day
            result[prevDay] = i - prevDay;
        }
        
        // Push current day's index
        s.push(i);
    }
    
    return result;
}

int main() {
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result = dailyTemperatures(temps);
    
    cout << "Days to wait until warmer: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
```

#### Detailed Stack-based Approach

Let's trace through the algorithm for the input `[73, 74, 75, 71, 69, 72, 76, 73]`:

1. Initialize empty stack and result array `[0, 0, 0, 0, 0, 0, 0, 0]`
2. i=0, temp=73: Push 0 to stack. Stack: [0]
3. i=1, temp=74:
   - 74 > 73, so pop 0 from stack
   - Calculate result[0] = 1 - 0 = 1
   - Push 1 to stack. Stack: [1]
4. i=2, temp=75:
   - 75 > 74, so pop 1 from stack
   - Calculate result[1] = 2 - 1 = 1
   - Push 2 to stack. Stack: [2]
5. i=3, temp=71:
   - 71 < 75, no action
   - Push 3 to stack. Stack: [2, 3]
6. i=4, temp=69:
   - 69 < 71, no action
   - Push 4 to stack. Stack: [2, 3, 4]
7. i=5, temp=72:
   - 72 > 69, so pop 4 from stack
   - Calculate result[4] = 5 - 4 = 1
   - 72 > 71, so pop 3 from stack
   - Calculate result[3] = 5 - 3 = 2
   - 72 < 75, no action
   - Push 5 to stack. Stack: [2, 5]
8. i=6, temp=76:
   - 76 > 72, so pop 5 from stack
   - Calculate result[5] = 6 - 5 = 1
   - 76 > 75, so pop 2 from stack
   - Calculate result[2] = 6 - 2 = 4
   - Push 6 to stack. Stack: [6]
9. i=7, temp=73:
   - 73 < 76, no action
   - Push 7 to stack. Stack: [6, 7]
10. Final result: [1, 1, 4, 2, 1, 1, 0, 0]

#### Time and Space Complexity

- Time Complexity: O(n), where n is the number of days
- Space Complexity: O(n) for the stack and result array

### 3. Optimized Approach (Next Greater Element)

#### Intuition

This problem is essentially asking for the "next greater element" for each temperature, but with the additional requirement to calculate the distance. We can solve it in reverse order to avoid using a stack.

#### Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> dailyTemperaturesOptimized(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    
    // Start from the right
    for (int i = n - 2; i >= 0; i--) {
        int j = i + 1;
        
        // While we haven't found a warmer day
        while (j < n && temperatures[j] <= temperatures[i]) {
            // If the next day has a warmer temperature in the future
            // skip directly to that day to avoid redundant checks
            if (result[j] > 0) {
                j += result[j];
            } else {
                // If no warmer day exists in the future, break
                j = n;
            }
        }
        
        // If we found a warmer day, calculate the distance
        if (j < n) {
            result[i] = j - i;
        }
    }
    
    return result;
}

int main() {
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result = dailyTemperaturesOptimized(temps);
    
    cout << "Days to wait until warmer: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
```

#### Time and Space Complexity

- Time Complexity: O(n), where n is the number of days
- Space Complexity: O(n) for the result array

### 4. Stack with Pair Approach

#### Intuition

Instead of just storing indices in the stack, we can store pairs of (temperature, index) to make the code more readable.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperaturesPair(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<pair<int, int>> s; // Stack of (temperature, index) pairs
    
    for (int i = 0; i < n; i++) {
        // While stack is not empty and current temperature is higher
        while (!s.empty() && temperatures[i] > s.top().first) {
            int prevTemp = s.top().first;
            int prevDay = s.top().second;
            s.pop();
            
            result[prevDay] = i - prevDay;
        }
        
        s.push({temperatures[i], i});
    }
    
    return result;
}

int main() {
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result = dailyTemperaturesPair(temps);
    
    cout << "Days to wait until warmer: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
```

### 5. Integer Stack with Monotonic Property

#### Intuition

We can use a monotonically decreasing stack for indices and directly use the temperature array for lookups, which is the most common implementation due to its simplicity and efficiency.

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> dailyTemperaturesMonotonic(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n);
    stack<int> stack;
    
    for (int i = 0; i < n; i++) {
        // Maintain monotonically decreasing stack
        while (!stack.empty() && temperatures[i] > temperatures[stack.top()]) {
            int prevIdx = stack.top();
            stack.pop();
            result[prevIdx] = i - prevIdx;
        }
        stack.push(i);
    }
    
    // All remaining indices in the stack have no warmer future day
    // result[i] defaults to 0 so no need to set them explicitly
    
    return result;
}

int main() {
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result = dailyTemperaturesMonotonic(temps);
    
    cout << "Days to wait until warmer: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    return 0;
}
```

## Related LeetCode Problems

1. [LeetCode 739: Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
2. [LeetCode 496: Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
3. [LeetCode 503: Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)
4. [LeetCode 901: Online Stock Span](https://leetcode.com/problems/online-stock-span/)
5. [LeetCode 1019: Next Greater Node In Linked List](https://leetcode.com/problems/next-greater-node-in-linked-list/)

## Applications

1. **Weather Analysis**: Finding waiting periods for temperature changes
2. **Stock Market Analysis**: Finding the next day with higher stock price
3. **Resource Monitoring**: Detecting threshold crossings in time series data
4. **Event Processing**: Finding the next occurrence of a specific event type

## Extensions and Variations

### 1. Find Days Until Colder Temperature

```cpp
vector<int> daysUntilColder(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> s;
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && temperatures[i] < temperatures[s.top()]) {
            int prevDay = s.top();
            s.pop();
            result[prevDay] = i - prevDay;
        }
        s.push(i);
    }
    
    return result;
}
```

### 2. Find Days Until Temperature Change of K Degrees

```cpp
vector<int> daysUntilTemperatureChangeK(vector<int>& temperatures, int k) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> s;
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && abs(temperatures[i] - temperatures[s.top()]) >= k) {
            int prevDay = s.top();
            s.pop();
            result[prevDay] = i - prevDay;
        }
        s.push(i);
    }
    
    return result;
}
```

## Summary

| Approach | Time Complexity | Space Complexity | Notes |
| --- | --- | --- | --- |
| Brute Force | O(n²) | O(n) | Simple but inefficient for large inputs |
| Stack-based | O(n) | O(n) | Efficient solution using a monotonic stack |
| Optimized (Next Greater) | O(n) | O(n) | Reverse iteration to avoid redundant checks |
| Stack with Pairs | O(n) | O(n) | More readable code with pairs |
| Monotonic Stack | O(n) | O(n) | Clean implementation with minimal space |
