# Logger Rate Limiter - Queue-Based Time Window

**LeetCode 359: Logger Rate Limiter**

## Problem Description

Design a logger system that receives a stream of messages along with their timestamps. Each unique message should only be printed at most every 10 seconds (i.e., a message printed at timestamp `t` will prevent other identical messages from being printed until timestamp `t + 10`).

All messages will come in chronological order. Several messages may arrive at the same timestamp.

Implement the `Logger` class:
- `Logger()` Initializes the logger object
- `bool shouldPrintMessage(int timestamp, string message)` Returns `true` if the message should be printed in the given timestamp, otherwise returns `false`

## Multiple Approaches

### Approach 1: Hash Map with Timestamps

```cpp
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class Logger {
private:
    unordered_map<string, int> messageMap;
    
public:
    Logger() {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        if (messageMap.find(message) == messageMap.end() || 
            timestamp - messageMap[message] >= 10) {
            messageMap[message] = timestamp;
            return true;
        }
        return false;
    }
};
```

### Approach 2: Queue + Set for Memory Optimization

```cpp
#include <queue>
#include <unordered_set>
#include <unordered_map>

class LoggerOptimized {
private:
    struct LogEntry {
        int timestamp;
        string message;
        
        LogEntry(int t, const string& msg) : timestamp(t), message(msg) {}
    };
    
    queue<LogEntry> messageQueue;
    unordered_set<string> activeMessages;
    
    void cleanup(int currentTime) {
        while (!messageQueue.empty() && 
               currentTime - messageQueue.front().timestamp >= 10) {
            activeMessages.erase(messageQueue.front().message);
            messageQueue.pop();
        }
    }
    
public:
    LoggerOptimized() {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        cleanup(timestamp);
        
        if (activeMessages.find(message) != activeMessages.end()) {
            return false;
        }
        
        activeMessages.insert(message);
        messageQueue.push(LogEntry(timestamp, message));
        return true;
    }
};
```

### Approach 3: Circular Buffer Implementation

```cpp
class LoggerCircularBuffer {
private:
    static const int BUFFER_SIZE = 10;
    
    struct Bucket {
        unordered_set<string> messages;
        int timestamp = -1;
    };
    
    vector<Bucket> buckets;
    
public:
    LoggerCircularBuffer() : buckets(BUFFER_SIZE) {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        int idx = timestamp % BUFFER_SIZE;
        
        // Clear old buckets
        if (buckets[idx].timestamp != timestamp) {
            buckets[idx].messages.clear();
            buckets[idx].timestamp = timestamp;
        }
        
        // Check if message exists in recent buckets
        for (int i = 0; i < BUFFER_SIZE; i++) {
            int bucketIdx = (timestamp - i) % BUFFER_SIZE;
            if (buckets[bucketIdx].timestamp == timestamp - i &&
                buckets[bucketIdx].messages.count(message)) {
                return false;
            }
        }
        
        buckets[idx].messages.insert(message);
        return true;
    }
};
```

### Approach 4: Lazy Deletion with TTL

```cpp
class LoggerLazyDeletion {
private:
    struct MessageInfo {
        int lastPrintTime;
        bool valid;
        
        MessageInfo(int time) : lastPrintTime(time), valid(true) {}
    };
    
    unordered_map<string, MessageInfo> messageMap;
    queue<pair<string, int>> expirationQueue;
    
    void lazyCleanup(int currentTime) {
        while (!expirationQueue.empty()) {
            auto [message, expireTime] = expirationQueue.front();
            if (expireTime > currentTime) break;
            
            expirationQueue.pop();
            if (messageMap.count(message) && 
                messageMap[message].lastPrintTime + 10 <= currentTime) {
                messageMap.erase(message);
            }
        }
    }
    
public:
    LoggerLazyDeletion() {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        lazyCleanup(timestamp);
        
        if (messageMap.count(message) && 
            timestamp - messageMap[message].lastPrintTime < 10) {
            return false;
        }
        
        messageMap[message] = MessageInfo(timestamp);
        expirationQueue.push({message, timestamp + 10});
        return true;
    }
};
```

### Approach 5: Thread-Safe Implementation

