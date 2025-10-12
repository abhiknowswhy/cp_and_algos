# Dota2 Senate - Queue Reconstruction
## LeetCode Problem 649

**Difficulty:** Medium  
**Category:** Queue Reconstruction  
**Pattern:** Round-robin elimination with queue-based simulation

## Problem Description

In the world of Dota2, there are two parties: the Radiant and the Dire. The Dota2 senate consists of senators coming from two parties. Now the senators want to decide on a change in the Dota2 game. The voting for this change is a round-based procedure:

1. In each round, each senator can choose one of the two rights:
   - **Ban one senator's right**: A senator can make another senator lose all his rights in this and all the following rounds.
   - **Announce the victory**: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.

2. Given a string senate representing each senator's party belonging (R for Radiant, D for Dire), predict which party will finally announce the victory and output "Radiant" or "Dire".

**Key Constraints:**
- Senators will always choose to ban (if they can) in the optimal strategy
- Senators from the same party will cooperate
- The voting is in the order given in the string

## Real-World Applications

1. **Political Voting Systems**: Modeling sequential voting with elimination rules
2. **Resource Competition**: Simulating competitive resource allocation scenarios
3. **Game Theory**: Implementing optimal strategy games with elimination mechanics
4. **Conflict Resolution**: Modeling negotiation processes with progressive elimination

## Core Algorithm Approaches

### Approach 1: Two Queues Simulation (Optimal)

The most intuitive approach uses two queues to track active senators from each party:

```cpp
#include <queue>
#include <string>
using namespace std;

class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> radiant, dire;
        int n = senate.length();
        
        // Initialize queues with senator positions
        for (int i = 0; i < n; i++) {
            if (senate[i] == 'R') {
                radiant.push(i);
            } else {
                dire.push(i);
            }
        }
        
        // Simulate the voting process
        while (!radiant.empty() && !dire.empty()) {
            int r_idx = radiant.front(); radiant.pop();
            int d_idx = dire.front(); dire.pop();
            
            // Earlier senator wins and gets next turn
            if (r_idx < d_idx) {
                radiant.push(r_idx + n); // Next round position
            } else {
                dire.push(d_idx + n);
            }
        }
        
        return radiant.empty() ? "Dire" : "Radiant";
    }
};
```

**Time Complexity:** O(n) where n is the number of senators  
**Space Complexity:** O(n) for the two queues

### Approach 2: Greedy Counter Method

Track the balance of power using counters:

```cpp
class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.length();
        int radiantCount = 0, direCount = 0;
        int banRadiant = 0, banDire = 0;
        
        // Count initial senators
        for (char c : senate) {
            if (c == 'R') radiantCount++;
            else direCount++;
        }
        
        while (radiantCount > 0 && direCount > 0) {
            for (int i = 0; i < n && radiantCount > 0 && direCount > 0; i++) {
                if (senate[i] == 'R') {
                    if (banRadiant > 0) {
                        banRadiant--;
                        radiantCount--;
                        senate[i] = 'X'; // Banned
                    } else {
                        banDire++;
                    }
                } else if (senate[i] == 'D') {
                    if (banDire > 0) {
                        banDire--;
                        direCount--;
                        senate[i] = 'X'; // Banned
                    } else {
                        banRadiant++;
                    }
                }
            }
        }
        
        return radiantCount > 0 ? "Radiant" : "Dire";
    }
};
```

### Approach 3: Advanced Queue with Round Tracking

Enhanced simulation with explicit round management:

```cpp
#include <queue>
#include <vector>

class AdvancedSenateSimulator {
private:
    struct Senator {
        int id;
        char party;
        int round;
        bool active;
        
        Senator(int i, char p, int r = 0) : id(i), party(p), round(r), active(true) {}
    };
    
public:
    string predictPartyVictory(string senate) {
        queue<Senator> radiant, dire;
        int n = senate.length();
        
        // Initialize with round 0
        for (int i = 0; i < n; i++) {
            if (senate[i] == 'R') {
                radiant.push(Senator(i, 'R', 0));
            } else {
                dire.push(Senator(i, 'D', 0));
            }
        }
        
        int currentRound = 0;
        
        while (!radiant.empty() && !dire.empty()) {
            if (radiant.front().round == currentRound && 
                dire.front().round == currentRound) {
                
                Senator r = radiant.front(); radiant.pop();
                Senator d = dire.front(); dire.pop();
                
                if (r.id < d.id) {
                    radiant.push(Senator(r.id, 'R', currentRound + 1));
                } else {
                    dire.push(Senator(d.id, 'D', currentRound + 1));
                }
            } else if (radiant.front().round < dire.front().round) {
                Senator r = radiant.front(); radiant.pop();
                radiant.push(Senator(r.id, 'R', currentRound + 1));
            } else {
                Senator d = dire.front(); dire.pop();
                dire.push(Senator(d.id, 'D', currentRound + 1));
            }
            
            currentRound++;
        }
        
        return radiant.empty() ? "Dire" : "Radiant";
    }
};
```

## Detailed Algorithm Analysis

### Step-by-Step Process

1. **Initialization Phase**:
   - Parse input string to identify senator positions
   - Create separate queues for each party
   - Store original positions for tie-breaking

