# Restore IP Addresses (Leetcode 93)

## Problem Definition

Given a string containing only digits, restore all possible valid IP address configurations by adding dots. A valid IP address consists of exactly four decimal numbers, each ranging from 0 to 255, separated by dots.

For example, given the string "25525511135", possible valid IP addresses are:
- "255.255.11.135"
- "255.255.111.35"

## Understanding IP Address Rules

A valid IP address must satisfy these conditions:
1. Consists of exactly 4 segments separated by dots
2. Each segment must be between 0 and 255 (inclusive)
3. No leading zeros in any segment (e.g., "01" is invalid, but "0" is valid)

## Implementations

### 1. Backtracking Solution

We can use backtracking to explore all valid ways to place dots:

```cpp
#include <iostream>
#include <vector>
#include <string>

class IPAddressRestorer {
private:
    bool isValidSegment(const std::string& s, int start, int end) {
        // Check length - segments can't be longer than 3 digits
        if (end - start + 1 > 3) {
            return false;
        }
        
        // Check for leading zeros
        if (s[start] == '0' && end > start) {
            return false;
        }
        
        // Check numeric value
        int value = 0;
        for (int i = start; i <= end; i++) {
            value = value * 10 + (s[i] - '0');
        }
        
        return value <= 255;
    }
    
    void backtrack(std::vector<std::string>& result, const std::string& s, 
                  std::string current, int start, int dots) {
        // If we've placed 3 dots, check if the remaining segment is valid
        if (dots == 3) {
            if (isValidSegment(s, start, s.length() - 1)) {
                // Add the final segment and construct a valid IP address
                result.push_back(current + s.substr(start));
            }
            return;
        }
        
        // Try placing a dot after each valid digit position
        for (int i = start; i < s.length() && i < start + 3; i++) {
            // Check if the current segment is valid
            if (isValidSegment(s, start, i)) {
                // Place a dot and continue recursively
                backtrack(result, s, current + s.substr(start, i - start + 1) + ".", i + 1, dots + 1);
            }
        }
    }

public:
    std::vector<std::string> restoreIpAddresses(std::string s) {
        std::vector<std::string> result;
        
        // IP address can't be shorter than 4 characters or longer than 12 characters
        if (s.length() < 4 || s.length() > 12) {
            return result;
        }
        
        backtrack(result, s, "", 0, 0);
        
        return result;
    }
};

int main() {
    IPAddressRestorer restorer;
    
    // Test cases
    std::vector<std::string> testCases = {
        "25525511135",
        "0000",
        "101023"
    };
    
    for (const std::string& s : testCases) {
        std::vector<std::string> results = restorer.restoreIpAddresses(s);
        
        std::cout << "Input: \"" << s << "\"" << std::endl;
        std::cout << "Valid IP addresses:" << std::endl;
        
        for (const std::string& ip : results) {
            std::cout << ip << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(1), as we have a fixed constraint of placing 3 dots in a string that's at most 12 characters long. The exact number of operations depends on the number of valid IP addresses that can be formed, but it's bounded by a constant.

**Space Complexity**: O(1) for the recursion stack, since the maximum depth is limited by the constraints of IP addresses.

### 2. Iterative Solution

For those who prefer an iterative approach:

```cpp
#include <iostream>
#include <vector>
#include <string>

class IterativeIPAddressRestorer {
private:
    bool isValidSegment(const std::string& s) {
        // Empty segment is invalid
        if (s.empty()) {
            return false;
        }
        
        // Check for leading zeros
        if (s[0] == '0' && s.length() > 1) {
            return false;
        }
        
        // Check numeric value
        int value = std::stoi(s);
        return value <= 255;
    }

public:
    std::vector<std::string> restoreIpAddresses(std::string s) {
        std::vector<std::string> result;
        
        int n = s.length();
        
        // IP address must have between 4 and 12 digits
        if (n < 4 || n > 12) {
            return result;
        }
        
        // Try all possible positions to place 3 dots
        // i, j, k are the positions after which we place dots
        for (int i = 0; i < 3 && i < n - 3; i++) {
            for (int j = i + 1; j < i + 4 && j < n - 2; j++) {
                for (int k = j + 1; k < j + 4 && k < n - 1; k++) {
                    // Extract the four segments
                    std::string seg1 = s.substr(0, i + 1);
                    std::string seg2 = s.substr(i + 1, j - i);
                    std::string seg3 = s.substr(j + 1, k - j);
                    std::string seg4 = s.substr(k + 1);
                    
                    // Validate all segments
                    if (isValidSegment(seg1) && isValidSegment(seg2) &&
                        isValidSegment(seg3) && isValidSegment(seg4)) {
                        // Construct a valid IP address
                        result.push_back(seg1 + "." + seg2 + "." + seg3 + "." + seg4);
                    }
                }
            }
        }
        
        return result;
    }
};

