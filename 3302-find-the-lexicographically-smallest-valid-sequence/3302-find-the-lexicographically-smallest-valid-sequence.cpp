class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // Store positions of every character in word1.
        vector<vector<int>> pos(26);

        for (int i = 0; i < n; i++) {
            pos[word1[i] - 'a'].push_back(i);
        }

        /*
         * exact[i] =
         * maximum possible first index in word1 from which
         * word2[i..m-1] can be matched EXACTLY.
         *
         * exact[m] = n means empty suffix.
         */
        vector<int> exact(m + 1, -1);
        exact[m] = n;

        for (int i = m - 1; i >= 0; i--) {
            int limit = exact[i + 1];

            if (limit == -1)
                continue;

            auto &v = pos[word2[i] - 'a'];

            // Largest position < limit
            auto it = lower_bound(v.begin(), v.end(), limit);

            if (it != v.begin()) {
                --it;
                exact[i] = *it;
            }
        }

        /*
         * almost[i] =
         * maximum possible first index in word1 from which
         * word2[i..m-1] can be matched with AT MOST ONE mismatch.
         *
         * We calculate this using two possibilities:
         *
         * 1. word1[p] == word2[i]
         *    -> mismatch can happen later.
         *
         * 2. word1[p] != word2[i]
         *    -> use the one mismatch here,
         *       so the rest must match exactly.
         */
        vector<int> almost(m + 1, -1);
        almost[m] = n;

        for (int i = m - 1; i >= 0; i--) {

            // Option 1: current character matches.
            if (almost[i + 1] != -1) {
                auto &v = pos[word2[i] - 'a'];

                auto it = lower_bound(
                    v.begin(),
                    v.end(),
                    almost[i + 1]
                );

                if (it != v.begin()) {
                    --it;
                    almost[i] = max(almost[i], *it);
                }
            }

            // Option 2: use the one mismatch here.
            if (exact[i + 1] != -1) {

                int limit = exact[i + 1];

                // We need the largest position < limit
                // whose character is NOT word2[i].
                int best = -1;

                for (int c = 0; c < 26; c++) {
                    if (c == word2[i] - 'a')
                        continue;

                    auto &v = pos[c];

                    auto it = lower_bound(
                        v.begin(),
                        v.end(),
                        limit
                    );

                    if (it != v.begin()) {
                        --it;
                        best = max(best, *it);
                    }
                }

                almost[i] = max(almost[i], best);
            }
        }

        /*
         * Precompute the end of every equal-character run.
         *
         * runEnd[i] = first index >= i whose character
         * is different from word1[i].
         */
        vector<int> runEnd(n);

        runEnd[n - 1] = n;

        for (int i = n - 2; i >= 0; i--) {
            if (word1[i] == word1[i + 1])
                runEnd[i] = runEnd[i + 1];
            else
                runEnd[i] = i + 1;
        }

        vector<int> ans;
        ans.reserve(m);

        int prev = -1;
        bool mismatchUsed = false;

        /*
         * Greedily choose the smallest possible index.
         */
        for (int i = 0; i < m; i++) {

            int start = prev + 1;

            // -----------------------------------------
            // Candidate 1: exact character
            // -----------------------------------------
            int exactCandidate = n;

            auto &v = pos[word2[i] - 'a'];

            auto it = lower_bound(
                v.begin(),
                v.end(),
                start
            );

            if (it != v.end())
                exactCandidate = *it;

            // -----------------------------------------
            // Candidate 2: mismatch character
            // -----------------------------------------
            int mismatchCandidate = n;

            if (!mismatchUsed && start < n) {

                if (word1[start] != word2[i]) {
                    mismatchCandidate = start;
                }
                else {
                    // Skip the entire run of word2[i].
                    mismatchCandidate = runEnd[start];
                }
            }

            /*
             * Try candidates in increasing index order.
             *
             * This is what guarantees the lexicographically
             * smallest INDEX ARRAY.
             */
            int chosen = n;
            bool chooseMismatch = false;

            if (exactCandidate < n) {

                bool possible;

                if (i == m - 1) {
                    possible = true;
                }
                else {
                    /*
                     * We haven't used mismatch yet, so the
                     * remaining suffix may contain one mismatch.
                     *
                     * If mismatch was already used, it must
                     * match exactly.
                     */
                    if (mismatchUsed)
                        possible = exact[i + 1] > exactCandidate;
                    else
                        possible = almost[i + 1] > exactCandidate;
                }

                if (possible) {
                    chosen = exactCandidate;
                    chooseMismatch = false;
                }
            }

            /*
             * Check mismatch candidate.
             *
             * If we use mismatch here, the remaining suffix
             * MUST match exactly.
             */
            if (!mismatchUsed && mismatchCandidate < n) {

                bool possible;

                if (i == m - 1) {
                    possible = true;
                }
                else {
                    possible =
                        exact[i + 1] > mismatchCandidate;
                }

                if (possible && mismatchCandidate < chosen) {
                    chosen = mismatchCandidate;
                    chooseMismatch = true;
                }
            }

            if (chosen == n) {
                return {};
            }

            ans.push_back(chosen);
            prev = chosen;

            if (chooseMismatch)
                mismatchUsed = true;
        }

        return ans;
    }
};