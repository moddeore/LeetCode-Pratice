class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        string half = "";
        char mid = '\0';

        for (int i = 0; i < 26; i++) {
            half += string(freq[i] / 2, 'a' + i);

            if (freq[i] % 2 == 1) {
                mid = 'a' + i;
            }
        }

        string rev = half;
        reverse(rev.begin(), rev.end());

        if (mid != '\0') {
            return half + mid + rev;
        }

        return half + rev;
    }
};