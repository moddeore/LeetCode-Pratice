class Solution {
    public int distinctSubseqII(String s) {
        int MOD = 1_000_000_007;

        // dp = number of distinct subsequences including empty subsequence
        long dp = 1;

        // last[c] = dp value before the previous occurrence of character c
        long[] last = new long[26];

        for (char ch : s.toCharArray()) {
            int idx = ch - 'a';

            long newDp = (2 * dp - last[idx] + MOD) % MOD;

            // Store current dp before updating
            last[idx] = dp;

            dp = newDp;
        }

        // Remove empty subsequence
        return (int) ((dp - 1 + MOD) % MOD);
    }
}