# Web Crawler Multithreading - Complex Producer-Consumer System
## LeetCode Problem 1242

**Difficulty:** Medium  
**Category:** Producer-Consumer, Multithreading, Graph Traversal  
**Pattern:** Multi-threaded BFS with shared work queue and deduplication

## Problem Description

Given a URL `startUrl` and an interface `HtmlParser`, implement a **multi-threaded web crawler** to crawl all links that are under the **same hostname** as `startUrl`.

Return all URLs obtained by your web crawler in **any order**.

Your crawler should:
- Start from the given URL and call `HtmlParser.getUrls(url)` to get all URLs from a webpage
- Do not crawl the same link twice
- Explore only the URLs under the same hostname as `startUrl`
- Use multiple threads for concurrent crawling

**Constraints:**
- Multiple threads must work concurrently
- Thread-safe data structures required
- No duplicate URL processing
- Same hostname restriction

## Real-World Applications

1. **Search Engine Indexing**: Distributed web crawling systems
2. **Website Monitoring**: Parallel health checking and content monitoring
3. **Data Mining**: Concurrent web scraping operations
4. **Link Validation**: Multi-threaded broken link detection
5. **Content Discovery**: Parallel exploration of website structures

## Core Algorithm Approaches

### Approach 1: Thread Pool with Blocking Queue

Classic producer-consumer with worker threads:

```cpp
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <unordered_set>
#include <vector>
#include <string>

class HtmlParser {
public:
    virtual vector<string> getUrls(string url) = 0;
};

class WebCrawler {
private:
    queue<string> urlQueue;
    unordered_set<string> visited;
    vector<string> result;
    mutex queueMutex;
    mutex visitedMutex;
    mutex resultMutex;
    condition_variable cv;
    bool finished = false;
    int activeWorkers = 0;
    
    string getHostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find("/", start);
        if (end == string::npos) end = url.length();
        return url.substr(start, end - start);
    }
    
    void workerThread(HtmlParser& htmlParser, const string& hostname) {
        while (true) {
            string currentUrl;
            
            // Get next URL from queue
            {
                unique_lock<mutex> lock(queueMutex);
                cv.wait(lock, [this] { return !urlQueue.empty() || finished; });
                
                if (finished && urlQueue.empty()) {
                    break;
                }
                
                if (!urlQueue.empty()) {
                    currentUrl = urlQueue.front();
                    urlQueue.pop();
                    activeWorkers++;
                }
            }
            
            if (!currentUrl.empty()) {
                // Process current URL
                vector<string> urls = htmlParser.getUrls(currentUrl);
                
                // Add current URL to result
                {
                    lock_guard<mutex> lock(resultMutex);
                    result.push_back(currentUrl);
                }
                
                // Add new URLs to queue
                {
                    lock_guard<mutex> queueLock(queueMutex);
                    lock_guard<mutex> visitedLock(visitedMutex);
                    
                    for (const string& url : urls) {
                        if (getHostname(url) == hostname && visited.find(url) == visited.end()) {
                            visited.insert(url);
                            urlQueue.push(url);
                        }
                    }
                    
                    activeWorkers--;
                    
                    // Check if all work is done
                    if (urlQueue.empty() && activeWorkers == 0) {
                        finished = true;
                    }
                }
                
                cv.notify_all();
            }
        }
    }
    
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        string hostname = getHostname(startUrl);
        
        // Initialize
        urlQueue.push(startUrl);
        visited.insert(startUrl);
        
        // Create worker threads
        const int NUM_THREADS = 4;
        vector<thread> workers;
        
        for (int i = 0; i < NUM_THREADS; i++) {
            workers.emplace_back(&WebCrawler::workerThread, this, 
                               ref(htmlParser), hostname);
        }
        
        // Wait for completion
        for (auto& worker : workers) {
            worker.join();
        }
        
        return result;
    }
};
```

**Time Complexity:** O(V + E) where V is URLs, E is links  
**Space Complexity:** O(V) for visited set and result

### Approach 2: Lock-Free Atomic Operations

High-performance approach using atomics:

