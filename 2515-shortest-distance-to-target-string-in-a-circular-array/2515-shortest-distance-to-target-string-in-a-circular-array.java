class Solution {
    public int closestTarget(String[] words, String target, int startIndex) {
        int n = words.length;
        int ans = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            if (words[i].equals(target)) {

                // Clockwise distance
                int clockwise = Math.abs(i - startIndex);

                // Circular shortest distance
                int distance = Math.min(clockwise, n - clockwise);

                ans = Math.min(ans, distance);
            }
        }

        return ans == Integer.MAX_VALUE ? -1 : ans;
    }
}