# Exclusive Time of Functions

## Problem Description

On a single-threaded CPU, we execute a program containing `n` functions. Each function has a unique ID between `0` and `n-1`.

We receive a log of function calls and returns in the form of a list of strings. Each log string has the format `"{function_id}:{"start" | "end"}:{timestamp}"` indicating that the function with ID `function_id` either started or ended at the timestamp.

Each function has an "exclusive time", which is the sum of execution time spent in this function only, not including time spent in any called functions. We need to return the exclusive time of each function sorted by their function IDs.

## Approaches to Solve the Problem

### 1. Stack-based Approach

#### Intuition

- Use a stack to keep track of the active function calls
- When a function starts, push it onto the stack
- When a function ends, pop it from the stack and calculate its exclusive time
- Handle nested function calls by accounting for the time spent in called functions

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> result(n, 0); // Initialize result with 0 for all n functions
    stack<pair<int, int>> st; // Stack to store (function_id, start_time)
    
    for (const string& log : logs) {
        // Parse the log entry
        size_t firstColon = log.find(":");
        size_t secondColon = log.find(":", firstColon + 1);
        
        int functionId = stoi(log.substr(0, firstColon));
        string type = log.substr(firstColon + 1, secondColon - firstColon - 1);
        int timestamp = stoi(log.substr(secondColon + 1));
        
        if (type == "start") {
            // If there was an active function, adjust its exclusive time
            if (!st.empty()) {
                result[st.top().first] += timestamp - st.top().second;
                st.top().second = timestamp; // Update the start time
            }
            // Push the new function onto stack
            st.push({functionId, timestamp});
        } else { // type == "end"
            // Calculate exclusive time for the current function
            int startTime = st.top().second;
            st.pop();
            result[functionId] += timestamp - startTime + 1; // +1 because end time is inclusive
            
            // Update the start time for the parent function (if any)
            if (!st.empty()) {
                st.top().second = timestamp + 1; // Parent function resumes at next timestamp
            }
        }
    }
    
    return result;
}
```

#### Explanation

- We iterate through each log entry and parse it to extract the function ID, type (start or end), and timestamp
- For a "start" log:
  - If there's an active function, we calculate its exclusive time up to this point and update its start time
  - We push the new function onto the stack
- For an "end" log:
  - We calculate the exclusive time for the current function and add it to our result
  - We pop the function from the stack
  - If there's a parent function, we update its start time to resume from the next timestamp

### 2. Optimized Stack Approach

#### Intuition

- Similar to the first approach but with some optimizations
- Keep track of the previous timestamp to simplify calculations
- Handle the exclusive time calculation more directly

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> result(n, 0);
    stack<int> callStack; // Stack to store function IDs
    int prevTimestamp = 0;
    
    for (const string& log : logs) {
        // Parse the log entry
        int pos1 = log.find(":");
        int pos2 = log.find(":", pos1 + 1);
        
        int id = stoi(log.substr(0, pos1));
        string status = log.substr(pos1 + 1, pos2 - pos1 - 1);
        int timestamp = stoi(log.substr(pos2 + 1));
        
        if (!callStack.empty()) {
            // Add time to the current active function
            result[callStack.top()] += timestamp - prevTimestamp;
        }
        
        prevTimestamp = timestamp;
        
        if (status == "start") {
            callStack.push(id);
        } else { // status == "end"
            result[callStack.top()]++; // Add one more unit for the inclusive end
            callStack.pop();
            prevTimestamp++; // Move to next timestamp since end is inclusive
        }
    }
    
    return result;
}
```

### 3. Using a Map for Time Tracking

#### Intuition

- Use a map to keep track of the start times for each function
- Calculate exclusive time by considering the time spent in child functions

