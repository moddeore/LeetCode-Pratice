class Solution {
    public int missingMultiple(int[] nums, int k) {
        boolean[] present = new boolean[101];

        for (int num : nums) {
            present[num] = true;
        }

        int multiple = k;

        while (multiple <= 100) {
            if (!present[multiple]) {
                return multiple;
            }
            multiple += k;
        }

        // If all multiples up to 100 are present
        return multiple;
    }
}