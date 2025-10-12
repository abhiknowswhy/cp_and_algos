# Reveal Cards in Increasing Order - Queue Reconstruction
## LeetCode Problem 950

**Difficulty:** Medium  
**Category:** Queue Reconstruction, Simulation  
**Pattern:** Reverse engineering card deck arrangement using deque simulation

## Problem Description

You are given an integer array `deck` representing a deck of cards. Every card has a unique integer. You can order the deck in any way you want.

Initially, all the cards start face down (unrevealed) in one deck.

You will do the following steps repeatedly until all cards are revealed:

1. Take the top card of the deck, reveal it, and take it out of the deck.
2. If there are still cards in the deck, take the next top card of the deck and put it on the bottom of the deck.
3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.

Return an ordering of the deck that would reveal the cards in **increasing order**.

**Note:** The first entry in the answer is considered to be the top of the deck.

## Real-World Applications

1. **Card Games**: Magic trick implementations and card shuffling algorithms
2. **Task Scheduling**: Round-robin scheduling with priority adjustments
3. **Data Streaming**: Reorganizing data streams for sequential processing
4. **Memory Management**: Page replacement algorithms with specific access patterns
5. **Entertainment Systems**: Playlist management with skip patterns

## Core Algorithm Approaches

### Approach 1: Reverse Simulation with Deque (Optimal)

The key insight is to work backwards from the desired result:

```cpp
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        // Sort the deck to get the desired reveal order
        sort(deck.begin(), deck.end());
        
        deque<int> result;
        
        // Work backwards through the sorted deck
        for (int i = deck.size() - 1; i >= 0; i--) {
            if (!result.empty()) {
                // Move the last card to the front (reverse of step 2)
                result.push_front(result.back());
                result.pop_back();
            }
            // Place the current card on top (reverse of step 1)
            result.push_front(deck[i]);
        }
        
        return vector<int>(result.begin(), result.end());
    }
};
```

**Time Complexity:** O(n log n) due to sorting  
**Space Complexity:** O(n) for the deque

### Approach 2: Forward Simulation with Position Tracking

Simulate the exact process to understand the pattern:

```cpp
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());
        
        // Create a queue with positions
        queue<int> positions;
        for (int i = 0; i < n; i++) {
            positions.push(i);
        }
        
        vector<int> result(n);
        
        for (int card : deck) {
            // Reveal: place card at current position
            result[positions.front()] = card;
            positions.pop();
            
            // Move next card to bottom (if exists)
            if (!positions.empty()) {
                positions.push(positions.front());
                positions.pop();
            }
        }
        
        return result;
    }
};
```

### Approach 3: Mathematical Pattern Recognition

Direct calculation using position patterns:

```cpp
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        sort(deck.begin(), deck.end());
        
        vector<int> result(n);
        vector<bool> used(n, false);
        
        int index = 0;
        for (int card : deck) {
            int count = 0;
            
            // Skip to next available position
            while (count < 2) {
                if (!used[index]) count++;
                if (count < 2) index = (index + 1) % n;
            }
            
            result[index] = card;
            used[index] = true;
            index = (index + 1) % n;
        }
        
        return result;
    }
};
```

### Approach 4: Enhanced Simulation with Detailed Tracking

Advanced implementation with step-by-step visualization:

```cpp
#include <deque>
#include <iostream>

class DetailedCardSimulator {
public:
    struct SimulationStep {
        vector<int> deckState;
        int revealedCard;
        string action;
        
        SimulationStep(const vector<int>& deck, int card, const string& act)
            : deckState(deck), revealedCard(card), action(act) {}
    };
    
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());
        
        deque<int> simulation;
        vector<SimulationStep> steps;
        
        // Reverse simulation
        for (int i = deck.size() - 1; i >= 0; i--) {
            if (!simulation.empty()) {
                int moved = simulation.back();
                simulation.pop_back();
                simulation.push_front(moved);
                
                vector<int> currentState(simulation.begin(), simulation.end());
                steps.emplace_back(currentState, moved, "Move to front");
            }
            
            simulation.push_front(deck[i]);
            vector<int> currentState(simulation.begin(), simulation.end());
            steps.emplace_back(currentState, deck[i], "Place card");
        }
        
        return vector<int>(simulation.begin(), simulation.end());
    }
    
    void printSimulation(const vector<SimulationStep>& steps) {
        for (int i = steps.size() - 1; i >= 0; i--) {
            cout << "Step " << (steps.size() - i) << ": " << steps[i].action << endl;
            cout << "Deck: ";
            for (int card : steps[i].deckState) {
                cout << card << " ";
            }
            cout << endl << endl;
        }
    }
};
```

## Detailed Algorithm Analysis

### Step-by-Step Process (Reverse Simulation)

