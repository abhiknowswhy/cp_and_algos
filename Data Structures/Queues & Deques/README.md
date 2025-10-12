
# Queue Data Structure - Coding Patterns & Examples

## 1. Basic Queue Operations

### Pattern: Fundamental queue operations (enqueue, dequeue, peek, isEmpty)

**Examples:**

* Implement a queue using arrays
* Implement a queue using linked lists
* Design a circular queue
* Implement queue with stack operations

**Sample Problem:**

```python
class Queue:
    def __init__(self):
        self.items = []
  
    def enqueue(self, item):
        self.items.append(item)
  
    def dequeue(self):
        if not self.is_empty():
            return self.items.pop(0)
        return None
  
    def peek(self):
        if not self.is_empty():
            return self.items[0]
        return None
  
    def is_empty(self):
        return len(self.items) == 0
```

## 2. Breadth-First Search (BFS) Pattern

### Pattern: Level-by-level traversal using queue

**Examples:**

* Binary tree level order traversal
* Graph BFS traversal
* Shortest path in unweighted graph
* Connected components in graph
* Word ladder problem
* Rotting oranges problem
* Knight's shortest path on chessboard

**Sample Problem - Binary Tree Level Order:**

```python
def levelOrder(root):
    if not root:
        return []
  
    result = []
    queue = [root]
  
    while queue:
        level = []
        for _ in range(len(queue)):
            node = queue.pop(0)
            level.append(node.val)
          
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
      
        result.append(level)
  
    return result
```

## 3. Level-by-Level Processing

### Pattern: Process elements level by level, often requiring level size tracking

**Examples:**

* Binary tree zigzag level order traversal
* Binary tree right side view
* Average of levels in binary tree
* Minimum depth of binary tree
* Maximum width of binary tree
* Populating next right pointers

**Sample Problem - Right Side View:**

```python
def rightSideView(root):
    if not root:
        return []
  
    result = []
    queue = [root]
  
    while queue:
        level_size = len(queue)
        for i in range(level_size):
            node = queue.pop(0)
          
            # Add rightmost node of each level
            if i == level_size - 1:
                result.append(node.val)
          
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
  
    return result
```

## 4. Multi-Source BFS Pattern

### Pattern: Start BFS from multiple sources simultaneously

**Examples:**

* Rotting oranges
* Walls and gates
* 01 Matrix (distance to nearest 0)
* Pacific Atlantic water flow
* Shortest distance from all buildings

**Sample Problem - Rotting Oranges:**

```python
def orangesRotting(grid):
    from collections import deque
  
    rows, cols = len(grid), len(grid[0])
    queue = deque()
    fresh_count = 0
  
    # Add all rotten oranges to queue
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 2:
                queue.append((r, c, 0))  # (row, col, time)
            elif grid[r][c] == 1:
                fresh_count += 1
  
    directions = [(0,1), (1,0), (0,-1), (-1,0)]
    max_time = 0
  
    while queue:
        r, c, time = queue.popleft()
        max_time = max(max_time, time)
      
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                grid[nr][nc] = 2
                fresh_count -= 1
                queue.append((nr, nc, time + 1))
  
    return max_time if fresh_count == 0 else -1
```

## 5. Sliding Window with Queue Pattern

### Pattern: Maintain elements in a window using deque for optimization

**Examples:**

* Sliding window maximum
* Sliding window minimum
* First negative integer in every window
* Sum of minimum and maximum elements of all subarrays

**Sample Problem - Sliding Window Maximum:**

```python
from collections import deque

def maxSlidingWindow(nums, k):
    dq = deque()  # stores indices
    result = []
  
    for i in range(len(nums)):
        # Remove indices outside current window
        while dq and dq[0] <= i - k:
            dq.popleft()
      
        # Remove indices of smaller elements
        while dq and nums[dq[-1]] <= nums[i]:
            dq.pop()
      
        dq.append(i)
      
        # Add to result when window is complete
        if i >= k - 1:
            result.append(nums[dq[0]])
  
    return result
```

## 6. Task Scheduling Pattern

### Pattern: Process tasks with dependencies or priorities using queue

**Examples:**

* Task scheduler
* Course schedule problems
* Alien dictionary
* Minimum height trees
* Topological sorting

**Sample Problem - Course Schedule II:**

