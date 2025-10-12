# LRU Cache (Using Queue-like Operations)

## Problem Description

Design a data structure that follows the constraints of a **Least Recently Used (LRU) cache**.

Implement the `LRUCache` class:
- `LRUCache(int capacity)` Initialize the LRU cache with positive size capacity.
- `int get(int key)` Return the value of the key if the key exists, otherwise return -1.
- `void put(int key, int value)` Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.

The functions `get` and `put` must each run in O(1) average time complexity.

**LeetCode Problem:** [146. LRU Cache](https://leetcode.com/problems/lru-cache/)

## Approach

Implement LRU Cache using queue-like operations with different data structures:
1. **Deque + HashMap**: Use deque for order tracking and HashMap for O(1) access
2. **Doubly Linked List + HashMap**: Classic approach adapted with queue semantics
3. **Custom Queue**: Implement specialized queue operations for LRU management

## Algorithm Steps

1. **Initialization**: Set up capacity, hash map for key-value storage, and queue structure for order tracking
2. **Get Operation**: 
   - Check if key exists in hash map
   - If exists, move to front (most recently used)
   - Return value or -1
3. **Put Operation**:
   - If key exists, update value and move to front
   - If new key and at capacity, remove least recently used (back of queue)
   - Add new key-value pair to front of queue

## Implementation

### Approach 1: Deque + HashMap (Queue-like Operations)
```cpp
#include <unordered_map>
#include <deque>
#include <iostream>
#include <cassert>

class LRUCache {
private:
    int capacity;
    std::unordered_map<int, int> keyToValue;
    std::unordered_map<int, std::deque<int>::iterator> keyToIter;
    std::deque<int> accessOrder; // Front = most recent, Back = least recent
    
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (keyToValue.find(key) == keyToValue.end()) {
            return -1;
        }
        
        // Move to front (most recently used)
        moveToFront(key);
        return keyToValue[key];
    }
    
    void put(int key, int value) {
        if (keyToValue.find(key) != keyToValue.end()) {
            // Update existing key
            keyToValue[key] = value;
            moveToFront(key);
        } else {
            // Add new key
            if (accessOrder.size() >= capacity) {
                // Remove least recently used (back of deque)
                int lruKey = accessOrder.back();
                accessOrder.pop_back();
                keyToValue.erase(lruKey);
                keyToIter.erase(lruKey);
            }
            
            // Add to front
            accessOrder.push_front(key);
            keyToValue[key] = value;
            keyToIter[key] = accessOrder.begin();
        }
    }
    
private:
    void moveToFront(int key) {
        // Remove from current position
        auto iter = keyToIter[key];
        accessOrder.erase(iter);
        
        // Add to front
        accessOrder.push_front(key);
        keyToIter[key] = accessOrder.begin();
    }
};
```

### Approach 2: Custom Queue Implementation
```cpp
#include <unordered_map>
#include <list>

class LRUCacheCustomQueue {
private:
    struct Node {
        int key, value;
        Node(int k, int v) : key(k), value(v) {}
    };
    
    int capacity;
    std::list<Node> queue; // Front = most recent, Back = least recent
    std::unordered_map<int, std::list<Node>::iterator> keyToIter;
    
public:
    LRUCacheCustomQueue(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        if (keyToIter.find(key) == keyToIter.end()) {
            return -1;
        }
        
        // Move to front of queue
        auto iter = keyToIter[key];
        int value = iter->value;
        queue.erase(iter);
        queue.push_front(Node(key, value));
        keyToIter[key] = queue.begin();
        
        return value;
    }
    
    void put(int key, int value) {
        if (keyToIter.find(key) != keyToIter.end()) {
            // Update existing
            auto iter = keyToIter[key];
            queue.erase(iter);
            queue.push_front(Node(key, value));
            keyToIter[key] = queue.begin();
        } else {
            // Add new
            if (queue.size() >= capacity) {
                // Remove from back (least recently used)
                int lruKey = queue.back().key;
                queue.pop_back();
                keyToIter.erase(lruKey);
            }
            
            // Add to front (most recently used)
            queue.push_front(Node(key, value));
            keyToIter[key] = queue.begin();
        }
    }
};
```

### Approach 3: Queue-based with Timestamps
```cpp
#include <unordered_map>
#include <queue>
#include <chrono>

class LRUCacheTimestamp {
private:
    struct CacheItem {
        int key, value;
        long long timestamp;
        CacheItem(int k, int v, long long t) : key(k), value(v), timestamp(t) {}
        
        bool operator<(const CacheItem& other) const {
            return timestamp > other.timestamp; // Min heap by timestamp
        }
    };
    
    int capacity;
    std::unordered_map<int, int> keyToValue;
    std::unordered_map<int, long long> keyToTimestamp;
    std::priority_queue<CacheItem> cleanupQueue;
    long long currentTime;
    
    long long getNextTimestamp() {
        return ++currentTime;
    }
    
public:
    LRUCacheTimestamp(int capacity) : capacity(capacity), currentTime(0) {}
    
    int get(int key) {
        if (keyToValue.find(key) == keyToValue.end()) {
            return -1;
        }
        
        // Update timestamp
        keyToTimestamp[key] = getNextTimestamp();
        return keyToValue[key];
    }
    
    void put(int key, int value) {
        if (keyToValue.find(key) != keyToValue.end()) {
            // Update existing
            keyToValue[key] = value;
            keyToTimestamp[key] = getNextTimestamp();
        } else {
            // Add new
            if (keyToValue.size() >= capacity) {
                // Find and remove LRU item
                evictLRU();
            }
            
            keyToValue[key] = value;
            keyToTimestamp[key] = getNextTimestamp();
        }
    }
    
private:
    void evictLRU() {
        // Find key with minimum timestamp
        int lruKey = -1;
        long long minTimestamp = LLONG_MAX;
        
        for (const auto& pair : keyToTimestamp) {
            if (pair.second < minTimestamp) {
                minTimestamp = pair.second;
                lruKey = pair.first;
            }
        }
        
        if (lruKey != -1) {
            keyToValue.erase(lruKey);
            keyToTimestamp.erase(lruKey);
        }
    }
};
```

### Approach 4: Ring Buffer Implementation
```cpp
#include <vector>
#include <unordered_map>

class LRUCacheRingBuffer {
private:
    struct CacheNode {
        int key, value;
        bool valid;
        CacheNode() : key(-1), value(-1), valid(false) {}
        CacheNode(int k, int v) : key(k), value(v), valid(true) {}
    };
    
    int capacity;
    std::vector<CacheNode> ring;
    std::unordered_map<int, int> keyToIndex;
    int head, tail;
    int size;
    
public:
    LRUCacheRingBuffer(int capacity) : capacity(capacity), ring(capacity), head(0), tail(0), size(0) {}
    
    int get(int key) {
        if (keyToIndex.find(key) == keyToIndex.end()) {
            return -1;
        }
        
        int index = keyToIndex[key];
        int value = ring[index].value;
        
        // Move to head position
        moveToHead(key, value);
        return value;
    }
    
    void put(int key, int value) {
        if (keyToIndex.find(key) != keyToIndex.end()) {
            // Update existing
            moveToHead(key, value);
        } else {
            // Add new
            if (size >= capacity) {
                // Remove tail
                removeTail();
            }
            
            addToHead(key, value);
        }
    }
    
private:
    void moveToHead(int key, int value) {
        // Remove from current position
        int oldIndex = keyToIndex[key];
        ring[oldIndex].valid = false;
        
        // Add to head
        addToHead(key, value);
    }
    
    void addToHead(int key, int value) {
        ring[head] = CacheNode(key, value);
        keyToIndex[key] = head;
        head = (head + 1) % capacity;
        if (size < capacity) size++;
    }
    
    void removeTail() {
        while (!ring[tail].valid && tail != head) {
            tail = (tail + 1) % capacity;
        }
        
        if (ring[tail].valid) {
            keyToIndex.erase(ring[tail].key);
            ring[tail].valid = false;
            tail = (tail + 1) % capacity;
            size--;
        }
    }
};
```

### Time Complexity
- **Get**: O(1) average for deque/list approaches, O(capacity) worst case for timestamp approach
- **Put**: O(1) average for deque/list approaches, O(capacity) worst case for timestamp approach

### Space Complexity
- **All Approaches**: O(capacity) for storing cache items and metadata

## Examples

### Example 1: Basic LRU Operations
```cpp
void testBasicLRU() {
    LRUCache lru(2);
    
    lru.put(1, 1);
    lru.put(2, 2);
    assert(lru.get(1) == 1);       // returns 1
    
    lru.put(3, 3);                // evicts key 2
    assert(lru.get(2) == -1);      // returns -1 (not found)
    
    lru.put(4, 4);                // evicts key 1
    assert(lru.get(1) == -1);      // returns -1 (not found)
    assert(lru.get(3) == 3);       // returns 3
    assert(lru.get(4) == 4);       // returns 4
    
    std::cout << "Basic LRU test passed!" << std::endl;
}
```

### Example 2: Update Existing Key
```cpp
void testUpdateExisting() {
    LRUCache lru(2);
    
    lru.put(1, 1);
    lru.put(2, 2);
    lru.put(1, 10);               // Update key 1
    
    assert(lru.get(1) == 10);     // Should return updated value
    
    lru.put(3, 3);                // Should evict key 2 (not key 1)
    assert(lru.get(2) == -1);     // Key 2 evicted
    assert(lru.get(1) == 10);     // Key 1 still exists
    assert(lru.get(3) == 3);      // Key 3 exists
    
    std::cout << "Update existing test passed!" << std::endl;
}
```

## Advanced Features

### Thread-Safe LRU Cache
```cpp
#include <mutex>
#include <shared_mutex>

class ThreadSafeLRUCache {
private:
    mutable std::shared_mutex rwMutex;
    LRUCache cache;
    
public:
    ThreadSafeLRUCache(int capacity) : cache(capacity) {}
    
    int get(int key) {
        std::shared_lock<std::shared_mutex> lock(rwMutex);
        return cache.get(key);
    }
    
    void put(int key, int value) {
        std::unique_lock<std::shared_mutex> lock(rwMutex);
        cache.put(key, value);
    }
};
```

### LRU Cache with Statistics
```cpp
#include <unordered_map>
#include <deque>

class LRUCacheWithStats {
private:
    LRUCache cache;
    int hits, misses, puts, evictions;
    
public:
    LRUCacheWithStats(int capacity) : cache(capacity), hits(0), misses(0), puts(0), evictions(0) {}
    
    int get(int key) {
        int result = cache.get(key);
        if (result == -1) {
            misses++;
        } else {
            hits++;
        }
        return result;
    }
    
    void put(int key, int value) {
        // Check if this will cause eviction
        bool willEvict = cache.size() >= cache.capacity() && cache.get(key) == -1;
        
        cache.put(key, value);
        puts++;
        
        if (willEvict) {
            evictions++;
        }
    }
    
    double getHitRate() const {
        int total = hits + misses;
        return total > 0 ? (double)hits / total : 0.0;
    }
    
    void printStats() const {
        std::cout << "Cache Statistics:" << std::endl;
        std::cout << "Hits: " << hits << std::endl;
        std::cout << "Misses: " << misses << std::endl;
        std::cout << "Hit Rate: " << getHitRate() * 100 << "%" << std::endl;
        std::cout << "Puts: " << puts << std::endl;
        std::cout << "Evictions: " << evictions << std::endl;
    }
};
```

### Performance Benchmarking
```cpp
#include <chrono>
#include <random>

void benchmarkLRUCache() {
    const int capacity = 1000;
    const int operations = 100000;
    
    LRUCache cache(capacity);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> keyDis(1, 2000);
    std::uniform_int_distribution<> valueDis(1, 10000);
    std::uniform_int_distribution<> opDis(0, 1);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < operations; i++) {
        if (opDis(gen) == 0) {
            // Get operation
            cache.get(keyDis(gen));
        } else {
            // Put operation
            cache.put(keyDis(gen), valueDis(gen));
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Benchmark: " << operations << " operations in " 
              << duration.count() << " microseconds" << std::endl;
    std::cout << "Average time per operation: " 
              << (double)duration.count() / operations << " microseconds" << std::endl;
}
```

## Real-World Applications

### 1. Web Browser Cache
```cpp
class BrowserCache {
private:
    LRUCache urlCache;
    std::unordered_map<std::string, std::string> urlToContent;
    
public:
    BrowserCache(int capacity) : urlCache(capacity) {}
    
    std::string getPage(const std::string& url) {
        int hash = std::hash<std::string>{}(url);
        int cached = urlCache.get(hash);
        
        if (cached != -1) {
            return urlToContent[url];
        }
        
        // Simulate fetching from network
        std::string content = fetchFromNetwork(url);
        urlCache.put(hash, 1); // Dummy value
        urlToContent[url] = content;
        
        return content;
    }
    
private:
    std::string fetchFromNetwork(const std::string& url) {
        // Simulate network delay and return content
        return "Content for " + url;
    }
};
```

### 2. Database Buffer Pool
```cpp
class BufferPool {
private:
    LRUCache pageCache;
    std::unordered_map<int, std::vector<char>> pageData;
    int pageSize;
    
public:
    BufferPool(int capacity, int pageSize) : pageCache(capacity), pageSize(pageSize) {}
    
    std::vector<char> getPage(int pageId) {
        int cached = pageCache.get(pageId);
        
        if (cached != -1) {
            return pageData[pageId];
        }
        
        // Load page from disk
        std::vector<char> data = loadPageFromDisk(pageId);
        pageCache.put(pageId, 1);
        pageData[pageId] = data;
        
        return data;
    }
    
    void updatePage(int pageId, const std::vector<char>& data) {
        pageData[pageId] = data;
        pageCache.put(pageId, 1); // Mark as recently used
        // Mark page as dirty for eventual write-back
    }
    
private:
    std::vector<char> loadPageFromDisk(int pageId) {
        // Simulate disk I/O
        return std::vector<char>(pageSize, 'A' + (pageId % 26));
    }
};
```

### 3. CPU Cache Simulator
```cpp
class CPUCacheSimulator {
private:
    LRUCache l1Cache, l2Cache, l3Cache;
    int l1Hits, l2Hits, l3Hits, memoryAccesses;
    
public:
    CPUCacheSimulator(int l1Size, int l2Size, int l3Size) 
        : l1Cache(l1Size), l2Cache(l2Size), l3Cache(l3Size),
          l1Hits(0), l2Hits(0), l3Hits(0), memoryAccesses(0) {}
    
    int accessMemory(int address) {
        // Try L1 cache
        if (l1Cache.get(address) != -1) {
            l1Hits++;
            return 1; // 1 cycle
        }
        
        // Try L2 cache
        if (l2Cache.get(address) != -1) {
            l2Hits++;
            l1Cache.put(address, 1); // Promote to L1
            return 10; // 10 cycles
        }
        
        // Try L3 cache
        if (l3Cache.get(address) != -1) {
            l3Hits++;
            l2Cache.put(address, 1); // Promote to L2
            l1Cache.put(address, 1); // Promote to L1
            return 50; // 50 cycles
        }
        
        // Memory access
        memoryAccesses++;
        l3Cache.put(address, 1);
        l2Cache.put(address, 1);
        l1Cache.put(address, 1);
        return 200; // 200 cycles
    }
    
    void printStats() const {
        int total = l1Hits + l2Hits + l3Hits + memoryAccesses;
        std::cout << "Cache Performance:" << std::endl;
        std::cout << "L1 Hit Rate: " << (double)l1Hits / total * 100 << "%" << std::endl;
        std::cout << "L2 Hit Rate: " << (double)l2Hits / total * 100 << "%" << std::endl;
        std::cout << "L3 Hit Rate: " << (double)l3Hits / total * 100 << "%" << std::endl;
        std::cout << "Memory Access Rate: " << (double)memoryAccesses / total * 100 << "%" << std::endl;
    }
};
```

## Notes

- **Queue Semantics**: LRU cache exhibits queue-like behavior with front (most recent) and back (least recent)
- **Iterator Invalidation**: Be careful with iterator-based approaches when using containers like deque
- **Memory Overhead**: HashMap + Deque approach has additional iterator storage overhead
- **Thread Safety**: Consider read-write locks for better performance in multi-threaded environments
- **Cache Warming**: Initial cold cache performance differs significantly from warm cache

## Related Problems

- [LeetCode 146. LRU Cache](https://leetcode.com/problems/lru-cache/)
- [LeetCode 460. LFU Cache](https://leetcode.com/problems/lfu-cache/)
- [LeetCode 432. All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/)
- [LeetCode 1206. Design Skiplist](https://leetcode.com/problems/design-skiplist/)
- [LeetCode 1670. Design Front Middle Back Queue](https://leetcode.com/problems/design-front-middle-back-queue/)

## Pattern: 09-Queue-with-Special-Properties

This problem demonstrates the Queue with Special Properties pattern by:

1. **FIFO with Exceptions**: LRU cache follows FIFO eviction but allows "jumping the queue" on access
2. **Queue Position Management**: Recent access moves items to front of queue (most recent position)
3. **Capacity-Bounded Queue**: Fixed-size queue that automatically evicts from back when full
4. **Dual Data Structure**: Combines queue operations (for ordering) with hash map (for O(1) access)

The queue-like behavior is evident in the access pattern management where the "front" represents most recently used items and the "back" represents candidates for eviction, making it a specialized queue with random access capabilities.
