# Karatsuba Multiplication Algorithm

## Introduction

Karatsuba algorithm is a fast multiplication algorithm that was discovered by Anatoly Karatsuba in 1960. It's a divide-and-conquer algorithm that reduces the multiplication of two n-digit numbers to at most n^log₂(3) ≈ n^1.585 single-digit multiplications, which is better than the classical algorithm that requires n² single-digit products.

## How It Works

Consider two large numbers x and y with n digits each. The Karatsuba algorithm breaks these numbers into smaller parts and reduces the number of multiplications needed.

Let's represent the numbers as:
- x = a × 10^(n/2) + b
- y = c × 10^(n/2) + d

Where a, b, c, and d are n/2 digit numbers.

Conventionally, computing x × y requires 4 multiplications:
x × y = (a × 10^(n/2) + b) × (c × 10^(n/2) + d)
      = ac × 10^n + ad × 10^(n/2) + bc × 10^(n/2) + bd
      = ac × 10^n + (ad + bc) × 10^(n/2) + bd

Karatsuba's insight was that we can compute the middle term (ad + bc) using only one multiplication:
- Compute ac
- Compute bd
- Compute (a+b)(c+d) = ac + ad + bc + bd
- Then: ad + bc = (a+b)(c+d) - ac - bd

Thus, we reduce from 4 multiplications to just 3:
1. z0 = a × c
2. z1 = b × d
3. z2 = (a + b) × (c + d)

And finally:
x × y = z0 × 10^n + (z2 - z0 - z1) × 10^(n/2) + z1

## C++ Implementation

```cpp
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Helper: Pads the strings to be of equal length (power of 2 if desired)
void makeEqualLength(string &a, string &b) {
    int len = max(a.size(), b.size());
    while (a.size() < len) a = "0" + a;
    while (b.size() < len) b = "0" + b;
}

// Helper: Adds two numeric strings
string addStrings(const string &a, const string &b) {
    string result = "";
    int carry = 0;
    int n = max(a.size(), b.size());

    string a_padded = a, b_padded = b;
    makeEqualLength(a_padded, b_padded);

    for (int i = n - 1; i >= 0; --i) {
        int sum = (a_padded[i] - '0') + (b_padded[i] - '0') + carry;
        carry = sum / 10;
        result += (sum % 10 + '0');
    }
    if (carry) result += (carry + '0');
    reverse(result.begin(), result.end());
    return result;
}

// Helper: Subtracts b from a (assumes a >= b)
string subtractStrings(const string &a, const string &b) {
    string result = "";
    int borrow = 0;

    string a_padded = a, b_padded = b;
    makeEqualLength(a_padded, b_padded);
    int n = a_padded.size();

    for (int i = n - 1; i >= 0; --i) {
        int diff = (a_padded[i] - '0') - (b_padded[i] - '0') - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else borrow = 0;
        result += (diff + '0');
    }
    while (result.size() > 1 && result.back() == '0') result.pop_back();
    reverse(result.begin(), result.end());
    return result;
}

// Karatsuba multiplication function
string karatsubaMultiply(string x, string y) {
    makeEqualLength(x, y);
    int n = x.size();

    if (n == 1)
        return to_string((x[0] - '0') * (y[0] - '0'));

    int half = n / 2;
    string a = x.substr(0, half);
    string b = x.substr(half);
    string c = y.substr(0, half);
    string d = y.substr(half);

    string ac = karatsubaMultiply(a, c);
    string bd = karatsubaMultiply(b, d);
    string ab_plus_cd = karatsubaMultiply(addStrings(a, b), addStrings(c, d));
    string ad_plus_bc = subtractStrings(subtractStrings(ab_plus_cd, ac), bd);

    // Add zeros for base powers
    for (int i = 0; i < 2 * (n - half); ++i) ac += "0";
    for (int i = 0; i < n - half; ++i) ad_plus_bc += "0";

    string result = addStrings(addStrings(ac, ad_plus_bc), bd);
    
    // Remove leading zeros
    while (result.size() > 1 && result[0] == '0') result.erase(0, 1);
    return result;
}

int main() {
    string num1 = "3141592653589793238462643383279502884197169399375105820974944592";
    string num2 = "2718281828459045235360287471352662497757247093699959574966967627";

    cout << "Product:\n" << karatsubaMultiply(num1, num2) << endl;

    return 0;
}
```

## Complexity Analysis

- **Time Complexity**: O(n^log₂(3)) ≈ O(n^1.585), where n is the number of digits.
- **Space Complexity**: O(n) due to recursion stack depth.

Compared to the traditional multiplication algorithm which has a time complexity of O(n²), Karatsuba algorithm is significantly faster for large numbers.

## When to Use

- Use Karatsuba multiplication when multiplying very large numbers that don't fit into standard data types
- Especially beneficial when numbers have hundreds or thousands of digits
- For small numbers (less than ~10 digits), the overhead of recursion may make traditional multiplication more efficient

## Applications

- Big integer arithmetic
- Cryptography
- Scientific computing
- High-precision numerical calculations

## Limitations

- Implementation can be complex due to string manipulation
- Additional overhead for small numbers
- The recursion can lead to stack overflow for extremely large numbers without proper handling