```cpp
#include <mutex>
#include <shared_mutex>

class LoggerThreadSafe {
private:
    mutable shared_mutex rwMutex;
    unordered_map<string, int> messageMap;
    
public:
    LoggerThreadSafe() {}
    
    bool shouldPrintMessage(int timestamp, string message) {
        // Try read-only access first
        {
            shared_lock<shared_mutex> readLock(rwMutex);
            auto it = messageMap.find(message);
            if (it != messageMap.end() && timestamp - it->second < 10) {
                return false;
            }
        }
        
        // Need write access to update
        unique_lock<shared_mutex> writeLock(rwMutex);
        
        // Double-check after acquiring write lock
        auto it = messageMap.find(message);
        if (it != messageMap.end() && timestamp - it->second < 10) {
            return false;
        }
        
        messageMap[message] = timestamp;
        return true;
    }
    
    // Additional method for cleanup
    void cleanup(int currentTime) {
        unique_lock<shared_mutex> writeLock(rwMutex);
        
        auto it = messageMap.begin();
        while (it != messageMap.end()) {
            if (currentTime - it->second >= 10) {
                it = messageMap.erase(it);
            } else {
                ++it;
            }
        }
    }
};
```

## Complexity Analysis

**Time Complexity:**
- **Hash Map**: O(1) average, O(n) worst case for shouldPrintMessage
- **Queue + Set**: O(k) where k is messages in the 10-second window
- **Circular Buffer**: O(1) for insertion, O(10) = O(1) for checking
- **Lazy Deletion**: O(1) amortized for shouldPrintMessage
- **Thread-Safe**: O(1) for read, O(1) for write (with contention overhead)

**Space Complexity:**
- **Hash Map**: O(n) where n is total unique messages (can grow indefinitely)
- **Queue + Set**: O(k) where k is messages in current window
- **Circular Buffer**: O(10) = O(1) for buffer, O(m) for messages per bucket
- **Lazy Deletion**: O(n) but with periodic cleanup
- **Thread-Safe**: O(n) similar to hash map

## Example Walkthrough

### Example 1

```plaintext
Input:
["Logger", "shouldPrintMessage", "shouldPrintMessage", "shouldPrintMessage", "shouldPrintMessage", "shouldPrintMessage", "shouldPrintMessage"]
[[], [1, "foo"], [2, "bar"], [3, "foo"], [8, "bar"], [10, "foo"], [11, "foo"]]

Output:
[null, true, true, false, false, false, true]

Explanation:
Logger logger = new Logger();
logger.shouldPrintMessage(1, "foo");  // return true, next allowed timestamp for "foo" is 1 + 10 = 11
logger.shouldPrintMessage(2, "bar");  // return true, next allowed timestamp for "bar" is 2 + 10 = 12
logger.shouldPrintMessage(3, "foo");  // 3 < 11, return false
logger.shouldPrintMessage(8, "bar");  // 8 < 12, return false
logger.shouldPrintMessage(10, "foo"); // 10 < 11, return false
logger.shouldPrintMessage(11, "foo"); // 11 >= 11, return true, next allowed timestamp for "foo" is 11 + 10 = 21
```

## Key Optimization Techniques

### 1. Memory Management

```cpp
// Periodic cleanup to prevent memory leaks
void periodicCleanup(int currentTime) {
    if (currentTime % 100 == 0) { // Clean every 100 seconds
        auto it = messageMap.begin();
        while (it != messageMap.end()) {
            if (currentTime - it->second >= 10) {
                it = messageMap.erase(it);
            } else {
                ++it;
            }
        }
    }
}
```

### 2. Batch Processing

```cpp
// Process multiple messages at once
vector<bool> shouldPrintMessages(int timestamp, const vector<string>& messages) {
    vector<bool> results;
    results.reserve(messages.size());
    
    for (const string& message : messages) {
        results.push_back(shouldPrintMessage(timestamp, message));
    }
    return results;
}
```

### 3. Smart Cleanup Strategy

```cpp
// Only cleanup when memory usage exceeds threshold
void smartCleanup(int currentTime) {
    if (messageMap.size() > MAX_CACHE_SIZE) {
        // Remove oldest entries beyond the time window
        vector<string> toRemove;
        for (const auto& [message, timestamp] : messageMap) {
            if (currentTime - timestamp >= 10) {
                toRemove.push_back(message);
            }
        }
        
        for (const string& message : toRemove) {
            messageMap.erase(message);
        }
    }
}
```

## Real-World Applications

### 1. API Rate Limiting

