# Minimum genetic mutation

## Problem Description

**LeetCode Problem #433 - Medium**
🔗 [LeetCode Link](https://leetcode.com/problems/minimum-genetic-mutation/)

A gene string can be represented by an 8-character string, with choices from `'A'`, `'C'`, `'G'`, and `'T'`.

Suppose we need to investigate a mutation from a gene string `start` to a gene string `end` where one mutation is defined as one single character change in the gene string.

- For example, `"AACCGGTT" → "AACCGGTA"` is one mutation.

There is also a gene bank `bank` that records all the valid gene mutations. A gene must be in `bank` to make it a valid gene string.

Given the three things - `start`, `end`, and `bank`, return the minimum number of mutations needed to mutate from `start` to `end`. If there is no such a mutation, return `-1`.

**Key Constraints:**
- `start.length == 8`
- `end.length == 8`
- `0 <= bank.length <= 10`
- `bank[i].length == 8`
- `start`, `end`, and `bank[i]` consist of only the characters `['A', 'C', 'G', 'T']`

## Queue Pattern Connection

This problem demonstrates **Bidirectional BFS** patterns where:
- We search simultaneously from both start and end points
- Two queues are used to explore from both directions
- Meeting point indicates shortest path found
- Significantly reduces search space compared to unidirectional BFS
- Pattern applies to shortest path problems in large state spaces

## Approach

### Approach 1: Bidirectional BFS (Optimal)
Use two BFS queues starting from both start and end genes. When they meet, return the sum of steps.

### Approach 2: Standard BFS
Single-direction BFS from start to end gene.

### Approach 3: A* Search
Use heuristic distance (Hamming distance) to guide search toward target.

### Approach 4: DFS with Memoization
Recursive approach with pruning based on minimum steps found.

## Algorithm Steps

### Bidirectional BFS Approach:
1. **Initialize**: Create two sets for visited genes from start and end
2. **Setup Queues**: Add start gene to forward queue, end gene to backward queue
3. **Alternate Search**: Process smaller queue first for optimization
4. **Generate Mutations**: For each gene, try all possible single-character mutations
5. **Check Intersection**: If a mutation exists in the opposite visited set, return total steps
6. **Continue**: Add valid mutations to queue and visited set
7. **Terminate**: Return -1 if no path exists

## Implementation

### Implementation 1: Optimal Bidirectional BFS

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <algorithm>

class GeneticMutation {
public:
    /**
     * Find minimum mutations using Bidirectional BFS
     * Time: O(4^n * n) where n = gene length (8)
     * Space: O(4^n)
     */
    int minMutation(std::string start, std::string end, std::vector<std::string>& bank) {
        if (start == end) return 0;
        
        std::unordered_set<std::string> bankSet(bank.begin(), bank.end());
        if (bankSet.find(end) == bankSet.end()) return -1;
        
        std::unordered_set<std::string> visitedStart{start};
        std::unordered_set<std::string> visitedEnd{end};
        
        std::queue<std::string> queueStart;
        std::queue<std::string> queueEnd;
        queueStart.push(start);
        queueEnd.push(end);
        
        int steps = 0;
        
        while (!queueStart.empty() && !queueEnd.empty()) {
            steps++;
            
            // Always process the smaller queue for optimization
            if (queueStart.size() > queueEnd.size()) {
                std::swap(queueStart, queueEnd);
                std::swap(visitedStart, visitedEnd);
            }
            
            int size = queueStart.size();
            for (int i = 0; i < size; i++) {
                std::string current = queueStart.front();
                queueStart.pop();
                
                // Generate all possible mutations
                for (int pos = 0; pos < 8; pos++) {
                    char originalChar = current[pos];
                    
                    for (char mutation : {'A', 'C', 'G', 'T'}) {
                        if (mutation == originalChar) continue;
                        
                        current[pos] = mutation;
                        
                        // Check if we found intersection
                        if (visitedEnd.find(current) != visitedEnd.end()) {
                            return steps;
                        }
                        
                        // Add to queue if valid and not visited
                        if (bankSet.find(current) != bankSet.end() && 
                            visitedStart.find(current) == visitedStart.end()) {
                            visitedStart.insert(current);
                            queueStart.push(current);
                        }
                    }
                    
                    current[pos] = originalChar;  // Restore
                }
            }
        }
        
        return -1;  // No path found
    }
    
    // Utility function to get Hamming distance
    int hammingDistance(const std::string& a, const std::string& b) {
        int distance = 0;
        for (int i = 0; i < 8; i++) {
            if (a[i] != b[i]) distance++;
        }
        return distance;
    }
};
```

### Implementation 2: Standard BFS with Optimizations

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

class GeneticMutationBFS {
public:
    int minMutation(std::string start, std::string end, std::vector<std::string>& bank) {
        if (start == end) return 0;
        
        std::unordered_set<std::string> bankSet(bank.begin(), bank.end());
        if (bankSet.find(end) == bankSet.end()) return -1;
        
        std::queue<std::pair<std::string, int>> queue;
        std::unordered_set<std::string> visited;
        
        queue.push({start, 0});
        visited.insert(start);
        
        while (!queue.empty()) {
            auto [current, steps] = queue.front();
            queue.pop();
            
            // Generate all valid mutations
            for (int pos = 0; pos < 8; pos++) {
                char originalChar = current[pos];
                
                for (char mutation : {'A', 'C', 'G', 'T'}) {
                    if (mutation == originalChar) continue;
                    
                    current[pos] = mutation;
                    
                    if (current == end) {
                        return steps + 1;
                    }
                    
                    if (bankSet.count(current) && !visited.count(current)) {
                        visited.insert(current);
                        queue.push({current, steps + 1});
                    }
                }
                
                current[pos] = originalChar;  // Restore
            }
        }
        
        return -1;
    }
    
    // Enhanced version with path tracking
    std::vector<std::string> findMutationPath(std::string start, std::string end, 
                                             std::vector<std::string>& bank) {
        if (start == end) return {start};
        
        std::unordered_set<std::string> bankSet(bank.begin(), bank.end());
        if (bankSet.find(end) == bankSet.end()) return {};
        
        std::queue<std::string> queue;
        std::unordered_map<std::string, std::string> parent;
        std::unordered_set<std::string> visited;
        
        queue.push(start);
        visited.insert(start);
        parent[start] = "";
        
        while (!queue.empty()) {
            std::string current = queue.front();
            queue.pop();
            
            for (int pos = 0; pos < 8; pos++) {
                char originalChar = current[pos];
                
                for (char mutation : {'A', 'C', 'G', 'T'}) {
                    if (mutation == originalChar) continue;
                    
                    current[pos] = mutation;
                    
                    if (current == end) {
                        // Reconstruct path
                        std::vector<std::string> path;
                        std::string node = end;
                        
                        while (node != "") {
                            path.push_back(node);
                            node = parent[node];
                        }
                        
                        std::reverse(path.begin(), path.end());
                        return path;
                    }
                    
                    if (bankSet.count(current) && !visited.count(current)) {
                        visited.insert(current);
                        parent[current] = queue.back();
                        queue.push(current);
                    }
                }
                
                current[pos] = originalChar;
            }
        }
        
        return {};  // No path found
    }
};
```

### Implementation 3: A* Search with Heuristic

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <priority_queue>
#include <unordered_map>

class GeneticMutationAStar {
private:
    struct Node {
        std::string gene;
        int gScore;  // Actual cost from start
        int fScore;  // gScore + heuristic
        
        bool operator>(const Node& other) const {
            return fScore > other.fScore;
        }
    };
    
    int heuristic(const std::string& current, const std::string& target) {
        int distance = 0;
        for (int i = 0; i < 8; i++) {
            if (current[i] != target[i]) distance++;
        }
        return distance;
    }
    
public:
    int minMutation(std::string start, std::string end, std::vector<std::string>& bank) {
        if (start == end) return 0;
        
        std::unordered_set<std::string> bankSet(bank.begin(), bank.end());
        if (bankSet.find(end) == bankSet.end()) return -1;
        
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::unordered_map<std::string, int> gScore;
        
        pq.push({start, 0, heuristic(start, end)});
        gScore[start] = 0;
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            if (current.gene == end) {
                return current.gScore;
            }
            
            // Skip if we've found a better path
            if (gScore.count(current.gene) && current.gScore > gScore[current.gene]) {
                continue;
            }
            
            // Generate mutations
            for (int pos = 0; pos < 8; pos++) {
                char originalChar = current.gene[pos];
                
                for (char mutation : {'A', 'C', 'G', 'T'}) {
                    if (mutation == originalChar) continue;
                    
                    current.gene[pos] = mutation;
                    
                    if (bankSet.count(current.gene)) {
                        int tentativeGScore = current.gScore + 1;
                        
                        if (!gScore.count(current.gene) || 
                            tentativeGScore < gScore[current.gene]) {
                            gScore[current.gene] = tentativeGScore;
                            int fScore = tentativeGScore + heuristic(current.gene, end);
                            pq.push({current.gene, tentativeGScore, fScore});
                        }
                    }
                }
                
                current.gene[pos] = originalChar;
            }
        }
        
        return -1;
    }
};
```

### Implementation 4: DFS with Memoization

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <climits>

class GeneticMutationDFS {
private:
    std::unordered_set<std::string> bankSet;
    std::unordered_map<std::string, int> memo;
    std::string target;
    
    int dfs(const std::string& current, std::unordered_set<std::string>& visited) {
        if (current == target) return 0;
        
        if (memo.count(current)) return memo[current];
        
        int minSteps = INT_MAX;
        
        for (int pos = 0; pos < 8; pos++) {
            char originalChar = current[pos];
            
            for (char mutation : {'A', 'C', 'G', 'T'}) {
                if (mutation == originalChar) continue;
                
                std::string mutated = current;
                mutated[pos] = mutation;
                
                if (bankSet.count(mutated) && !visited.count(mutated)) {
                    visited.insert(mutated);
                    int steps = dfs(mutated, visited);
                    if (steps != INT_MAX) {
                        minSteps = std::min(minSteps, steps + 1);
                    }
                    visited.erase(mutated);
                }
            }
        }
        
        return memo[current] = minSteps;
    }
    
public:
    int minMutation(std::string start, std::string end, std::vector<std::string>& bank) {
        if (start == end) return 0;
        
        bankSet = std::unordered_set<std::string>(bank.begin(), bank.end());
        if (!bankSet.count(end)) return -1;
        
        target = end;
        memo.clear();
        
        std::unordered_set<std::string> visited{start};
        int result = dfs(start, visited);
        
        return result == INT_MAX ? -1 : result;
    }
};
```

