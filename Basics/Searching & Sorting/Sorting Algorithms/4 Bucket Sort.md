# Bucket sort

Bucket sort is a distribution-based sorting algorithm that works by distributing elements into a number of buckets, sorting each bucket individually, and then concatenating the sorted buckets to get the final sorted array.

[Video Explanation](https://www.youtube.com/watch?v=VuXbEb5ywrU)

## How Bucket Sort Works

The algorithm follows these key steps:

1. **Create buckets** : Divide the input range into a fixed number of buckets
2. **Distribute elements** : Place each element into the appropriate bucket based on its value
3. **Sort individual buckets** : Sort each bucket using another sorting algorithm (often insertion sort)
4. **Concatenate** : Combine all sorted buckets to get the final result

## Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class BucketSort {
public:
    // Main bucket sort function for floating point numbers in range [0, 1)
    static void bucketSort(std::vector<double>& arr) {
        if (arr.empty()) return;
        
        int n = arr.size();
        
        // Create n empty buckets
        std::vector<std::vector<double>> buckets(n);
        
        // Put array elements in different buckets
        for (int i = 0; i < n; i++) {
            int bucketIndex = n * arr[i];  // Index in bucket
            buckets[bucketIndex].push_back(arr[i]);
        }
        
        // Sort individual buckets using insertion sort
        for (int i = 0; i < n; i++) {
            insertionSort(buckets[i]);
        }
        
        // Concatenate all buckets into arr[]
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                arr[index++] = buckets[i][j];
            }
        }
    }
    
    // Bucket sort for integers with custom range
    static void bucketSortInt(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        int n = arr.size();
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        
        // Create buckets
        int bucketCount = n;
        std::vector<std::vector<int>> buckets(bucketCount);
        
        // Calculate range for each bucket
        int range = (maxVal - minVal) / bucketCount + 1;
        
        // Distribute elements into buckets
        for (int i = 0; i < n; i++) {
            int bucketIndex = (arr[i] - minVal) / range;
            if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
            buckets[bucketIndex].push_back(arr[i]);
        }
        
        // Sort individual buckets
        for (int i = 0; i < bucketCount; i++) {
            std::sort(buckets[i].begin(), buckets[i].end());
        }
        
        // Concatenate buckets
        int index = 0;
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                arr[index++] = buckets[i][j];
            }
        }
    }

private:
    // Helper function: Insertion sort for small arrays
    static void insertionSort(std::vector<double>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            double key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

// Test function to demonstrate bucket sort
void testBucketSort() {
    std::cout << "=== Bucket Sort Demo ===" << std::endl;
    
    // Test 1: Floating point numbers
    std::vector<double> floatArr = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    std::cout << "Original float array: ";
    for (double val : floatArr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    BucketSort::bucketSort(floatArr);
    std::cout << "Sorted float array: ";
    for (double val : floatArr) {
        std::cout << val << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Test 2: Integer numbers
    std::vector<int> intArr = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    std::cout << "Original int array: ";
    for (int val : intArr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    BucketSort::bucketSortInt(intArr);
    std::cout << "Sorted int array: ";
    for (int val : intArr) {
        std::cout << val << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Test 3: Edge cases
    std::vector<int> emptyArr;
    BucketSort::bucketSortInt(emptyArr);
    std::cout << "Empty array test passed" << std::endl;
    
    std::vector<int> singleArr = {42};
    BucketSort::bucketSortInt(singleArr);
    std::cout << "Single element array: " << singleArr[0] << std::endl;
    
    std::vector<int> duplicateArr = {5, 5, 5, 5, 5};
    BucketSort::bucketSortInt(duplicateArr);
    std::cout << "Duplicate elements: ";
    for (int val : duplicateArr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    testBucketSort();
    return 0;
}
```

## Time Complexity

* **Best/Average case** : O(n + k) where n is the number of elements and k is the number of buckets
* **Worst case** : O(n²) when all elements fall into the same bucket

## Space Complexity

* O(n + k) for the buckets and additional storage## Related LeetCode Problems

Here are some LeetCode problems where bucket sort or similar distribution-based sorting techniques can be applied:

### 1. **Maximum Gap (Problem 164)**

* **Difficulty** : Hard
* **Application** : Use bucket sort to find the maximum difference between successive elements in sorted order
* **Key insight** : Create buckets based on the minimum possible gap

### 2. **Top K Frequent Elements (Problem 347)**

* **Difficulty** : Medium
* **Application** : Use bucket sort where bucket index represents frequency
* **Key insight** : Create buckets for each possible frequency count

### 3. **Sort Colors (Problem 75)**

* **Difficulty** : Medium
* **Application** : A simplified version of bucket sort with only 3 buckets (for colors 0, 1, 2)
* **Key insight** : Use counting sort or three-way partitioning

### 4. **H-Index (Problem 274)**

* **Difficulty** : Medium
* **Application** : Use bucket sort where buckets represent citation counts
* **Key insight** : Create buckets for citation counts up to array length

### 5. **Contains Duplicate III (Problem 220)**

* **Difficulty** : Hard
* **Application** : Use bucket sort concept with buckets representing value ranges
* **Key insight** : Map values to buckets to find nearby duplicates efficiently

The bucket sort algorithm is particularly effective when:

* Input is uniformly distributed
* You know the range of input values
* You need a stable sort
* The number of buckets is reasonable compared to input size

The implementation above provides both floating-point and integer versions, with comprehensive test cases to demonstrate the algorithm's functionality.
