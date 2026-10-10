
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        vector<int> diff(nums1.size());
        long long operations = (long long)k1 + k2;
        int maxDiff = 0;

        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diff[i]);
        }

        if (operations == 0) {
            long long ans = 0;
            for (int d : diff)
                ans += 1LL * d * d;
            return ans;
        }

        long long total = 0;
        for (int d : diff)
            total += d;

        if (operations >= total)
            return 0;

        int left = 0, right = maxDiff;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid)
                    needed += d - mid;
            }

            if (needed <= operations)
                right = mid;
            else
                left = mid + 1;
        }

        int limit = left;
        long long remaining = operations;
        long long ans = 0;

        for (int d : diff) {
            if (d > limit) {
                remaining -= d - limit;
                d = limit;
            }
            ans += 1LL * d * d;
        }

        // Use remaining operations to reduce differences from limit to limit - 1.
        // Each such reduction saves limit^2 - (limit - 1)^2.
        if (limit > 0) {
            long long count = min(remaining, (long long)diff.size());
            ans -= count * (2LL * limit - 1);
        }

        return ans;
    }
};