### Implementation 5: Advanced Bidirectional with Pruning

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>

class GeneticMutationAdvanced {
private:
    struct SearchState {
        std::unordered_set<std::string> visited;
        std::queue<std::string> queue;
        std::unordered_map<std::string, int> distance;
    };
    
    std::vector<std::string> generateMutations(const std::string& gene) {
        std::vector<std::string> mutations;
        mutations.reserve(24);  // 8 positions * 3 mutations each
        
        for (int pos = 0; pos < 8; pos++) {
            char originalChar = gene[pos];
            
            for (char mutation : {'A', 'C', 'G', 'T'}) {
                if (mutation != originalChar) {
                    std::string mutated = gene;
                    mutated[pos] = mutation;
                    mutations.push_back(mutated);
                }
            }
        }
        
        return mutations;
    }
    
public:
    int minMutation(std::string start, std::string end, std::vector<std::string>& bank) {
        if (start == end) return 0;
        
        std::unordered_set<std::string> bankSet(bank.begin(), bank.end());
        if (!bankSet.count(end)) return -1;
        
        SearchState forward, backward;
        
        // Initialize forward search
        forward.visited.insert(start);
        forward.queue.push(start);
        forward.distance[start] = 0;
        
        // Initialize backward search
        backward.visited.insert(end);
        backward.queue.push(end);
        backward.distance[end] = 0;
        
        while (!forward.queue.empty() && !backward.queue.empty()) {
            // Choose smaller frontier for expansion
            SearchState* current = (forward.queue.size() <= backward.queue.size()) 
                                  ? &forward : &backward;
            SearchState* opposite = (current == &forward) ? &backward : &forward;
            
            int currentSize = current->queue.size();
            
            for (int i = 0; i < currentSize; i++) {
                std::string gene = current->queue.front();
                current->queue.pop();
                
                std::vector<std::string> mutations = generateMutations(gene);
                
                for (const std::string& mutation : mutations) {
                    if (!bankSet.count(mutation)) continue;
                    
                    // Check if found in opposite search
                    if (opposite->visited.count(mutation)) {
                        return current->distance[gene] + 1 + opposite->distance[mutation];
                    }
                    
                    // Add to current search if not visited
                    if (!current->visited.count(mutation)) {
                        current->visited.insert(mutation);
                        current->queue.push(mutation);
                        current->distance[mutation] = current->distance[gene] + 1;
                    }
                }
            }
        }
        
        return -1;
    }
    
