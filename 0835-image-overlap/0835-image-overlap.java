class Solution {
    public int largestOverlap(int[][] img1, int[][] img2) {
        int n = img1.length;
        int maxOverlap = 0;

        // Try every possible row and column shift
        for (int dr = -(n - 1); dr <= n - 1; dr++) {
            for (int dc = -(n - 1); dc <= n - 1; dc++) {

                int overlap = 0;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {

                        int r = i + dr;
                        int c = j + dc;

                        if (r >= 0 && r < n && c >= 0 && c < n) {
                            if (img1[i][j] == 1 && img2[r][c] == 1) {
                                overlap++;
                            }
                        }
                    }
                }

                maxOverlap = Math.max(maxOverlap, overlap);
            }
        }

        return maxOverlap;
    }
}