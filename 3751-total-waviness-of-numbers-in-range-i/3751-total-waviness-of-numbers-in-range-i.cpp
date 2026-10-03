class Solution {
public:
    int getWaviness(int n) {
        string s = to_string(n);

        if (s.length() < 3)
            return 0;

        int count = 0;

        for (int i = 1; i < s.length() - 1; i++) {
            int left = s[i - 1] - '0';
            int curr = s[i] - '0';
            int right = s[i + 1] - '0';

            // Peak
            if (curr > left && curr > right)
                count++;

            // Valley
            else if (curr < left && curr < right)
                count++;
        }

        return count;
    }

    int totalWaviness(int num1, int num2) {
        int ans = 0;

        for (int n = num1; n <= num2; n++) {
            ans += getWaviness(n);
        }

        return ans;
    }
};