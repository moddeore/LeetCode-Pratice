
import java.util.*;

class Solution {
    public boolean findSafeWalk(List<List<Integer>> grid, int health) {
        int m = grid.size();
        int n = grid.get(0).size();

        // best[i][j] = maximum health with which we reached this cell
        int[][] best = new int[m][n];

        for (int[] row : best) {
            Arrays.fill(row, -1);
        }

        // Starting cell also costs health if it is unsafe
        int startHealth = health - grid.get(0).get(0);

        if (startHealth <= 0) {
            return false;
        }

        best[0][0] = startHealth;

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0, startHealth});

        int[] dr = {-1, 1, 0, 0};
        int[] dc = {0, 0, -1, 1};

        while (!queue.isEmpty()) {
            int[] cur = queue.poll();

            int r = cur[0];
            int c = cur[1];
            int h = cur[2];

            // Reached destination with positive health
            if (r == m - 1 && c == n - 1) {
                return true;
            }

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
                    continue;
                }

                int newHealth = h - grid.get(nr).get(nc);

                // Health must remain positive
                if (newHealth <= 0) {
                    continue;
                }

                // Only visit if we reach this cell with better health
                if (newHealth > best[nr][nc]) {
                    best[nr][nc] = newHealth;
                    queue.offer(new int[]{nr, nc, newHealth});
                }
            }
        }

        return false;
    }
}

