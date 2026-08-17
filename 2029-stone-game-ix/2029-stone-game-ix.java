class Solution {
    public boolean stoneGameIX(int[] stones) {

        int[] count = new int[3];

        // Count stones based on remainder
        for (int stone : stones) {
            count[stone % 3]++;
        }

        int c0 = count[0];
        int c1 = count[1];
        int c2 = count[2];

        // No remainder-1 or remainder-2 stones
        if (c1 == 0 && c2 == 0) {
            return false;
        }

        // If one side is missing
        if (c1 == 0) {
            return c2 > 2 && c0 % 2 == 1;
        }

        if (c2 == 0) {
            return c1 > 2 && c0 % 2 == 1;
        }

        // Both remainder-1 and remainder-2 stones exist
        if (c0 % 2 == 0) {
            return true;
        }

        return Math.abs(c1 - c2) > 2;
    }
}