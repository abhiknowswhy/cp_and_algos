# Time Based Key-Value Store

## Problem Description

**LeetCode Problem #981 - Medium**
🔗 [LeetCode Link](https://leetcode.com/problems/time-based-key-value-store/)

Create a timebased key-value data structure class `TimeMap`, that supports two operations:

1. `set(string key, string value, int timestamp)`: Stores the key and value, along with the given timestamp.
2. `get(string key, int timestamp)`: Returns a value such that `set(key, value, timestamp_prev)` was called previously, with `timestamp_prev <= timestamp`. If there are multiple such values, it returns the one with the largest `timestamp_prev`. If there are no values, it returns an empty string ("").

**Key Constraints:**
- All timestamps are strictly increasing
- 1 ≤ key.length, value.length ≤ 100
- Timestamps are positive integers
- All operations are case-sensitive

## Queue Pattern Connection

This problem demonstrates **Time-Series Data Management** patterns where:
- Historical data is stored in chronological order (natural queue behavior)
- Binary search optimization leverages sorted timestamp ordering
- Snapshot querying requires efficient time-range lookups
- Real-time data ingestion with historical query capabilities
- Pattern applies to logging systems, financial data, IoT sensor streams

## Approach

### Approach 1: HashMap + Binary Search (Optimal)
Store each key's values in a vector sorted by timestamp. Use binary search for efficient lookups.

### Approach 2: HashMap + TreeMap
Use a TreeMap (map in C++) for each key to maintain sorted timestamps with automatic ordering.

### Approach 3: Segment Tree Optimization
For very high-frequency operations, use segment trees for range queries.

### Approach 4: Compressed Time Windows
Optimize memory by compressing similar consecutive values.

## Algorithm Steps

### Binary Search Approach:
1. **Initialize**: Create a HashMap where each key maps to a vector of (timestamp, value) pairs
2. **Set Operation**: Append new (timestamp, value) to the key's vector (guaranteed sorted due to increasing timestamps)
3. **Get Operation**: Binary search for the largest timestamp ≤ query timestamp
4. **Return**: Extract and return the corresponding value

## Implementation

### Implementation 1: Optimal Binary Search Solution

```cpp
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class TimeMap {
private:
    // Each key maps to a vector of (timestamp, value) pairs
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> store;
    
public:
    /** Initialize data structure */
    TimeMap() {}
    
    /** 
     * Stores key-value pair with timestamp
     * Time: O(1), Space: O(1) per operation
     */
    void set(std::string key, std::string value, int timestamp) {
        store[key].push_back({timestamp, value});
    }
    
    /** 
     * Get value for key at given timestamp
     * Time: O(log n), Space: O(1) where n = number of timestamps for key
     */
    std::string get(std::string key, int timestamp) {
        if (store.find(key) == store.end()) {
            return "";
        }
        
        auto& values = store[key];
        
        // Binary search for largest timestamp <= given timestamp
        int left = 0, right = values.size() - 1;
        std::string result = "";
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (values[mid].first <= timestamp) {
                result = values[mid].second;
                left = mid + 1;  // Look for potentially larger valid timestamp
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Utility method for debugging
    void printStore() const {
        for (const auto& [key, values] : store) {
            std::cout << "Key: " << key << " -> ";
            for (const auto& [timestamp, value] : values) {
                std::cout << "(" << timestamp << "," << value << ") ";
            }
            std::cout << std::endl;
        }
    }
    
    // Get all values for a key
    std::vector<std::pair<int, std::string>> getAllValues(const std::string& key) const {
        if (store.find(key) != store.end()) {
            return store.at(key);
        }
        return {};
    }
};
```

### Implementation 2: STL lower_bound Optimization

```cpp
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

class TimeMapOptimized {
private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> store;
    
public:
    TimeMapOptimized() {}
    
    void set(std::string key, std::string value, int timestamp) {
        store[key].emplace_back(timestamp, value);
    }
    
    std::string get(std::string key, int timestamp) {
        if (store.find(key) == store.end()) {
            return "";
        }
        
        auto& values = store[key];
        
        // Find first element with timestamp > given timestamp
        auto it = std::upper_bound(values.begin(), values.end(), 
                                   std::make_pair(timestamp, std::string()),
                                   [](const auto& a, const auto& b) {
                                       return a.first < b.first;
                                   });
        
        // If no such element exists or it's the first element
        if (it == values.begin()) {
            return "";
        }
        
        // Return the previous element (largest timestamp <= given timestamp)
        return (--it)->second;
    }
    
    // Range query: get all values in timestamp range
    std::vector<std::pair<int, std::string>> getRange(const std::string& key, 
                                                      int startTime, int endTime) {
        std::vector<std::pair<int, std::string>> result;
        
        if (store.find(key) == store.end()) {
            return result;
        }
        
        auto& values = store[key];
        
        auto start_it = std::lower_bound(values.begin(), values.end(),
                                        std::make_pair(startTime, std::string()),
                                        [](const auto& a, const auto& b) {
                                            return a.first < b.first;
                                        });
        
        auto end_it = std::upper_bound(values.begin(), values.end(),
                                      std::make_pair(endTime, std::string()),
                                      [](const auto& a, const auto& b) {
                                          return a.first < b.first;
                                      });
        
        for (auto it = start_it; it != end_it; ++it) {
            result.push_back(*it);
        }
        
        return result;
    }
};
```

### Implementation 3: TreeMap Based Solution

```cpp
#include <unordered_map>
#include <map>
#include <string>

class TimeMapTree {
private:
    std::unordered_map<std::string, std::map<int, std::string>> store;
    
public:
    TimeMapTree() {}
    
    void set(std::string key, std::string value, int timestamp) {
        store[key][timestamp] = value;
    }
    
    std::string get(std::string key, int timestamp) {
        if (store.find(key) == store.end()) {
            return "";
        }
        
        auto& timestamps = store[key];
        
        // Find largest timestamp <= given timestamp
        auto it = timestamps.upper_bound(timestamp);
        
        if (it == timestamps.begin()) {
            return "";  // No valid timestamp found
        }
        
        return (--it)->second;
    }
    
    // Additional features enabled by TreeMap structure
    std::string getExact(std::string key, int timestamp) {
        if (store.find(key) == store.end()) {
            return "";
        }
        
        auto& timestamps = store[key];
        auto it = timestamps.find(timestamp);
        
        return (it != timestamps.end()) ? it->second : "";
    }
    
    std::vector<std::pair<int, std::string>> getLatestN(const std::string& key, int n) {
        std::vector<std::pair<int, std::string>> result;
        
        if (store.find(key) == store.end()) {
            return result;
        }
        
        auto& timestamps = store[key];
        auto it = timestamps.rbegin();  // Start from latest
        
        for (int i = 0; i < n && it != timestamps.rend(); ++i, ++it) {
            result.push_back({it->first, it->second});
        }
        
        return result;
    }
};
```

### Implementation 4: Thread-Safe Version

```cpp
#include <unordered_map>
#include <vector>
#include <string>
#include <shared_mutex>
#include <algorithm>

class TimeMapThreadSafe {
private:
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> store;
    mutable std::shared_mutex mutex_;
    
public:
    TimeMapThreadSafe() {}
    
    void set(std::string key, std::string value, int timestamp) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        store[key].emplace_back(timestamp, value);
    }
    
    std::string get(std::string key, int timestamp) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        
        if (store.find(key) == store.end()) {
            return "";
        }
        
        const auto& values = store[key];
        
        auto it = std::upper_bound(values.begin(), values.end(),
                                   std::make_pair(timestamp, std::string()),
                                   [](const auto& a, const auto& b) {
                                       return a.first < b.first;
                                   });
        
        if (it == values.begin()) {
            return "";
        }
        
        return (--it)->second;
    }
    
    // Bulk operations for better performance
    void setBatch(const std::vector<std::tuple<std::string, std::string, int>>& operations) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        
        for (const auto& [key, value, timestamp] : operations) {
            store[key].emplace_back(timestamp, value);
        }
    }
    
    std::vector<std::string> getBatch(const std::vector<std::pair<std::string, int>>& queries) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        std::vector<std::string> results;
        results.reserve(queries.size());
        
        for (const auto& [key, timestamp] : queries) {
            if (store.find(key) == store.end()) {
                results.push_back("");
                continue;
            }
            
            const auto& values = store[key];
            auto it = std::upper_bound(values.begin(), values.end(),
                                      std::make_pair(timestamp, std::string()),
                                      [](const auto& a, const auto& b) {
                                          return a.first < b.first;
                                      });
            
            results.push_back((it == values.begin()) ? "" : (--it)->second);
        }
        
        return results;
    }
};
```

### Implementation 5: Memory-Optimized Version

```cpp
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class TimeMapMemoryOptimized {
private:
    struct CompressedValue {
        int timestamp;
        std::shared_ptr<std::string> value;  // Shared storage for identical values
        
        CompressedValue(int t, const std::string& v) 
            : timestamp(t), value(std::make_shared<std::string>(v)) {}
    };
    
    std::unordered_map<std::string, std::vector<CompressedValue>> store;
    std::unordered_map<std::string, std::shared_ptr<std::string>> valuePool;
    
    std::shared_ptr<std::string> getSharedValue(const std::string& value) {
        auto it = valuePool.find(value);
        if (it != valuePool.end()) {
            return it->second;
        }
        
        auto sharedValue = std::make_shared<std::string>(value);
        valuePool[value] = sharedValue;
        return sharedValue;
    }
    
public:
    TimeMapMemoryOptimized() {}
    
    void set(std::string key, std::string value, int timestamp) {
        auto sharedValue = getSharedValue(value);
        store[key].emplace_back(timestamp, *sharedValue);
    }
    
    std::string get(std::string key, int timestamp) {
        if (store.find(key) == store.end()) {
            return "";
        }
        
        const auto& values = store[key];
        
        int left = 0, right = values.size() - 1;
        std::string result = "";
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (values[mid].timestamp <= timestamp) {
                result = *(values[mid].value);
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Memory usage statistics
    size_t getMemoryUsage() const {
        size_t total = 0;
        total += store.size() * sizeof(std::pair<std::string, std::vector<CompressedValue>>);
        
        for (const auto& [key, values] : store) {
            total += key.size();
            total += values.size() * sizeof(CompressedValue);
        }
        
        total += valuePool.size() * sizeof(std::pair<std::string, std::shared_ptr<std::string>>);
        for (const auto& [value, ptr] : valuePool) {
            total += value.size();
        }
        
        return total;
    }
};
```

## Complexity Analysis

### Binary Search Solution:
- **Set Operation**: O(1) time, O(1) space
- **Get Operation**: O(log n) time, O(1) space (n = number of timestamps for the key)
- **Overall Space**: O(m) where m is total number of set operations

### TreeMap Solution:
- **Set Operation**: O(log n) time, O(1) space
- **Get Operation**: O(log n) time, O(1) space
- **Memory Overhead**: Higher due to tree structure

### Thread-Safe Solution:
- **Additional Overhead**: Synchronization costs
- **Batch Operations**: Better amortized performance
- **Concurrent Reads**: Multiple readers supported

## Examples

### Example 1: Basic Operations

```cpp
void example1() {
    TimeMap timeMap;
    
    timeMap.set("foo", "bar", 1);
    std::cout << timeMap.get("foo", 1) << std::endl;  // "bar"
    std::cout << timeMap.get("foo", 3) << std::endl;  // "bar"
    
    timeMap.set("foo", "bar2", 4);
    std::cout << timeMap.get("foo", 4) << std::endl;  // "bar2"
    std::cout << timeMap.get("foo", 5) << std::endl;  // "bar2"
    std::cout << timeMap.get("foo", 0) << std::endl;  // ""
}
```

### Example 2: Multiple Keys and Complex Queries

```cpp
void example2() {
    TimeMapOptimized timeMap;
    
    // Set up data
    timeMap.set("love", "high", 10);
    timeMap.set("love", "low", 20);
    timeMap.set("love", "medium", 30);
    
    timeMap.set("peace", "world", 15);
    timeMap.set("peace", "harmony", 25);
    
    // Test queries
    std::cout << timeMap.get("love", 5) << std::endl;   // ""
    std::cout << timeMap.get("love", 10) << std::endl;  // "high"
    std::cout << timeMap.get("love", 15) << std::endl;  // "high"
    std::cout << timeMap.get("love", 20) << std::endl;  // "low"
    std::cout << timeMap.get("love", 25) << std::endl;  // "low"
    std::cout << timeMap.get("love", 30) << std::endl;  // "medium"
    std::cout << timeMap.get("love", 35) << std::endl;  // "medium"
    
    // Range queries
    auto range = timeMap.getRange("love", 15, 25);
    std::cout << "Range [15,25]: ";
    for (const auto& [timestamp, value] : range) {
        std::cout << "(" << timestamp << "," << value << ") ";
    }
    std::cout << std::endl;
}
```

### Example 3: Performance Benchmark

```cpp
#include <chrono>
#include <random>

void performanceBenchmark() {
    TimeMap timeMap;
    const int numOperations = 100000;
    
    // Generate test data
    std::vector<std::string> keys;
    std::vector<std::string> values;
    std::vector<int> timestamps;
    
    for (int i = 0; i < numOperations; i++) {
        keys.push_back("key" + std::to_string(i % 1000));
        values.push_back("value" + std::to_string(i));
        timestamps.push_back(i + 1);
    }
    
    // Benchmark set operations
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOperations; i++) {
        timeMap.set(keys[i], values[i], timestamps[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    auto setDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Set operations: " << setDuration.count() << " microseconds" << std::endl;
    
    // Benchmark get operations
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, numOperations);
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numOperations / 10; i++) {
        int randomTimestamp = dis(gen);
        std::string key = "key" + std::to_string(i % 1000);
        timeMap.get(key, randomTimestamp);
    }
    end = std::chrono::high_resolution_clock::now();
    
    auto getDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Get operations: " << getDuration.count() << " microseconds" << std::endl;
    
    std::cout << "Average set time: " << (double)setDuration.count() / numOperations << " μs" << std::endl;
    std::cout << "Average get time: " << (double)getDuration.count() / (numOperations / 10) << " μs" << std::endl;
}
```

## Real-World Applications

### 1. **Financial Trading System**

```cpp
class TradingDataStore {
private:
    TimeMapThreadSafe priceStore;
    TimeMapThreadSafe volumeStore;
    
public:
    void recordTrade(const std::string& symbol, double price, 
                    long volume, int timestamp) {
        priceStore.set(symbol, std::to_string(price), timestamp);
        volumeStore.set(symbol, std::to_string(volume), timestamp);
    }
    
    double getPrice(const std::string& symbol, int timestamp) {
        std::string priceStr = priceStore.get(symbol, timestamp);
        return priceStr.empty() ? 0.0 : std::stod(priceStr);
    }
    
    struct MarketSnapshot {
        double price;
        long volume;
        int timestamp;
    };
    
    MarketSnapshot getMarketSnapshot(const std::string& symbol, int timestamp) {
        double price = getPrice(symbol, timestamp);
        std::string volumeStr = volumeStore.get(symbol, timestamp);
        long volume = volumeStr.empty() ? 0 : std::stol(volumeStr);
        
        return {price, volume, timestamp};
    }
};
```

### 2. **IoT Sensor Data Management**

```cpp
class SensorDataManager {
private:
    TimeMapMemoryOptimized sensorStore;
    std::unordered_map<std::string, std::string> sensorTypes;
    
public:
    void recordSensorData(const std::string& sensorId, 
                         const std::string& reading, 
                         int timestamp) {
        sensorStore.set(sensorId, reading, timestamp);
    }
    
    std::string getLatestReading(const std::string& sensorId, int beforeTime) {
        return sensorStore.get(sensorId, beforeTime);
    }
    
    struct SensorStats {
        std::string minValue;
        std::string maxValue;
        int readingCount;
    };
    
    SensorStats calculateStats(const std::string& sensorId, 
                              int startTime, int endTime) {
        // Implementation would use range queries
        SensorStats stats;
        // Calculate min, max, count from time range
        return stats;
    }
    
    void registerSensorType(const std::string& sensorId, 
                           const std::string& type) {
        sensorTypes[sensorId] = type;
    }
};
```

### 3. **Distributed Logging System**

```cpp
class DistributedLogger {
private:
    TimeMapThreadSafe logStore;
    std::atomic<int> logCounter{0};
    
public:
    enum LogLevel { DEBUG, INFO, WARN, ERROR };
    
    void log(LogLevel level, const std::string& service, 
            const std::string& message, int timestamp) {
        std::string logEntry = formatLogEntry(level, service, message);
        std::string logKey = service + "_" + std::to_string(level);
        logStore.set(logKey, logEntry, timestamp);
        logCounter++;
    }
    
    std::vector<std::string> getLogsForService(const std::string& service, 
                                              int fromTime, int toTime) {
        std::vector<std::string> logs;
        
        for (int level = DEBUG; level <= ERROR; level++) {
            std::string logKey = service + "_" + std::to_string(level);
            // Would need range query functionality
            // Implementation simplified for example
        }
        
        return logs;
    }
    
private:
    std::string formatLogEntry(LogLevel level, const std::string& service, 
                              const std::string& message) {
        std::string levelStr[] = {"DEBUG", "INFO", "WARN", "ERROR"};
        return "[" + levelStr[level] + "] " + service + ": " + message;
    }
};
```

### 4. **Game State Versioning**

```cpp
class GameStateManager {
private:
    TimeMapOptimized gameStore;
    
public:
    struct GameState {
        std::string playerPositions;
        std::string scores;
        std::string gameMode;
        
        std::string serialize() const {
            return playerPositions + "|" + scores + "|" + gameMode;
        }
        
        static GameState deserialize(const std::string& data) {
            // Implementation would parse the serialized data
            return {"", "", ""};
        }
    };
    
    void saveGameState(const std::string& gameId, 
                      const GameState& state, 
                      int timestamp) {
        gameStore.set(gameId, state.serialize(), timestamp);
    }
    
    GameState loadGameState(const std::string& gameId, int timestamp) {
        std::string serialized = gameStore.get(gameId, timestamp);
        return serialized.empty() ? GameState{} : GameState::deserialize(serialized);
    }
    
    // Time travel debugging - get state at specific point
    GameState replayGame(const std::string& gameId, int replayTimestamp) {
        return loadGameState(gameId, replayTimestamp);
    }
};
```

### 5. **Configuration Management System**

```cpp
class ConfigurationManager {
private:
    TimeMapThreadSafe configStore;
    std::unordered_map<std::string, std::vector<std::string>> configHistory;
    
public:
    void updateConfig(const std::string& service, 
                     const std::string& configKey,
                     const std::string& configValue,
                     int timestamp) {
        std::string fullKey = service + "." + configKey;
        configStore.set(fullKey, configValue, timestamp);
        
        // Track configuration changes
        configHistory[fullKey].push_back(configValue);
    }
    
    std::string getConfig(const std::string& service,
                         const std::string& configKey,
                         int timestamp) {
        std::string fullKey = service + "." + configKey;
        return configStore.get(fullKey, timestamp);
    }
    
    std::map<std::string, std::string> getAllConfigs(const std::string& service,
                                                     int timestamp) {
        std::map<std::string, std::string> configs;
        
        // In real implementation, would iterate through all keys for service
        // This is simplified for example
        
        return configs;
    }
    
    void rollbackConfig(const std::string& service,
                       const std::string& configKey,
                       int rollbackToTimestamp,
                       int newTimestamp) {
        std::string value = getConfig(service, configKey, rollbackToTimestamp);
        if (!value.empty()) {
            updateConfig(service, configKey, value, newTimestamp);
        }
    }
};
```

## Pattern Insights

### Key Observations:

1. **Binary Search Optimization**: The problem leverages the fact that timestamps are strictly increasing, enabling O(log n) lookups instead of O(n) linear search

2. **Space-Time Tradeoffs**: Different implementations show various optimization strategies - memory sharing, compression, threading

3. **Temporal Locality**: Real-world time-based systems often exhibit temporal locality in access patterns, making caching strategies effective

4. **Immutable History**: Once data is stored with a timestamp, it's never modified, enabling lock-free read optimizations

### Related Patterns:
- **Snapshot Pattern**: Version control systems, database snapshots
- **Event Sourcing**: Storing events rather than current state
- **CQRS (Command Query Responsibility Segregation)**: Separate read/write models
- **Time Series Databases**: Specialized storage for time-ordered data

### Advanced Optimizations:
- **LSM Trees**: Log-Structured Merge Trees for write-heavy workloads
- **Bloom Filters**: Probabilistic data structures for existence checks
- **Compression**: Time-based compression for archival data
- **Sharding**: Distribute data across time ranges or key spaces
- **Caching**: LRU caches for frequently accessed time ranges

This problem excellently demonstrates how understanding data access patterns (time-based queries) can lead to significant algorithmic optimizations, making it valuable for both competitive programming and designing real-world systems that handle temporal data.
