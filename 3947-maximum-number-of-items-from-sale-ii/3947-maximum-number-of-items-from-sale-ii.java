
import java.util.*;

class Solution {
    public int maximumSaleItems(int[][] items, int budget) {
        int n = items.length;

        // Find minimum item price
        int minPrice = Integer.MAX_VALUE;

        // Frequency of each factor
        int[] freq = new int[n + 1];

        for (int[] item : items) {
            freq[item[0]]++;
            minPrice = Math.min(minPrice, item[1]);
        }

        // Count how many items each factor can divide
        int[] divisible = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                divisible[i] += freq[j];
            }
        }

        // Sort items by price
        long[] sorted = new long[n];

        for (int i = 0; i < n; i++) {
            sorted[i] = (long) items[i][1] * (n + 1) + i;
        }

        Arrays.sort(sorted);

        long remaining = budget;
        long bonus = 0;
        long spent = 0;

        // Select the cheapest bonus-generating purchases
        for (int i = 0; i < n; i++) {
            int index = (int) (sorted[i] % (n + 1));
            long price = items[index][1];

            // Bonus purchases costing more than 2 * minPrice
            // are never beneficial.
            if (price > 2L * minPrice) {
                break;
            }

            // Maximum free copies obtainable from this item type
            int freeCopies = divisible[items[index][0]] - 1;

            // Number of copies we can afford
            long take = Math.min(
                freeCopies,
                remaining / price
            );

            bonus += take;
            spent += take * price;
            remaining -= take * price;
        }

        // Spend remaining budget on the cheapest item
        long answer = 2 * bonus + remaining / minPrice;

        return (int) answer;
    }
}