    // Statistical analysis of search efficiency
    struct SearchStats {
        int totalNodesExplored;
        int maxQueueSize;
        int intersectionDepth;
        double pruningEfficiency;
    };
    
    SearchStats analyzeSearch(std::string start, std::string end, 
                             std::vector<std::string>& bank) {
        SearchStats stats = {0, 0, 0, 0.0};
        
        // Implementation would track statistics during search
        return stats;
    }
};
```

## Complexity Analysis

### Bidirectional BFS:
- **Time Complexity**: O(4^(n/2) * n) where n = 8 (gene length)
- **Space Complexity**: O(4^(n/2)) for visited sets and queues
- **Advantage**: Reduces search space from O(4^n) to O(2 * 4^(n/2))

### Standard BFS:
- **Time Complexity**: O(4^n * n) where n = 8
- **Space Complexity**: O(4^n) for visited set and queue
- **Total Mutations**: At most 4^8 = 65,536 possible gene strings

### A* Search:
- **Time Complexity**: O(4^n * n * log(4^n)) due to priority queue
- **Space Complexity**: O(4^n)
- **Advantage**: Can find optimal solution faster with good heuristic

## Examples

### Example 1: Basic Mutation Chain

```cpp
void example1() {
    GeneticMutation gm;
    
    std::string start = "AACCGGTT";
    std::string end = "AACCGGTA";
    std::vector<std::string> bank = {"AACCGGTA"};
    
    int result = gm.minMutation(start, end, bank);
    std::cout << "Minimum mutations: " << result << std::endl;  // Output: 1
    
    // Show the mutation
    std::cout << "Mutation: " << start << " -> " << end << std::endl;
    std::cout << "Changed position 7: T -> A" << std::endl;
}
```

### Example 2: Multi-Step Mutation

```cpp
void example2() {
    GeneticMutation gm;
    
    std::string start = "AACCGGTT";
    std::string end = "AAACGGTA";
    std::vector<std::string> bank = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    
    int result = gm.minMutation(start, end, bank);
    std::cout << "Minimum mutations: " << result << std::endl;  // Output: 2
    
    // Possible path: AACCGGTT -> AACCGGTA -> AAACGGTA
    GeneticMutationBFS gmBFS;
    auto path = gmBFS.findMutationPath(start, end, bank);
    
    std::cout << "Mutation path: ";
    for (const auto& gene : path) {
        std::cout << gene << " ";
    }
    std::cout << std::endl;
}
```

### Example 3: No Valid Path

```cpp
void example3() {
    GeneticMutation gm;
    
    std::string start = "AACCGGTT";
    std::string end = "AACCGGTA";
    std::vector<std::string> bank = {};  // Empty bank
    
    int result = gm.minMutation(start, end, bank);
    std::cout << "Minimum mutations: " << result << std::endl;  // Output: -1
    
    std::cout << "No valid mutations possible (empty bank)" << std::endl;
}
```

### Example 4: Performance Comparison

```cpp
#include <chrono>

