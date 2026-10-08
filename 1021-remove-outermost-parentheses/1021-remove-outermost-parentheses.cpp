class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int depth = 0;

        for (char c : s) {
            if (c == '(') {
                // Add '(' only if it is not the outermost one
                if (depth > 0) {
                    ans += c;
                }

                depth++;
            }
            else {
                depth--;

                // Add ')' only if it is not the outermost one
                if (depth > 0) {
                    ans += c;
                }
            }
        }

        return ans;
    }
};