1. **Sort Input**: Arrange cards in increasing order (target reveal sequence)
2. **Initialize Deque**: Start with empty deque for result construction
3. **Reverse Process**: For each card from largest to smallest:
   - If deque not empty: move last card to front (reverse step 2)
   - Add current card to front (reverse step 1)
4. **Return Result**: Convert deque to vector

### Key Insights

- **Reverse Engineering**: Working backwards simplifies the logic
- **Deque Operations**: Natural fit for front/back manipulations
- **Pattern Recognition**: The reveal process creates a specific permutation
- **Simulation Accuracy**: Forward simulation validates the reverse approach

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|--------|
| Reverse Simulation | O(n log n) | O(n) | Most elegant |
| Forward Simulation | O(n log n) | O(n) | Educational |
| Pattern Recognition | O(n log n) | O(n) | Complex logic |
| Enhanced Tracking | O(n log n) | O(n) | Debug-friendly |

## Test Cases and Examples

### Example 1: Basic Case
```cpp
void testBasicCase() {
    Solution sol;
    vector<int> deck = {17, 13, 11, 2, 3, 5, 7};
    vector<int> result = sol.deckRevealedIncreasing(deck);
    
    // Expected: [2, 13, 3, 11, 5, 17, 7]
    // Reveal sequence: 2, 3, 5, 7, 11, 13, 17
    
    cout << "Original: ";
    for (int card : deck) cout << card << " ";
    cout << endl;
    
    cout << "Arranged: ";
    for (int card : result) cout << card << " ";
    cout << endl;
}
```

### Example 2: Small Cases
```cpp
void testSmallCases() {
    Solution sol;
    
    // Single card
    vector<int> single = {1};
    vector<int> result1 = sol.deckRevealedIncreasing(single);
    // Expected: [1]
    
    // Two cards
    vector<int> two = {1, 2};
    vector<int> result2 = sol.deckRevealedIncreasing(two);
    // Expected: [1, 2]
    
    // Three cards
    vector<int> three = {1, 2, 3};
    vector<int> result3 = sol.deckRevealedIncreasing(three);
    // Expected: [1, 3, 2]
}
```

### Example 3: Validation Function
```cpp
bool validateSolution(vector<int>& original, vector<int>& arranged) {
    deque<int> deck(arranged.begin(), arranged.end());
    vector<int> revealed;
    
    while (!deck.empty()) {
        // Reveal top card
        revealed.push_back(deck.front());
        deck.pop_front();
        
        // Move next card to bottom
        if (!deck.empty()) {
            deck.push_back(deck.front());
            deck.pop_front();
        }
    }
    
    // Check if revealed sequence is sorted
    vector<int> sorted_original = original;
    sort(sorted_original.begin(), sorted_original.end());
    
    return revealed == sorted_original;
}
```

## Performance Analysis and Benchmarking

```cpp
#include <chrono>
#include <random>

class PerformanceTester {
public:
    void benchmarkApproaches() {
        vector<int> sizes = {10, 100, 1000, 10000};
        
        for (int size : sizes) {
            vector<int> deck = generateRandomDeck(size);
            
            cout << "Testing size: " << size << endl;
            
            // Test reverse simulation
            auto start = chrono::high_resolution_clock::now();
            Solution sol;
            vector<int> result1 = sol.deckRevealedIncreasing(deck);
            auto end = chrono::high_resolution_clock::now();
            auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
            
            cout << "Reverse Simulation: " << duration1.count() << " µs" << endl;
            
            // Validate result
            bool isValid = validateSolution(deck, result1);
            cout << "Validation: " << (isValid ? "PASS" : "FAIL") << endl << endl;
        }
    }
    
private:
    vector<int> generateRandomDeck(int size) {
        vector<int> deck(size);
        iota(deck.begin(), deck.end(), 1);
        
        random_device rd;
        mt19937 g(rd());
        shuffle(deck.begin(), deck.end(), g);
        
        return deck;
    }
};
```

## Visualization and Debugging Tools