void performanceComparison() {
    std::string start = "AACCGGTT";
    std::string end = "TTCCGGAA";
    
    // Generate comprehensive bank
    std::vector<std::string> bank;
    std::string base = "AAAAAAAA";
    
    // Generate all possible 2-3 step mutations
    for (int i = 0; i < 8; i++) {
        for (char c : {'A', 'C', 'G', 'T'}) {
            std::string mutation = start;
            mutation[i] = c;
            bank.push_back(mutation);
        }
    }
    
    // Test Bidirectional BFS
    auto start_time = std::chrono::high_resolution_clock::now();
    GeneticMutation gm;
    int result1 = gm.minMutation(start, end, bank);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    // Test Standard BFS
    start_time = std::chrono::high_resolution_clock::now();
    GeneticMutationBFS gmBFS;
    int result2 = gmBFS.minMutation(start, end, bank);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    // Test A* Search
    start_time = std::chrono::high_resolution_clock::now();
    GeneticMutationAStar gmAStar;
    int result3 = gmAStar.minMutation(start, end, bank);
    end_time = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    std::cout << "Results (all should be equal): " << result1 << ", " << result2 << ", " << result3 << std::endl;
    std::cout << "Bidirectional BFS: " << duration1.count() << " μs" << std::endl;
    std::cout << "Standard BFS: " << duration2.count() << " μs" << std::endl;
    std::cout << "A* Search: " << duration3.count() << " μs" << std::endl;
    
    double speedup = (double)duration2.count() / duration1.count();
    std::cout << "Bidirectional speedup: " << speedup << "x" << std::endl;
}
```

## Real-World Applications

### 1. **Bioinformatics Sequence Analysis**

```cpp
class SequenceAnalyzer {
private:
    GeneticMutationAdvanced mutationFinder;
    
public:
    struct MutationAnalysis {
        int minMutations;
        std::vector<std::string> mutationPath;
        std::vector<int> mutationPositions;
        double confidence;
    };
    
