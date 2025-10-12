# Bipartite Matching Algorithm (Hungarian Algorithm)

## Overview

The Hungarian algorithm is an optimization algorithm that solves the assignment problem in polynomial time. It was developed and published by Harold Kuhn in 1955, who named it the "Hungarian method" as it was based on earlier work of two Hungarian mathematicians: Dénes Kőnig and Jenő Egerváry.

Key concepts:
- **Bipartite Graph**: A graph whose vertices can be divided into two disjoint sets such that every edge connects a vertex in the first set to one in the second set.
- **Maximum Matching**: A matching with the largest possible number of edges.
- **Alternating Path**: A path in which edges alternate between being in the matching and not in the matching.
- **Augmenting Path**: An alternating path that starts and ends with vertices that are not matched.

## Real-world Applications

1. **Marriage Problem (Stable Marriage)**: Matching a set of men with a set of women based on preferences.
2. **Personnel Assignment**: Assigning workers to jobs optimally.
3. **Network Flow**: Maximum bipartite matching is a special case of the maximum flow problem.
4. **Job Scheduling**: Assigning tasks to processors to minimize completion time.

## Algorithm Explanation

The Hungarian algorithm for bipartite matching follows these steps:

1. Start with any initial matching (often empty).
2. Find an augmenting path in the graph.
3. Use this path to increase the size of the matching by one.
4. Repeat steps 2-3 until no more augmenting paths can be found.

The key insight is that we can find augmenting paths using a modified DFS or BFS search.

## C++ Implementation

