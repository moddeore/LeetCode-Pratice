class Solution {
public:
    using int64 = long long;

    long long gcdll(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    long long lcmLimited(long long a, long long b, long long limit) {
        long long g = gcdll(a, b);
        a /= g;

        // We only care about LCMs <= limit.
        if (a > limit / b)
            return limit + 1;

        return a * b;
    }

    long long countLE(long long x, const vector<int>& coins) {
        int n = coins.size();
        long long ans = 0;

        // Inclusion-exclusion over all subsets.
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long lcm = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    ++bits;

                    lcm = lcmLimited(lcm, coins[i], x);
                    if (lcm > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge)
                continue;

            long long cnt = x / lcm;

            if (bits & 1)
                ans += cnt;
            else
                ans -= cnt;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, long long k) {
        // Remove denominations whose multiples are already covered
        // by a smaller denomination.
        sort(coins.begin(), coins.end());

        vector<int> useful;

        for (int c : coins) {
            bool redundant = false;

            for (int d : useful) {
                if (c % d == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                useful.push_back(c);
        }

        // The answer is at most k * min(coins).
        long long lo = 1;
        long long hi = 1LL * useful[0] * k;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (countLE(mid, useful) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};