2. **Simulation Phase**:
   - Compare front senators from each queue
   - Earlier position wins and eliminates opponent
   - Winner advances to next round (position + n)
   - Continue until one party is eliminated

3. **Victory Determination**:
   - Return party with remaining active senators

### Key Insights

- **Greedy Strategy**: Each senator optimally bans the next opponent
- **Position Matters**: Earlier positions in current round have advantage
- **Cyclic Nature**: Senators get multiple turns in different rounds
- **Queue Simulation**: Natural fit for round-robin elimination

## Complexity Analysis

| Approach | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|--------|
| Two Queues | O(n) | O(n) | Most efficient |
| Greedy Counter | O(n²) | O(1) | Multiple passes |
| Advanced Queue | O(n log n) | O(n) | Detailed tracking |

## Test Cases and Examples

### Example 1: Radiant Victory
```cpp
void testRadiantWin() {
    Solution sol;
    string senate = "RD";
    string result = sol.predictPartyVictory(senate);
    // Expected: "Radiant"
    // Explanation: R eliminates D, R announces victory
}
```

### Example 2: Dire Victory
```cpp
void testDireWin() {
    Solution sol;
    string senate = "RDD";
    string result = sol.predictPartyVictory(senate);
    // Expected: "Dire"
    // Round 1: R eliminates first D, second D eliminates R
    // Round 2: Only D remains
}
```

### Example 3: Complex Scenario
```cpp
void testComplexScenario() {
    Solution sol;
    string senate = "DRDRR";
    string result = sol.predictPartyVictory(senate);
    // Expected: "Radiant"
    // Multiple rounds of elimination
}
```

## Performance Benchmarking

```cpp
#include <chrono>
#include <iostream>

class PerformanceTester {
public:
    void benchmarkApproaches() {
        vector<string> testCases = {
            "RD",
            "RDD", 
            "DRDRR",
            string(10000, 'R') + string(10000, 'D')
        };
        
        for (const auto& test : testCases) {
            cout << "Testing: " << test.substr(0, 10) << "..." << endl;
            
            // Test Two Queues approach
            auto start = chrono::high_resolution_clock::now();
            Solution sol;
            string result1 = sol.predictPartyVictory(test);
            auto end = chrono::high_resolution_clock::now();
            auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
            
            cout << "Two Queues: " << duration1.count() << " µs" << endl;
            cout << "Result: " << result1 << endl << endl;
        }
    }
};
```

## Edge Cases and Considerations

### Critical Edge Cases
1. **Single Senator**: `"R"` → `"Radiant"`
2. **Equal Parties**: `"RDRD"` → Position-dependent
3. **Large Imbalance**: `"RRRD"` → Majority advantage
4. **Alternating Pattern**: `"RDRDRD"` → Complex simulation

### Implementation Gotchas
- Integer overflow with large senate sizes
- Queue empty checks during simulation
- Proper round advancement logic
- Tie-breaking with original positions

## Pattern Recognition: Queue Reconstruction

This problem exemplifies the **Queue Reconstruction** pattern through:

1. **Sequential Processing**: Senators vote in order
2. **State Reconstruction**: Each round rebuilds active participant list
3. **Elimination Logic**: Systematic removal based on rules
4. **Cyclic Behavior**: Multiple rounds with persistent state

### Similar Pattern Problems
- **Task Scheduler** (LeetCode 621)
- **Design Circular Queue** (LeetCode 622)
- **Reveal Cards in Increasing Order** (LeetCode 950)

## Advanced Variations

### Multi-Party Extension
```cpp
class MultiPartySenate {
public:
    string predictMultiPartyVictory(string senate, vector<char> parties) {
        map<char, queue<int>> partyQueues;
        
        // Initialize queues for all parties
        for (char party : parties) {
            partyQueues[party] = queue<int>();
        }
        
        // Populate queues
        for (int i = 0; i < senate.length(); i++) {
            partyQueues[senate[i]].push(i);
        }
        
        // Simulation with multiple parties
        while (countActiveParties(partyQueues) > 1) {
            // Complex multi-party elimination logic
        }
        
        return getWinningParty(partyQueues);
    }
    
private:
    int countActiveParties(const map<char, queue<int>>& queues) {
        int count = 0;
        for (const auto& pair : queues) {
            if (!pair.second.empty()) count++;
        }
        return count;
    }
};
```

## Related LeetCode Problems

1. **[LeetCode 621] Task Scheduler** - Similar greedy queue strategy
2. **[LeetCode 950] Reveal Cards in Increasing Order** - Queue reconstruction
3. **[LeetCode 622] Design Circular Queue** - Queue implementation
4. **[LeetCode 346] Moving Average from Data Stream** - Queue-based sliding window

## Summary

The Dota2 Senate problem demonstrates how queue-based simulation can solve complex elimination scenarios. The key insights are:

- **Optimal Strategy**: Greedy elimination of next opponent
- **Position Importance**: Earlier positions provide voting advantage  
- **Queue Simulation**: Natural representation of round-robin process
- **State Management**: Tracking active participants across rounds

This pattern appears frequently in problems involving sequential processing with state reconstruction, making it a valuable technique for competitive programming and system design scenarios involving conflict resolution and resource allocation.
