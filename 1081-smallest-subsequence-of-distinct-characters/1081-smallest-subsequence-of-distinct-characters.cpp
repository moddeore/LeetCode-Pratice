class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(26, 0);
        vector<bool> used(26, false);

        // Store last occurrence of each character
        for (int i = 0; i < s.length(); i++) {
            last[s[i] - 'a'] = i;
        }

        string st;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            int x = c - 'a';

            // Skip if character is already in the result
            if (used[x])
                continue;

            // Remove larger characters if they appear again later
            while (!st.empty() &&
                   st.back() > c &&
                   last[st.back() - 'a'] > i) {

                used[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            used[x] = true;
        }

        return st;
    }
};