Below is a C++ implementation of the Hungarian algorithm for bipartite matching:

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class BipartiteMatching {
private:
    int n, m; // n: left side vertices, m: right side vertices
    vector<vector<int>> graph; // Adjacency list representation
    vector<int> matching; // Stores which vertex on right is matched to which vertex on left
    vector<bool> visited; // Used in the DFS

    // DFS to find an augmenting path
    bool dfs(int u) {
        if (visited[u]) return false;
        visited[u] = true;
        
        for (int v : graph[u]) {
            // If v is not matched or we can find an augmenting path through v's match
            if (matching[v] == -1 || dfs(matching[v])) {
                matching[v] = u;
                return true;
            }
        }
        return false;
    }

public:
    BipartiteMatching(int left, int right) : n(left), m(right) {
        graph.resize(left);
        matching.assign(right, -1);  // -1 means not matched
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    int findMaxMatching() {
        int maxMatching = 0;
        
        // Try to find a match for each vertex on the left side
        for (int u = 0; u < n; u++) {
            visited.assign(n, false);
            if (dfs(u)) {
                maxMatching++;
            }
        }
        
        return maxMatching;
    }

    // Returns the matching pairs
    vector<pair<int, int>> getMatchingPairs() {
        vector<pair<int, int>> pairs;
        for (int v = 0; v < m; v++) {
            if (matching[v] != -1) {
                pairs.emplace_back(matching[v], v);
            }
        }
        return pairs;
    }
};

// Example usage
int main() {
    // Create a bipartite graph with 4 vertices on the left and 4 on the right
    BipartiteMatching bm(4, 4);
    
    // Add edges
    bm.addEdge(0, 0);
    bm.addEdge(0, 1);
    bm.addEdge(1, 0);
    bm.addEdge(1, 2);
    bm.addEdge(2, 1);
    bm.addEdge(2, 2);
    bm.addEdge(2, 3);
    bm.addEdge(3, 2);
    
    int maxMatches = bm.findMaxMatching();
    cout << "Maximum number of matchings: " << maxMatches << endl;
    
    auto pairs = bm.getMatchingPairs();
    cout << "Matching pairs (left, right):" << endl;
    for (auto& pair : pairs) {
        cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    }
    
    return 0;
}
```

## Hopcroft-Karp Algorithm

A more efficient algorithm for bipartite matching is the Hopcroft-Karp algorithm, which runs in O(E√V) time:

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class HopcroftKarp {
private:
    int n, m; // n: left side vertices, m: right side vertices
    vector<vector<int>> graph;
    vector<int> matching_left, matching_right;
    vector<int> dist; // For BFS
    const int INF = INT_MAX;

    // BFS to find augmenting paths
    bool bfs() {
        queue<int> q;
        dist.assign(n + 1, INF);
        
        // Add all unmatched vertices from left side to the queue
        for (int u = 0; u < n; u++) {
            if (matching_left[u] == -1) {
                dist[u] = 0;
                q.push(u);
            }
        }
        dist[n] = INF;  // n is used as a dummy node
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (u != n) {
                for (int v : graph[u]) {
                    // Match on right side
                    int u2 = matching_right[v];
                    // If this vertex on the right is not matched or can lead to an augmenting path
                    if (u2 == -1 || (dist[u2] == INF && dist[u] + 1 < dist[n])) {
                        dist[u2 == -1 ? n : u2] = dist[u] + 1;
                        if (u2 == -1) dist[n] = dist[u] + 1;
                        else q.push(u2);
                    }
                }
            }
        }
        
        return dist[n] != INF; // Return true if an augmenting path was found
    }
    
    // DFS to find an augmenting path
    bool dfs(int u) {
        if (u == n) return true;
        
        for (int v : graph[u]) {
            int u2 = matching_right[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                matching_right[v] = u;
                matching_left[u] = v;
                return true;
            }
        }
        
        dist[u] = INF;
        return false;
    }

public:
    HopcroftKarp(int left, int right) : n(left), m(right) {
        graph.resize(left);
        matching_left.assign(left, -1);  // -1 means not matched
        matching_right.assign(right, -1);
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    int findMaxMatching() {
        int maxMatching = 0;
        
        // Repeatedly find augmenting paths
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (matching_left[u] == -1 && dfs(u)) {
                    maxMatching++;
                }
            }
        }
        
        return maxMatching;
    }

    // Returns the matching pairs
    vector<pair<int, int>> getMatchingPairs() {
        vector<pair<int, int>> pairs;
        for (int u = 0; u < n; u++) {
            if (matching_left[u] != -1) {
                pairs.emplace_back(u, matching_left[u]);
            }
        }
        return pairs;
    }
};

// Example usage
int main() {
    // Create a bipartite graph with 4 vertices on the left and 4 on the right
    HopcroftKarp hk(4, 4);
    
    // Add edges
    hk.addEdge(0, 0);
    hk.addEdge(0, 1);
    hk.addEdge(1, 0);
    hk.addEdge(1, 2);
    hk.addEdge(2, 1);
    hk.addEdge(2, 2);
    hk.addEdge(2, 3);
    hk.addEdge(3, 2);
    
    int maxMatches = hk.findMaxMatching();
    cout << "Maximum number of matchings: " << maxMatches << endl;
    
    auto pairs = hk.getMatchingPairs();
    cout << "Matching pairs (left, right):" << endl;
    for (auto& pair : pairs) {
        cout << "(" << pair.first << ", " << pair.second << ")" << endl;
    }
    
    return 0;
}
```

## Complexity Analysis

- **Time Complexity**:
  - Basic Hungarian Algorithm: O(V * E)
  - Hopcroft-Karp Algorithm: O(E * √V)
- **Space Complexity**: O(V + E)

## Related LeetCode Problems

1. **[LeetCode 1820 - Maximum Number of Accepted Invitations](https://leetcode.com/problems/maximum-number-of-accepted-invitations/)**: This problem directly asks for the maximum bipartite matching.

2. **[LeetCode 1066 - Campus Bikes II](https://leetcode.com/problems/campus-bikes-ii/)**: Can be solved using bipartite matching techniques.

3. **[LeetCode 1125 - Smallest Sufficient Team](https://leetcode.com/problems/smallest-sufficient-team/)**: While not directly a bipartite matching problem, the concepts are related.

4. **[LeetCode 1947 - Maximum Compatibility Score Sum](https://leetcode.com/problems/maximum-compatibility-score-sum/)**: This is an assignment problem that can be solved using the Hungarian algorithm.

5. **[LeetCode 1595 - Minimum Cost to Connect Two Groups of Points](https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/)**: A variation that can use bipartite matching concepts.

## References

1. Kuhn, H. W. (1955). "The Hungarian method for the assignment problem". Naval Research Logistics Quarterly, 2: 83–97.
2. Kőnig, D. (1931). "Gráfok és mátrixok". Matematikai és Fizikai Lapok, 38: 116–119.
3. Hopcroft, J. E.; Karp, R. M. (1973). "An n^5/2 algorithm for maximum matchings in bipartite graphs". SIAM Journal on Computing, 2(4): 225–231.

## Additional Notes

- For weighted bipartite matching (where edges have weights and we want to maximize or minimize the total weight), the Hungarian algorithm can be modified to solve this problem as well.
- In practice, the Hopcroft-Karp algorithm is usually preferred due to its better asymptotic runtime, especially for sparse graphs.
