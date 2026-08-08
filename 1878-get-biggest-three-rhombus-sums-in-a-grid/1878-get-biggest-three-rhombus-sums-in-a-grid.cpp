class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // down-right diagonal prefix sum
        vector<vector<int>> dr(m + 1, vector<int>(n + 1, 0));

        // down-left diagonal prefix sum
        vector<vector<int>> dl(m + 1, vector<int>(n + 2, 0));

        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                dr[i][j] = grid[i][j] + dr[i + 1][j + 1];
            }

            for (int j = n - 1; j >= 0; j--) {
                dl[i][j] = grid[i][j] + dl[i + 1][j - 1 + 1];
            }
        }

        // Use a set to keep only distinct sums.
        set<int> sums;

        // Every cell itself is a rhombus of area 0.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sums.insert(grid[i][j]);
            }
        }

        /*
            Top vertex = (i, j)
            Left vertex = (i + k, j - k)
            Right vertex = (i + k, j + k)
            Bottom vertex = (i + 2k, j)

            k >= 1
        */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Maximum possible radius.
                int k = 1;

                while (i + 2 * k < m &&
                       j - k >= 0 &&
                       j + k < n) {

                    int top = grid[i][j];
                    int left = grid[i + k][j - k];
                    int right = grid[i + k][j + k];
                    int bottom = grid[i + 2 * k][j];

                    /*
                     * Four diagonal sides.
                     *
                     * top -> left
                     * top -> right
                     * left -> bottom
                     * right -> bottom
                     *
                     * Each corner gets counted twice,
                     * so subtract the four corners once.
                     */

                    int sum = 0;

                    // Top -> Left
                    sum += diagonalDownLeft(i, j,
                                            i + k, j - k,
                                            grid);

                    // Top -> Right
                    sum += diagonalDownRight(i, j,
                                             i + k, j + k,
                                             grid);

                    // Left -> Bottom
                    sum += diagonalDownRight(i + k, j - k,
                                             i + 2 * k, j,
                                             grid);

                    // Right -> Bottom
                    sum += diagonalDownLeft(i + k, j + k,
                                            i + 2 * k, j,
                                            grid);

                    // Corners were counted twice.
                    sum -= top + left + right + bottom;

                    sums.insert(sum);

                    k++;
                }
            }
        }

        vector<int> ans;

        // set is sorted ascending, so iterate backwards.
        for (auto it = sums.rbegin();
             it != sums.rend() && ans.size() < 3;
             ++it) {

            ans.push_back(*it);
        }

        return ans;
    }

private:

    int diagonalDownRight(
        int r1, int c1,
        int r2, int c2,
        vector<vector<int>>& grid) {

        int sum = 0;

        while (r1 <= r2) {
            sum += grid[r1][c1];
            r1++;
            c1++;
        }

        return sum;
    }

    int diagonalDownLeft(
        int r1, int c1,
        int r2, int c2,
        vector<vector<int>>& grid) {

        int sum = 0;

        while (r1 <= r2) {
            sum += grid[r1][c1];
            r1++;
            c1--;
        }

        return sum;
    }
};