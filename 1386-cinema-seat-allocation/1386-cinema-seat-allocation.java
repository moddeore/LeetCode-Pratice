import java.util.*;

class Solution {
    public int maxNumberOfFamilies(int n, int[][] reservedSeats) {
        Map<Integer, Integer> rows = new HashMap<>();

        // Build a bitmask for every row containing reservations.
        for (int[] seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Seat 1 -> bit 0, seat 10 -> bit 9
            rows.put(row, rows.getOrDefault(row, 0) | (1 << col));
        }

        int answer = (n - rows.size()) * 2;

        for (int mask : rows.values()) {
            boolean left = (mask & ((1 << 2) | (1 << 3) |
                                   (1 << 4) | (1 << 5))) == 0;

            boolean middle = (mask & ((1 << 4) | (1 << 5) |
                                      (1 << 6) | (1 << 7))) == 0;

            boolean right = (mask & ((1 << 6) | (1 << 7) |
                                     (1 << 8) | (1 << 9))) == 0;

            if (left && right) {
                // Two non-overlapping groups:
                // 2-5 and 6-9
                answer += 2;
            } else if (left || middle || right) {
                // At least one block is available.
                answer += 1;
            }
        }

        return answer;
    }
}