int main() {
    IterativeIPAddressRestorer restorer;
    
    // Test cases
    std::vector<std::string> testCases = {
        "25525511135",
        "0000",
        "101023"
    };
    
    for (const std::string& s : testCases) {
        std::vector<std::string> results = restorer.restoreIpAddresses(s);
        
        std::cout << "Input: \"" << s << "\"" << std::endl;
        std::cout << "Valid IP addresses (iterative):" << std::endl;
        
        for (const std::string& ip : results) {
            std::cout << ip << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(1), as we have a finite number of possible positions for placing dots.
**Space Complexity**: O(1).

### 3. Using Four Nested Loops

Another straightforward approach is to use four nested loops to directly generate all possible segments:

```cpp
#include <iostream>
#include <vector>
#include <string>

class FourLoopIPAddressRestorer {
private:
    bool isValid(const std::string& s, int start, int length) {
        // Segment cannot be empty or longer than 3 digits
        if (length <= 0 || length > 3) {
            return false;
        }
        
        // Check for leading zeros
        if (s[start] == '0' && length > 1) {
            return false;
        }
        
        // Check numeric value
        int val = 0;
        for (int i = start; i < start + length; i++) {
            val = val * 10 + (s[i] - '0');
        }
        
        return val <= 255;
    }

public:
    std::vector<std::string> restoreIpAddresses(std::string s) {
        std::vector<std::string> result;
        int n = s.length();
        
        // IP address must have between 4 and 12 digits
        if (n < 4 || n > 12) {
            return result;
        }
        
        // Try different lengths for each of the four segments
        for (int len1 = 1; len1 <= 3; len1++) {
            for (int len2 = 1; len2 <= 3; len2++) {
                for (int len3 = 1; len3 <= 3; len3++) {
                    for (int len4 = 1; len4 <= 3; len4++) {
                        // Check if the total length matches the string length
                        if (len1 + len2 + len3 + len4 == n) {
                            // Check if each segment is valid
                            if (isValid(s, 0, len1) && isValid(s, len1, len2) &&
                                isValid(s, len1 + len2, len3) && isValid(s, len1 + len2 + len3, len4)) {
                                // Construct a valid IP address
                                std::string ip = s.substr(0, len1) + "." +
                                                s.substr(len1, len2) + "." +
                                                s.substr(len1 + len2, len3) + "." +
                                                s.substr(len1 + len2 + len3, len4);
                                result.push_back(ip);
                            }
                        }
                    }
                }
            }
        }
        
        return result;
    }
};

int main() {
    FourLoopIPAddressRestorer restorer;
    
    // Test cases
    std::vector<std::string> testCases = {
        "25525511135",
        "0000",
        "101023"
    };
    
    for (const std::string& s : testCases) {
        std::vector<std::string> results = restorer.restoreIpAddresses(s);
        
        std::cout << "Input: \"" << s << "\"" << std::endl;
        std::cout << "Valid IP addresses (four loops):" << std::endl;
        
        for (const std::string& ip : results) {
            std::cout << ip << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(1), as we have a fixed number of iterations (3^4 possibilities at most).
**Space Complexity**: O(1).

## Common Pitfalls

1. **Leading Zeros**: Be careful with segments like "01", which are invalid because of the leading zero, while "0" by itself is valid.
2. **Segment Value Range**: Each segment must be between 0 and 255 inclusive.
3. **Dot Placement**: Exactly 3 dots must be placed in the string, creating 4 segments.
4. **Input Length**: The input string must have between 4 and 12 digits to form a valid IP address.
5. **Boundary Checking**: Make sure not to go beyond the string length when extracting segments.

## Extensions

### IPv6 Address Restoration

For IPv6, the rules are different:
- 8 segments separated by colons
- Each segment is a hexadecimal value between 0 and FFFF
- Leading zeros can be omitted
- One or more consecutive segments of all zeros can be replaced with "::"

Restoring IPv6 addresses would require a similar approach but with different validation rules.

## Related LeetCode Problems

1. [93. Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/) - The problem we've covered
2. [17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) - Similar backtracking pattern
3. [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) - Similar string partitioning approach
4. [306. Additive Number](https://leetcode.com/problems/additive-number/) - String partitioning with additional constraints
