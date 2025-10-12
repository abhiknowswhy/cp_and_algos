# Letter Combinations of a Phone Number (Leetcode 17)

## Problem Definition

Given a string containing digits from 2-9, return all possible letter combinations that the number could represent, according to the mapping on a telephone keypad.

The mapping of digits to letters is as follows (same as on telephone buttons):
- 2: "abc"
- 3: "def"
- 4: "ghi"
- 5: "jkl"
- 6: "mno"
- 7: "pqrs"
- 8: "tuv"
- 9: "wxyz"

Note that 1 does not map to any letters.

## Implementations

### 1. Recursive Backtracking Solution

The most intuitive approach is to use recursive backtracking:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class PhoneLetterCombinations {
private:
    std::unordered_map<char, std::string> digitToLetters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };
    
    void backtrack(const std::string& digits, int index, std::string current, 
                  std::vector<std::string>& result) {
        // If we've processed all digits, add the current combination
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }
        
        // Get the letters corresponding to the current digit
        std::string letters = digitToLetters[digits[index]];
        
        // Try each letter
        for (char letter : letters) {
            // Add this letter to our current combination and recurse
            backtrack(digits, index + 1, current + letter, result);
        }
    }

public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> result;
        
        // Handle empty input
        if (digits.empty()) {
            return result;
        }
        
        backtrack(digits, 0, "", result);
        
        return result;
    }
};

int main() {
    PhoneLetterCombinations combiner;
    
    std::vector<std::string> testCases = {
        "23",
        "2",
        "234"
    };
    
    for (const std::string& digits : testCases) {
        std::vector<std::string> combinations = combiner.letterCombinations(digits);
        
        std::cout << "Input: \"" << digits << "\"" << std::endl;
        std::cout << "Letter combinations:" << std::endl;
        
        for (const std::string& combo : combinations) {
            std::cout << "\"" << combo << "\" ";
        }
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(4^n), where n is the length of the input digit string. In the worst case (using digits 7 and 9, which map to 4 letters each), we have 4^n combinations.

**Space Complexity**: O(n) for the recursion stack, plus O(4^n) to store all combinations.

### 2. Iterative Solution

We can also solve this problem iteratively using a queue-like approach:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class IterativePhoneLetterCombinations {
private:
    std::unordered_map<char, std::string> digitToLetters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };

public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> result;
        
        // Handle empty input
        if (digits.empty()) {
            return result;
        }
        
        // Start with an empty string
        result.push_back("");
        
        // Process each digit
        for (char digit : digits) {
            std::vector<std::string> newCombinations;
            std::string letters = digitToLetters[digit];
            
            // For each existing combination, append each letter of the current digit
            for (const std::string& combination : result) {
                for (char letter : letters) {
                    newCombinations.push_back(combination + letter);
                }
            }
            
            // Replace previous combinations with the new ones
            result = newCombinations;
        }
        
        return result;
    }
};

int main() {
    IterativePhoneLetterCombinations combiner;
    
    std::vector<std::string> testCases = {
        "23",
        "2",
        "234"
    };
    
    for (const std::string& digits : testCases) {
        std::vector<std::string> combinations = combiner.letterCombinations(digits);
        
        std::cout << "Input: \"" << digits << "\"" << std::endl;
        std::cout << "Letter combinations (iterative):" << std::endl;
        
        for (const std::string& combo : combinations) {
            std::cout << "\"" << combo << "\" ";
        }
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(4^n), same as the recursive solution.
**Space Complexity**: O(4^n) to store the combinations.

### 3. Optimized Solution with String Reuse

To optimize memory usage, we can modify the recursive solution to reuse the string:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class OptimizedPhoneLetterCombinations {
private:
    std::unordered_map<char, std::string> digitToLetters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };
    
    void backtrack(const std::string& digits, int index, std::string& current, 
                  std::vector<std::string>& result) {
        // If we've processed all digits, add the current combination
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }
        
        // Get the letters corresponding to the current digit
        std::string letters = digitToLetters[digits[index]];
        
        // Try each letter
        for (char letter : letters) {
            // Add this letter
            current.push_back(letter);
            
            // Recurse with the next digit
            backtrack(digits, index + 1, current, result);
            
            // Backtrack (remove the last letter)
            current.pop_back();
        }
    }

public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> result;
        
        // Handle empty input
        if (digits.empty()) {
            return result;
        }
        
        std::string current = "";
        backtrack(digits, 0, current, result);
        
        return result;
    }
};

