# Binary Exponentiation (a.k.a. Exponentiation by Squaring)

Binary exponentiation is a **fast algorithm** to compute `a^n` (a raised to power n), especially useful when `n` is large.
It reduces the time complexity from **O(n)** (naive method) to **O(log n)**.

---

### Idea

Instead of multiplying `a` by itself `n` times, we use the binary representation of the exponent:

- If `n` is even:
  `a^n = (a^(n/2))^2`
- If `n` is odd:
  `a^n = a × (a^(n/2))^2`

We keep squaring the base and halving the exponent.

---

### Time Complexity

- **O(log n)** because the exponent is halved at each step.

---

### C++ Code (Iterative)

```cpp
#include <iostream>
using namespace std;

long long binaryExponentiation(long long a, long long n) {
    long long result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= a;  // If n is odd, multiply the result by a
        }
        a *= a;           // Square the base
        n /= 2;           // Divide the exponent by 2
    }
    return result;
}

int main() {
    long long a = 2, n = 10;
    cout << a << "^" << n << " = " << binaryExponentiation(a, n) << endl;
    return 0;
}
```

---

### Modular Binary Exponentiation

Useful when results can overflow or for problems involving modulus (computing (a^n)%mod)

```cpp
long long modExp(long long a, long long n, long long mod) {
    long long result = 1;
    a = a % mod;  // Handle case when a > mod
    while (n > 0) {
        if (n & 1) result = (result * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return result;
}
```
