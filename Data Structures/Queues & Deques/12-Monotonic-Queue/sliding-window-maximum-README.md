# Sliding Window Maximum

## Pattern: Monotonic Queue

### Problem Statement
You are given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

**Constraints:**
- 1 ≤ nums.length ≤ 10^5
- -10^4 ≤ nums[i] ≤ 10^4
- 1 ≤ k ≤ nums.length

### Approach 1: Monotonic Deque (Optimal)

The key insight is to maintain a deque that stores indices in decreasing order of their values. This allows O(1) access to the maximum element in each window.

```python
from collections import deque

def maxSlidingWindow(nums, k):
    """
    Sliding window maximum using monotonic decreasing deque
    """
    if not nums or k == 0:
        return []
    
    dq = deque()  # Store indices in decreasing order of values
    result = []
    
    for i in range(len(nums)):
        # Remove indices that are out of current window
        while dq and dq[0] <= i - k:
            dq.popleft()
        
        # Remove indices whose values are smaller than current
        # (they can never be maximum while current element exists)
        while dq and nums[dq[-1]] <= nums[i]:
            dq.pop()
        
        dq.append(i)
        
        # Add maximum of current window to result
        if i >= k - 1:
            result.append(nums[dq[0]])
    
    return result
```

**Time Complexity:** O(n) - each element is added and removed at most once
**Space Complexity:** O(k) - deque stores at most k elements

### Approach 2: Max Heap with Lazy Deletion

Using a max heap with index tracking:

```python
import heapq

def maxSlidingWindowHeap(nums, k):
    """
    Using max heap with lazy deletion
    """
    if not nums or k == 0:
        return []
    
    # Max heap: store (-value, index)
    heap = []
    result = []
    
    for i in range(len(nums)):
        # Add current element to heap
        heapq.heappush(heap, (-nums[i], i))
        
        if i >= k - 1:
            # Remove elements outside current window (lazy deletion)
            while heap and heap[0][1] <= i - k:
                heapq.heappop(heap)
            
            # Maximum element in current window
            result.append(-heap[0][0])
    
    return result
```

**Time Complexity:** O(n log n)
**Space Complexity:** O(n)

### Approach 3: Segment Tree

For multiple queries or updates:

```python
class SegmentTree:
    def __init__(self, nums):
        self.n = len(nums)
        self.tree = [0] * (4 * self.n)
        self.nums = nums
        self.build(0, 0, self.n - 1)
    
    def build(self, node, start, end):
        if start == end:
            self.tree[node] = self.nums[start]
        else:
            mid = (start + end) // 2
            self.build(2 * node + 1, start, mid)
            self.build(2 * node + 2, mid + 1, end)
            self.tree[node] = max(self.tree[2 * node + 1], 
                                  self.tree[2 * node + 2])
    
    def query(self, node, start, end, l, r):
        if r < start or end < l:
            return float('-inf')
        if l <= start and end <= r:
            return self.tree[node]
        
        mid = (start + end) // 2
        left_max = self.query(2 * node + 1, start, mid, l, r)
        right_max = self.query(2 * node + 2, mid + 1, end, l, r)
        return max(left_max, right_max)
    
    def range_max(self, l, r):
        return self.query(0, 0, self.n - 1, l, r)

def maxSlidingWindowSegTree(nums, k):
    """
    Using segment tree for range maximum queries
    """
    if not nums or k == 0:
        return []
    
    seg_tree = SegmentTree(nums)
    result = []
    
    for i in range(len(nums) - k + 1):
        max_val = seg_tree.range_max(i, i + k - 1)
        result.append(max_val)
    
    return result
```

**Time Complexity:** O(n log n) for preprocessing, O(log n) per query
**Space Complexity:** O(n)

### Approach 4: Sparse Table (For Static Arrays)

Preprocessing for O(1) range maximum queries:

```python
import math

class SparseTable:
    def __init__(self, nums):
        self.nums = nums
        self.n = len(nums)
        self.k = int(math.log2(self.n)) + 1
        self.st = [[0] * self.k for _ in range(self.n)]
        self.build()
    
    def build(self):
        # Fill first column (intervals of length 1)
        for i in range(self.n):
            self.st[i][0] = self.nums[i]
        
        # Fill remaining columns
        j = 1
        while (1 << j) <= self.n:
            i = 0
            while (i + (1 << j) - 1) < self.n:
                self.st[i][j] = max(self.st[i][j-1], 
                                    self.st[i + (1 << (j-1))][j-1])
                i += 1
            j += 1
    
    def query(self, l, r):
        # Length of range
        length = r - l + 1
        k = int(math.log2(length))
        
        return max(self.st[l][k], self.st[r - (1 << k) + 1][k])

def maxSlidingWindowSparseTable(nums, k):
    """
    Using sparse table for O(1) range maximum queries
    """
    if not nums or k == 0:
        return []
    
    sparse_table = SparseTable(nums)
    result = []
    
    for i in range(len(nums) - k + 1):
        max_val = sparse_table.query(i, i + k - 1)
        result.append(max_val)
    
    return result
```

**Time Complexity:** O(n log n) preprocessing, O(1) per query
**Space Complexity:** O(n log n)

### Approach 5: Optimized Monotonic Deque with Templates

Generic implementation for different operations:

```python
from collections import deque
from typing import List, Callable

class MonotonicDeque:
    def __init__(self, is_max_queue=True):
        self.dq = deque()
        self.compare = (lambda a, b: a >= b) if is_max_queue else (lambda a, b: a <= b)
    
    def push(self, val, idx):
        # Remove elements that violate monotonic property
        while self.dq and self.compare(val, self.dq[-1][0]):
            self.dq.pop()
        self.dq.append((val, idx))
    
    def pop_expired(self, cutoff_idx):
        # Remove elements outside current window
        while self.dq and self.dq[0][1] <= cutoff_idx:
            self.dq.popleft()
    
    def get_extremum(self):
        return self.dq[0][0] if self.dq else None

def maxSlidingWindowTemplate(nums, k):
    """
    Template-based monotonic deque implementation
    """
    if not nums or k == 0:
        return []
    
    mq = MonotonicDeque(is_max_queue=True)
    result = []
    
    for i in range(len(nums)):
        # Remove expired elements
        mq.pop_expired(i - k)
        
        # Add current element
        mq.push(nums[i], i)
        
        # Add result for current window
        if i >= k - 1:
            result.append(mq.get_extremum())
    
    return result
```

### Approach 6: Block-based Solution (Square Root Decomposition)

For very large arrays or when memory is constrained:

```python
import math

def maxSlidingWindowBlocks(nums, k):
    """
    Square root decomposition approach
    """
    if not nums or k == 0:
        return []
    
    n = len(nums)
    block_size = int(math.sqrt(n)) + 1
    
    # Precompute maximum for each block
    blocks = []
    for i in range(0, n, block_size):
        block_max = max(nums[i:min(i + block_size, n)])
        blocks.append(block_max)
    
    result = []
    
    for i in range(n - k + 1):
        left, right = i, i + k - 1
        left_block, right_block = left // block_size, right // block_size
        
        if left_block == right_block:
            # Window entirely within one block
            window_max = max(nums[left:right + 1])
        else:
            # Window spans multiple blocks
            window_max = float('-inf')
            
            # Partial left block
            if left % block_size != 0:
                window_max = max(window_max, max(nums[left:(left_block + 1) * block_size]))
                left_block += 1
            
            # Complete middle blocks
            for block_idx in range(left_block, right_block):
                window_max = max(window_max, blocks[block_idx])
            
            # Partial right block
            if right % block_size != block_size - 1:
                window_max = max(window_max, max(nums[right_block * block_size:right + 1]))
        
        result.append(window_max)
    
    return result
```

### Example Usage

```python
# Example 1: Basic case
nums1 = [1, 3, -1, -3, 5, 3, 6, 7]
k1 = 3
print(maxSlidingWindow(nums1, k1))  # Output: [3, 3, 5, 5, 6, 7]

# Example 2: All same elements
nums2 = [1, 1, 1, 1, 1]
k2 = 3
print(maxSlidingWindow(nums2, k2))  # Output: [1, 1, 1]

# Example 3: Single element window
nums3 = [1, -1]
k3 = 1
print(maxSlidingWindow(nums3, k3))  # Output: [1, -1]

# Example 4: Large numbers
nums4 = [9, 11]
k4 = 2
print(maxSlidingWindow(nums4, k4))  # Output: [11]

# Example 5: Performance test
import time
large_nums = list(range(100000))
start = time.time()
result = maxSlidingWindow(large_nums, 1000)
print(f"Time taken: {time.time() - start:.4f} seconds")
```

### Monotonic Queue Pattern Analysis

The monotonic deque pattern is powerful because:

1. **Invariant Maintenance**: Keeps elements in monotonic order
2. **Lazy Deletion**: Removes expired elements only when needed
3. **Optimal Access**: Always O(1) access to extremum
4. **Amortized Efficiency**: Each element added/removed at most once

### Key Optimizations

1. **Index Storage**: Store indices instead of values for window management
2. **Lazy Cleanup**: Remove expired elements only when accessing front
3. **Early Termination**: Stop processing when smaller elements found
4. **Memory Efficiency**: Reuse deque space

### Common Pitfalls

1. **Window Boundary**: Correctly handling first k-1 elements
2. **Index Management**: Off-by-one errors in window calculation
3. **Empty Queue**: Checking for empty deque before accessing
4. **Duplicate Values**: Handling equal elements correctly

### Related Problems

- **Sliding Window Minimum**: Same pattern with min deque
- **Shortest Subarray with Sum at Least K**: Monotonic deque with prefix sums
- **Jump Game VI**: DP optimization with sliding window maximum
- **Constrained Subsequence Sum**: Similar monotonic deque application

### Real-World Applications

1. **Time Series Analysis**: Finding peaks in moving windows
2. **Image Processing**: Maximum filters for noise reduction
3. **Financial Analysis**: Rolling maximum/minimum calculations
4. **System Monitoring**: Peak detection in metric streams
5. **Game Development**: Collision detection optimization
Output: 
Explanation: 
```

### Example 2
```
Input: 
Output: 
Explanation: 
```

## Notes
<!-- Add any additional notes, edge cases, or variations -->

## Related Problems
<!-- List related problems -->

## Pattern: 12-Monotonic-Queue
<!-- Explain how this problem fits the pattern -->