```python
def findOrder(numCourses, prerequisites):
    from collections import defaultdict, deque
  
    # Build graph and indegree array
    graph = defaultdict(list)
    indegree = [0] * numCourses
  
    for course, prereq in prerequisites:
        graph[prereq].append(course)
        indegree[course] += 1
  
    # Start with courses having no prerequisites
    queue = deque([i for i in range(numCourses) if indegree[i] == 0])
    result = []
  
    while queue:
        course = queue.popleft()
        result.append(course)
      
        # Reduce indegree for dependent courses
        for dependent in graph[course]:
            indegree[dependent] -= 1
            if indegree[dependent] == 0:
                queue.append(dependent)
  
    return result if len(result) == numCourses else []
```

## 7. State Space Search Pattern

### Pattern: Explore different states using BFS to find optimal solution

**Examples:**

* Open the lock
* Word ladder
* Minimum genetic mutation
* Jump game problems
* Water jug problem
* 8-puzzle problem

**Sample Problem - Open the Lock:**

```python
def openLock(deadends, target):
    from collections import deque
  
    dead_set = set(deadends)
    if "0000" in dead_set:
        return -1
  
    queue = deque([("0000", 0)])
    visited = {"0000"}
  
    def get_neighbors(code):
        neighbors = []
        for i in range(4):
            digit = int(code[i])
            for move in [-1, 1]:
                new_digit = (digit + move) % 10
                new_code = code[:i] + str(new_digit) + code[i+1:]
                neighbors.append(new_code)
        return neighbors
  
    while queue:
        code, steps = queue.popleft()
      
        if code == target:
            return steps
      
        for neighbor in get_neighbors(code):
            if neighbor not in visited and neighbor not in dead_set:
                visited.add(neighbor)
                queue.append((neighbor, steps + 1))
  
    return -1
```

## 8. Island/Connected Components Pattern

### Pattern: Find connected regions using BFS

**Examples:**

* Number of islands
* Max area of island
* Surrounded regions
* Pacific Atlantic water flow
* Number of distinct islands
* Making a large island

**Sample Problem - Number of Islands:**

```python
def numIslands(grid):
    from collections import deque
  
    if not grid:
        return 0
  
    rows, cols = len(grid), len(grid[0])
    visited = set()
    islands = 0
  
    def bfs(r, c):
        queue = deque([(r, c)])
        visited.add((r, c))
      
        while queue:
            row, col = queue.popleft()
          
            for dr, dc in [(0,1), (1,0), (0,-1), (-1,0)]:
                nr, nc = row + dr, col + dc
                if (0 <= nr < rows and 0 <= nc < cols and 
                    (nr, nc) not in visited and grid[nr][nc] == '1'):
                    queue.append((nr, nc))
                    visited.add((nr, nc))
  
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1' and (r, c) not in visited:
                bfs(r, c)
                islands += 1
  
    return islands
```

## 9. Queue with Special Properties Pattern

### Pattern: Implement queues with additional constraints or operations

**Examples:**

* Design circular queue
* Design hit counter
* Moving average from data stream
* Design snake game
* LRU cache (using queue-like operations)
* Design phone directory

**Sample Problem - Moving Average:**

```python
from collections import deque

class MovingAverage:
    def __init__(self, size):
        self.size = size
        self.queue = deque()
        self.sum = 0
  
    def next(self, val):
        self.queue.append(val)
        self.sum += val
      
        if len(self.queue) > self.size:
            self.sum -= self.queue.popleft()
      
        return self.sum / len(self.queue)
```

## 10. Matrix/Grid BFS Pattern

### Pattern: Navigate through 2D grid using BFS

**Examples:**

* Shortest path in binary matrix
* As far from land as possible
* Shortest bridge
* Jump game IV
* Minimum knight moves
* Cut off trees for golf event

**Sample Problem - Shortest Path in Binary Matrix:**

```python
def shortestPathBinaryMatrix(grid):
    from collections import deque
  
    n = len(grid)
    if grid[0][0] == 1 or grid[n-1][n-1] == 1:
        return -1
  
    if n == 1:
        return 1
  
    queue = deque([(0, 0, 1)])  # (row, col, path_length)
    visited = {(0, 0)}
  
    directions = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]
  
    while queue:
        r, c, path_len = queue.popleft()
      
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
          
            if nr == n-1 and nc == n-1:
                return path_len + 1
          
            if (0 <= nr < n and 0 <= nc < n and 
                (nr, nc) not in visited and grid[nr][nc] == 0):
                queue.append((nr, nc, path_len + 1))
                visited.add((nr, nc))
  
    return -1
```

## 11. Queue Reconstruction Pattern

### Pattern: Rebuild queue based on certain properties

**Examples:**

* Queue reconstruction by height
* Reveal cards in increasing order
* Dota2 senate
* Design circular deque

