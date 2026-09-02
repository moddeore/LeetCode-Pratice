class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;

        // Store indices for each value
        vector<vector<int>> pos(n + 1);

        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
        }

        // For every value, check consecutive groups of 3
        for (int x = 1; x <= n; x++) {
            for (int i = 0; i + 2 < pos[x].size(); i++) {
                int a = pos[x][i];
                int b = pos[x][i + 1];
                int c = pos[x][i + 2];

                int distance = 2 * (c - a);
                ans = min(ans, distance);
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};