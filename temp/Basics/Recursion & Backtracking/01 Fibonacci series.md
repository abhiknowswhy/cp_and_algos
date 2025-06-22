# Fibonacci Series

## What is the Fibonacci Series?

The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones, usually starting with 0 and 1.

Mathematical definition:

- F(0) = 0
- F(1) = 1
- F(n) = F(n-1) + F(n-2) for n > 1

The sequence begins: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

## Implementations

### 1. Recursive Implementation

The most straightforward but least efficient approach is using recursion:

```cpp
#include <iostream>

int fibonacci(int n) {
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;
  
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n = 10;
    std::cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
    return 0;
}
```

**Time Complexity**: O(2^n) - exponential time due to repeated calculations
**Space Complexity**: O(n) - for the recursion stack

### 2. Dynamic Programming - Memoization (Top-Down)

This approach uses recursion with caching:

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>

// Using unordered_map for memoization
int fibonacciMemoMap(int n, std::unordered_map<int, int>& memo) {
    // Check if already calculated
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
  
    // Base cases
    if (n == 0) return 0;
    if (n == 1) return 1;
  
    // Store and return the result
    memo[n] = fibonacciMemoMap(n - 1, memo) + fibonacciMemoMap(n - 2, memo);
    return memo[n];
}

int fibonacci_map(int n) {
    std::unordered_map<int, int> memo;
    return fibonacciMemoMap(n, memo);
}

// Alternative: Using vector for memoization
int fibonacciMemoVec(int n, std::vector<int>& memo) {
    // Base cases
    if (n <= 1) return n;
  
    // If value is already computed
    if (memo[n] != -1) return memo[n];
  
    // Compute and store the result
    memo[n] = fibonacciMemoVec(n - 1, memo) + fibonacciMemoVec(n - 2, memo);
    return memo[n];
}

int fibonacci_vector(int n) {
    std::vector<int> memo(n + 1, -1);
    return fibonacciMemoVec(n, memo);
}

int main() {
    int n = 10;
    std::cout << "Using map - Fibonacci(" << n << ") = " << fibonacci_map(n) << std::endl;
    std::cout << "Using vector - Fibonacci(" << n << ") = " << fibonacci_vector(n) << std::endl;
    return 0;
}
```

**Time Complexity**: O(n)
**Space Complexity**: O(n)

### 3. Dynamic Programming - Tabulation (Bottom-Up)

This approach builds the solution iteratively:

```cpp
#include <iostream>
#include <vector>

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
  
    // Create table to store results
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
  
    // Fill table in bottom-up manner
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
  
    return dp[n];
}

int main() {
    int n = 10;
    std::cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
    return 0;
}
```

**Time Complexity**: O(n)
**Space Complexity**: O(n)

### 4. Space-Optimized Iteration

We don't need to store all values, just the last two:

```cpp
#include <iostream>

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
  
    int prev = 0;     // F(0)
    int current = 1;  // F(1)
    int next;
  
    for (int i = 2; i <= n; i++) {
        next = prev + current;
        prev = current;
        current = next;
    }
  
    return current;
}

int main() {
    int n = 10;
    std::cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
    return 0;
}
```

**Time Complexity**: O(n)
**Space Complexity**: O(1)

## Matrix Exponentiation (Advanced)

For very large values of n, we can use matrix exponentiation to calculate Fibonacci numbers in O(log n) time:

```cpp
#include <iostream>
#include <vector>

std::vector<std::vector<long long>> matrixMultiply(
    const std::vector<std::vector<long long>>& A, 
    const std::vector<std::vector<long long>>& B) {
  
    std::vector<std::vector<long long>> C(2, std::vector<long long>(2, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

std::vector<std::vector<long long>> matrixPower(
    std::vector<std::vector<long long>> A, int n) {
  
    std::vector<std::vector<long long>> result = {{1, 0}, {0, 1}}; // Identity matrix
  
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, A);
        }
        A = matrixMultiply(A, A);
        n /= 2;
    }
  
    return result;
}

long long fibonacci(int n) {
    if (n == 0) return 0;
  
    std::vector<std::vector<long long>> base = {{1, 1}, {1, 0}};
    std::vector<std::vector<long long>> result = matrixPower(base, n - 1);
  
    return result[0][0];
}

int main() {
    int n = 50; // Using a larger number to demonstrate the efficiency
    std::cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
    return 0;
}
```

**Time Complexity**: O(log n)
**Space Complexity**: O(1)

## Common Pitfalls

1. **Integer Overflow**: Fibonacci numbers grow exponentially, causing integer overflow for larger values of n. Consider using `long long` or BigInteger libraries.
2. **Inefficiency in Naive Recursion**: The simple recursive solution has exponential time complexity, making it impractical for larger values.
3. **Negative Inputs**: Define how your function should handle negative inputs (usually by returning an error or extending the definition).

## Related LeetCode Problems

1. [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) - Basic implementation of the Fibonacci sequence
2. [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) - Similar to Fibonacci calculation
3. [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) - Extension of the Fibonacci concept
4. [1137. N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/) - Similar to Fibonacci but with three terms
5. [873. Length of Longest Fibonacci Subsequence](https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/) - Advanced application
6. [842. Split Array into Fibonacci Sequence](https://leetcode.com/problems/split-array-into-fibonacci-sequence/) - Complex application
