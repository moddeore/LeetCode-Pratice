class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        // All piles have been taken
        if (i >= n)
            return 0;

        // Already calculated
        if (dp[i][M] != -1)
            return dp[i][M];

        int best = 0;

        // Can take between 1 and 2*M piles
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {

            // Stones Alice takes now
            int taken = suffix[i] - suffix[i + X];

            // Bob plays optimally afterward
            int remaining = suffix[i + X] - solve(i + X, max(M, X));

            best = max(best, taken + remaining);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = sum of piles from i to n-1
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};