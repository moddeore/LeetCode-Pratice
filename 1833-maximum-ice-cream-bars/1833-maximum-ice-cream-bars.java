class Solution {
    public int maxIceCream(int[] costs, int coins) {
        // Find maximum cost
        int max = 0;
        for (int cost : costs) {
            max = Math.max(max, cost);
        }

        // Counting array
        int[] count = new int[max + 1];

        for (int cost : costs) {
            count[cost]++;
        }

        // Buy cheapest ice creams first
        int ans = 0;

        for (int price = 1; price <= max; price++) {
            if (count[price] == 0) {
                continue;
            }

            // Maximum bars we can buy at this price
            int canBuy = Math.min(count[price], coins / price);

            ans += canBuy;
            coins -= canBuy * price;

            // No more money
            if (coins == 0) {
                break;
            }
        }

        return ans;
    }
}