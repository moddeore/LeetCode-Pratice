class Solution {

    public String lexGreaterPermutation(String s, String target) {
        int[] freq = new int[26];

        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        StringBuilder ans = new StringBuilder();

        if (solve(0, target, freq, ans)) {
            return ans.toString();
        }

        return "";
    }

    private boolean solve(int pos, String target, int[] freq,
                          StringBuilder ans) {

        int n = target.length();

        if (pos == n) {
            return false;
        }

        int t = target.charAt(pos) - 'a';

        // Try same character first
        if (freq[t] > 0) {
            freq[t]--;
            ans.append((char) ('a' + t));

            // Continue matching target
            if (solve(pos + 1, target, freq, ans)) {
                return true;
            }

            ans.deleteCharAt(ans.length() - 1);
            freq[t]++;
        }

        // Try the smallest character greater than target[pos]
        for (int c = t + 1; c < 26; c++) {

            if (freq[c] > 0) {
                freq[c]--;
                ans.append((char) ('a' + c));

                // Put remaining characters in sorted order
                for (int x = 0; x < 26; x++) {
                    while (freq[x] > 0) {
                        ans.append((char) ('a' + x));
                        freq[x]--;
                    }
                }

                return true;
            }
        }

        return false;
    }
}