# Design Hit Counter

## Problem Description
Design a hit counter which counts the number of hits received in the past `5 minutes` (i.e., the past `300 seconds`).

Your system should accept a `timestamp` parameter (in seconds granularity), and you may assume that calls are being made to the system in chronological order (i.e., `timestamp` is monotonically increasing). Several hits may arrive roughly at the same time.

Implement the `HitCounter` class:
- `HitCounter()` Initializes the object of the hit counter system.
- `void hit(int timestamp)` Records a hit that happened at `timestamp` (in seconds). Several hits may happen at the same `timestamp`.
- `int getHits(int timestamp)` Returns the number of hits in the past 5 minutes from `timestamp` (i.e., from `timestamp - 300 + 1` to `timestamp`).

**LeetCode Link:** [362. Design Hit Counter](https://leetcode.com/problems/design-hit-counter/) (Premium)

## Approach
This problem can be solved using a **Queue** to store timestamps efficiently. We maintain a sliding window of 5 minutes and remove outdated hits.

**Key Insight:** Use a queue to maintain hits in chronological order and remove hits older than 5 minutes when queried.

## Algorithm Steps
1. Use a queue to store hit timestamps
2. For `hit(timestamp)`: Add timestamp to queue
3. For `getHits(timestamp)`: Remove all timestamps older than 5 minutes, then return queue size
4. Optimize by storing counts for same timestamps

## Implementation

### C++ - Queue-based Simple Approach
```cpp
#include <queue>
using namespace std;

class HitCounter {
private:
    queue<int> hits;
    
public:
    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        hits.push(timestamp);
    }
    
    int getHits(int timestamp) {
        // Remove hits older than 5 minutes (300 seconds)
        while (!hits.empty() && hits.front() <= timestamp - 300) {
            hits.pop();
        }
        return hits.size();
    }
};
```

### C++ - Queue with Count Optimization
```cpp
#include <queue>
using namespace std;

class HitCounter {
private:
    queue<pair<int, int>> hits; // {timestamp, count}
    
public:
    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        if (!hits.empty() && hits.back().first == timestamp) {
            hits.back().second++;
        } else {
            hits.push({timestamp, 1});
        }
    }
    
    int getHits(int timestamp) {
        int totalHits = 0;
        
        // Remove hits older than 5 minutes and count valid hits
        while (!hits.empty() && hits.front().first <= timestamp - 300) {
            hits.pop();
        }
        
        // Count all remaining hits
        queue<pair<int, int>> temp = hits;
        while (!temp.empty()) {
            totalHits += temp.front().second;
            temp.pop();
        }
        
        return totalHits;
    }
};
```

### C++ - Circular Array Approach (Memory Efficient)
```cpp
class HitCounter {
private:
    vector<int> times;
    vector<int> hits;
    
public:
    HitCounter() : times(300), hits(300) {
        
    }
    
    void hit(int timestamp) {
        int index = timestamp % 300;
        if (times[index] != timestamp) {
            times[index] = timestamp;
            hits[index] = 1;
        } else {
            hits[index]++;
        }
    }
    
    int getHits(int timestamp) {
        int totalHits = 0;
        for (int i = 0; i < 300; i++) {
            if (timestamp - times[i] < 300) {
                totalHits += hits[i];
            }
        }
        return totalHits;
    }
};
```

### C++ - Deque Approach
```cpp
#include <deque>
using namespace std;

class HitCounter {
private:
    deque<int> hitTimes;
    
public:
    HitCounter() {
        
    }
    
    void hit(int timestamp) {
        hitTimes.push_back(timestamp);
    }
    
    int getHits(int timestamp) {
        // Remove hits older than 5 minutes from front
        while (!hitTimes.empty() && hitTimes.front() <= timestamp - 300) {
            hitTimes.pop_front();
        }
        return hitTimes.size();
    }
};
```

### Time Complexity
- **Queue approach:** hit() - O(1), getHits() - O(n) worst case
- **Circular array:** hit() - O(1), getHits() - O(300) = O(1)
- **Deque approach:** hit() - O(1), getHits() - O(n) worst case

### Space Complexity
- **Queue/Deque:** O(n) where n is number of hits in 5 minutes
- **Circular array:** O(300) = O(1) - Fixed space

## Examples

### Example 1
```
Input: ["HitCounter", "hit", "hit", "hit", "getHits", "hit", "getHits", "getHits"]
       [[], [1], [2], [3], [4], [300], [300], [301]]
Output: [null, null, null, null, 3, null, 4, 3]

Explanation:
HitCounter hitCounter = new HitCounter();
hitCounter.hit(1);       // hit at timestamp 1
hitCounter.hit(2);       // hit at timestamp 2
hitCounter.hit(3);       // hit at timestamp 3
hitCounter.getHits(4);   // get hits at timestamp 4, return 3
hitCounter.hit(300);     // hit at timestamp 300
hitCounter.getHits(300); // get hits at timestamp 300, return 4
hitCounter.getHits(301); // get hits at timestamp 301, return 3
```

## Notes
- **5-minute window:** Only count hits from (timestamp - 300 + 1) to timestamp
- **Chronological order:** Timestamps are monotonically increasing
- **Multiple hits:** Same timestamp can have multiple hits
- **Space optimization:** Circular array provides O(1) space complexity

## Related Problems
- [LeetCode 359: Logger Rate Limiter](https://leetcode.com/problems/logger-rate-limiter/)
- [LeetCode 981: Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)
- [LeetCode 933: Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)

## Pattern: 09-Queue-with-Special-Properties
This problem demonstrates **Queue with Special Properties** where:
- **Sliding window maintenance:** Queue maintains a 5-minute sliding window
- **FIFO order:** Older hits are removed first when they expire
- **Efficient expiration:** Queue front contains oldest hits for easy removal
- **Space optimization:** Circular array approach provides constant space complexity