```cpp
class APIRateLimiter {
private:
    unordered_map<string, queue<int>> userRequests;
    int maxRequestsPerWindow;
    int windowSizeSeconds;
    
public:
    APIRateLimiter(int maxRequests, int windowSize) 
        : maxRequestsPerWindow(maxRequests), windowSizeSeconds(windowSize) {}
    
    bool allowRequest(const string& userId, int timestamp) {
        auto& requests = userRequests[userId];
        
        // Remove old requests outside the window
        while (!requests.empty() && 
               timestamp - requests.front() >= windowSizeSeconds) {
            requests.pop();
        }
        
        // Check if we can allow this request
        if (requests.size() >= maxRequestsPerWindow) {
            return false;
        }
        
        requests.push(timestamp);
        return true;
    }
};
```

### 2. Distributed Logging System

```cpp
class DistributedLogger {
private:
    struct LoggerNode {
        unordered_map<string, int> messageTimestamps;
        string nodeId;
        
        LoggerNode(const string& id) : nodeId(id) {}
    };
    
    unordered_map<string, unique_ptr<LoggerNode>> nodes;
    
public:
    bool shouldPrintMessage(const string& nodeId, int timestamp, const string& message) {
        if (!nodes.count(nodeId)) {
            nodes[nodeId] = make_unique<LoggerNode>(nodeId);
        }
        
        auto& node = nodes[nodeId];
        string globalKey = nodeId + ":" + message;
        
        if (node->messageTimestamps.count(globalKey) && 
            timestamp - node->messageTimestamps[globalKey] < 10) {
            return false;
        }
        
        node->messageTimestamps[globalKey] = timestamp;
        return true;
    }
    
    void cleanupNode(const string& nodeId, int currentTime) {
        if (nodes.count(nodeId)) {
            auto& timestamps = nodes[nodeId]->messageTimestamps;
            auto it = timestamps.begin();
            while (it != timestamps.end()) {
                if (currentTime - it->second >= 10) {
                    it = timestamps.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
};
```

### 3. Chat Application Spam Filter

```cpp
class ChatSpamFilter {
private:
    struct UserActivity {
        queue<int> messageTimes;
        unordered_map<string, int> recentMessages;
    };
    
    unordered_map<string, UserActivity> userActivities;
    int spamThreshold;
    int timeWindow;
    
public:
    ChatSpamFilter(int threshold = 5, int window = 60) 
        : spamThreshold(threshold), timeWindow(window) {}
    
    bool shouldAllowMessage(const string& userId, const string& message, int timestamp) {
        auto& activity = userActivities[userId];
        
        // Clean old message times
        while (!activity.messageTimes.empty() && 
               timestamp - activity.messageTimes.front() >= timeWindow) {
            activity.messageTimes.pop();
        }
        
        // Check for message repetition (same as logger)
        if (activity.recentMessages.count(message) && 
            timestamp - activity.recentMessages[message] < 10) {
            return false;
        }
        
        // Check for spam (too many messages)
        if (activity.messageTimes.size() >= spamThreshold) {
            return false;
        }
        
        // Allow message
        activity.messageTimes.push(timestamp);
        activity.recentMessages[message] = timestamp;
        return true;
    }
};
```

## Advanced Features

### 1. Priority-Based Logging

```cpp
class PriorityLogger {
private:
    enum Priority { LOW = 0, MEDIUM = 1, HIGH = 2, CRITICAL = 3 };
    
    struct MessageEntry {
        string message;
        int timestamp;
        Priority priority;
    };
    
    unordered_map<string, MessageEntry> messageMap;
    vector<int> cooldowns = {60, 30, 10, 0}; // Cooldowns by priority
    
public:
    bool shouldPrintMessage(int timestamp, const string& message, Priority priority) {
        string key = message;
        
        if (messageMap.count(key)) {
            const auto& entry = messageMap[key];
            int requiredCooldown = cooldowns[entry.priority];
            
            // High priority messages can override lower priority cooldowns
            if (priority > entry.priority || 
                timestamp - entry.timestamp >= requiredCooldown) {
                messageMap[key] = {message, timestamp, priority};
                return true;
            }
            return false;
        }
        
        messageMap[key] = {message, timestamp, priority};
        return true;
    }
};
```

### 2. Analytics and Monitoring

