# C++ Lambda Functions Quick Reference

**Syntax:** `[capture](parameters) -> return_type { body };`

## Capture Types
- `[]` - No capture
- `[x]` - Capture `x` by value
- `[&x]` - Capture `x` by reference  
- `[=]` - Capture all by value
- `[&]` - Capture all by reference
- `[=, &x]` - All by value, `x` by reference
- `[&, x]` - All by reference, `x` by value

## Basic Examples

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    // 1. Basic lambda
    auto greet = []() { std::cout << "Hello Lambda!\n"; };
    greet();
    
    // 2. With parameters
    auto add = [](int a, int b) { return a + b; };
    std::cout << add(3, 4) << "\n"; // 7
    
    // 3. Capture by value vs reference
    int x = 10;
    auto printX = [x]() { std::cout << "x: " << x << "\n"; };
    auto modifyX = [&x]() { x += 5; };
    
    printX(); // 10
    modifyX();
    std::cout << "Modified x: " << x << "\n"; // 15
    
    // 4. Explicit return type
    auto divide = [](double a, double b) -> double { return a / b; };
    std::cout << divide(10, 2) << "\n"; // 5.0
    
    // 5. Stored in std::function
    std::function<int(int, int)> multiply = [](int a, int b) { return a * b; };
    std::cout << multiply(4, 5) << "\n"; // 20
    
    return 0;
}
```

## STL Algorithms with Lambdas

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

int main() {
    std::vector<int> nums = {5, 2, 8, 1, 3, 2, 5};
    
    // 1. Sorting with custom comparator
    std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
    std::cout << "Descending: ";
    for (int n : nums) std::cout << n << " "; // 8 5 5 3 2 2 1
    std::cout << "\n";
    
    // 2. Transform elements
    std::transform(nums.begin(), nums.end(), nums.begin(), [](int n) { return n * 2; });
    
    // 3. Find first element > 10
    auto it = std::find_if(nums.begin(), nums.end(), [](int n) { return n > 10; });
    if (it != nums.end()) std::cout << "First > 10: " << *it << "\n";
    
    // 4. Remove elements > 6
    nums.erase(std::remove_if(nums.begin(), nums.end(), [](int n) { return n > 6; }), nums.end());
    
    // 5. Apply function to each element
    std::for_each(nums.begin(), nums.end(), [](int n) { std::cout << n << " "; });
    std::cout << "\n";
    
    return 0;
}
```

## Custom Containers with Lambdas

```cpp
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>

int main() {
    // 1. Set with custom comparator (descending order)
    auto cmp = [](int a, int b) { return a > b; };
    std::set<int, decltype(cmp)> mySet(cmp);
    mySet.insert({10, 5, 20});
    std::cout << "Set: ";
    for (int n : mySet) std::cout << n << " "; // 20 10 5
    std::cout << "\n";
    
    // 2. Map with custom key sorting
    std::map<int, std::string, decltype(cmp)> myMap(cmp);
    myMap[3] = "Three"; myMap[1] = "One"; myMap[2] = "Two";
    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << " ";
    } // 3: Three 2: Two 1: One
    std::cout << "\n";
    
    // 3. Priority queue with custom comparator
    auto pqCmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second; // Min heap by second element
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(pqCmp)> pq(pqCmp);
    
    pq.push({10, 2}); pq.push({20, 1}); pq.push({30, 3});
    while (!pq.empty()) {
        auto [val, priority] = pq.top();
        std::cout << "Val: " << val << ", Priority: " << priority << "\n";
        pq.pop();
    }
    
    return 0;
}
```

## Graph Traversal with Lambda

```cpp
#include <iostream>
#include <vector>
#include <functional>

int main() {
    int n = 5;
    std::vector<std::vector<int>> graph = {
        {1, 2},    // Node 0 connects to 1, 2
        {0, 3, 4}, // Node 1 connects to 0, 3, 4
        {0},       // Node 2 connects to 0
        {1},       // Node 3 connects to 1
        {1}        // Node 4 connects to 1
    };
    
    std::vector<bool> visited(n, false);
    
    // DFS using lambda with recursion
    std::function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        std::cout << node << " ";
        
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };
    
    std::cout << "DFS Traversal: ";
    dfs(0); // Output: 0 1 3 4 2
    std::cout << "\n";
    
    return 0;
}
```