int main() {
    OptimizedPhoneLetterCombinations combiner;
    
    std::vector<std::string> testCases = {
        "23",
        "2",
        "234"
    };
    
    for (const std::string& digits : testCases) {
        std::vector<std::string> combinations = combiner.letterCombinations(digits);
        
        std::cout << "Input: \"" << digits << "\"" << std::endl;
        std::cout << "Letter combinations (optimized):" << std::endl;
        
        for (const std::string& combo : combinations) {
            std::cout << "\"" << combo << "\" ";
        }
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(4^n)
**Space Complexity**: O(n) for the recursion stack and current string, plus O(4^n) for the output.

### 4. Efficient Solution with Predetermined Vector Size

If we know the exact number of combinations beforehand, we can pre-allocate the result vector:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

class EfficientPhoneLetterCombinations {
private:
    std::unordered_map<char, std::string> digitToLetters = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };

public:
    std::vector<std::string> letterCombinations(std::string digits) {
        // Handle empty input
        if (digits.empty()) {
            return {};
        }
        
        // Calculate the total number of combinations
        int totalCombinations = 1;
        for (char digit : digits) {
            totalCombinations *= digitToLetters[digit].size();
        }
        
        std::vector<std::string> result;
        result.reserve(totalCombinations);
        
        std::string current(digits.size(), ' '); // Pre-allocate string of correct size
        
        std::function<void(int)> backtrack = [&](int index) {
            // If we've processed all digits, add the current combination
            if (index == digits.size()) {
                result.push_back(current);
                return;
            }
            
            // Get the letters corresponding to the current digit
            std::string letters = digitToLetters[digits[index]];
            
            // Try each letter
            for (char letter : letters) {
                current[index] = letter;
                backtrack(index + 1);
            }
        };
        
        backtrack(0);
        
        return result;
    }
};

int main() {
    EfficientPhoneLetterCombinations combiner;
    
    std::vector<std::string> testCases = {
        "23",
        "2",
        "234"
    };
    
    for (const std::string& digits : testCases) {
        std::vector<std::string> combinations = combiner.letterCombinations(digits);
        
        std::cout << "Input: \"" << digits << "\"" << std::endl;
        std::cout << "Letter combinations (efficient):" << std::endl;
        
        for (const std::string& combo : combinations) {
            std::cout << "\"" << combo << "\" ";
        }
        std::cout << std::endl << std::endl;
    }
    
    return 0;
}
```

**Time Complexity**: O(4^n)
**Space Complexity**: O(n) for recursion and current string, plus O(4^n) for the output.

## Extensions

### 1. Word Formation

Extending the problem to find actual words that can be formed from the phone number:

```cpp
std::vector<std::string> findValidWords(const std::string& digits, const std::unordered_set<std::string>& dictionary) {
    std::vector<std::string> allCombinations = letterCombinations(digits);
    std::vector<std::string> validWords;
    
    for (const std::string& combination : allCombinations) {
        if (dictionary.find(combination) != dictionary.end()) {
            validWords.push_back(combination);
        }
    }
    
    return validWords;
}
```

### 2. T9 Predictive Text

Implement a T9 predictive text system that suggests words as the user types digits:

```cpp
class T9System {
private:
    std::unordered_map<std::string, std::vector<std::string>> wordsByDigits;
    
    // Convert a word to its T9 digit sequence
    std::string wordToDigits(const std::string& word) {
        std::unordered_map<char, char> letterToDigit = {
            {'a', '2'}, {'b', '2'}, {'c', '2'},
            {'d', '3'}, {'e', '3'}, {'f', '3'},
            {'g', '4'}, {'h', '4'}, {'i', '4'},
            {'j', '5'}, {'k', '5'}, {'l', '5'},
            {'m', '6'}, {'n', '6'}, {'o', '6'},
            {'p', '7'}, {'q', '7'}, {'r', '7'}, {'s', '7'},
            {'t', '8'}, {'u', '8'}, {'v', '8'},
            {'w', '9'}, {'x', '9'}, {'y', '9'}, {'z', '9'}
        };
        
        std::string digits;
        for (char c : word) {
            digits.push_back(letterToDigit[c]);
        }
        return digits;
    }

public:
    // Initialize the T9 system with a dictionary
    void buildDictionary(const std::vector<std::string>& words) {
        for (const std::string& word : words) {
            std::string digits = wordToDigits(word);
            wordsByDigits[digits].push_back(word);
        }
    }
    
    // Get suggestions for a sequence of digits
    std::vector<std::string> getSuggestions(const std::string& digits) {
        if (wordsByDigits.find(digits) != wordsByDigits.end()) {
            return wordsByDigits[digits];
        }
        return {};
    }
};
```

## Common Pitfalls

1. **Handling Empty Input**: Remember to handle the case when the input string is empty.
2. **Digit-to-Letter Mapping**: Make sure to use the correct mapping according to standard telephone keypads.
3. **Optimization**: For large inputs, consider optimizing memory usage by reusing strings.
4. **Invalid Digits**: Handle the case when digits outside the range 2-9 are provided.

## Related LeetCode Problems

1. [17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) - The problem we've covered
2. [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) - Similar backtracking pattern
3. [93. Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/) - String partitioning with backtracking
4. [784. Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation/) - Generating permutations with letter case variations
5. [46. Permutations](https://leetcode.com/problems/permutations/) - General permutation generation