    MutationAnalysis analyzeEvolution(const std::string& ancestral,
                                     const std::string& modern,
                                     const std::vector<std::string>& fossils) {
        MutationAnalysis analysis;
        
        // Find minimum mutation path
        std::vector<std::string> bank = fossils;
        analysis.minMutations = mutationFinder.minMutation(ancestral, modern, bank);
        
        // Calculate confidence based on fossil evidence
        analysis.confidence = calculateConfidence(ancestral, modern, fossils);
        
        return analysis;
    }
    
private:
    double calculateConfidence(const std::string& start, const std::string& end,
                              const std::vector<std::string>& evidence) {
        // Complex confidence calculation based on evolutionary models
        return 0.85;  // Simplified
    }
};
```

### 2. **Drug Discovery Molecular Design**

```cpp
class MolecularDesign {
private:
    struct Molecule {
        std::string sequence;
        double bindingAffinity;
        double toxicity;
        double stability;
    };
    
    GeneticMutation optimizer;
    
public:
    std::vector<Molecule> findOptimalDrug(const std::string& targetProtein,
                                         const std::vector<std::string>& knownCompounds) {
        std::vector<Molecule> candidates;
        
        // Use mutation search to explore chemical space
        for (const auto& compound : knownCompounds) {
            // Find mutations that improve binding
            auto mutations = generateTherapeuticMutations(compound, targetProtein);
            
            for (const auto& mutation : mutations) {
                Molecule candidate;
                candidate.sequence = mutation;
                candidate.bindingAffinity = calculateBinding(mutation, targetProtein);
                candidate.toxicity = assessToxicity(mutation);
                candidate.stability = measureStability(mutation);
                
                if (isViableDrug(candidate)) {
                    candidates.push_back(candidate);
                }
            }
        }
        
        return candidates;
    }
    
private:
    std::vector<std::string> generateTherapeuticMutations(const std::string& compound,
                                                          const std::string& target) {
        // Implementation would use domain-specific mutation rules
        return {};
    }
    
    double calculateBinding(const std::string& compound, const std::string& target) {
        // Simplified binding affinity calculation
        return 0.5;
    }
    
    double assessToxicity(const std::string& compound) {
        // Toxicity prediction model
        return 0.1;
    }
    
    double measureStability(const std::string& compound) {
        // Molecular stability assessment
        return 0.8;
    }
    
    bool isViableDrug(const Molecule& candidate) {
        return candidate.bindingAffinity > 0.7 && 
               candidate.toxicity < 0.3 && 
               candidate.stability > 0.6;
    }
};
```

### 3. **Evolutionary Biology Simulation**

```cpp
class EvolutionSimulator {
private:
    struct Population {
        std::vector<std::string> individuals;
        std::vector<double> fitness;
        int generation;
    };
    
    GeneticMutationDFS pathFinder;
    
public:
    struct EvolutionResult {
        std::vector<Population> generations;
        std::vector<std::string> evolutionaryPath;
        int totalGenerations;
        double averageFitness;
    };
    