#### Implementation

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> result(n, 0);
    stack<int> functionStack; // Stack to store function IDs
    unordered_map<int, int> startTimes; // Map function ID to its start time
    unordered_map<int, int> childTime; // Map function ID to total time spent in child functions
    
    for (const string& log : logs) {
        // Parse the log entry
        int pos1 = log.find(':');
        int pos2 = log.find(':', pos1 + 1);
        
        int id = stoi(log.substr(0, pos1));
        string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
        int timestamp = stoi(log.substr(pos2 + 1));
        
        if (type == "start") {
            functionStack.push(id);
            startTimes[id] = timestamp;
            if (childTime.find(id) == childTime.end()) {
                childTime[id] = 0;
            }
        } else { // type == "end"
            int duration = timestamp - startTimes[id] + 1; // Total duration including child functions
            result[id] += duration - childTime[id]; // Exclusive time
            
            functionStack.pop();
            if (!functionStack.empty()) {
                // Add this function's total time to parent's child time
                childTime[functionStack.top()] += duration;
            }
        }
    }
    
    return result;
}
```

## Complexity Analysis

### Stack-based Approach
- **Time Complexity**: O(n), where n is the number of logs. We process each log entry once.
- **Space Complexity**: O(m), where m is the maximum depth of the function call stack.

### Optimized Stack Approach
- **Time Complexity**: O(n), where n is the number of logs.
- **Space Complexity**: O(m), where m is the maximum depth of the function call stack.

### Map-based Approach
- **Time Complexity**: O(n), where n is the number of logs.
- **Space Complexity**: O(n), where n is the number of functions. In the worst case, we might need to store information for all functions.

## Step-by-Step Execution

Let's trace through the original stack-based approach with an example:

Input:
```
n = 2
logs = ["0:start:0", "1:start:2", "1:end:5", "0:end:6"]
```

1. Parse "0:start:0":
   - Function 0 starts at time 0
   - Push (0, 0) onto stack
   - Stack: [(0, 0)]

2. Parse "1:start:2":
   - Function 0 has been running for 2 units (2 - 0)
   - result[0] += 2, result = [2, 0]
   - Update stack top to (0, 2)
   - Push (1, 2) onto stack
   - Stack: [(0, 2), (1, 2)]

3. Parse "1:end:5":
   - Function 1 runs for 3 units (5 - 2)
   - Pop (1, 2) from stack
   - result[1] += 3 + 1, result = [2, 4] (+1 because end is inclusive)
   - Update parent function start time to 6 (5 + 1)
   - Stack: [(0, 6)]

4. Parse "0:end:6":
   - Function 0 runs for 0 units (6 - 6)
   - Pop (0, 6) from stack
   - result[0] += 0 + 1, result = [3, 4] (+1 because end is inclusive)
   - Stack: []

Final result: `[3, 4]`

Explanation:
- Function 0 has an exclusive time of 3 (2 units before function 1 starts + 1 unit at the end)
- Function 1 has an exclusive time of 4 (from time 2 to time 5, inclusive)

## Related LeetCode Problems

- [LeetCode 636: Exclusive Time of Functions](https://leetcode.com/problems/exclusive-time-of-functions/)
- [LeetCode 394: Decode String](https://leetcode.com/problems/decode-string/) - Uses stack to handle nested structures
- [LeetCode 726: Number of Atoms](https://leetcode.com/problems/number-of-atoms/) - Stack-based parsing
- [LeetCode 20: Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) - Basic stack operations

## Applications

- **Profiling Tools**: Measuring function execution times in program performance profiling
- **Call Stack Analysis**: Debugging tools that analyze program execution flow
- **Log Processing Systems**: Processing timestamped logs to extract execution metrics
- **Process Scheduling**: Managing time slices in operating system process scheduling
- **Project Management**: Tracking time spent on various tasks and subtasks

## Summary

| Approach | Time Complexity | Space Complexity | Pros | Cons |
|----------|-----------------|------------------|------|------|
| Stack-based | O(n) | O(m) | Intuitive implementation, directly models the call stack | Slightly more complex timestamp handling |
| Optimized Stack | O(n) | O(m) | Simplified timestamp calculation, more efficient | Same core algorithm as the first approach |
| Map-based | O(n) | O(n) | Clear separation of child time tracking | Higher space usage, potentially less intuitive |

The stack-based approach is generally preferred for this problem because:
1. It naturally models the function call stack behavior
2. It provides an efficient way to track the active function at any point
3. It handles nested function calls appropriately

When implementing this solution, pay special attention to:
- The inclusive/exclusive nature of timestamps
- Properly updating parent function times when a child function ends
- Handling edge cases like empty logs or overlapping function calls (which should not occur in the problem)
