# Design Hit Counter

## Pattern: Simulation

### Problem Statement
Design a hit counter which counts the number of hits received in the past 5 minutes (i.e., the past 300 seconds).

Your system should accept a `timestamp` parameter (in seconds granularity), and you may assume that calls are being made to the system in chronological order (i.e., `timestamp` is monotonically increasing). Several hits may arrive roughly at the same time.

Implement the `HitCounter` class:
- `HitCounter()`: Initializes the object of the hit counter system
- `void hit(int timestamp)`: Records a hit that happened at timestamp (in seconds). Several hits may happen at the same timestamp
- `int getHits(int timestamp)`: Returns the number of hits in the past 5 minutes from timestamp (i.e., from timestamp - 300 + 1 to timestamp)

**Constraints:**
- 1 ≤ timestamp ≤ 2 × 10^9
- All calls are being made in chronological order
- At most 300 calls will be made to hit and getHits

### Approach 1: Queue-based Solution

Use a queue to store hit timestamps and remove expired hits.

```python
from collections import deque

class HitCounter:
    
    def __init__(self):
        """Initialize hit counter"""
        self.hits = deque()
        self.window_size = 300
    
    def hit(self, timestamp: int) -> None:
        """Records a hit at given timestamp"""
        self.hits.append(timestamp)
    
    def getHits(self, timestamp: int) -> int:
        """Get hits in last 300 seconds"""
        # Remove hits older than 300 seconds
        cutoff_time = timestamp - self.window_size + 1
        
        while self.hits and self.hits[0] < cutoff_time:
            self.hits.popleft()
        
        return len(self.hits)
```

**Time Complexity:** 
- `hit()`: O(1)
- `getHits()`: O(n) worst case, O(1) amortized
**Space Complexity:** O(n) where n is number of hits in window

### Approach 2: Circular Array (Bucket-based)

Use fixed-size array where each bucket represents one second.

```python
class HitCounterCircular:
    
    def __init__(self):
        """Initialize with circular array of 300 seconds"""
        self.window_size = 300
        self.hits = [0] * self.window_size
        self.timestamps = [0] * self.window_size
    
    def hit(self, timestamp: int) -> None:
        """Record hit at timestamp"""
        index = timestamp % self.window_size
        
        if self.timestamps[index] != timestamp:
            # New timestamp, reset the bucket
            self.timestamps[index] = timestamp
            self.hits[index] = 1
        else:
            # Same timestamp, increment count
            self.hits[index] += 1
    
    def getHits(self, timestamp: int) -> int:
        """Get total hits in last 300 seconds"""
        total_hits = 0
        cutoff_time = timestamp - self.window_size + 1
        
        for i in range(self.window_size):
            if self.timestamps[i] >= cutoff_time:
                total_hits += self.hits[i]
        
        return total_hits
```

**Time Complexity:** 
- `hit()`: O(1)
- `getHits()`: O(300) = O(1)
**Space Complexity:** O(300) = O(1)

### Real-World Applications

1. **API Rate Limiting**: Track requests per time window
2. **Web Analytics**: Real-time visitor counting
3. **System Monitoring**: Request rate tracking
4. **Game Development**: Action frequency limiting
5. **Financial Systems**: Transaction rate monitoring