    EvolutionResult simulateEvolution(const std::string& ancestor,
                                     const std::string& target,
                                     int populationSize,
                                     double mutationRate) {
        EvolutionResult result;
        Population currentPop;
        
        // Initialize population
        currentPop.individuals.resize(populationSize, ancestor);
        currentPop.fitness.resize(populationSize);
        currentPop.generation = 0;
        
        while (!hasReachedTarget(currentPop, target) && currentPop.generation < 1000) {
            // Calculate fitness for current population
            for (int i = 0; i < populationSize; i++) {
                currentPop.fitness[i] = calculateFitness(currentPop.individuals[i], target);
            }
            
            result.generations.push_back(currentPop);
            
            // Generate next generation
            currentPop = generateNextGeneration(currentPop, mutationRate);
            currentPop.generation++;
        }
        
        result.totalGenerations = currentPop.generation;
        result.averageFitness = calculateAverageFitness(result.generations.back());
        
        return result;
    }
    
private:
    bool hasReachedTarget(const Population& pop, const std::string& target) {
        for (const auto& individual : pop.individuals) {
            if (individual == target) return true;
        }
        return false;
    }
    
    double calculateFitness(const std::string& individual, const std::string& target) {
        int differences = 0;
        for (int i = 0; i < 8; i++) {
            if (individual[i] != target[i]) differences++;
        }
        return 1.0 / (1.0 + differences);  // Higher fitness for fewer differences
    }
    
    Population generateNextGeneration(const Population& current, double mutationRate) {
        Population next;
        next.generation = current.generation + 1;
        next.individuals.reserve(current.individuals.size());
        next.fitness.reserve(current.individuals.size());
        
        // Selection and mutation logic
        for (const auto& individual : current.individuals) {
            std::string offspring = individual;
            
            // Apply mutations
            for (int pos = 0; pos < 8; pos++) {
                if ((double)rand() / RAND_MAX < mutationRate) {
                    char mutations[] = {'A', 'C', 'G', 'T'};
                    offspring[pos] = mutations[rand() % 4];
                }
            }
            
            next.individuals.push_back(offspring);
        }
        
        return next;
    }
    
    double calculateAverageFitness(const Population& pop) {
        double sum = 0.0;
        for (double fitness : pop.fitness) {
            sum += fitness;
        }
        return sum / pop.fitness.size();
    }
};
```

### 4. **Genetic Algorithm Optimization**

```cpp
class GeneticOptimizer {
private:
    GeneticMutationAdvanced searcher;
    
public:
    struct OptimizationResult {
        std::string bestSolution;
        double bestFitness;
        int iterations;
        std::vector<std::string> convergencePath;
    };
    
    OptimizationResult optimize(const std::string& initial,
                               std::function<double(const std::string&)> fitnessFunction,
                               const std::vector<std::string>& constraints,
                               int maxIterations = 1000) {
        OptimizationResult result;
        
        std::string currentBest = initial;
        double currentBestFitness = fitnessFunction(initial);
        
        result.convergencePath.push_back(initial);
        
        for (int iteration = 0; iteration < maxIterations; iteration++) {
            // Generate neighboring solutions using single mutations
            std::vector<std::string> neighbors = generateNeighbors(currentBest);
            
            // Filter by constraints
            neighbors = filterByConstraints(neighbors, constraints);
            
            // Evaluate neighbors
            for (const auto& neighbor : neighbors) {
                double fitness = fitnessFunction(neighbor);
                
                if (fitness > currentBestFitness) {
                    currentBest = neighbor;
                    currentBestFitness = fitness;
                    result.convergencePath.push_back(neighbor);
                }
            }
            
            // Convergence check
            if (hasConverged(result.convergencePath)) {
                break;
            }
        }
        
        result.bestSolution = currentBest;
        result.bestFitness = currentBestFitness;
        result.iterations = result.convergencePath.size() - 1;
        
        return result;
    }
    
private:
    std::vector<std::string> generateNeighbors(const std::string& current) {
        std::vector<std::string> neighbors;
        
        for (int pos = 0; pos < 8; pos++) {
            for (char mutation : {'A', 'C', 'G', 'T'}) {
                if (mutation != current[pos]) {
                    std::string neighbor = current;
                    neighbor[pos] = mutation;
                    neighbors.push_back(neighbor);
                }
            }
        }
        
        return neighbors;
    }
    