```cpp
#include <atomic>
#include <concurrent_queue.h>  // Assuming thread-safe queue

class AtomicWebCrawler {
private:
    concurrent_queue<string> urlQueue;
    unordered_set<string> visited;
    vector<string> result;
    mutex visitedMutex;
    mutex resultMutex;
    atomic<int> activeWorkers{0};
    atomic<bool> shouldStop{false};
    
    string getHostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find("/", start);
        if (end == string::npos) end = url.length();
        return url.substr(start, end - start);
    }
    
    void workerThread(HtmlParser& htmlParser, const string& hostname) {
        while (!shouldStop.load()) {
            string currentUrl;
            
            if (urlQueue.try_pop(currentUrl)) {
                activeWorkers.fetch_add(1);
                
                // Process URL
                vector<string> urls = htmlParser.getUrls(currentUrl);
                
                // Add to result
                {
                    lock_guard<mutex> lock(resultMutex);
                    result.push_back(currentUrl);
                }
                
                // Add new URLs
                {
                    lock_guard<mutex> lock(visitedMutex);
                    for (const string& url : urls) {
                        if (getHostname(url) == hostname && visited.find(url) == visited.end()) {
                            visited.insert(url);
                            urlQueue.push(url);
                        }
                    }
                }
                
                activeWorkers.fetch_sub(1);
            } else {
                // No work available, check if we should stop
                if (activeWorkers.load() == 0) {
                    shouldStop.store(true);
                }
                this_thread::sleep_for(chrono::milliseconds(1));
            }
        }
    }
    
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        string hostname = getHostname(startUrl);
        
        urlQueue.push(startUrl);
        visited.insert(startUrl);
        
        const int NUM_THREADS = thread::hardware_concurrency();
        vector<thread> workers;
        
        for (int i = 0; i < NUM_THREADS; i++) {
            workers.emplace_back(&AtomicWebCrawler::workerThread, this, 
                               ref(htmlParser), hostname);
        }
        
        for (auto& worker : workers) {
            worker.join();
        }
        
        return result;
    }
};
```

### Approach 3: Work-Stealing Implementation

Advanced approach with work stealing between threads:

```cpp
class WorkStealingCrawler {
private:
    struct WorkerData {
        queue<string> localQueue;
        mutex queueMutex;
        atomic<bool> hasWork{false};
    };
    
    vector<unique_ptr<WorkerData>> workers;
    unordered_set<string> visited;
    vector<string> result;
    mutex visitedMutex;
    mutex resultMutex;
    atomic<int> activeWorkers{0};
    atomic<bool> finished{false};
    
    string getHostname(const string& url) {
        size_t start = url.find("://") + 3;
        size_t end = url.find("/", start);
        if (end == string::npos) end = url.length();
        return url.substr(start, end - start);
    }
    
    string stealWork(int workerIndex) {
        // Try to steal from other workers
        for (int i = 0; i < workers.size(); i++) {
            if (i == workerIndex) continue;
            
            lock_guard<mutex> lock(workers[i]->queueMutex);
            if (!workers[i]->localQueue.empty()) {
                string url = workers[i]->localQueue.front();
                workers[i]->localQueue.pop();
                
                if (workers[i]->localQueue.empty()) {
                    workers[i]->hasWork.store(false);
                }
                
                return url;
            }
        }
        return "";
    }
    
    void workerThread(int workerIndex, HtmlParser& htmlParser, const string& hostname) {
        WorkerData& worker = *workers[workerIndex];
        
        while (!finished.load()) {
            string currentUrl;
            
            // Try local queue first
            {
                lock_guard<mutex> lock(worker.queueMutex);
                if (!worker.localQueue.empty()) {
                    currentUrl = worker.localQueue.front();
                    worker.localQueue.pop();
                    
                    if (worker.localQueue.empty()) {
                        worker.hasWork.store(false);
                    }
                }
            }
            
            // If no local work, try stealing
            if (currentUrl.empty()) {
                currentUrl = stealWork(workerIndex);
            }
            
            if (!currentUrl.empty()) {
                activeWorkers.fetch_add(1);
                
                // Process URL
                vector<string> urls = htmlParser.getUrls(currentUrl);
                
                // Add to result
                {
                    lock_guard<mutex> lock(resultMutex);
                    result.push_back(currentUrl);
                }
                
                // Distribute new URLs
                {
                    lock_guard<mutex> visitedLock(visitedMutex);
                    
                    for (const string& url : urls) {
                        if (getHostname(url) == hostname && visited.find(url) == visited.end()) {
                            visited.insert(url);
                            
                            // Add to least loaded worker
                            int targetWorker = workerIndex;
                            size_t minQueueSize = worker.localQueue.size();
                            
                            for (int i = 0; i < workers.size(); i++) {
                                lock_guard<mutex> lock(workers[i]->queueMutex);
                                if (workers[i]->localQueue.size() < minQueueSize) {
                                    minQueueSize = workers[i]->localQueue.size();
                                    targetWorker = i;
                                }
                            }
                            
                            lock_guard<mutex> lock(workers[targetWorker]->queueMutex);
                            workers[targetWorker]->localQueue.push(url);
                            workers[targetWorker]->hasWork.store(true);
                        }
                    }
                }
                
                activeWorkers.fetch_sub(1);
            } else {
                // No work available, check termination condition
                bool hasAnyWork = false;
                for (const auto& w : workers) {
                    if (w->hasWork.load()) {
                        hasAnyWork = true;
                        break;
                    }
                }
                
                if (!hasAnyWork && activeWorkers.load() == 0) {
                    finished.store(true);
                }
                
                this_thread::sleep_for(chrono::milliseconds(1));
            }
        }
    }
    
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        string hostname = getHostname(startUrl);
        
        const int NUM_THREADS = thread::hardware_concurrency();
        workers.resize(NUM_THREADS);
        
        for (int i = 0; i < NUM_THREADS; i++) {
            workers[i] = make_unique<WorkerData>();
        }
        
        // Initialize first worker with start URL
        workers[0]->localQueue.push(startUrl);
        workers[0]->hasWork.store(true);
        visited.insert(startUrl);
        
        vector<thread> threads;
        for (int i = 0; i < NUM_THREADS; i++) {
            threads.emplace_back(&WorkStealingCrawler::workerThread, this, 
                               i, ref(htmlParser), hostname);
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        return result;
    }
};
```

