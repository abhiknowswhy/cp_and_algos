# Sliding window median

The sliding window median algorithm finds the median of all subarrays of size k in an array. The median is the middle value when elements are sorted - for odd-sized windows, it's the middle element; for even-sized windows, it's the average of the two middle elements.

The main challenge is efficiently maintaining the median as we slide the window. A naive approach would sort each window, giving O(n * k log k) complexity. The optimal approach uses two data structures to maintain the median in O(log k) time per window.

## Algorithm Approach

The key insight is to use two balanced data structures:

- A max heap for the smaller half of elements
- A min heap for the larger half of elements

We maintain the invariant that the max heap contains the smaller half and the min heap contains the larger half. The median is either the top of the max heap (odd size) or the average of both tops (even size).

For the sliding window version, we need to efficiently remove elements that are no longer in the current window. We can use multiset (balanced BST) instead of heaps for O(log k) insertion, deletion, and median access.## Time and Space Complexity

## Code

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>

class SlidingWindowMedian {
private:
    std::multiset<int> left;  // max heap simulation (smaller half)
    std::multiset<int> right; // min heap simulation (larger half)
    int k;
    
    void balance() {
        // Ensure left size is either equal to right size or one more
        if (left.size() > right.size() + 1) {
            right.insert(*left.rbegin());
            left.erase(left.find(*left.rbegin()));
        } else if (right.size() > left.size()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    }
    
    void addElement(int num) {
        if (left.empty() || num <= *left.rbegin()) {
            left.insert(num);
        } else {
            right.insert(num);
        }
        balance();
    }
    
    void removeElement(int num) {
        if (left.count(num)) {
            left.erase(left.find(num));
        } else {
            right.erase(right.find(num));
        }
        balance();
    }
    
    double getMedian() {
        if (k % 2 == 1) {
            return *left.rbegin();
        } else {
            return (*left.rbegin() + *right.begin()) / 2.0;
        }
    }
    
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        this->k = k;
        std::vector<double> result;
        
        // Initialize first window
        for (int i = 0; i < k; i++) {
            addElement(nums[i]);
        }
        result.push_back(getMedian());
        
        // Slide the window
        for (int i = k; i < nums.size(); i++) {
            // Remove the leftmost element of previous window
            removeElement(nums[i - k]);
            // Add the new element
            addElement(nums[i]);
            result.push_back(getMedian());
        }
        
        return result;
    }
};

// Alternative implementation using single multiset with iterators
class SlidingWindowMedianV2 {
private:
    std::multiset<int> window;
    std::multiset<int>::iterator median;
    int k;
    
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        this->k = k;
        std::vector<double> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Add new element
            window.insert(nums[i]);
            
            // Remove element that's out of window
            if (i >= k) {
                window.erase(window.find(nums[i - k]));
            }
            
            // Calculate median when window is full
            if (i >= k - 1) {
                auto it = window.begin();
                std::advance(it, (k - 1) / 2);
                
                if (k % 2 == 1) {
                    result.push_back(*it);
                } else {
                    double median = (*it + *std::next(it)) / 2.0;
                    result.push_back(median);
                }
            }
        }
        
        return result;
    }
};

// Test function
void testSlidingWindowMedian() {
    SlidingWindowMedian solver;
    
    // Test case 1: [1,3,-1,-3,5,3,6,7], k = 3
    std::vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    std::vector<double> result1 = solver.medianSlidingWindow(nums1, 3);
    
    std::cout << "Test 1 - Input: [1,3,-1,-3,5,3,6,7], k=3" << std::endl;
    std::cout << "Output: ";
    for (int i = 0; i < result1.size(); i++) {
        std::cout << std::fixed << std::setprecision(1) << result1[i];
        if (i < result1.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Expected: [1.0, -1.0, -1.0, 3.0, 5.0, 6.0]" << std::endl << std::endl;
    
    // Test case 2: [1,2,3,4,2,3,1,4,2], k = 3
    std::vector<int> nums2 = {1, 2, 3, 4, 2, 3, 1, 4, 2};
    std::vector<double> result2 = solver.medianSlidingWindow(nums2, 3);
    
    std::cout << "Test 2 - Input: [1,2,3,4,2,3,1,4,2], k=3" << std::endl;
    std::cout << "Output: ";
    for (int i = 0; i < result2.size(); i++) {
        std::cout << std::fixed << std::setprecision(1) << result2[i];
        if (i < result2.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Expected: [2.0, 3.0, 3.0, 2.0, 2.0, 3.0, 4.0]" << std::endl << std::endl;
    
    // Test case 3: Even window size
    std::vector<int> nums3 = {1, 4, 2, 3};
    std::vector<double> result3 = solver.medianSlidingWindow(nums3, 4);
    
    std::cout << "Test 3 - Input: [1,4,2,3], k=4" << std::endl;
    std::cout << "Output: ";
    for (int i = 0; i < result3.size(); i++) {
        std::cout << std::fixed << std::setprecision(1) << result3[i];
        if (i < result3.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Expected: [2.5]" << std::endl << std::endl;
    
    // Test alternative implementation
    std::cout << "Testing alternative implementation:" << std::endl;
    SlidingWindowMedianV2 solver2;
    std::vector<double> result4 = solver2.medianSlidingWindow(nums1, 3);
    
    std::cout << "Alternative - Input: [1,3,-1,-3,5,3,6,7], k=3" << std::endl;
    std::cout << "Output: ";
    for (int i = 0; i < result4.size(); i++) {
        std::cout << std::fixed << std::setprecision(1) << result4[i];
        if (i < result4.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

int main() {
    testSlidingWindowMedian();
    return 0;
}
```

**Time Complexity:** O(n log k) where n is the array length and k is the window size

- Each insertion and deletion in multiset takes O(log k)
- We perform these operations for each of the n elements

**Space Complexity:** O(k) for storing the window elements

## Algorithm Variations

1. **Two Multisets Approach:** Maintains smaller and larger halves separately
2. **Single Multiset Approach:** Uses iterator arithmetic to find median
3. **Heap-based Approach:** Uses priority queues with lazy deletion (more complex for removals)

## Related LeetCode Problems

1. **LeetCode 480 - Sliding Window Median** (Hard)
   - Direct implementation of this algorithm
   - Input: array of integers and window size k
   - Output: array of medians for each window

2. **LeetCode 295 - Find Median from Data Stream** (Hard)
   - Foundation problem for understanding median maintenance
   - Uses two heaps to maintain running median

3. **LeetCode 239 - Sliding Window Maximum** (Hard)
   - Similar sliding window concept but for maximum values
   - Uses deque for O(n) solution

4. **LeetCode 346 - Moving Average from Data Stream** (Easy)
   - Simpler version focusing on mean instead of median
   - Good starting point for sliding window concepts

5. **LeetCode 703 - Kth Largest Element in a Stream** (Easy)
   - Uses heap to maintain kth largest element
   - Related to order statistics maintenance

The sliding window median problem is particularly challenging because it requires efficient insertion, deletion, and order statistics queries. The multiset approach provides a clean solution with good performance characteristics, making it suitable for most practical applications.