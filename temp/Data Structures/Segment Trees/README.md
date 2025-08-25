# Comprehensive List of Segment Tree Interview Questions

## 1. Basic Range Query Problems

### Range Sum Queries

* **Range Sum Query - Mutable** - [LeetCode 307](https://leetcode.com/problems/range-sum-query-mutable/)
* **Range Sum Query 2D - Mutable** - [LeetCode 308](https://leetcode.com/problems/range-sum-query-2d-mutable/) (Premium)
* **Count of Range Sum** - [LeetCode 327](https://leetcode.com/problems/count-of-range-sum/)

### Range Minimum/Maximum Queries

* **Range Minimum Query** (Classic problem, not on LeetCode but frequently asked)
* **Range Maximum Query** (Classic problem, not on LeetCode but frequently asked)
* **Sliding Window Maximum** - [LeetCode 239](https://leetcode.com/problems/sliding-window-maximum/) (Can be solved with segment tree)

## 2. Range Update Problems

### Lazy Propagation

* **Range Sum Query - Mutable with Range Updates** (Classic lazy propagation problem)
* **Range Addition** - [LeetCode 370](https://leetcode.com/problems/range-addition/) (Premium)
* **Corporate Flight Bookings** - [LeetCode 1109](https://leetcode.com/problems/corporate-flight-bookings/)
* **Car Pooling** - [LeetCode 1094](https://leetcode.com/problems/car-pooling/)

### Range Set/Add Operations

* **My Calendar II** - [LeetCode 731](https://leetcode.com/problems/my-calendar-ii/) (Can use segment tree with lazy propagation)
* **My Calendar III** - [LeetCode 732](https://leetcode.com/problems/my-calendar-iii/)

## 3. Frequency and Counting Problems

### Element Counting

* **Count of Smaller Numbers After Self** - [LeetCode 315](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
* **Reverse Pairs** - [LeetCode 493](https://leetcode.com/problems/reverse-pairs/)
* **Create Sorted Array through Instructions** - [LeetCode 1649](https://leetcode.com/problems/create-sorted-array-through-instructions/)

### Frequency Queries

* **Online Majority Element In Subarray** - [LeetCode 1157](https://leetcode.com/problems/online-majority-element-in-subarray/) (Premium)

## 4. Dynamic Programming with Segment Trees

### Optimization Problems

* **Falling Squares** - [LeetCode 699](https://leetcode.com/problems/falling-squares/)
* **The Skyline Problem** - [LeetCode 218](https://leetcode.com/problems/the-skyline-problem/) (Can be solved with segment tree)
* **Perfect Rectangle** - [LeetCode 391](https://leetcode.com/problems/perfect-rectangle/) (Advanced segment tree application)

## 5. 2D Segment Trees / Quad Trees

### 2D Range Queries

* **Range Sum Query 2D - Mutable** - [LeetCode 308](https://leetcode.com/problems/range-sum-query-2d-mutable/) (Premium)
* **Quad Tree Intersection** - [LeetCode 558](https://leetcode.com/problems/quad-tree-intersection/)
* **Construct Quad Tree** - [LeetCode 427](https://leetcode.com/problems/construct-quad-tree/)

## 6. Advanced Segment Tree Applications

### Persistent Segment Trees

* **Kth Smallest Element in a Range** (Classic problem, not on LeetCode)
* **Number of Different Integers After Reverse Operations** (Advanced interview question)

### Segment Tree with Coordinate Compression

* **Count of Range Sum** - [LeetCode 327](https://leetcode.com/problems/count-of-range-sum/)
* **Reverse Pairs** - [LeetCode 493](https://leetcode.com/problems/reverse-pairs/)

## 7. Segment Tree Variants

### Binary Indexed Tree (Fenwick Tree) Related

* **Range Sum Query - Mutable** - [LeetCode 307](https://leetcode.com/problems/range-sum-query-mutable/)
* **Count of Smaller Numbers After Self** - [LeetCode 315](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)

### Merge Sort Tree

* **Count of Range Sum** - [LeetCode 327](https://leetcode.com/problems/count-of-range-sum/)

## 8. String/Character Based Segment Trees

### Character Frequency Queries

* **Shortest Subarray to be Removed to Make Array Sorted** - [LeetCode 1574](https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/) (Can use segment tree approach)

## 9. Graph-Related Segment Tree Problems

### Heavy-Light Decomposition

* **Path queries in trees** (Advanced competitive programming concept)
* **Tree path sum queries** (Not typically on LeetCode but asked in advanced interviews)

## 10. Real-time Data Stream Problems

### Online Algorithms

* **Find Median from Data Stream** - [LeetCode 295](https://leetcode.com/problems/find-median-from-data-stream/) (Can be solved with segment tree)
* **Sliding Window Median** - [LeetCode 480](https://leetcode.com/problems/sliding-window-median/)

## 11. Interval-Based Problems

### Interval Scheduling

* **My Calendar I** - [LeetCode 729](https://leetcode.com/problems/my-calendar-i/)
* **My Calendar II** - [LeetCode 731](https://leetcode.com/problems/my-calendar-ii/)
* **My Calendar III** - [LeetCode 732](https://leetcode.com/problems/my-calendar-iii/)
* **Interval List Intersections** - [LeetCode 986](https://leetcode.com/problems/interval-list-intersections/)

## 12. Matrix-Based Segment Tree Problems

### 2D Matrix Operations

* **Maximal Rectangle** - [LeetCode 85](https://leetcode.com/problems/maximal-rectangle/) (Advanced segment tree application)
* **Largest Rectangle in Histogram** - [LeetCode 84](https://leetcode.com/problems/largest-rectangle-in-histogram/) (Can use segment tree for RMQ)

## 13. Company-Specific Advanced Problems

### Google/Facebook Level

* **Maximum Gap** - [LeetCode 164](https://leetcode.com/problems/maximum-gap/) (Can be solved with segment tree)
* **Contains Duplicate III** - [LeetCode 220](https://leetcode.com/problems/contains-duplicate-iii/) (Can use segment tree with coordinate compression)

### Amazon/Microsoft Level

* **Subarrays with K Different Integers** - [LeetCode 992](https://leetcode.com/problems/subarrays-with-k-different-integers/) (Advanced segment tree application)

## 14. Mathematical Segment Tree Problems

### GCD/LCM Queries

* **Range GCD Queries** (Classic problem, frequently asked but not on LeetCode)
* **Range LCM Queries** (Advanced mathematical segment tree problem)

### Modular Arithmetic

* **Range Modular Queries** (Asked in mathematical programming contests)

## Key Concepts to Master:

1. **Basic Segment Tree Construction and Queries**
2. **Lazy Propagation for Range Updates**
3. **Coordinate Compression**
4. **2D Segment Trees**
5. **Persistent Segment Trees**
6. **Segment Tree with Binary Search**
7. **Memory Optimization Techniques**
8. **Time Complexity Analysis**

## Difficulty Levels:

* **Easy** : LeetCode 307, 729
* **Medium** : LeetCode 315, 327, 493, 731, 732
* **Hard** : LeetCode 218, 308, 1649, 699

## Interview Tips:

1. Always clarify if updates are point updates or range updates
2. Ask about the constraints (array size, number of queries)
3. Consider if coordinate compression is needed
4. Think about lazy propagation for range updates
5. Consider space-time tradeoffs between different approaches
6. Be prepared to implement both recursive and iterative versions
