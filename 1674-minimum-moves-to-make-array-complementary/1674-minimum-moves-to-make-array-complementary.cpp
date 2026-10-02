
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();

        // diff[x] = change in number of moves at sum x
        vector<int> diff(2 * limit + 2, 0);

        for (int i = 0; i < n / 2; i++) {
            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = min(a, b);
            int high = max(a, b);

            // 0 moves for sum = a + b
            diff[a + b] -= 1;
            diff[a + b + 1] += 1;

            // 1 move is possible for sums:
            // [low + 1, high + limit]
            diff[low + 1] -= 1;
            diff[high + limit + 1] += 1;

            // 2 moves for everything else
            diff[2] += 2;
        }

        int answer = n;
        int moves = 0;

        // Possible sum is from 2 to 2 * limit
        for (int sum = 2; sum <= 2 * limit; sum++) {
            moves += diff[sum];
            answer = min(answer, moves);
        }

        return answer;
    }
};

