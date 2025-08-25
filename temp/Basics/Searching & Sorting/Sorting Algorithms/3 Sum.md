# 3 Sum Problem

## Problem Statement

Given an array of integers `nums`, find all unique triplets `(a, b, c)` in the array such that `a + b + c = 0`.

## Algorithm Explanation

1. **Sort the Array:** Sorting helps in efficiently skipping duplicates and using the two-pointer technique.
2. **Iterate with Fixed First Element:** For each index `i`, fix `nums[i]` as the first element of the triplet.
3. **Two-Pointer Search:** Use two pointers (`left` and `right`) to find pairs such that `nums[i] + nums[left] + nums[right] == 0`.
4. **Skip Duplicates:** After finding a valid triplet, move the pointers to skip over duplicate values.
5. **Continue Until All Triplets Are Found.**

## C++ Code (Executable)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicates
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) ++left; // skip duplicates
                while (left < right && nums[right] == nums[right - 1]) --right; // skip duplicates
                ++left;
                --right;
            } else if (sum < 0) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return res;
}

int main() {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto result = threeSum(nums);
    for (const auto& triplet : result) {
        for (int num : triplet) std::cout << num << " ";
        std::cout << std::endl;
    }
    return 0;
}
```

## References

- [LeetCode 15. 3Sum](https://leetcode.com/problems/3sum/)
- [LeetCode 16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/)
- [LeetCode 18. 4Sum](https://leetcode.com/problems/4sum/)
