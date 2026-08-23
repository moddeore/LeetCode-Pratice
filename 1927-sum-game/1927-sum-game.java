class Solution {
    public boolean sumGame(String num) {
        int n = num.length();

        int sumDiff = 0;
        int qDiff = 0;

        for (int i = 0; i < n / 2; i++) {
            if (num.charAt(i) == '?') {
                qDiff++;
            } else {
                sumDiff += num.charAt(i) - '0';
            }
        }

        for (int i = n / 2; i < n; i++) {
            if (num.charAt(i) == '?') {
                qDiff--;
            } else {
                sumDiff -= num.charAt(i) - '0';
            }
        }

        // Bob can force equality only in this case.
        return 2 * sumDiff + 9 * qDiff != 0;
    }
}