## Detailed Algorithm Analysis

### Synchronization Challenges

1. **Work Distribution**: Efficiently distributing URLs among threads
2. **Deduplication**: Thread-safe visited set management
3. **Termination Detection**: Knowing when all work is complete
4. **Load Balancing**: Preventing thread starvation

### Key Design Decisions

- **Queue Strategy**: Shared queue vs per-thread queues
- **Locking Granularity**: Coarse-grained vs fine-grained locks
- **Work Stealing**: Dynamic load balancing mechanism
- **Termination Logic**: Detecting completion in distributed system

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Scalability |
|----------|----------------|------------------|-------------|
| Thread Pool | O(V + E) | O(V) | Medium |
| Atomic Operations | O(V + E) | O(V) | High |
| Work Stealing | O(V + E) | O(V) | Very High |

## Test Cases and Usage Examples

### Example 1: Basic Web Crawling
```cpp
class MockHtmlParser : public HtmlParser {
private:
    unordered_map<string, vector<string>> graph;
    
public:
    MockHtmlParser() {
        graph["http://news.yahoo.com"] = {
            "http://news.yahoo.com/news",
            "http://news.yahoo.com/sports"
        };
        graph["http://news.yahoo.com/news"] = {
            "http://news.yahoo.com/weather"
        };
        graph["http://news.yahoo.com/sports"] = {};
        graph["http://news.yahoo.com/weather"] = {};
    }
    
    vector<string> getUrls(string url) override {
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate network delay
        return graph.count(url) ? graph[url] : vector<string>{};
    }
};

void testBasicCrawling() {
    WebCrawler crawler;
    MockHtmlParser parser;
    
    auto start = chrono::high_resolution_clock::now();
    vector<string> result = crawler.crawl("http://news.yahoo.com", parser);
    auto end = chrono::high_resolution_clock::now();
    
    cout << "Crawled " << result.size() << " URLs:" << endl;
    for (const string& url : result) {
        cout << "  " << url << endl;
    }
    
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;
}
```

