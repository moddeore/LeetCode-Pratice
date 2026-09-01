class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> ans(m, vector<int>(n));

        k = k % (m * n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Convert 2D position to 1D position
                int oldPos = i * n + j;

                // New position after k shifts
                int newPos = (oldPos + k) % (m * n);

                // Convert 1D position back to 2D
                int newRow = newPos / n;
                int newCol = newPos % n;

                ans[newRow][newCol] = grid[i][j];
            }
        }

        return ans;
    }
};