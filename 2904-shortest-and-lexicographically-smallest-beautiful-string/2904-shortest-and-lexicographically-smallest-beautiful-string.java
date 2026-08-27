class Solution {
    public String shortestBeautifulSubstring(String s, int k) {
        int n = s.length();

        // Store positions of all 1s
        int[] pos = new int[n];
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '1') {
                pos[count++] = i;
            }
        }

        // Not enough 1s
        if (count < k) {
            return "";
        }

        int minLen = Integer.MAX_VALUE;
        String answer = "";

        // Every group of k consecutive 1s gives
        // a substring containing exactly k ones.
        for (int i = 0; i + k - 1 < count; i++) {

            int left = pos[i];
            int right = pos[i + k - 1];

            // Remove zeros from the left and right
            while (left < right && s.charAt(left) == '0') {
                left++;
            }

            while (right > left && s.charAt(right) == '0') {
                right--;
            }

            int len = right - left + 1;

            if (len < minLen) {
                minLen = len;
                answer = s.substring(left, right + 1);
            } 
            else if (len == minLen) {
                String current = s.substring(left, right + 1);

                if (current.compareTo(answer) < 0) {
                    answer = current;
                }
            }
        }

        return answer;
    }
}