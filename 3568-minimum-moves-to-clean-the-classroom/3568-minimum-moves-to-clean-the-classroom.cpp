#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        vector<pair<int, int>> litter;

        // Find S and all L cells
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        // No litter to collect
        if (k == 0)
            return 0;

        // Map each litter cell to a bit
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            litterId[litter[i].first][litter[i].second] = i;
        }

        int fullMask = (1 << k) - 1;
        int cells = m * n;

        /*
            best[pos][mask] = maximum energy with which
            we have reached this position having collected
            exactly 'mask' litter.

            If we reach the same (pos, mask) later with
            less/equal energy, that state is useless.
        */
        vector<vector<int>> best(cells, vector<int>(1 << k, -1));

        struct State {
            int pos;
            int mask;
            int energy;
        };

        queue<State> q;

        int startPos = sr * n + sc;

        best[startPos][0] = energy;
        q.push({startPos, 0, energy});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            // BFS level = number of moves
            while (sz--) {
                State cur = q.front();
                q.pop();

                int r = cur.pos / n;
                int c = cur.pos % n;

                // All litter collected
                if (cur.mask == fullMask)
                    return moves;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // Cannot make a move with zero energy
                    if (cur.energy == 0)
                        continue;

                    int newEnergy = cur.energy - 1;
                    int newMask = cur.mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        int id = litterId[nr][nc];
                        newMask |= (1 << id);
                    }

                    // Reset energy on R
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    int newPos = nr * n + nc;

                    /*
                        If we've already reached this position
                        with the same mask and >= energy,
                        this state is dominated.
                    */
                    if (best[newPos][newMask] >= newEnergy)
                        continue;

                    best[newPos][newMask] = newEnergy;

                    q.push({
                        newPos,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};