
class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> ans(n);
        vector<bool> seenA(n + 1, false), seenB(n + 1, false);
        int common = 0;

        for (int i = 0; i < n; i++) {
            seenA[A[i]] = true;
            seenB[B[i]] = true;

            for (int x = 1; x <= n; x++) {
                if (seenA[x] && seenB[x]) {
                    // Count common elements for this prefix.
                }
            }

            common = 0;
            for (int x = 1; x <= n; x++) {
                if (seenA[x] && seenB[x]) {
                    common++;
                }
            }

            ans[i] = common;
        }

        return ans;
    }
};
