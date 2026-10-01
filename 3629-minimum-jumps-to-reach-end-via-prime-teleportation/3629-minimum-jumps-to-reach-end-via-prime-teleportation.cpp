class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();

        if (n == 1)
            return 0;

        int mx = *max_element(nums.begin(), nums.end());

        // Smallest Prime Factor
        vector<int> spf(mx + 1);

        for (int i = 0; i <= mx; i++)
            spf[i] = i;

        for (int i = 2; i * i <= mx; i++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= mx; j += i) {
                    if (spf[j] == j)
                        spf[j] = i;
                }
            }
        }

        // prime -> indices whose value is divisible by prime
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            while (x > 1) {
                int p = spf[x];

                mp[p].push_back(i);

                // Remove duplicate factors
                while (x % p == 0)
                    x /= p;
            }
        }

        // BFS
        queue<int> q;
        vector<int> dist(n, -1);

        q.push(0);
        dist[0] = 0;

        // We only use each prime teleport once
        unordered_set<int> used;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            int d = dist[i];

            if (i == n - 1)
                return d;

            // Move to i - 1
            if (i > 0 && dist[i - 1] == -1) {
                dist[i - 1] = d + 1;
                q.push(i - 1);
            }

            // Move to i + 1
            if (i + 1 < n && dist[i + 1] == -1) {
                dist[i + 1] = d + 1;
                q.push(i + 1);
            }

            // Teleportation
            int p = nums[i];

            // nums[i] must itself be prime
            if (p > 1 && spf[p] == p && !used.count(p)) {

                used.insert(p);

                // All indices whose value is divisible by p
                for (int j : mp[p]) {
                    if (dist[j] == -1) {
                        dist[j] = d + 1;
                        q.push(j);
                    }
                }

                // Never need this list again
                mp[p].clear();
            }
        }

        return -1;
    }
};