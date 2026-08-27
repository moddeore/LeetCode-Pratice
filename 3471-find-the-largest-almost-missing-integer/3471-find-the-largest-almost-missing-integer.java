class Solution {
    public int largestInteger(int[] nums, int k) {
        int[] count = new int[51];

        // Check every subarray of size k
        for (int i = 0; i <= nums.length - k; i++) {

            boolean[] seen = new boolean[51];

            // Mark distinct numbers in this subarray
            for (int j = i; j < i + k; j++) {
                seen[nums[j]] = true;
            }

            // Count this subarray for each distinct number
            for (int x = 0; x <= 50; x++) {
                if (seen[x]) {
                    count[x]++;
                }
            }
        }

        // Find largest number appearing in exactly one subarray
        for (int x = 50; x >= 0; x--) {
            if (count[x] == 1) {
                return x;
            }
        }

        return -1;
    }
}