### Example 2: Performance Comparison
```cpp
void comparePerformance() {
    MockHtmlParser parser;
    string startUrl = "http://news.yahoo.com";
    
    cout << "Performance Comparison:" << endl;
    
    // Single-threaded baseline
    {
        auto start = chrono::high_resolution_clock::now();
        
        // Single-threaded implementation (for comparison)
        vector<string> result;
        queue<string> q;
        unordered_set<string> visited;
        
        q.push(startUrl);
        visited.insert(startUrl);
        
        while (!q.empty()) {
            string url = q.front();
            q.pop();
            result.push_back(url);
            
            vector<string> urls = parser.getUrls(url);
            for (const string& newUrl : urls) {
                string hostname = getHostname(newUrl);
                if (hostname == getHostname(startUrl) && visited.find(newUrl) == visited.end()) {
                    visited.insert(newUrl);
                    q.push(newUrl);
                }
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Single-threaded: " << duration.count() << " ms" << endl;
    }
    
    // Multi-threaded implementations
    {
        auto start = chrono::high_resolution_clock::now();
        WebCrawler crawler;
        vector<string> result = crawler.crawl(startUrl, parser);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Thread Pool: " << duration.count() << " ms" << endl;
    }
    
    {
        auto start = chrono::high_resolution_clock::now();
        WorkStealingCrawler crawler;
        vector<string> result = crawler.crawl(startUrl, parser);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Work Stealing: " << duration.count() << " ms" << endl;
    }
}
```

### Example 3: Large-Scale Simulation
```cpp
void simulateLargeWebsite() {
    // Create a large simulated website
    class LargeWebsiteParser : public HtmlParser {
    private:
        const int PAGES_PER_LEVEL = 10;
        const int MAX_DEPTH = 4;
        
    public:
        vector<string> getUrls(string url) override {
            // Simulate network delay
            this_thread::sleep_for(chrono::milliseconds(50 + rand() % 100));
            
            vector<string> urls;
            
            // Extract depth from URL (simplified)
            size_t depth = count(url.begin(), url.end(), '/') - 2;
            
            if (depth < MAX_DEPTH) {
                for (int i = 0; i < PAGES_PER_LEVEL; i++) {
                    urls.push_back(url + "/page" + to_string(i));
                }
            }
            
            return urls;
        }
    };
    
    LargeWebsiteParser parser;
    WorkStealingCrawler crawler;
    
    auto start = chrono::high_resolution_clock::now();
    vector<string> result = crawler.crawl("http://example.com", parser);
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::seconds>(end - start);
    cout << "Crawled " << result.size() << " pages in " << duration.count() << " seconds" << endl;
    
    // Calculate expected total pages
    int expectedPages = 0;
    for (int level = 0; level <= 4; level++) {
        expectedPages += pow(PAGES_PER_LEVEL, level);
    }
    cout << "Expected pages: " << expectedPages << endl;
}
```

## Advanced Features and Extensions

### Rate Limiting and Politeness
```cpp
class PoliteCrawler : public WebCrawler {
private:
    unordered_map<string, chrono::steady_clock::time_point> lastRequestTime;
    mutex rateLimitMutex;
    chrono::milliseconds minDelay{1000}; // 1 second between requests to same host
    
    void enforceRateLimit(const string& hostname) {
        lock_guard<mutex> lock(rateLimitMutex);
        
        auto now = chrono::steady_clock::now();
        auto& lastTime = lastRequestTime[hostname];
        
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastTime);
        if (elapsed < minDelay) {
            this_thread::sleep_for(minDelay - elapsed);
        }
        
        lastRequestTime[hostname] = chrono::steady_clock::now();
    }
    
public:
    // Override worker thread to add rate limiting
    void politeWorkerThread(HtmlParser& htmlParser, const string& hostname) {
        // ... existing worker logic ...
        
        // Before making request:
        enforceRateLimit(hostname);
        vector<string> urls = htmlParser.getUrls(currentUrl);
        
        // ... rest of processing ...
    }
};
```

### Monitoring and Statistics
```cpp
class CrawlerMonitor {
private:
    atomic<int> pagesProcessed{0};
    atomic<int> linksFound{0};
    atomic<int> activeThreads{0};
    chrono::steady_clock::time_point startTime;
    
public:
    void start() {
        startTime = chrono::steady_clock::now();
    }
    
    void recordPageProcessed() {
        pagesProcessed.fetch_add(1);
    }
    
    void recordLinksFound(int count) {
        linksFound.fetch_add(count);
    }
    
    void threadStarted() {
        activeThreads.fetch_add(1);
    }
    
    void threadFinished() {
        activeThreads.fetch_sub(1);
    }
    
    void printStats() {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - startTime);
        
        cout << "Crawler Statistics:" << endl;
        cout << "  Pages processed: " << pagesProcessed.load() << endl;
        cout << "  Links found: " << linksFound.load() << endl;
        cout << "  Active threads: " << activeThreads.load() << endl;
        cout << "  Runtime: " << elapsed.count() << " seconds" << endl;
        
        if (elapsed.count() > 0) {
            cout << "  Pages/second: " << (pagesProcessed.load() / elapsed.count()) << endl;
        }
    }
};
```

