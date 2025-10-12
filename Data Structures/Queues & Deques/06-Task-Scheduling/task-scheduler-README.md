# Task Scheduler

## Problem Description
Given a characters array `tasks`, representing the tasks a CPU needs to do, where each letter represents a different task. Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer `n` that represents the cooldown period between two **same** tasks (the same letter in the array), that is, there must be at least `n` units of time between any two same tasks.

Return the least number of units of time that the CPU will take to finish all the given tasks.

**LeetCode Link:** [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/)

## Approach
This problem involves **task scheduling with cooldown constraints**. We can solve it using:

1. **Greedy with Priority Queue/Heap:** Schedule most frequent tasks first
2. **Mathematical Formula:** Calculate based on most frequent task
3. **Queue-based Simulation:** Simulate the scheduling process with queues

**Key Insight:** The total time is determined by either the natural task completion time or the cooldown constraints of the most frequent task.

## Algorithm Steps
1. Count frequency of each task
2. Use a max heap to always schedule the most frequent available task
3. Use a queue to track tasks in cooldown period
4. Simulate time units until all tasks are completed
5. Return total time taken

## Implementation

### C++ - Priority Queue + Queue Approach
```cpp
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if (n == 0) return tasks.size();
        
        // Count frequency of each task
        unordered_map<char, int> freq;
        for (char task : tasks) {
            freq[task]++;
        }
        
        // Max heap to store frequencies
        priority_queue<int> maxHeap;
        for (auto& pair : freq) {
            maxHeap.push(pair.second);
        }
        
        // Queue to store tasks in cooldown: {frequency, available_time}
        queue<pair<int, int>> cooldown;
        int time = 0;
        
        while (!maxHeap.empty() || !cooldown.empty()) {
            time++;
            
            // Check if any task's cooldown is over
            if (!cooldown.empty() && cooldown.front().second == time) {
                maxHeap.push(cooldown.front().first);
                cooldown.pop();
            }
            
            // Schedule a task if available
            if (!maxHeap.empty()) {
                int taskFreq = maxHeap.top();
                maxHeap.pop();
                
                // If task has more instances, put it in cooldown
                if (taskFreq > 1) {
                    cooldown.push({taskFreq - 1, time + n + 1});
                }
            }
            // If no task available, CPU is idle (time still increments)
        }
        
        return time;
    }
};
```

### C++ - Mathematical Formula Approach
```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if (n == 0) return tasks.size();
        
        // Count frequencies
        vector<int> freq(26, 0);
        int maxFreq = 0;
        
        for (char task : tasks) {
            freq[task - 'A']++;
            maxFreq = max(maxFreq, freq[task - 'A']);
        }
        
        // Count how many tasks have maximum frequency
        int maxCount = 0;
        for (int f : freq) {
            if (f == maxFreq) {
                maxCount++;
            }
        }
        
        // Calculate minimum time needed
        // Part 1: Time slots needed for most frequent task
        int partCount = maxFreq - 1;
        int partLength = n - (maxCount - 1);
        int emptySlots = partCount * partLength;
        int availableTasks = tasks.size() - maxFreq * maxCount;
        int idles = max(0, emptySlots - availableTasks);
        
        return tasks.size() + idles;
    }
};
```

### C++ - Simulation with Arrays
```cpp
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26, 0);
        for (char task : tasks) {
            freq[task - 'A']++;
        }
        
        int time = 0;
        int completed = 0;
        int totalTasks = tasks.size();
        
        while (completed < totalTasks) {
            // Find the most frequent available task
            int maxFreq = 0;
            int maxIndex = -1;
            
            for (int i = 0; i < 26; i++) {
                if (freq[i] > maxFreq) {
                    maxFreq = freq[i];
                    maxIndex = i;
                }
            }
            
            if (maxIndex != -1) {
                // Schedule this task
                freq[maxIndex]--;
                completed++;
                
                // Simulate cooldown
                if (completed < totalTasks) {
                    for (int coolTime = 0; coolTime < n && completed < totalTasks; coolTime++) {
                        time++;
                        
                        // Find next best task (excluding the one in cooldown)
                        int nextMaxFreq = 0;
                        int nextMaxIndex = -1;
                        
                        for (int i = 0; i < 26; i++) {
                            if (i != maxIndex && freq[i] > nextMaxFreq) {
                                nextMaxFreq = freq[i];
                                nextMaxIndex = i;
                            }
                        }
                        
                        if (nextMaxIndex != -1) {
                            freq[nextMaxIndex]--;
                            completed++;
                        }
                        // Otherwise, CPU is idle
                    }
                }
            }
            
            time++;
        }
        
        return time;
    }
};
```

### Time Complexity
- **Priority Queue:** O(n log k) where k is number of unique tasks
- **Mathematical:** O(n) for counting + O(k) for finding max = O(n)
- **Simulation:** O(n × k) in worst case

### Space Complexity
- **Priority Queue:** O(k) for heap and queue
- **Mathematical:** O(1) with fixed-size array
- **Simulation:** O(1) with fixed-size array

## Examples

### Example 1
```
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B
The optimal scheduling ensures at least 2 units between same tasks.
```

### Example 2
```
Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: No cooldown needed, so tasks can be done consecutively.
```

### Example 3
```
Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: One possible solution is A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
```

## Notes
- **Cooldown constraint:** Same tasks must be separated by at least `n` units
- **Greedy strategy:** Always schedule the most frequent available task
- **Mathematical insight:** Total time is max(tasks.length, time_needed_for_most_frequent_task)
- **Edge cases:** n = 0, all tasks same, many different tasks

## Related Problems
- [LeetCode 358: Rearrange String k Distance Apart](https://leetcode.com/problems/rearrange-string-k-distance-apart/)
- [LeetCode 767: Reorganize String](https://leetcode.com/problems/reorganize-string/)
- [LeetCode 1405: Longest Happy String](https://leetcode.com/problems/longest-happy-string/)

## Pattern: 06-Task-Scheduling
This problem demonstrates **Task Scheduling** pattern where:
- **Priority-based scheduling:** Use heap to always pick highest priority task
- **Cooldown management:** Use queue to track tasks in cooldown period
- **Time simulation:** Advance time step by step while maintaining constraints
- **Greedy optimization:** Make locally optimal choices for global optimum