    std::vector<std::string> filterByConstraints(const std::vector<std::string>& candidates,
                                                const std::vector<std::string>& constraints) {
        std::vector<std::string> filtered;
        std::unordered_set<std::string> validSet(constraints.begin(), constraints.end());
        
        for (const auto& candidate : candidates) {
            if (constraints.empty() || validSet.count(candidate)) {
                filtered.push_back(candidate);
            }
        }
        
        return filtered;
    }
    
    bool hasConverged(const std::vector<std::string>& path) {
        if (path.size() < 10) return false;
        
        // Check if no improvement in last 5 iterations
        for (int i = path.size() - 5; i < path.size() - 1; i++) {
            if (path[i] != path.back()) return false;
        }
        
        return true;
    }
};
```

### 5. **Protein Folding Prediction**

```cpp
class ProteinFolder {
private:
    GeneticMutationAStar pathOptimizer;
    
public:
    struct FoldingPrediction {
        std::string sequence;
        std::string structure;
        double foldingEnergy;
        double stability;
        std::vector<std::string> intermediates;
    };
    
    FoldingPrediction predictFolding(const std::string& aminoAcidSequence,
                                    const std::vector<std::string>& knownFolds) {
        FoldingPrediction prediction;
        prediction.sequence = aminoAcidSequence;
        
        // Find optimal folding path using mutation search
        std::string startConformation = generateExtendedConformation(aminoAcidSequence);
        std::string targetConformation = findLowestEnergyConformation(aminoAcidSequence, knownFolds);
        
        // Use mutation search to find folding pathway
        std::vector<std::string> foldingBank = generateFoldingIntermediates(knownFolds);
        
        int steps = pathOptimizer.minMutation(startConformation, targetConformation, foldingBank);
        
        if (steps != -1) {
            prediction.structure = targetConformation;
            prediction.foldingEnergy = calculateFoldingEnergy(targetConformation);
            prediction.stability = assessStability(targetConformation);
        }
        
        return prediction;
    }
    
private:
    std::string generateExtendedConformation(const std::string& sequence) {
        // Generate extended (unfolded) protein conformation
        return std::string(sequence.length(), 'E');  // E = extended
    }
    
    std::string findLowestEnergyConformation(const std::string& sequence,
                                           const std::vector<std::string>& knownFolds) {
        // Find the most stable known folding pattern
        return knownFolds.empty() ? "" : knownFolds[0];  // Simplified
    }
    
    std::vector<std::string> generateFoldingIntermediates(const std::vector<std::string>& knownFolds) {
        // Generate intermediate folding states
        return knownFolds;  // Simplified
    }
    
    double calculateFoldingEnergy(const std::string& conformation) {
        // Simplified energy calculation
        return -100.0;  // Negative = stable
    }
    
    double assessStability(const std::string& conformation) {
        // Stability assessment
        return 0.8;
    }
};
```

## Pattern Insights

### Key Observations:

1. **Bidirectional Optimization**: Meeting in the middle reduces search space exponentially, especially crucial for large state spaces

2. **Symmetry Exploitation**: The problem has symmetric structure - searching from either direction is equivalent

3. **Pruning Effectiveness**: Early termination when frontiers meet prevents exploring unnecessary paths

4. **Memory vs. Time Trade-off**: Storing visited sets uses more memory but prevents revisiting states

### Related Patterns:
- **Meet-in-the-Middle**: Classic algorithmic technique for optimization problems
- **Shortest Path**: Dijkstra's algorithm, Floyd-Warshall
- **State Space Search**: Game tree search, puzzle solving
- **Graph Algorithms**: Connected components, cycle detection

### Advanced Optimizations:
- **Frontier Size Balancing**: Always expand smaller frontier for optimal performance
- **Heuristic Integration**: A* can guide search toward target more efficiently
- **Parallel Search**: Multiple threads can explore different branches simultaneously
- **Memory-Bounded Search**: IDA* for memory-constrained environments
- **Bidirectional A***: Combine bidirectional search with heuristic guidance

This problem perfectly demonstrates how bidirectional search can dramatically improve performance in shortest path problems, making it essential for both competitive programming and real-world applications involving large search spaces like bioinformatics, drug discovery, and molecular simulation.