### Error Handling and Resilience
```cpp
class ResilientCrawler {
private:
    int maxRetries = 3;
    chrono::milliseconds retryDelay{1000};
    
    vector<string> safeGetUrls(HtmlParser& parser, const string& url) {
        for (int attempt = 0; attempt < maxRetries; attempt++) {
            try {
                return parser.getUrls(url);
            } catch (const exception& e) {
                cout << "Error crawling " << url << ": " << e.what() 
                     << " (attempt " << (attempt + 1) << "/" << maxRetries << ")" << endl;
                
                if (attempt < maxRetries - 1) {
                    this_thread::sleep_for(retryDelay);
                }
            }
        }
        
        cout << "Failed to crawl " << url << " after " << maxRetries << " attempts" << endl;
        return {};
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **Circular Links**: Handling cycles in website structure
2. **Network Failures**: Robust error handling and retries
3. **Rate Limiting**: Respecting server rate limits
4. **Memory Constraints**: Managing large crawl queues
5. **Dynamic Content**: Handling JavaScript-generated links

### Implementation Gotchas
- **Hostname Extraction**: Proper URL parsing for domain comparison
- **Thread Termination**: Clean shutdown without hanging threads
- **Memory Leaks**: Proper cleanup of thread-local storage
- **Race Conditions**: Atomic operations for shared counters

## Pattern Recognition: Producer-Consumer

This problem exemplifies **Producer-Consumer** coordination through:

1. **Work Queue Management**: Threads producing and consuming URLs
2. **Resource Sharing**: Multiple threads accessing shared data structures
3. **Load Balancing**: Distributing work efficiently among threads
4. **Synchronization**: Coordinating access to shared state

### Related Distributed Systems Problems
- **Map-Reduce**: Distributed computation patterns
- **Actor Model**: Message-passing concurrency
- **Pipeline Processing**: Multi-stage parallel processing

## Performance Optimization Strategies

### Memory Optimization
- **URL Interning**: Reduce memory usage for duplicate strings
- **Bloom Filters**: Probabilistic duplicate detection
- **Compressed URLs**: Store URLs in compressed format

### Network Optimization
- **Connection Pooling**: Reuse HTTP connections
- **Batch Requests**: Group requests to same server
- **Adaptive Timeouts**: Dynamic timeout adjustment

### CPU Optimization
- **Lock-Free Data Structures**: Minimize synchronization overhead
- **NUMA Awareness**: Consider CPU topology for thread placement
- **Cache-Friendly Access**: Optimize memory access patterns

## Related LeetCode Problems

1. **[LeetCode 1117] Building H2O** - Multi-threaded resource coordination
2. **[LeetCode 1188] Design Bounded Blocking Queue** - Producer-consumer basics
3. **[LeetCode 1115] Print FooBar Alternately** - Thread synchronization
4. **[LeetCode 207] Course Schedule** - Graph traversal algorithms

## Summary

The Web Crawler Multithreading problem demonstrates advanced Producer-Consumer patterns:

- **Distributed Work Processing**: Multiple threads collaboratively processing tasks
- **Complex Synchronization**: Managing multiple shared data structures safely
- **Performance Optimization**: Balancing correctness with speed and scalability
- **Real-World Complexity**: Handling network failures, rate limiting, and resource management

Key insights for distributed systems programming:
- **Work Distribution**: Choose appropriate load balancing strategies
- **Fault Tolerance**: Build resilience into distributed processing
- **Monitoring**: Track performance and identify bottlenecks
- **Resource Management**: Handle memory and network resources efficiently

This pattern is fundamental to understanding large-scale distributed systems, web crawling technologies, and concurrent data processing frameworks used in search engines, data mining, and content discovery systems.
