
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> prefixes;

        for (int x : arr1) {
            while (x > 0) {
                prefixes.insert(x);
                x /= 10;
            }
        }

        int ans = 0;

        for (int x : arr2) {
            while (x > 0) {
                if (prefixes.count(x)) {
                    int len = to_string(x).length();
                    ans = max(ans, len);
                }
                x /= 10;
            }
        }

        return ans;
    }
};
