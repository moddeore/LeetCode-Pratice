
class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int maxi = nums[0];
        int mini = nums[0];

        for (int x : nums) {
            maxi = max(maxi, x);
            mini = min(mini, x);
        }

        return 1LL * (maxi - mini) * k;
    }
};
