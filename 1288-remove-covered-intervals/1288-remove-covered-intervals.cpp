class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0])
                return a[1] > b[1];   // larger right first
            return a[0] < b[0];       // smaller left first
        });

        int maxRight = 0;
        int remaining = 0;

        for (auto &interval : intervals) {
            int left = interval[0];
            int right = interval[1];

            if (right > maxRight) {
                // Not covered
                remaining++;
                maxRight = right;
            }
            // Otherwise, it is covered
        }

        return remaining;
    }
};