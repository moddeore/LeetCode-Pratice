
class Solution {
    public int maximumSaleItems(int[][] items, int budget) {
        int n = items.length;

        // Calculate free copies received from buying each item type
        int[] bonus = new int[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    bonus[i]++;
                }
            }
        }

        // dp[b] = maximum items obtainable with exact cost b
        int NEG = -1000000000;
        int[] dp = new int[budget + 1];
        java.util.Arrays.fill(dp, NEG);
        dp[0] = 0;

        // Process each item type
        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int extra = bonus[i];

            int[] next = dp.clone();

            // Process each possible remainder modulo price
            for (int r = 0; r < price && r <= budget; r++) {
                int best = NEG;

                for (int t = 0; r + t * price <= budget; t++) {
                    // Previous state with at least one copy purchased
                    if (t > 0) {
                        int prev = dp[r + (t - 1) * price];
                        if (prev != NEG) {
                            best = Math.max(best, prev - (t - 1));
                        }
                    }

                    if (best != NEG) {
                        int current = r + t * price;
                        next[current] = Math.max(
                            next[current],
                            t + extra + best
                        );
                    }
                }
            }

            dp = next;
        }

        int answer = 0;

        for (int b = 0; b <= budget; b++) {
            answer = Math.max(answer, dp[b]);
        }

        return answer;
    }
}
