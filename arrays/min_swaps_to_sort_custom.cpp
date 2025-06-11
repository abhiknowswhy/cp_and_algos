// Leetcode: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        vector<int> nums1 = nums;
        sort(nums1.begin(), nums1.end(), [](int num1, int num2){
            int sum1 = 0, sum2 = 0;
            int num = num1;
            while(num > 0) {
                sum1 += num%10; num = num/10;
            }
            num = num2;
            while(num > 0) {
                sum2 += num%10; num = num/10;
            }
            return sum1 < sum2 || (sum1 == sum2 && num1 < num2);
        });

        unordered_map<int, pair<int, int>> positions;

        for(int i = 0; i<nums.size(); i++) {
            if(positions.find(nums[i]) != positions.end()) {
                positions[nums[i]].first = i;
            } else {
                positions[nums[i]] = {i, -1};
            }

            if(positions.find(nums1[i]) != positions.end()) {
                positions[nums1[i]].second = i;
            } else {
                positions[nums1[i]] = {-1, i};
            }

            // cout<<nums[i]<<" "<<nums1[i]<<"\n";
        }

        int num_swaps = 0;
        for(int i = 0; i<nums.size(); i++) {
            int pos = positions[nums1[i]].first, pos1 = positions[nums1[i]].second;
            if(pos != pos1) {
                int x = nums[pos1];
                nums[pos1] = nums[pos];
                nums[pos] = x;
                positions[x].first = pos;
                positions[nums[pos1]].first = pos1;
                num_swaps++;
            }
        }
        return num_swaps;
    }
};