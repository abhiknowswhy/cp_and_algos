# Primes & Sieve

## Sieve of Eratosthenes

- **Description**: The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to a specified limit efficiently. Named after the Greek mathematician Eratosthenes who first introduced it, this algorithm works by iteratively marking the multiples of each prime number as composite (not prime), starting from 2.

- **Key Concepts**:
  - Time Complexity: O(N log log N), where N is the upper limit
  - Space Complexity: O(N) to store the sieve
  - Very efficient for finding all primes up to 10^7 or 10^8
  - Can be optimized further with various techniques

- **Algorithm Steps**:
  1. Create a boolean array of size n+1, initialized to true (assuming all numbers are prime initially)
  2. Start with the smallest prime number, p = 2
  3. Mark all multiples of p (2p, 3p, 4p, ...) as non-prime (false)
  4. Find the next number in the array that is still marked as prime
  5. Repeat steps 3-4 until you've processed all numbers up to √n
  6. All numbers still marked as true are prime

## Implementation in C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    
    // 0 and 1 are not prime
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // Mark all multiples of i as non-prime
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Function to get all prime numbers up to n
vector<int> getPrimes(int n) {
    vector<bool> isPrime = sieve(n);
    vector<int> primes;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// Example usage
int main() {
    int n = 100;
    vector<int> primes = getPrimes(n);
    
    cout << "Prime numbers up to " << n << " are:" << endl;
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl;
    
    return 0;
}
```

## Optimizations

### Memory-Optimized Sieve (Odd Numbers Only)

```cpp
// Only consider odd numbers to save memory
vector<bool> sieveOptimized(int n) {
    vector<bool> isPrime((n + 1) / 2, true);
    isPrime[0] = false; // 1 is not prime
    
    for (int i = 3; i * i <= n; i += 2) {
        if (isPrime[i/2]) {
            for (int j = i * i; j <= n; j += 2 * i) {
                isPrime[j/2] = false;
            }
        }
    }
    
    return isPrime;
}
```

### Segmented Sieve (for larger ranges)

```cpp
vector<int> segmentedSieve(int low, int high) {
    int limit = sqrt(high) + 1;
    vector<int> basePrimes = getPrimes(limit);
    
    int n = high - low + 1;
    vector<bool> isPrime(n, true);
    
    // If low is 1, mark it as not prime
    if (low == 1) isPrime[0] = false;
    
    for (int p : basePrimes) {
        // Find the first multiple of p greater than or equal to low
        int start = max((low / p) * p, p * p);
        if (start < low) start += p;
        
        // Mark all multiples of p in range [low, high] as non-prime
        for (int j = start; j <= high; j += p) {
            isPrime[j - low] = false;
        }
    }
    
    // Collect primes from the range
    vector<int> primes;
    for (int i = 0; i < n; i++) {
        if (isPrime[i]) {
            primes.push_back(low + i);
        }
    }
    
    return primes;
}
```

## Alternative Prime Finding Approach

Instead of using a boolean array to mark numbers as prime or not, we can directly build a list of primes by checking each new number against the already found primes. This approach uses the property that a number is prime if it's not divisible by any prime number less than or equal to its square root.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Find all primes up to n by testing divisibility with already found primes
vector<int> findPrimes(int n) {
    vector<int> primes;
    
    // Add 2 as the first prime
    if (n >= 2) {
        primes.push_back(2);
    }
    
    // Check odd numbers starting from 3
    for (int num = 3; num <= n; num += 2) {
        bool isPrime = true;
        int sqrtNum = sqrt(num);
        
        // Check if num is divisible by any prime in our list
        for (int i = 0; i < primes.size() && primes[i] <= sqrtNum; i++) {
            if (num % primes[i] == 0) {
                isPrime = false;
                break;
            }
        }
        
        // If not divisible by any prime, num is prime
        if (isPrime) {
            primes.push_back(num);
        }
    }
    
    return primes;
}

// Example usage
int main() {
    int n = 100;
    vector<int> primes = findPrimes(n);
    
    cout << "Prime numbers up to " << n << " are:" << endl;
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl;
    
    return 0;
}
```

### Performance Comparison

The traditional Sieve of Eratosthenes has a time complexity of O(N log log N), while this approach has a time complexity of O(N√N / log N) due to checking each number against a list of primes. The sieve is generally more efficient for finding all primes up to a large limit, but this alternative approach:

1. Uses less memory - only stores the prime numbers themselves
2. Is conceptually simpler to understand
3. Is more suitable when you need to find primes one by one
4. Can be faster for smaller values of n or when memory is constrained

### Optimized Version with Early Stopping

A further optimization is to only check divisibility by primes up to the square root of the number:

```cpp
vector<int> findPrimesOptimized(int n) {
    vector<int> primes;
    
    if (n >= 2) {
        primes.push_back(2);
    }
    
    for (int num = 3; num <= n; num += 2) {
        bool isPrime = true;
        int sqrtNum = sqrt(num);
        
        for (int i = 0; primes[i] <= sqrtNum && i < primes.size(); i++) {
            if (num % primes[i] == 0) {
                isPrime = false;
                break;
            }
        }
        
        if (isPrime) {
            primes.push_back(num);
        }
    }
    
    return primes;
}
```

This approach is particularly useful in scenarios where you need to:
1. Find primes up to a moderate limit (e.g., up to 10^6)
2. Check primality of numbers on-the-fly
3. Generate primes incrementally rather than all at once
4. Work with constrained memory environments

While the traditional Sieve of Eratosthenes is more efficient for finding all primes in a large range, this direct testing approach can be more intuitive and sometimes more practical depending on the specific requirements.

## Sample Problems:

### 1. Count Primes (LeetCode 204)
Count the number of prime numbers less than a non-negative number, n.

```cpp
int countPrimes(int n) {
    if (n <= 2) return 0;
    
    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i < n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (isPrime[i]) count++;
    }
    
    return count;
}
```

### 2. Prime Factorization (using precalculated smallest prime factors)

```cpp
// Preprocessing to find smallest prime factor for each number
vector<int> smallestPrimeFactor(int n) {
    vector<int> spf(n + 1);
    
    // Initialize SPF for every number
    for (int i = 0; i <= n; i++)
        spf[i] = i;
        
    // Set SPF for all even numbers as 2
    for (int i = 4; i <= n; i += 2)
        spf[i] = 2;
        
    for (int i = 3; i * i <= n; i++) {
        if (spf[i] == i) { // If i is prime
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) // If SPF not set yet
                    spf[j] = i;
            }
        }
    }
    
    return spf;
}

// Get prime factorization of a number
vector<int> primeFactorize(int x, const vector<int>& spf) {
    vector<int> factors;
    
    while (x > 1) {
        factors.push_back(spf[x]);
        x = x / spf[x];
    }
    
    return factors;
}
```

### 3. Sum of all divisors of numbers up to N

```cpp
// Using sieve-like approach to calculate sum of divisors
vector<int> sumOfDivisors(int n) {
    vector<int> sum(n + 1, 0);
    
    // For each number, add it as a divisor to all its multiples
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            sum[j] += i;
        }
    }
    
    return sum;
}
```

### 4. Euler's Totient Function from 1 to N (Counting relatively prime numbers)

#### What is Euler's Totient Function?

Euler's Totient Function (also called Phi Function) φ(n) counts the positive integers up to n that are relatively prime to n (i.e., numbers that share no common factors with n except 1, or in other words, numbers whose greatest common divisor with n is 1).

For example:
- φ(1) = 1 (only 1 is relatively prime to 1)
- φ(6) = 2 (only 1 and 5 are relatively prime to 6)
- φ(7) = 6 (all numbers from 1 to 6 are relatively prime to 7 since 7 is prime)

#### Important Properties:

1. If p is a prime number, φ(p) = p - 1
   - Every number less than a prime is relatively prime to it

2. If p is a prime and k ≥ 1, then φ(p^k) = p^k - p^(k-1) = p^k(1 - 1/p)
   - Example: φ(8) = φ(2^3) = 2^3 - 2^2 = 8 - 4 = 4

3. If a and b are coprime, then φ(ab) = φ(a) × φ(b)
   - This is the multiplicative property

4. For arbitrary n, we can express φ(n) using its prime factorization:
   - If n = p₁^a₁ × p₂^a₂ × ... × pₖ^aₖ, then:
   - φ(n) = n × (1 - 1/p₁) × (1 - 1/p₂) × ... × (1 - 1/pₖ)

#### Applications:

- Number Theory: Used in modular arithmetic and solving equations
- Cryptography: Essential in RSA cryptosystem
- Counting solutions to equations in modular arithmetic
- Euler's Theorem: a^φ(n) ≡ 1 (mod n) when a and n are coprime

#### Calculating Euler's Totient using Sieve:

```cpp
// Using Sieve technique to compute Euler's totient for all numbers up to n
vector<int> eulerTotient(int n) {
    vector<int> phi(n + 1);
    
    // Initialize all euler totient values
    for (int i = 0; i <= n; i++)
        phi[i] = i;
        
    for (int p = 2; p <= n; p++) {
        if (phi[p] == p) { // p is prime
            phi[p] = p - 1; // phi of prime is prime-1
            
            // Update phi values for all multiples of p
            for (int i = 2 * p; i <= n; i += p) {
                phi[i] = (phi[i] / p) * (p - 1);
            }
        }
    }
    
    return phi;
}
```

#### Calculating Euler's Totient for a single number:

```cpp
int eulerPhi(int n) {
    int result = n; // Initialize result as n
    
    // Consider all prime factors of n and subtract their
    // multiples from result
    for (int p = 2; p * p <= n; p++) {
        // Check if p is a prime factor
        if (n % p == 0) {
            // If yes, then update n and result
            while (n % p == 0)
                n /= p;
                
            result -= result / p;
        }
    }
    
    // If n has a prime factor greater than sqrt(n)
    // (There can be at most one such prime factor)
    if (n > 1)
        result -= result / n;
        
    return result;
}
```

These applications of the Sieve of Eratosthenes demonstrate its versatility in solving various number theory problems efficiently.
