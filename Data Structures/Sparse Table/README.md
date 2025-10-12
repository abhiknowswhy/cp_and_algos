# Sparse Table

Sparse Table Interview Questions - Comprehensive List

### **1. Basic Range Query Problems**

**Range Minimum Query (RMQ)**

* **Problem** : Given an array, answer multiple queries for minimum element in range [L, R]
* **LeetCode** : While no direct RMQ problem exists, similar concepts appear in:
* [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) (LC 303)
* [Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) (LC 307)

**Range Maximum Query**

* **Problem** : Find maximum element in given range
* **Variations** : Static vs dynamic arrays
* **LeetCode** : Concepts used in problems like Maximum Subarray variations

**Range GCD Query**

* **Problem** : Find GCD of elements in range [L, R]
* **Application** : Number theory problems

**Range LCM Query**

* **Problem** : Find LCM of elements in range [L, R]

### **2. Advanced Range Query Problems**

**Range Bitwise AND Query**

* **Problem** : Find bitwise AND of all elements in range
* **LeetCode** : Related to bit manipulation problems

**Range Bitwise OR Query**

* **Problem** : Find bitwise OR of all elements in range

**Range Bitwise XOR Query**

* **Problem** : Find XOR of elements in range

### **3. Practical Application Problems**

**Lowest Common Ancestor (LCA)**

* **Problem** : Find LCA of two nodes in a tree using sparse table
* **LeetCode** :
* [Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) (LC 236)
* [Lowest Common Ancestor of Deepest Leaves](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/) (LC 1123)

**Binary Lifting for Tree Queries**

* **Problem** : Answer ancestor queries efficiently
* **Applications** : Tree path queries, distance calculations

### **4. String-Related Sparse Table Problems**

**Range Character Frequency**

* **Problem** : Count frequency of characters in substring
* **LeetCode** : [Range Frequency Queries](https://leetcode.com/problems/range-frequency-queries/) (LC 2080)

**Longest Common Prefix Queries**

* **Problem** : Find LCP of suffixes in given ranges
* **Applications** : String matching, suffix array problems

### **5. 2D Sparse Table Problems**

**2D Range Minimum Query**

* **Problem** : Find minimum in 2D submatrix
* **Complexity** : O(log²(min(n,m))) per query after O(nm log n log m) preprocessing

**2D Range Maximum Query**

* **Problem** : Find maximum in 2D submatrix

### **6. Dynamic Programming Enhancement**

**Range DP Optimization**

* **Problem** : Use sparse table to optimize certain DP transitions
* **Applications** : Interval DP problems

### **7. Competitive Programming Specific**

**K-th Smallest in Range**

* **Problem** : Find k-th smallest element in range (using coordinate compression + sparse table)

**Range Mode Query**

* **Problem** : Find most frequent element in range

**Range Distinct Count**

* **Problem** : Count distinct elements in range

### **8. Implementation and Optimization Questions**

**Space-Optimized Sparse Table**

* **Problem** : Implement sparse table with reduced space complexity
* **Technique** : Only store necessary powers of 2

**Parallel Sparse Table Construction**

* **Problem** : Build sparse table using parallel processing

### **9. Hybrid Data Structure Problems**

**Sparse Table + Segment Tree**

* **Problem** : Combine both for different types of queries
* **Example** : Range updates with range minimum queries

**Sparse Table + Binary Search**

* **Problem** : Find first/last element satisfying condition in range
* **LeetCode** : Similar to [Minimum Interval to Include Each Query](https://leetcode.com/problems/minimum-interval-to-include-each-query/) (LC 1851)

### **10. Real-World Application Questions**

**Stock Price Analysis**

* **Problem** : Find minimum/maximum stock price in date ranges
* **Variation** : Multiple stock analysis

**Weather Data Queries**

* **Problem** : Temperature/rainfall queries for date ranges

**Sensor Network Monitoring**

* **Problem** : Query sensor readings across time intervals

### **Common Interview Patterns:**

1. **"Implement sparse table from scratch"**
2. **"Compare sparse table vs segment tree trade-offs"**
3. **"Handle edge cases in range queries"**
4. **"Optimize for specific query patterns"**
5. **"Extend to 2D or higher dimensions"**

### **Key LeetCode Problems Using Similar Concepts:**

* LC 303: Range Sum Query - Immutable
* LC 307: Range Sum Query - Mutable
* LC 236: Lowest Common Ancestor of a Binary Tree
* LC 2080: Range Frequency Queries
* LC 1851: Minimum Interval to Include Each Query
* LC 1123: Lowest Common Ancestor of Deepest Leaves

The sparse table approach is particularly valuable for problems requiring fast range queries on static arrays where the operation is idempotent (like min, max, gcd, bitwise operations). While not every problem explicitly mentions "sparse table," the underlying technique is often the optimal solution for these range query scenarios.
