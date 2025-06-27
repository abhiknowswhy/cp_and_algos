# Useful methods

## Vector

Algorithms for binary search - works on a sorted vectors

- lower_bound(first, last, value, [comp])
  - Returns an iterator to the first element not less than the given value
  - Return: Iterator to the first element that is not less than `value`, or `last` if no such element exists
  - Optional comparator: Custom binary predicate function that defines the ordering

- upper_bound(first, last, value, [comp])
  - Returns an iterator to the first element greater than the given value
  - Return: Iterator to the first element that is greater than `value`, or `last` if no such element exists
  - Optional comparator: Custom binary predicate function that defines the ordering

- binary_search(first, last, value, [comp])
  - Checks if value exists in the sorted range
  - Return: Boolean - `true` if an element equal to `value` is found, otherwise `false`
  - Optional comparator: Custom binary predicate function that defines the ordering

Example usage of all three methods:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Regular usage with default sorting
    std::vector<int> v = {10, 20, 30, 30, 40, 50};
    
    // Using custom comparator
    auto comp = [](int a, int b) { return a > b; }; // Reverse order (descending)
    std::vector<int> v2 = {10, 50, 30, 20, 40, 30};
    
    // Sort with custom comparator first
    std::sort(v2.begin(), v2.end(), comp);
    std::cout << "Sorted with custom comparator: ";
    for (int x : v2) std::cout << x << " ";
    std::cout << "\n";
    
    // Now use the binary search methods with the same comparator
    auto lb = std::lower_bound(v2.begin(), v2.end(), 30, comp);
    auto ub = std::upper_bound(v2.begin(), v2.end(), 30, comp);
    auto found = std::binary_search(v2.begin(), v2.end(), 30, comp);
    
    std::cout << "With comparator - lower_bound(30): " << (lb - v2.begin()) << " (value: " << *lb << ")\n";
    std::cout << "With comparator - upper_bound(30): " << (ub - v2.begin()) << " (value: " << *ub << ")\n";
    std::cout << "With comparator - binary_search(30): " << (found ? "found" : "not found") << "\n";
    
    return 0;
}
```

## String

- stoi(string String) -> converts a string with all numbers to integers
- to_string() -> converts a class that implements to_string() method into string
- 