### Step-by-Step Visualizer
```cpp
class CardRevealVisualizer {
public:
    void visualizeProcess(vector<int>& deck) {
        cout << "=== Card Reveal Visualization ===" << endl;
        
        // Show original and sorted
        cout << "Original deck: ";
        for (int card : deck) cout << card << " ";
        cout << endl;
        
        vector<int> sorted_deck = deck;
        sort(sorted_deck.begin(), sorted_deck.end());
        cout << "Target sequence: ";
        for (int card : sorted_deck) cout << card << " ";
        cout << endl << endl;
        
        // Reverse simulation with steps
        deque<int> result;
        cout << "Reverse simulation steps:" << endl;
        
        for (int i = sorted_deck.size() - 1; i >= 0; i--) {
            if (!result.empty()) {
                int moved = result.back();
                result.pop_back();
                result.push_front(moved);
                
                cout << "Move " << moved << " to front: ";
                printDeque(result);
            }
            
            result.push_front(sorted_deck[i]);
            cout << "Place " << sorted_deck[i] << " on top: ";
            printDeque(result);
        }
        
        cout << endl << "Final arrangement: ";
        for (int card : result) cout << card << " ";
        cout << endl;
        
        // Verify by forward simulation
        verifyBySimulation(vector<int>(result.begin(), result.end()));
    }
    
private:
    void printDeque(const deque<int>& dq) {
        cout << "[";
        for (int i = 0; i < dq.size(); i++) {
            cout << dq[i];
            if (i < dq.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    void verifyBySimulation(vector<int> arranged) {
        cout << endl << "Verification by forward simulation:" << endl;
        deque<int> deck(arranged.begin(), arranged.end());
        
        int step = 1;
        while (!deck.empty()) {
            cout << "Step " << step++ << ": ";
            
            // Reveal
            int revealed = deck.front();
            deck.pop_front();
            cout << "Reveal " << revealed;
            
            if (!deck.empty()) {
                // Move to bottom
                int moved = deck.front();
                deck.pop_front();
                deck.push_back(moved);
                cout << ", Move " << moved << " to bottom";
            }
            
            cout << " -> Deck: ";
            printDeque(deck);
        }
    }
};
```

## Edge Cases and Special Scenarios

### Critical Edge Cases
1. **Single Card**: `[1]` → `[1]`
2. **Two Cards**: `[1,2]` → `[1,2]`
3. **Sorted Input**: Already in increasing order
4. **Reverse Sorted**: Maximum shuffling needed
5. **Large Deck**: Performance with 10^4 cards

### Implementation Considerations
- Deque vs vector performance trade-offs
- Memory allocation patterns
- Sorting algorithm stability
- Integer overflow for large card values

## Pattern Recognition: Queue Reconstruction

This problem exemplifies **Queue Reconstruction** through:

1. **Process Reversal**: Working backwards from desired outcome
2. **State Simulation**: Modeling card deck operations precisely
3. **Queue Operations**: Natural deque usage for front/back access
4. **Pattern Analysis**: Understanding the permutation structure

### Similar Problems in This Pattern
- **Josephus Problem**: Elimination in circular arrangement
- **Task Scheduling**: Round-robin with priorities
- **Casino Card Games**: Specific dealing patterns

## Advanced Variations and Extensions

### Variation 1: Custom Reveal Pattern
```cpp
class CustomRevealPattern {
public:
    vector<int> deckRevealedWithPattern(vector<int>& deck, vector<int>& pattern) {
        // pattern[i] = number of cards to move to bottom at step i
        sort(deck.begin(), deck.end());
        
        deque<int> result;
        for (int i = deck.size() - 1; i >= 0; i--) {
            if (!result.empty()) {
                int moves = pattern[i] % result.size();
                for (int j = 0; j < moves; j++) {
                    result.push_front(result.back());
                    result.pop_back();
                }
            }
            result.push_front(deck[i]);
        }
        
        return vector<int>(result.begin(), result.end());
    }
};
```

### Variation 2: Multiple Decks
```cpp
class MultiDeckSimulator {
public:
    vector<vector<int>> revealMultipleDecks(vector<vector<int>>& decks) {
        vector<vector<int>> results;
        
        for (auto& deck : decks) {
            Solution sol;
            results.push_back(sol.deckRevealedIncreasing(deck));
        }
        
        return results;
    }
};
```

## Related LeetCode Problems

1. **[LeetCode 649] Dota2 Senate** - Similar queue simulation
2. **[LeetCode 641] Design Circular Deque** - Deque implementation
3. **[LeetCode 622] Design Circular Queue** - Queue operations
4. **[LeetCode 1535] Find the Winner of an Array Game** - Elimination pattern

## Mathematical Properties

### Permutation Analysis
The reveal process creates a specific permutation that can be characterized by:
- Position mapping function: `f(i) = reveal_position(i)`
- Inverse permutation for reconstruction
- Cycle structure in the permutation

### Complexity Bounds
- Minimum comparisons: Ω(n log n) due to sorting requirement
- Optimal space: O(n) for storing the result
- Worst-case operations: O(n) deque manipulations

## Summary

The Reveal Cards in Increasing Order problem demonstrates elegant queue reconstruction principles:

- **Reverse Engineering**: Solving by working backwards from the goal
- **Deque Efficiency**: Natural data structure for the required operations
- **Simulation Accuracy**: Forward validation confirms reverse construction
- **Pattern Recognition**: Understanding the underlying permutation structure

This problem teaches valuable lessons about:
- When to use reverse simulation vs forward simulation
- The power of deque operations for complex rearrangements
- How sorting combined with simulation can solve ordering problems
- The importance of validation in algorithm design

The techniques learned here apply broadly to problems involving sequential processing, game simulations, and data structure manipulation in competitive programming.
