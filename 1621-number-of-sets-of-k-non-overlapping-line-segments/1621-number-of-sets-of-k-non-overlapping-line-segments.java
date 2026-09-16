class Solution {
    public int numberOfSets(int n, int k) {
        final long MOD = 1_000_000_007L;

        long[][] dp = new long[k + 1][n];

        // 0 segments can always be chosen.
        for (int i = 0; i < n; i++) {
            dp[0][i] = 1;
        }

        for (int segments = 1; segments <= k; segments++) {
            long open = 0;

            for (int i = 0; i < n; i++) {
                // Start a segment at i.
                if (i > 0) {
                    open = (open + dp[segments - 1][i - 1]) % MOD;
                }

                // Finish the segment at i.
                // It must have a different left endpoint.
                dp[segments][i] = open;

                // We can also ignore point i.
                if (i > 0) {
                    dp[segments][i] =
                        (dp[segments][i] + dp[segments][i - 1]) % MOD;
                }
            }
        }

        return (int) dp[k][n - 1];
    }
}