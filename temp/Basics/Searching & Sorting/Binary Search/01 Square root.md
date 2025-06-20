# Binary Search for Square Root

## Problem Statement
Given a non-negative integer `x`, find its square root without using any built-in square root function. Return the integer part only.

## Approach
We can use binary search to find the square root efficiently. The key insights are:
1. The square root of `x` must be between `0` and `x` (for `x ≥ 1`)
2. We can use binary search to narrow down this range quickly

## Algorithm
1. Initialize search range: `left = 0` and `right = x`
2. While `left ≤ right`:
   - Calculate `mid = (left + right) / 2`
   - If `mid * mid == x`, return `mid` as the exact square root
   - If `mid * mid > x`, search in the left half: `right = mid - 1`
   - If `mid * mid < x`, search in the right half: `left = mid + 1` and update the answer
3. Return the integer part of the square root

## Time Complexity
O(log n) where n is the input number

## Space Complexity
O(1) - constant space

## C++ Implementation

```cpp
#include <iostream>
using namespace std;

// Function to find square root using binary search
int mySqrt(int x) {
    // Handle edge cases
    if (x == 0 || x == 1)
        return x;
        
    long long left = 1, right = x, ans = 0;
    
    // Binary search for the square root
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        // If mid is the exact square root, return it
        if (mid * mid == x)
            return mid;
            
        // If mid*mid is less than x, search in right half
        if (mid * mid < x) {
            left = mid + 1;
            // Update answer (we want the floor value)
            ans = mid;
        }
        // If mid*mid is greater than x, search in left half
        else {
            right = mid - 1;
        }
    }
    
    return ans;
}

// Driver code
int main() {
    int x = 16;
    cout << "Square root of " << x << " is " << mySqrt(x) << endl;
    
    x = 8;
    cout << "Square root of " << x << " is " << mySqrt(x) << endl;
    
    x = 2;
    cout << "Square root of " << x << " is " << mySqrt(x) << endl;
    
    return 0;
}
```

## Example

For input `x = 8`:
- Start with `left = 1` and `right = 8`
- Calculate `mid = (1 + 8) / 2 = 4`
- `mid * mid = 16`, which is > 8, so set `right = mid - 1 = 3`
- Calculate `mid = (1 + 3) / 2 = 2`
- `mid * mid = 4`, which is < 8, so set `left = mid + 1 = 3` and `ans = 2`
- Calculate `mid = (3 + 3) / 2 = 3`
- `mid * mid = 9`, which is > 8, so set `right = mid - 1 = 2`
- Now `left = 3` and `right = 2`, so the loop terminates
- Return `ans = 2`

So, the square root of 8 is 2 (integer part only).

## Square Root with Decimal Precision

If we need to find the square root with decimal precision, we can modify our binary search approach to work with floating-point numbers.

### Algorithm
1. Initialize search range: `left = 0.0` and `right = x`
2. Define a precision threshold (e.g., `1e-10`)
3. While `right - left > precision`:
   - Calculate `mid = (left + right) / 2`
   - If `mid * mid > x`, search in the left half: `right = mid`
   - Otherwise, search in the right half: `left = mid`
4. Return either `left` or `right` (they'll be very close)

### C++ Implementation with Floating-Point Precision

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

// Function to find square root with decimal precision using binary search
double sqrtPrecise(double x, double precision = 1e-10) {
    // Handle edge cases
    if (x < 0) 
        return -1; // Error: negative input
    if (x == 0 || x == 1)
        return x;
        
    double left = 0;
    double right = x;
    
    // Binary search for the square root
    while (right - left > precision) {
        double mid = left + (right - left) / 2;
        
        if (mid * mid > x) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return left;
}

// Driver code
int main() {
    double x = 2.0;
    cout << fixed << setprecision(10);
    cout << "Square root of " << x << " is " << sqrtPrecise(x) << endl;
    
    x = 3.0;
    cout << "Square root of " << x << " is " << sqrtPrecise(x) << endl;
    
    x = 10.0;
    cout << "Square root of " << x << " is " << sqrtPrecise(x) << endl;
    
    return 0;
}
```

### Example with Decimal Precision

For input `x = 2.0` with precision `1e-10`:
1. Start with `left = 0.0` and `right = 2.0`
2. Repeatedly calculate the midpoint and adjust the search range:
   - Check if `mid * mid > x` to determine which half to search
   - Continue until the search range is smaller than our precision
3. The final result will be approximately `1.4142135624`, very close to the actual square root of 2

### Time Complexity
The time complexity depends on the precision we want:
- O(log(x/ε)) where x is the input number and ε is the precision

### Applications
This more precise square root calculation is useful in:
- Scientific calculations
- Computer graphics (distance calculations)
- Numerical algorithms
- Machine learning algorithms
