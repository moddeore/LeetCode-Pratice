
import java.util.*;

class Solution {
    public int[] maximumWeight(List<List<Integer>> intervals) {
        int n = intervals.size();

        int[][] a = new int[n][4];

        for (int i = 0; i < n; i++) {
            a[i][0] = intervals.get(i).get(0);
            a[i][1] = intervals.get(i).get(1);
            a[i][2] = intervals.get(i).get(2);
            a[i][3] = i;
        }

        Arrays.sort(a, (x, y) -> {
            if (x[1] != y[1])
                return Integer.compare(x[1], y[1]);
            return Integer.compare(x[3], y[3]);
        });

        int[] prev = new int[n];

        for (int i = 0; i < n; i++) {
            int left = a[i][0];

            int lo = 0;
            int hi = i - 1;
            int ans = -1;

            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;

                if (a[mid][1] < left) {
                    ans = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            prev[i] = ans;
        }

        State[][] dp = new State[5][n + 1];

        for (int i = 0; i <= n; i++) {
            dp[0][i] = new State(0, new int[0]);
        }

        for (int k = 1; k <= 4; k++) {
            dp[k][0] = new State(0, new int[0]);

            for (int i = 1; i <= n; i++) {
                State skip = dp[k][i - 1];

                int current = i - 1;
                int p = prev[current];

                State before = dp[k - 1][p + 1];

                long newScore = before.score + (long) a[current][2];

                int[] newIndices = Arrays.copyOf(
                    before.indices,
                    before.indices.length + 1
                );

                newIndices[newIndices.length - 1] = a[current][3];

                Arrays.sort(newIndices);

                State take = new State(newScore, newIndices);

                dp[k][i] = better(skip, take);
            }
        }

        return dp[4][n].indices;
    }

    private State better(State a, State b) {
        if (a.score != b.score) {
            return a.score > b.score ? a : b;
        }

        return lexicographicallySmaller(a.indices, b.indices) ? a : b;
    }

    private boolean lexicographicallySmaller(int[] a, int[] b) {
        int len = Math.min(a.length, b.length);

        for (int i = 0; i < len; i++) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }

        return a.length < b.length;
    }

    static class State {
        long score;
        int[] indices;

        State(long score, int[] indices) {
            this.score = score;
            this.indices = indices;
        }
    }
}

