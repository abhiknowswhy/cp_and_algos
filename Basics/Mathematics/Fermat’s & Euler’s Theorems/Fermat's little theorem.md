# Fermat's Little Theorem: Your Secret Weapon for Modular Division

If you've been grinding competitive programming problems for a while, you've probably encountered situations where you need to compute `(a/b) % MOD` where `MOD` is a large prime like `1000000007` (1e9+7). The catch? You can't just divide and then take the modulo because division in modular arithmetic isn't straightforward. This is where Fermat's Little Theorem becomes your best friend.

## What is Fermat's Little Theorem?

Fermat's Little Theorem states that if `p` is a prime number and `a` is not divisible by `p`, then:

**a^(p-1) ≡ 1 (mod p)**

This seemingly simple statement has profound implications. It tells us that when we raise any number `a` to the power `(p-1)` and take modulo `p`, we always get 1 (assuming `a` and `p` are coprime).

Let's see this in action with a small example. Take `p = 7` and `a = 3`:

* 3^6 = 729
* 729 % 7 = 1 ✓

## The Multiplicative Inverse Connection

Here's where it gets interesting for competitive programming. From Fermat's Little Theorem, we can derive:

**a^(p-1) ≡ 1 (mod p)**

Rearranging this:
**a × a^(p-2) ≡ 1 (mod p)**

This means `a^(p-2)` is the multiplicative inverse of `a` modulo `p`! In other words, `a^(p-2) % p` gives us the number that, when multiplied by `a`, yields 1 modulo `p`.

## Solving the Division Problem

Now we can tackle our original problem: computing `(a/b) % MOD`.

Division by `b` is equivalent to multiplication by the multiplicative inverse of `b`. So:

**(a/b) % MOD = (a × b^(MOD-2)) % MOD**

Here's how to implement this:

```cpp
const long long MOD = 1000000007;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long modInverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}

long long modDivision(long long a, long long b, long long mod) {
    return (a * modInverse(b, mod)) % mod;
}
```

## Why 1e9+7?

You might wonder why `1000000007` is so popular in competitive programming. There are several reasons:

1. **It's prime** : This allows us to use Fermat's Little Theorem
2. **It's large** : Reduces the chance of hash collisions and provides a good range
3. **It fits in 32-bit integers** : `2 × (1e9+7) - 1` is still within `long long` range
4. **It's close to 1e9** : Easy to remember and work with

## Practical Example

Let's say you need to compute the number of ways to arrange objects, which involves calculating `n! / (k! × (n-k)!)` modulo `1e9+7`. Instead of trying to divide factorials directly, you would:

```cpp
long long result = factorial[n];
result = (result * modInverse(factorial[k], MOD)) % MOD;
result = (result * modInverse(factorial[n-k], MOD)) % MOD;
```

## Time Complexity

The modular exponentiation algorithm runs in O(log MOD) time, which is approximately O(30) operations for `1e9+7`. This is extremely fast and won't be a bottleneck in your solutions.

## Key Takeaways

* Fermat's Little Theorem: `a^(p-1) ≡ 1 (mod p)` for prime `p`
* Multiplicative inverse: `a^(p-2) ≡ a^(-1) (mod p)`
* Division becomes: `(a/b) % p = (a × b^(p-2)) % p`
* Always use fast exponentiation for computing `b^(p-2)`

Next time you encounter a problem requiring modular division, remember Fermat's Little Theorem. It transforms what seems like a complex operation into a straightforward computation, making your competitive programming journey much smoother!

## Example leetcode questions

* [Range product queries of Powers](https://leetcode.com/problems/range-product-queries-of-powers/submissions/1732097408/?envType=daily-question&envId=2025-08-11)