**Sample Problem - Queue Reconstruction by Height:**

```python
def reconstructQueue(people):
    # Sort by height desc, then by count asc
    people.sort(key=lambda x: (-x[0], x[1]))
  
    result = []
    for person in people:
        # Insert at the position equal to the count
        result.insert(person[1], person)
  
    return result
```

## 12. Monotonic Queue Pattern

### Pattern: Maintain queue elements in monotonic order

**Examples:**

* Sliding window maximum
* Shortest subarray with sum at least K
* Jump game VI
* Constrained subsequence sum

**Sample Problem - Jump Game VI:**

```python
from collections import deque

def maxResult(nums, k):
    n = len(nums)
    dp = [0] * n
    dp[0] = nums[0]
  
    # Monotonic decreasing deque (stores indices)
    dq = deque([0])
  
    for i in range(1, n):
        # Remove indices outside window
        while dq and dq[0] < i - k:
            dq.popleft()
      
        # Current max score
        dp[i] = dp[dq[0]] + nums[i]
      
        # Maintain monotonic decreasing property
        while dq and dp[dq[-1]] <= dp[i]:
            dq.pop()
      
        dq.append(i)
  
    return dp[n-1]
```

## 13. Producer-Consumer Pattern

### Pattern: Coordinate between producers and consumers using queue

**Examples:**

* Design bounded blocking queue
* Web crawler multithreading
* Print in order problems
* Building H2O molecules

**Sample Problem - Print in Order:**

```python
from threading import Lock

class Foo:
    def __init__(self):
        self.first_done = Lock()
        self.second_done = Lock()
        self.first_done.acquire()
        self.second_done.acquire()
  
    def first(self, printFirst):
        printFirst()
        self.first_done.release()
  
    def second(self, printSecond):
        self.first_done.acquire()
        printSecond()
        self.first_done.release()
        self.second_done.release()
  
    def third(self, printThird):
        self.second_done.acquire()
        printThird()
        self.second_done.release()
```

## 14. Simulation Pattern

### Pattern: Simulate real-world scenarios using queue

**Examples:**

* Design hit counter
* Logger rate limiter
* Time based key-value store
* Design phone directory
* Design tic-tac-toe game

**Sample Problem - Hit Counter:**

```python
from collections import deque

class HitCounter:
    def __init__(self):
        self.hits = deque()
  
    def hit(self, timestamp):
        self.hits.append(timestamp)
  
    def getHits(self, timestamp):
        # Remove hits older than 300 seconds
        while self.hits and self.hits[0] <= timestamp - 300:
            self.hits.popleft()
      
        return len(self.hits)
```

## 15. Bidirectional BFS Pattern

### Pattern: Search from both ends to meet in middle

**Examples:**

* Word ladder
* Minimum genetic mutation
* Open the lock (optimized)

**Sample Problem - Word Ladder (Bidirectional):**

```python
def ladderLength(beginWord, endWord, wordList):
    if endWord not in wordList:
        return 0
  
    word_set = set(wordList)
    front = {beginWord}
    back = {endWord}
    steps = 1
  
    while front and back:
        # Always expand the smaller set
        if len(front) > len(back):
            front, back = back, front
      
        next_front = set()
      
        for word in front:
            for i in range(len(word)):
                for c in 'abcdefghijklmnopqrstuvwxyz':
                    new_word = word[:i] + c + word[i+1:]
                  
                    if new_word in back:
                        return steps + 1
                  
                    if new_word in word_set:
                        next_front.add(new_word)
                        word_set.remove(new_word)
      
        front = next_front
        steps += 1
  
    return 0
```

## Key Insights for Queue Problems

### When to Use BFS/Queue:

* Finding shortest path in unweighted graphs
* Level-by-level processing
* Exploring all possibilities at current level before moving to next
* State space search problems
* Processing elements in FIFO order

### Common Optimizations:

* Use deque from collections for O(1) operations at both ends
* Bidirectional search for shortest path problems
* Monotonic deque for sliding window problems
* Multiple queues for different priority levels

### Time/Space Complexity Patterns:

* Most BFS problems: O(V + E) time, O(V) space for graphs
* Grid BFS: O(m × n) time and space
* Sliding window with deque: O(n) time, O(k) space
* Multi-source BFS: O(m × n) time and space for grids

### Common Pitfalls:

* Forgetting to mark nodes as visited
* Not handling edge cases (empty input, single element)
* Incorrect queue size tracking in level-order problems
* Not optimizing with bidirectional search when possible
* Using list.pop(0) instead of deque.popleft() for performance