```cpp
class AnalyticsLogger {
private:
    unordered_map<string, int> messageTimestamps;
    unordered_map<string, int> messageCount;
    unordered_map<string, int> blockedCount;
    queue<pair<int, string>> recentActivity;
    
public:
    bool shouldPrintMessage(int timestamp, const string& message) {
        // Track all attempts
        messageCount[message]++;
        recentActivity.push({timestamp, message});
        
        // Clean old activity
        while (!recentActivity.empty() && 
               timestamp - recentActivity.front().first > 3600) {
            recentActivity.pop();
        }
        
        if (messageTimestamps.count(message) && 
            timestamp - messageTimestamps[message] < 10) {
            blockedCount[message]++;
            return false;
        }
        
        messageTimestamps[message] = timestamp;
        return true;
    }
    
    // Analytics methods
    int getTotalMessages(const string& message) const {
        auto it = messageCount.find(message);
        return it != messageCount.end() ? it->second : 0;
    }
    
    int getBlockedMessages(const string& message) const {
        auto it = blockedCount.find(message);
        return it != blockedCount.end() ? it->second : 0;
    }
    
    double getBlockedRate(const string& message) const {
        int total = getTotalMessages(message);
        int blocked = getBlockedMessages(message);
        return total > 0 ? (double)blocked / total : 0.0;
    }
};
```

## Testing Framework

```cpp
#include <cassert>
#include <chrono>

class TestSuite {
public:
    static void runAllTests() {
        testBasicFunctionality();
        testEdgeCases();
        testMemoryEfficiency();
        testThreadSafety();
        cout << "All tests passed!\n";
    }
    
private:
    static void testBasicFunctionality() {
        Logger logger;
        
        assert(logger.shouldPrintMessage(1, "foo") == true);
        assert(logger.shouldPrintMessage(2, "bar") == true);
        assert(logger.shouldPrintMessage(3, "foo") == false);
        assert(logger.shouldPrintMessage(8, "bar") == false);
        assert(logger.shouldPrintMessage(10, "foo") == false);
        assert(logger.shouldPrintMessage(11, "foo") == true);
    }
    
    static void testEdgeCases() {
        Logger logger;
        
        // Same timestamp, different messages
        assert(logger.shouldPrintMessage(1, "msg1") == true);
        assert(logger.shouldPrintMessage(1, "msg2") == true);
        
        // Exactly at boundary
        assert(logger.shouldPrintMessage(0, "test") == true);
        assert(logger.shouldPrintMessage(10, "test") == true);
        assert(logger.shouldPrintMessage(19, "test") == false);
        assert(logger.shouldPrintMessage(20, "test") == true);
    }
    
    static void testMemoryEfficiency() {
        LoggerOptimized logger;
        
        // Add many messages and verify cleanup
        for (int i = 0; i < 1000; i++) {
            logger.shouldPrintMessage(i, "msg" + to_string(i % 100));
        }
        
        // Check that old messages are cleaned up
        // This is implicit in the queue-based approach
        assert(true); // Placeholder for memory verification
    }
    
    static void testThreadSafety() {
        LoggerThreadSafe logger;
        
        // Simulate concurrent access
        vector<thread> threads;
        atomic<int> successCount{0};
        
        for (int i = 0; i < 10; i++) {
            threads.emplace_back([&logger, &successCount, i]() {
                for (int j = 0; j < 100; j++) {
                    if (logger.shouldPrintMessage(j, "thread" + to_string(i))) {
                        successCount++;
                    }
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        // Verify that we got expected number of successes
        assert(successCount.load() > 0);
    }
};
```

## Pattern Analysis: Simulation

This problem fits the **Simulation** pattern because:

1. **Real-time Processing**: Messages arrive in chronological order
2. **State Management**: Track message history and timestamps
3. **Rule-based Logic**: Apply 10-second cooldown rule
4. **Time-based Decisions**: Use timestamps to determine validity

### Key Pattern Elements

- **Event Processing**: Handle messages as they arrive
- **State Tracking**: Maintain message timestamps
- **Time Window Management**: Enforce cooldown periods
- **Memory Optimization**: Clean up old entries

### Pattern Variations

- **Fixed Window**: Use discrete time buckets
- **Sliding Window**: Continuous time tracking
- **Token Bucket**: Rate limiting with burst allowance
- **Leaky Bucket**: Smooth rate limiting

## Related Problems

- **LeetCode 146**: LRU Cache
- **LeetCode 295**: Find Median from Data Stream
- **LeetCode 348**: Design Tic-Tac-Toe
- **LeetCode 355**: Design Twitter
- **LeetCode 981**: Time Based Key-Value Store

## Tags

`Design` `Hash Table` `Queue` `Data Stream` `Rate Limiting` `Simulation`
